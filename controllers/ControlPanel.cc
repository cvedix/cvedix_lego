#include "ControlPanel.h"

using json = nlohmann::json;
bool init_flag = false;
namespace
{
    std::atomic<bool> g_pipelineRunning{false};
    std::thread g_pipelineThread;
}

// CVEDIX_SET_LOG_LEVEL(cvedix_utils::cvedix_log_level::INFO);
// CVEDIX_LOGGER_INIT();

void ControlPanel::runPipeline(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback)
{
    if (g_pipelineThread.joinable())
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k409Conflict);
        resp->setBody("Pipeline thread still cleaning up");
        callback(resp);
        return;
    }
    if (g_pipelineRunning.load())
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setStatusCode(k409Conflict);
        resp->setBody("Pipeline already running");
        callback(resp);
        return;
    }
    json jsonData = json::parse(req->body());
    std::ofstream file("../JSON/lego_config.json");
    if (!file.is_open())
    {
        std::cerr << "Cannot open file\n";
    }
    file << req->body();
    file.close();

    json resp;
    resp["status"] = "ok";
    auto httpResp = HttpResponse::newHttpResponse();
    httpResp->setBody(resp.dump());
    callback(httpResp);
    g_pipelineThread = std::thread([jsonData]()
                                   {
        try
        {
            if(!init_flag)
            {
                CVEDIX_SET_LOG_LEVEL(cvedix_utils::cvedix_log_level::INFO);
                CVEDIX_LOGGER_INIT();
                init_flag = true;
            }
            MakeNode makeNode;
            makeNode.NodeRegister(const_cast<json &>(jsonData));
            makeNode.MatchingPipeline();
            g_pipelineRunning = true;
            makeNode.StartPipeline();
            while (g_pipelineRunning)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(50));
            }
            makeNode.StopPipeline();
        }
        catch (const std::exception &e)
        {
            g_pipelineRunning = false;
            std::cerr << "[ERROR] Pipeline exception: " << e.what() << std::endl;
        } });
}

void ControlPanel::stopPipeline(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback)
{
    if (!g_pipelineRunning)
    {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody(R"({"status":"not running"})");
        callback(resp);
        return;
    }

    g_pipelineRunning = false;
    if (g_pipelineThread.joinable())
    {
        g_pipelineThread.join();
    }
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(R"({"status":"stopping"})");
    callback(resp);
}
