#pragma once

// ---- Behavior analysis nodes (lightweight kept by default) ----
#include "cvedix/nodes/ba/cvedix_ba_crossline_node.h"
#include "cvedix/nodes/ba/cvedix_ba_jam_node.h"
#include "cvedix/nodes/ba/cvedix_ba_stop_node.h"

// Broker/messaging nodes removed from default aggregator to reduce build surface
// Re-enable any of these if you depend on broker/messaging features.
// #include "cvedix/nodes/broker/cereal_archive/cvedix_objects_cereal_archive.h"
// #include "cvedix/nodes/broker/cvedix_ba_socket_broker_node.h"
// #include "cvedix/nodes/broker/cvedix_embeddings_properties_socket_broker_node.h"
// #include "cvedix/nodes/broker/cvedix_embeddings_socket_broker_node.h"
// #include "cvedix/nodes/broker/cvedix_expr_socket_broker_node.h"
#include "cvedix/nodes/broker/cvedix_json_console_broker_node.h"
// #include "cvedix/nodes/broker/cvedix_json_enhanced_console_broker_node.h"
#include "cvedix/nodes/broker/cvedix_json_kafka_broker_node.h"
#include "cvedix/nodes/broker/cvedix_json_mqtt_broker_node.h"
#include "cvedix/nodes/broker/cvedix_msg_broker_node.h"
// #include "cvedix/nodes/broker/cvedix_plate_socket_broker_node.h"
// #include "cvedix/nodes/broker/cvedix_xml_file_broker_node.h"
// #include "cvedix/nodes/broker/cvedix_xml_socket_broker_node.h"
// #include "cvedix/nodes/broker/kafka_utils/KafkaProducer.h"

// Core/common headers kept (useful across many controllers)
#include "cvedix/nodes/common/cvedix_node.h"
#include "cvedix/nodes/common/cvedix_src_node.h"
#include "cvedix/nodes/common/cvedix_des_node.h"
#include "cvedix/nodes/common/cvedix_meta_hookable.h"
#include "cvedix/nodes/common/cvedix_meta_publisher.h"
#include "cvedix/nodes/common/cvedix_meta_subscriber.h"
#include "cvedix/nodes/common/cvedix_stream_info_hookable.h"
#include "cvedix/nodes/common/cvedix_stream_status_hookable.h"
#include "cvedix/nodes/common/frame_utils.h"

// Des/outputs: keep the common ones used by controllers
#include "cvedix/nodes/des/cvedix_rtmp_des_node.h"
#include "cvedix/nodes/des/cvedix_screen_des_node.h"
#include "cvedix/nodes/des/cvedix_app_des_node.h"
#include "cvedix/nodes/des/cvedix_fake_des_node.h"
#include "cvedix/nodes/des/cvedix_file_des_node.h"
#include "cvedix/nodes/des/cvedix_image_des_node.h"
#include "cvedix/nodes/des/cvedix_rtsp_des_node.h"

// FFIO nodes (commented out to slim)
#include "cvedix/nodes/ffio/cvedix_ff_des_node.h"
#include "cvedix/nodes/ffio/cvedix_ff_src_node.h"
#include "cvedix/nodes/ffio/ff_common.h"
#include "cvedix/nodes/ffio/ff_des.h"
#include "cvedix/nodes/ffio/ff_src.h"

// Infers: keep only the most commonly used example infer node
#include "cvedix/nodes/infers/base/cvedix_infer_node.h"
#include "cvedix/nodes/infers/base/cvedix_primary_infer_node.h"
#include "cvedix/nodes/infers/base/cvedix_secondary_infer_node.h"
#include "cvedix/nodes/infers/cvedix_classifier_node.h"
#include "cvedix/nodes/infers/cvedix_enet_seg_node.h"
#include "cvedix/nodes/infers/cvedix_face_swap_node.h"
#include "cvedix/nodes/infers/cvedix_feature_encoder_node.h"
#include "cvedix/nodes/infers/cvedix_lane_detector_node.h"
#include "cvedix/nodes/infers/cvedix_mask_rcnn_detector_node.h"
#include "cvedix/nodes/infers/cvedix_mllm_analyser_node.h"
#include "cvedix/nodes/infers/cvedix_openpose_detector_node.h"
#include "cvedix/nodes/infers/cvedix_ppocr_text_detector_node.h"
#include "cvedix/nodes/infers/cvedix_restoration_node.h"
// #include "cvedix/nodes/infers/cvedix_rknn_face_detector_node.h"
// #include "cvedix/nodes/infers/cvedix_rknn_yolov8_detector_node.h"
#include "cvedix/nodes/infers/cvedix_sface_feature_encoder_node.h"
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
#include "cvedix/nodes/infers/cvedix_yunet_face_detector_node.h"

// Middle-tier nodes (keep commented to slim)
#include "cvedix/nodes/mid/cvedix_custom_data_transform_node.h"
#include "cvedix/nodes/mid/cvedix_message_broker_node.h"
#include "cvedix/nodes/mid/cvedix_placeholder_node.h"
#include "cvedix/nodes/mid/cvedix_skip_node.h"
#include "cvedix/nodes/mid/cvedix_split_node.h"
#include "cvedix/nodes/mid/cvedix_sync_node.h"

// OSD nodes are visual/debug helpers — comment out to reduce includes
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

// Proc nodes (commented)
#include "cvedix/nodes/proc/cvedix_expr_check_node.h"
#include "cvedix/nodes/proc/cvedix_frame_fusion_node.h"

// Keep a small record API set (commonly used)
#include "cvedix/nodes/record/cvedix_record_node.h"
#include "cvedix/nodes/record/cvedix_image_record_task.h"
#include "cvedix/nodes/record/cvedix_record_status_hookable.h"
#include "cvedix/nodes/record/cvedix_record_task.h"
#include "cvedix/nodes/record/cvedix_video_record_task.h"

// Keep tracking helpers
#include "cvedix/nodes/track/cvedix_sort_track_node.h"
#include "cvedix/nodes/track/cvedix_dsort_track_node.h"
#include "cvedix/nodes/track/cvedix_track_node.h"

// Keep source node includes most commonly used by controllers
#include "cvedix/nodes/src/cvedix_file_src_node.h"
#include "cvedix/nodes/src/cvedix_rtsp_src_node.h"
#include "cvedix/nodes/src/cvedix_app_src_node.h"
#include "cvedix/nodes/src/cvedix_image_src_node.h"
#include "cvedix/nodes/src/cvedix_rtmp_src_node.h"
#include "cvedix/nodes/src/cvedix_udp_src_node.h"
