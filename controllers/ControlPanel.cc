#include "ControlPanel.h"
#include <filesystem>

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


        std::string yolo_weights = "../Model/yolov3-tiny-2022-0721_best.weights";
        std::string yolo_config = "../Model/yolov3-tiny-2022-0721.cfg";
        std::string yolo_classes = "../Model/yolov3_tiny_5classes.txt";


        auto face_detector = std::make_shared<cvedix_nodes::cvedix_yunet_face_detector_node>(
            "face_detector",
            "../Model/model.onnx",
            0.7,  // score_threshold
            0.5,  // nms_threshold
            50    // top_k
        );

        auto tracker = std::make_shared<cvedix_nodes::cvedix_sort_track_node>("sort_tracker");

        auto osd = std::make_shared<cvedix_nodes::cvedix_face_osd_node_v2>("osd");

        auto screen_des_0 = std::make_shared<cvedix_nodes::cvedix_screen_des_node>(
        "screen_des_0",
        0,
        true  // Enable OSD
        );



        // face_detector->attach_to({file});
        // tracker->attach_to({face_detector});
        osd->attach_to({file});
        rtmp->attach_to({file});
        screen_des_0->attach_to({osd});

        file->start();


        cvedix_utils::cvedix_analysis_board board({file});
        board.display(1, false);


        file->detach_recursively();
    }
    catch (const std::exception &e) {
        std::cerr << "[ERROR] Pipeline exception: " << e.what() << std::endl;
    } })
        .detach();
}
