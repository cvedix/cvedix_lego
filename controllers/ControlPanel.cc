#include "ControlPanel.h"

using json = nlohmann::json;

void ControlPanel::runPipeline(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback)
{
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

    std::thread([jsonData]()
                {
    try {
        CVEDIX_SET_LOG_LEVEL(cvedix_utils::cvedix_log_level::INFO);
        CVEDIX_LOGGER_INIT();
        MakeNode makeNode;  
        makeNode.NodeRegister(const_cast<json&>(jsonData));
        makeNode.StartPipeline();
    while (1)
    {
            std::this_thread::sleep_for(std::chrono::microseconds(33));
    }
    makeNode.StopPipeline();
    }

    
    catch (const std::exception &e) {
        std::cerr << "[ERROR] Pipeline exception: " << e.what() << std::endl;
    } })
        .detach();
}
