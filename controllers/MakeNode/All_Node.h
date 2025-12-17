#pragma once

#include <memory>
//----------------------------------------------------------------------------------------------------------------
/*
                                _____  _____ _   _______  _____  _____
                                /  ___||  _  | | | | ___ \/  __ \|  ___|
                                \ `--. | | | | | | | |_/ /| /  \/| |__
                                `--. \ | | | | | | |    / | |    |  __|
                                /\__/ /\ \_/ / |_| | |\ \ | \__/\| |___
                                \____/  \___/ \___/\_| \_| \____/\____/
*/
#include "cvedix/nodes/src/cvedix_file_src_node.h"
#include "cvedix/nodes/src/cvedix_rtsp_src_node.h"
#include "cvedix/nodes/src/cvedix_app_src_node.h"
#include "cvedix/nodes/src/cvedix_image_src_node.h"
#include "cvedix/nodes/src/cvedix_rtmp_src_node.h"
#include "cvedix/nodes/src/cvedix_udp_src_node.h"
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
/*
                                ______ _____ _____ _________________
                                | ___ \  ___/  __ \  _  | ___ \  _  \
                                | |_/ / |__ | /  \/ | | | |_/ / | | |
                                |    /|  __|| |   | | | |    /| | | |
                                | |\ \| |___| \__/\ \_/ / |\ \| |/ /
                                \_| \_\____/ \____/\___/\_| \_|___/
*/

#include "cvedix/nodes/record/cvedix_record_node.h"
#include "cvedix/nodes/record/cvedix_image_record_task.h"
#include "cvedix/nodes/record/cvedix_record_status_hookable.h"
#include "cvedix/nodes/record/cvedix_record_task.h"
#include "cvedix/nodes/record/cvedix_video_record_task.h"
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
/*
                                        ______ _____ _____
                                        |  _  \  ___/  ___|
                                        | | | | |__ \ `--.
                                        | | | |  __| `--. \
                                        | |/ /| |___/\__/ /
                                        |___/ \____/\____/
*/
#include "cvedix/nodes/des/cvedix_rtmp_des_node.h"
#include "cvedix/nodes/des/cvedix_screen_des_node.h"
#include "cvedix/nodes/des/cvedix_app_des_node.h"
#include "cvedix/nodes/des/cvedix_fake_des_node.h"
#include "cvedix/nodes/des/cvedix_file_des_node.h"
#include "cvedix/nodes/des/cvedix_image_des_node.h"
#include "cvedix/nodes/des/cvedix_rtsp_des_node.h"
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
/*                                          ____
                                            |  _ \   /\
                                            | |_) | /  \
                                            |  _ < / /\ \
                                            | |_) / ____ \
                                            |____/_/    \_\
*/

#include "cvedix/nodes/ba/cvedix_ba_crossline_node.h"
#include "cvedix/nodes/ba/cvedix_ba_jam_node.h"
#include "cvedix/nodes/ba/cvedix_ba_stop_node.h"
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
/*
                                    ____________ _____ _   __ ___________
                                    | ___ \ ___ \  _  | | / /|  ___| ___ \
                                    | |_/ / |_/ / | | | |/ / | |__ | |_/ /
                                    | ___ \    /| | | |    \ |  __||    /
                                    | |_/ / |\ \\ \_/ / |\  \| |___| |\ \
                                    \____/\_| \_|\___/\_| \_/\____/\_| \_|
*/
#include "cvedix/nodes/broker/cereal_archive/cvedix_objects_cereal_archive.h"
#include "cvedix/nodes/broker/cvedix_ba_socket_broker_node.h"
#include "cvedix/nodes/broker/cvedix_embeddings_properties_socket_broker_node.h"
#include "cvedix/nodes/broker/cvedix_embeddings_socket_broker_node.h"
#include "cvedix/nodes/broker/cvedix_expr_socket_broker_node.h"
#include "cvedix/nodes/broker/cvedix_json_console_broker_node.h"
#include "cvedix/nodes/broker/cvedix_json_enhanced_console_broker_node.h"
#include "cvedix/nodes/broker/cvedix_json_kafka_broker_node.h"
#include "cvedix/nodes/broker/cvedix_json_mqtt_broker_node.h"
#include "cvedix/nodes/broker/cvedix_msg_broker_node.h"
#include "cvedix/nodes/broker/cvedix_plate_socket_broker_node.h"
#include "cvedix/nodes/broker/cvedix_xml_file_broker_node.h"
#include "cvedix/nodes/broker/cvedix_xml_socket_broker_node.h"
#include "cvedix/nodes/broker/kafka_utils/KafkaProducer.h"
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
/*
                                      _____ ____  __  __ __  __  ____  _   _
                                     / ____/ __ \|  \/  |  \/  |/ __ \| \ | |
                                    | |   | |  | | \  / | \  / | |  | |  \| |
                                    | |   | |  | | |\/| | |\/| | |  | | . ` |
                                    | |___| |__| | |  | | |  | | |__| | |\  |
                                     \_____\____/|_|  |_|_|  |_|\____/|_| \_|
*/
#include "cvedix/nodes/common/cvedix_node.h"
#include "cvedix/nodes/common/cvedix_src_node.h"
#include "cvedix/nodes/common/cvedix_des_node.h"
#include "cvedix/nodes/common/cvedix_meta_hookable.h"
#include "cvedix/nodes/common/cvedix_meta_publisher.h"
#include "cvedix/nodes/common/cvedix_meta_subscriber.h"
#include "cvedix/nodes/common/cvedix_stream_info_hookable.h"
#include "cvedix/nodes/common/cvedix_stream_status_hookable.h"
#include "cvedix/nodes/common/frame_utils.h"
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
/*
                                         ______ ______ _____ ____
                                        |  ____|  ____|_   _/ __ \
                                        | |__  | |__    | || |  | |
                                        |  __| |  __|   | || |  | |
                                        | |    | |     _| || |__| |
                                        |_|    |_|    |_____\____/
*/

#include "cvedix/nodes/ffio/cvedix_ff_des_node.h"
#include "cvedix/nodes/ffio/cvedix_ff_src_node.h"
#include "cvedix/nodes/ffio/ff_common.h"
#include "cvedix/nodes/ffio/ff_des.h"
#include "cvedix/nodes/ffio/ff_src.h"
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
/*
                                     _____ _   _ ______ ______ _____   _____
                                    |_   _| \ | |  ____|  ____|  __ \/ ____|
                                      | | |  \| | |__  | |__  | |__) | (___
                                      | | | . ` |  __| |  __| |  _  / \___ \
                                      | |_| |\  | |    | |____| | \ \ ____) |
                                    |_____|_| \_|_|    |______|_|  \_\_____/

*/
#include "cvedix/nodes/infers/base/cvedix_infer_node.h"
#include "cvedix/nodes/infers/base/cvedix_primary_infer_node.h"
#include "cvedix/nodes/infers/base/cvedix_secondary_infer_node.h"
#include "cvedix/nodes/infers/cvedix_classifier_node.h"
#include "cvedix/nodes/infers/cvedix_enet_seg_node.h"
#include "cvedix/nodes/infers/cvedix_face_swap_node.h"
#include "cvedix/nodes/infers/cvedix_face_yunet_int8_face_detection_mode.h"
#include "cvedix/nodes/infers/cvedix_feature_encoder_node.h"
#include "cvedix/nodes/infers/cvedix_insight_face_recognition_node.h"
#include "cvedix/nodes/infers/cvedix_lane_detector_node.h"
#include "cvedix/nodes/infers/cvedix_mask_rcnn_detector_node.h"
#include "cvedix/nodes/infers/cvedix_mllm_analyser_node.h"
#include "cvedix/nodes/infers/cvedix_openpose_detector_node.h"
#include "cvedix/nodes/infers/cvedix_ppocr_text_detector_node.h"
#include "cvedix/nodes/infers/cvedix_restoration_node.h"
// #include "cvedix/nodes/infers/cvedix_rknn_face_detector_node.h"
// #include "cvedix/nodes/infers/cvedix_rknn_yolov8_detector_node.h"
// #include "cvedix/nodes/infers/cvedixrknn_yolov11_detector_node.h"
#include "cvedix/nodes/infers/cvedix_sface_feature_encoder_node.h"
#include "cvedix/nodes/infers/cvedix_trt_insight_face_recognition_node.h"
#include "cvedix/nodes/infers/cvedix_trt_vehicle_color_classifier.h"
#include "cvedix/nodes/infers/cvedix_trt_vehicle_detector.h"
#include "cvedix/nodes/infers/cvedix_trt_vehicle_feature_encoder.h"
#include "cvedix/nodes/infers/cvedix_trt_vehicle_plate_detector.h"
#include "cvedix/nodes/infers/cvedix_trt_vehicle_plate_detector_v2.h"
#include "cvedix/nodes/infers/cvedix_trt_vehicle_scanner.h"
#include "cvedix/nodes/infers/cvedix_trt_vehicle_type_classifier.h"
#include "cvedix/nodes/infers/cvedix_trt_yolov8_classifier.h"
#include "cvedix/nodes/infers/cvedix_trt_yolov8_detector.h"
#include "cvedix/nodes/infers/cvedix_trt_yolov8_pose_detector.h"
#include "cvedix/nodes/infers/cvedix_trt_yolov8_seg_detector.h"
#include "cvedix/nodes/infers/cvedix_yolo_detector_node.h"
#include "cvedix/nodes/infers/cvedix_yolov11_detector_node.h"
#include "cvedix/nodes/infers/cvedix_yunet_face_detector_node.h"
// #include "cvedix/nodes/infers/rknn_yolov11.h"
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
/*
                                                                ___  ______________
                                                                |  \/  |_   _|  _  \
                                                                | .  . | | | | | | |
                                                                | |\/| | | | | | | |
                                                                | |  | |_| |_| |/ /
                                                                \_|  |_/\___/|___/

*/
// Middle-tier nodes (keep commented to slim)
#include "cvedix/nodes/mid/cvedix_custom_data_transform_node.h"
#include "cvedix/nodes/mid/cvedix_message_broker_node.h"
#include "cvedix/nodes/mid/cvedix_placeholder_node.h"
#include "cvedix/nodes/mid/cvedix_skip_node.h"
#include "cvedix/nodes/mid/cvedix_split_node.h"
#include "cvedix/nodes/mid/cvedix_sync_node.h"
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
/*
                                                _____ ___________
                                                |  _  /  ___|  _  \
                                                | | | \ `--.| | | |
                                                | | | |`--. \ | | |
                                                \ \_/ /\__/ / |/ /
                                                \___/\____/|___/
*/
#include "cvedix/nodes/osd/cvedix_ba_crossline_osd_node.h"
#include "cvedix/nodes/osd/cvedix_ba_jam_osd_node.h"
#include "cvedix/nodes/osd/cvedix_ba_stop_osd_node.h"
#include "cvedix/nodes/osd/cvedix_cluster_node.h"
#include "cvedix/nodes/osd/cvedix_expr_osd_node.h"
#include "cvedix/nodes/osd/cvedix_face_osd_node.h"
#include "cvedix/nodes/osd/cvedix_face_osd_node_v2.h"
#include "cvedix/nodes/osd/cvedix_lane_osd_node.h"
#include "cvedix/nodes/osd/cvedix_mllm_osd_node.h"
#include "cvedix/nodes/osd/cvedix_osd_node.h"
#include "cvedix/nodes/osd/cvedix_osd_node_v2.h"
#include "cvedix/nodes/osd/cvedix_osd_node_v3.h"
#include "cvedix/nodes/osd/cvedix_plate_osd_node.h"
#include "cvedix/nodes/osd/cvedix_pose_osd_node.h"
#include "cvedix/nodes/osd/cvedix_seg_osd_node.h"
#include "cvedix/nodes/osd/cvedix_text_osd_node.h"
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
/*
                                             _____  _____   ____   _____
                                            |  __ \|  __ \ / __ \ / ____|
                                            | |__) | |__) | |  | | |
                                            |  ___/|  _  /| |  | | |
                                            | |    | | \ \| |__| | |____
                                            |_|    |_|  \_\\____/ \_____|
*/
// Proc nodes (commented)
#include "cvedix/nodes/proc/cvedix_expr_check_node.h"
#include "cvedix/nodes/proc/cvedix_frame_fusion_node.h"
//----------------------------------------------------------------------------------------------------------------
//----------------------------------------------------------------------------------------------------------------
/*
                                      _______ _____            _____ _  __
                                     |__   __|  __ \     /\   / ____| |/ /
                                        | |  | |__) |   /  \ | |    | ' /
                                        | |  |  _  /   / /\ \| |    |  <
                                        | |  | | \ \  / ____ \ |____| . \
                                        |_|  |_|  \_\/_/    \_\_____|_|\_\
*/
// Keep tracking helpers
#include "cvedix/nodes/track/cvedix_sort_track_node.h"
#include "cvedix/nodes/track/cvedix_dsort_track_node.h"
//----------------------------------------------------------------------------------------------------------------
