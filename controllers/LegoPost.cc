#include "LegoPost.h"

using json = nlohmann::json;


static NodeRegister rtsp(
    "cvedix_rtsp_src_node",
    [](const json& cfg) {
        return std::make_shared<cvedix_nodes::cvedix_rtsp_src_node>(
            cfg["node_name_rtsp"].get<std::string>(),   // ✔ đúng key
            cfg["channel_index"].get<int>(),
            cfg["rtsp_url"].get<std::string>(),
            cfg["resize_ratio"].get<float>(),
            cfg["gst_decoder_name"].get<std::string>(),
            cfg["skip_interval"].get<int>(),
            cfg["expected_codec"].get<std::string>()
        );
    }
);


void LegoPost::runPipeline(
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

        // auto rtsp = std::make_shared<cvedix_nodes::cvedix_rtsp_src_node>(
        //     jsonData["node_name_rtsp"].get<std::string>(),
        //     jsonData["channel_index"].get<int>(),
        //     jsonData["rtsp_url"].get<std::string>(),
        //     jsonData["resize_ratio"].get<float>(),
        //     jsonData["gst_decoder_name"].get<std::string>(),
        //     jsonData["skip_interval"].get<int>(),
        //     jsonData["expected_codec"].get<std::string>()
        // );
        auto rtsp = NodeFactory::Instance().CreateNode(
            "cvedix_rtsp_src_node",
            jsonData
        );


        auto rtmp = std::make_shared<cvedix_nodes::cvedix_rtmp_des_node>(
            jsonData["node_name_rtmp"].get<std::string>(),
            jsonData["channel_index"].get<int>(),
            jsonData["rtmp_url"].get<std::string>(),
            cvedix_objects::cvedix_size
            {
                jsonData["resolution_width"].get<int>(),
                jsonData["resolution_height"].get<int>()
            },
            jsonData["bitrate"].get<int>(),
            jsonData["osd"].get<bool>(),
            jsonData["gst_encoder_name"].get<std::string>()
        );


        rtmp->attach_to({rtsp});
        rtsp->start();


        while (true) {
            char c = std::cin.get();
            if (c == 'q') {
                std::cout << "Quitting pipeline..." << std::endl;
                break;
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }

        rtsp->detach_recursively();
    }
    catch (const std::exception &e) {
        std::cerr << "[ERROR] Pipeline exception: " << e.what() << std::endl;
    } })
        .detach();
}
