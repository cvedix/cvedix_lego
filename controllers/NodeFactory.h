#pragma once
#include <nlohmann/json.hpp>
#include "All_Node.h"
#include <vector>
#include "cvedix/utils/analysis_board/cvedix_analysis_board.h"
#include <memory>

using json = nlohmann::json;
class MakeNode
{
public:
    //----------------------------------------------------------------------------------------------------------------
    /*
                                _____  _____ _   _______  _____  _____
                                /  ___||  _  | | | | ___ \/  __ \|  ___|
                                \ `--. | | | | | | | |_/ /| /  \/| |__
                                `--. \ | | | | | | |    / | |    |  __|
                                /\__/ /\ \_/ / |_| | |\ \ | \__/\| |___
                                \____/  \___/ \___/\_| \_| \____/\____/
    */
    std::shared_ptr<cvedix_nodes::cvedix_app_src_node> app_src;
    std::shared_ptr<cvedix_nodes::cvedix_file_src_node> file_src;
    std::shared_ptr<cvedix_nodes::cvedix_rtsp_src_node> rtsp_src;
    std::shared_ptr<cvedix_nodes::cvedix_image_src_node> image_src;
    //std::shared_ptr<cvedix_nodes::cvedix_ff_src_node> ff_src;
    //std::shared_ptr<cvedix_nodes::cvedix_rtmp_src_node> rtmp_src;
    std::shared_ptr<cvedix_nodes::cvedix_udp_src_node> udp_src;

    /*
                                ______ _____ _____ _________________
                                | ___ \  ___/  __ \  _  | ___ \  _  \
                                | |_/ / |__ | /  \/ | | | |_/ / | | |
                                |    /|  __|| |   | | | |    /| | | |
                                | |\ \| |___| \__/\ \_/ / |\ \| |/ /
                                \_| \_\____/ \____/\___/\_| \_|___/
    */

    std::shared_ptr<cvedix_nodes::cvedix_record_node> record;

    /*
                                ______ _____ _____ _____ _____ _____
                                |  _  \  ___|_   _|  ___/  __ \_   _|
                                | | | | |__   | | | |__ | /  \/ | |
                                | | | |  __|  | | |  __|| |     | |
                                | |/ /| |___  | | | |___| \__/\ | |
                                |___/ \____/  \_/ \____/ \____/ \_/
    */

    // std::shared_ptr<cvedix_nodes::cvedix_classifier_node> classifier;
    std::shared_ptr<cvedix_nodes::cvedix_dsort_track_node> dsort_track;
    // std::shared_ptr<cvedix_nodes::cvedix_enet_seg_node> enet_seg;
    std::shared_ptr<cvedix_nodes::cvedix_face_swap_node> face_swap;
    // std::shared_ptr<cvedix_nodes::cvedix_feature_encoder_node> feature_encoder;
    std::shared_ptr<cvedix_nodes::cvedix_lane_detector_node> lane_detector;
    // std::shared_ptr<cvedix_nodes::cvedix_mask_rcnn_detector_node> mask_rcnn_detector;
    // std::shared_ptr<cvedix_nodes::cvedix_mllm_analyser_node> mllm_analyser;
    std::shared_ptr<cvedix_nodes::cvedix_openpose_detector_node> openpose_detector;
    // std::shared_ptr<cvedix_nodes::cvedix_ppocr_text_detector_node> ppocr_text_detector;
    std::shared_ptr<cvedix_nodes::cvedix_restoration_node> restoration;
    // std::shared_ptr<cvedix_nodes::cvedix_rknn_face_detector_node> rknn_face_detector;
    // std::shared_ptr<cvedix_nodes::cvedix_rknn_yolov8_detector_node> rknn_yolov8_detector;
    std::shared_ptr<cvedix_nodes::cvedix_sface_feature_encoder_node> sface_feature_encoder;
    std::shared_ptr<cvedix_nodes::cvedix_sort_track_node> sort_track;
    // std::shared_ptr<cvedix_nodes::cvedix_track_node> track;
    // std::shared_ptr<cvedix_nodes::cvedix_trt_vehicle_color_classifier> trt_vehicle_color_classifier;
    // std::shared_ptr<cvedix_nodes::cvedix_trt_vehicle_detector> trt_vehicle_detector;
    // std::shared_ptr<cvedix_nodes::cvedix_trt_vehicle_feature_encoder> trt_vehicle_feature_encoder;
    // std::shared_ptr<cvedix_nodes::cvedix_trt_vehicle_plate_detector> trt_vehicle_plate_detector;
    // std::shared_ptr<cvedix_nodes::cvedix_trt_vehicle_plate_detector_v2> trt_vehicle_plate_detector_v2;
    // std::shared_ptr<cvedix_nodes::cvedix_trt_vehicle_scanner> trt_vehicle_scanner;
    // std::shared_ptr<cvedix_nodes::cvedix_trt_vehicle_type_classifier> trt_vehicle_type_classifier;
    // std::shared_ptr<cvedix_nodes::cvedix_trt_yolov8_classifier> trt_yolov8_classifier;
    // std::shared_ptr<cvedix_nodes::cvedix_trt_yolov8_detector> trt_yolov8_detector;
    // std::shared_ptr<cvedix_nodes::cvedix_trt_yolov8_pose_detector> trt_yolov8_pose_detector;
    // std::shared_ptr<cvedix_nodes::cvedix_trt_yolov8_seg_detector> trt_yolov8_seg_detector;
    std::shared_ptr<cvedix_nodes::cvedix_yolo_detector_node> yolo_detector;
    std::shared_ptr<cvedix_nodes::cvedix_yunet_face_detector_node> yunet_face_detector;
    /*
                                            _____ ___________
                                            |  _  /  ___|  _  \
                                            | | | \ `--.| | | |
                                            | | | |`--. \ | | |
                                            | |/ / /\__/ / |/ /
                                            |___/  \____/|___/
    */

    std::shared_ptr<cvedix_nodes::cvedix_ba_crossline_osd_node> ba_crossline_osd;
    std::shared_ptr<cvedix_nodes::cvedix_ba_jam_osd_node> ba_jam_osd;
    std::shared_ptr<cvedix_nodes::cvedix_ba_stop_osd_node> ba_stop_osd;
    std::shared_ptr<cvedix_nodes::cvedix_expr_osd_node> expr_osd;
    std::shared_ptr<cvedix_nodes::cvedix_face_osd_node> face_osd;
    std::shared_ptr<cvedix_nodes::cvedix_face_osd_node_v2> face_osd_v2;
    std::shared_ptr<cvedix_nodes::cvedix_lane_osd_node> lane_osd;
    // std::shared_ptr<cvedix_nodes::cvedix_mllm_osd_node> mllm_osd;
    std::shared_ptr<cvedix_nodes::cvedix_osd_node> osd;
    std::shared_ptr<cvedix_nodes::cvedix_osd_node_v2> osd_v2;
    std::shared_ptr<cvedix_nodes::cvedix_osd_node_v3> osd_v3;
    std::shared_ptr<cvedix_nodes::cvedix_plate_osd_node> plate_osd;
    std::shared_ptr<cvedix_nodes::cvedix_pose_osd_node> pose_osd;
    std::shared_ptr<cvedix_nodes::cvedix_seg_osd_node> seg_osd;
    std::shared_ptr<cvedix_nodes::cvedix_text_osd_node> text_osd;
    /*
                                    ____________ _____ _   __ ___________
                                    | ___ \ ___ \  _  | | / /|  ___| ___ \
                                    | |_/ / |_/ / | | | |/ / | |__ | |_/ /
                                    | ___ \    /| | | |    \ |  __||    /
                                    | |_/ / |\ \\ \_/ / |\  \| |___| |\ \
                                    \____/\_| \_|\___/\_| \_/\____/\_| \_|
    */

    // std::shared_ptr<cvedix_nodes::cvedix_ba_socket_broker_node> ba_socket_broker;
    // std::shared_ptr<cvedix_nodes::cvedix_embeddings_properties_socket_broker_node> embeddings_properties_socket_broker;
    // std::shared_ptr<cvedix_nodes::cvedix_embeddings_socket_broker_node> embeddings_socket_broker;
    // std::shared_ptr<cvedix_nodes::cvedix_expr_socket_broker_node> expr_socket_broker;
    // std::shared_ptr<cvedix_nodes::cvedix_json_console_broker_node> json_console_broker;
    // std::shared_ptr<cvedix_nodes::cvedix_json_enhanced_console_broker_node> json_enhanced_console_broker;
    // std::shared_ptr<cvedix_nodes::cvedix_json_kafka_broker_node> json_kafka_broker;
    std::shared_ptr<cvedix_nodes::cvedix_json_mqtt_broker_node> json_mqtt_broker;
    // std::shared_ptr<cvedix_nodes::cvedix_msg_broker_node> msg_broker;
    // std::shared_ptr<cvedix_nodes::cvedix_plate_socket_broker_node> plate_socket_broker;
    // std::shared_ptr<cvedix_nodes::cvedix_xml_file_broker_node> xml_file_broker;
    // std::shared_ptr<cvedix_nodes::cvedix_xml_socket_broker_node> xml_socket_broker;
    /*
                                            ___  ______________
                                            |  \/  |_   _|  _  \
                                            | .  . | | | | | | |
                                            | |\/| | | | | | | |
                                            | |  | |_| |_| |/ /
                                            \_|  |_/\___/|___/

    */

    std::shared_ptr<cvedix_nodes::cvedix_cluster_node> cluster;
    std::shared_ptr<cvedix_nodes::cvedix_custom_data_transform_node> custom_data_transform;
    std::shared_ptr<cvedix_nodes::cvedix_expr_check_node> expr_check;
    std::shared_ptr<cvedix_nodes::cvedix_frame_fusion_node> frame_fusion;

    /*
                                            ______ _____ _____
                                            |  _  \  ___/  ___|
                                            | | | | |__ \ `--.
                                            | | | |  __| `--. \
                                            | |/ /| |___/\__/ /
                                            |___/ \____/\____/
    */
    std::shared_ptr<cvedix_nodes::cvedix_app_des_node> app_des;
    std::shared_ptr<cvedix_nodes::cvedix_fake_des_node> fake_des;
    //std::shared_ptr<cvedix_nodes::cvedix_ff_des_node> ff_des;
    std::shared_ptr<cvedix_nodes::cvedix_file_des_node> file_des;
    std::shared_ptr<cvedix_nodes::cvedix_image_des_node> image_des;
    // std::shared_ptr<cvedix_nodes::cvedix_rtsp_des_node> rtsp_des;
    std::shared_ptr<cvedix_nodes::cvedix_rtmp_des_node> rtmp_des;
    std::shared_ptr<cvedix_nodes::cvedix_screen_des_node> screen_des;
    //----------------------------------------------------------------------------------------------------------------



    // Controller Function
    std::vector<std::shared_ptr<cvedix_nodes::cvedix_node>> nodes;
    void MatchingPipeline();
    void NodeRegister(json &jsonData);
    void StartPipeline();
    void StopPipeline();

private:
    int des_node = 0;
    std::string Node;
};
