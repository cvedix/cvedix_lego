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

        auto file = std::make_shared<cvedix_nodes::cvedix_file_src_node>(
            jsonData["nodes"][0]["config"]["node_name"].get<std::string>(),
            jsonData["nodes"][0]["config"]["channel_index"].get<int>(),
            "/home/cvedix/Documents/Template/cvedix_backend/Video/sample.mp4",
            jsonData["nodes"][0]["config"]["resize_ratio"].get<int>(),
            jsonData["nodes"][0]["config"]["cycle"].get<bool>(),
            jsonData["nodes"][0]["config"]["gst_decoder_name"].get<std::string>(),
            jsonData["nodes"][0]["config"]["skip_interval"].get<int>()
        );

        auto rtmp = std::make_shared<cvedix_nodes::cvedix_rtmp_des_node>(
            jsonData["nodes"][1]["config"]["node_name"].get<std::string>(),
            jsonData["nodes"][1]["config"]["channel_index"].get<int>(),
            jsonData["nodes"][1]["config"]["rtmp_url"].get<std::string>(),
            cvedix_objects::cvedix_size
            {
                jsonData["nodes"][1]["config"]["resolution_width"].get<int>(),
                jsonData["nodes"][1]["config"]["resolution_height"].get<int>()
            },
            jsonData["nodes"][1]["config"]["bitrate"].get<int>(),
            jsonData["nodes"][1]["config"]["osd"].get<bool>(),
            jsonData["nodes"][1]["config"]["gst_encoder_name"].get<std::string>()
        );


        auto face_detector = std::make_shared<cvedix_nodes::cvedix_yunet_face_detector_node>(
            jsonData["nodes"][2]["config"]["node_name"].get<std::string>(),
            "../Model/face_detection_yunet_2022mar.onnx"
        );

        auto osd = std::make_shared<cvedix_nodes::cvedix_face_osd_node>(
            jsonData["nodes"][3]["config"]["node_name"].get<std::string>()
        );

        auto screen = std::make_shared<cvedix_nodes::cvedix_screen_des_node>(
            jsonData["nodes"][4]["config"]["node_name"].get<std::string>(),
            jsonData["nodes"][4]["config"]["channel_index"].get<int>(),
            jsonData["nodes"][4]["config"]["osd"].get<bool>()  // Enable OSD
        );



        face_detector->attach_to({file});
        osd->attach_to({face_detector});
        screen->attach_to({osd});
        rtmp->attach_to({osd});


        file->start();

        std::cout << "[INFO] Pipeline started successfully" << std::endl;

        cvedix_utils::cvedix_analysis_board board({file});
        board.display(1, false);

        while(1);

        file->detach_recursively();
    }
    catch (const std::exception &e) {
        std::cerr << "[ERROR] Pipeline exception: " << e.what() << std::endl;
    } })
        .detach();
}
