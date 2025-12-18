#include "ControlPanel.h"

using json = nlohmann::json;

namespace
{
    std::atomic<bool> g_pipelineRunning{false};
    std::atomic<bool> g_pipelineStopping{false};
    std::thread g_pipelineThread;
    std::once_flag g_loggerInitFlag;
}

// CVEDIX_SET_LOG_LEVEL(cvedix_utils::cvedix_log_level::INFO);
// CVEDIX_LOGGER_INIT();

void ControlPanel::runPipeline(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback)
{
    if (g_pipelineRunning.load())
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k409Conflict);
        resp->setBody("Pipeline already running");
        callback(resp);
        return;
    }

    json jsonData = json::parse(req->body());

    g_pipelineRunning.store(true);
    g_pipelineStopping.store(false);

    g_pipelineThread = std::thread([jsonData]()
                                   {
        try
        {
            std::call_once(g_loggerInitFlag, []
                           {
                CVEDIX_SET_LOG_LEVEL(cvedix_utils::cvedix_log_level::INFO);
                CVEDIX_LOGGER_INIT(); });

            MakeNode makeNode;
            makeNode.NodeRegister(const_cast<json &>(jsonData));
            makeNode.MatchingPipeline();
            makeNode.StartPipeline();

            while (g_pipelineRunning.load())
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }

            makeNode.StopPipeline();
        }
        catch (const std::exception &e)
        {
            std::cerr << "[ERROR] Pipeline exception: " << e.what() << std::endl;
        }

        g_pipelineRunning.store(false); });

    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(R"({"status":"started"})");
    callback(resp);
}

void ControlPanel::stopPipeline(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback)
{
    if (!g_pipelineRunning.load())
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody(R"({"status":"not running"})");
        callback(resp);
        return;
    }

    g_pipelineRunning.store(false);

    if (g_pipelineThread.joinable() &&
        std::this_thread::get_id() != g_pipelineThread.get_id())
    {
        g_pipelineThread.join();
    }

    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(R"({"status":"stopped"})");
    callback(resp);
}
