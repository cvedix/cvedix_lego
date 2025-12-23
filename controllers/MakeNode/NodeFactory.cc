#include "NodeFactory.h"

void MakeNode::NodeRegister(json &jsonData)
{
    for (int countNode = 0; countNode < jsonData["nodes"].size(); countNode++)
    {
        Node = jsonData["nodes"][countNode]["type"].get<std::string>();
        std::cout << "[INFO] Creating node: " << Node << std::endl;
        //----------------------------------------------------------------------------------------------------------------
        /*
                            _____  _____ _   _______  _____  _____
                            /  ___||  _  | | | | ___ \/  __ \|  ___|
                            \ `--. | | | | | | | |_/ /| /  \/| |__
                            `--. \ | | | | | | |    / | |    |  __|
                            /\__/ /\ \_/ / |_| | |\ \ | \__/\| |___
                            \____/  \___/ \___/\_| \_| \____/\____/
        */
        if (Node == "cvedix_app_src_node")
        {
            app_src = std::make_shared<cvedix_nodes::cvedix_app_src_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["channel_index"].get<int>());
            nodes.push_back(app_src);
        }
        else if (Node == "cvedix_file_src_node")
        {
            std::cout << "[DEBUG] Creating cvedix_file_src_node" << std::endl;
            file_src = std::make_shared<cvedix_nodes::cvedix_file_src_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["channel_index"].get<int>(),
                "/opt/cvedix/media/" + jsonData["nodes"][countNode]["config"]["video_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["resize_ratio"].get<int>(),
                jsonData["nodes"][countNode]["config"]["cycle"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["gst_decoder_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["skip_interval"].get<int>());
            nodes.push_back(file_src);
        }
        else if (Node == "cvedix_image_src_node")
        {
            auto image_src = std::make_shared<cvedix_nodes::cvedix_image_src_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["channel_index"].get<int>(),
                jsonData["nodes"][countNode]["config"]["port_or_location"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["interval"].get<int>(),
                jsonData["nodes"][countNode]["config"]["resize_ratio"].get<float>(),
                jsonData["nodes"][countNode]["config"]["cycle"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["gst_decoder_name"].get<std::string>());
            nodes.push_back(image_src);
        }
        else if (Node == "cvedix_rtsp_src_node")
        {
            rtsp_src = std::make_shared<cvedix_nodes::cvedix_rtsp_src_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["channel_index"].get<int>(),
                jsonData["nodes"][countNode]["config"]["rtsp_url"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["resize_ratio"].get<float>(),
                jsonData["nodes"][countNode]["config"]["gst_decoder_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["skip_interval"].get<int>(),
                jsonData["nodes"][countNode]["config"]["codec_type"].get<std::string>());
            nodes.push_back(rtsp_src);
        }
        else if (Node == "cvedix_rtmp_src_node")
        {
            auto rtmp_src = std::make_shared<cvedix_nodes::cvedix_rtmp_src_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["channel_index"].get<int>(),
                jsonData["nodes"][countNode]["config"]["rtmp_url"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["resize_ratio"].get<float>(),
                jsonData["nodes"][countNode]["config"]["gst_decoder_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["skip_interval"].get<int>());
            nodes.push_back(rtmp_src);
        }
        else if (Node == "cvedix_udp_src_node")
        {
            auto udp_src = std::make_shared<cvedix_nodes::cvedix_udp_src_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["channel_index"].get<int>(),
                jsonData["nodes"][countNode]["config"]["port"].get<int>(),
                jsonData["nodes"][countNode]["config"]["resize_ratio"].get<int>(),
                jsonData["nodes"][countNode]["config"]["gst_decoder_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["skip_interval"].get<int>());
            nodes.push_back(udp_src);
        }
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

        else if (Node == "cvedix_record_node")
        {
            auto record = std::make_shared<cvedix_nodes::cvedix_record_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["video_save_dir"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["image_save_dir"].get<std::string>(),
                cvedix_objects::cvedix_size{
                    jsonData["nodes"][countNode]["config"]["resolution_width"].get<int>(),
                    jsonData["nodes"][countNode]["config"]["resolution_height"].get<int>()},
                jsonData["nodes"][countNode]["config"]["osd"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["pre_record_video_duration"].get<int>(),
                jsonData["nodes"][countNode]["config"]["record_video_duration"].get<int>(),
                jsonData["nodes"][countNode]["config"]["auto_sub_dir"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["bitrate"].get<int>());
            nodes.push_back(record);
            // record node is a destination node
            des_node++;
        }
        else if (Node == "cvedix_image_record_task")
        {
            // use placeholder node to represent image record task in pipeline
            auto image_record = std::make_shared<cvedix_nodes::cvedix_placeholder_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>());
            nodes.push_back(image_record);
        }
        else if (Node == "cvedix_video_record_task")
        {
            // use placeholder node to represent video record task in pipeline
            auto video_record = std::make_shared<cvedix_nodes::cvedix_placeholder_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>());
            nodes.push_back(video_record);
        }
        else if (Node == "cvedix_record_task")
        {
            // generic record task placeholder
            auto record_task = std::make_shared<cvedix_nodes::cvedix_placeholder_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>());
            nodes.push_back(record_task);
        }
        else if (Node == "cvedix_record_status_hookable")
        {
            // status hookable treated as a passive node placeholder
            auto record_status = std::make_shared<cvedix_nodes::cvedix_placeholder_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>());
            nodes.push_back(record_status);
        }
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

        else if (Node == "cvedix_classifier_node")
        {
            auto classifier = std::make_shared<cvedix_nodes::cvedix_classifier_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["model_path"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["model_config_path"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["labels_path"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["input_width"].get<int>(),
                jsonData["nodes"][countNode]["config"]["input_height"].get<int>(),
                jsonData["nodes"][countNode]["config"]["batch_size"].get<int>(),
                jsonData["nodes"][countNode]["config"]["p_class_ids_applied_to"].get<std::vector<int>>(),
                jsonData["nodes"][countNode]["config"]["min_width_applied_to"].get<int>(),
                jsonData["nodes"][countNode]["config"]["min_height_applied_to"].get<int>(),
                jsonData["nodes"][countNode]["config"]["crop_padding"].get<int>(),
                jsonData["nodes"][countNode]["config"]["need_softmax"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["scale"].get<float>(),
                cv::Scalar(123.675, 116.28, 103.53),
                cv::Scalar(0.229, 0.224, 0.225),
                jsonData["nodes"][countNode]["config"]["swap_rb"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["swap_chn"].get<bool>());
            nodes.push_back(classifier);
        }
        else if (Node == "cvedix_dsort_track_node")
        {
            auto dsort_track = std::make_shared<cvedix_nodes::cvedix_dsort_track_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                static_cast<cvedix_nodes::cvedix_track_for>(jsonData["nodes"][countNode]["config"]["track_for"].get<int>()));
            nodes.push_back(dsort_track);
        }
        else if (Node == "cvedix_enet_seg_node")
        {
            auto enet_seg = std::make_shared<cvedix_nodes::cvedix_enet_seg_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["model_path"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["model_config_path"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["labels_path"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["input_width"].get<int>(),
                jsonData["nodes"][countNode]["config"]["input_height"].get<int>(),
                jsonData["nodes"][countNode]["config"]["batch_size"].get<int>(),
                jsonData["nodes"][countNode]["config"]["class_id_offset"].get<int>(),
                jsonData["nodes"][countNode]["config"]["scale"].get<float>(),
                cv::Scalar(0),
                cv::Scalar(1),
                jsonData["nodes"][countNode]["config"]["swap_rb"].get<bool>());
            nodes.push_back(enet_seg);
        }
        else if (Node == "cvedix_face_swap_node")
        {
            auto face_swap = std::make_shared<cvedix_nodes::cvedix_face_swap_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["yunet_face_detect_model"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["buffalo_l_face_encoding_model"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["emap_file_for_embeddings"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["insightface_swap_model"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["swap_source_image"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["swap_source_face_index"].get<int>(),
                jsonData["nodes"][countNode]["config"]["min_face_w_h"].get<int>(),
                jsonData["nodes"][countNode]["config"]["swap_on_osd"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["act_as_primary_detector"].get<bool>());
            nodes.push_back(face_swap);
        }
        // else if (Node == "cvedix_feature_encoder_node")
        // {
        //     auto feature_encoder = std::make_shared<cvedix_nodes::cvedix_feature_encoder_node>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["model_path"].get<std::string>());
        // }
        else if (Node == "cvedix_lane_detector_node")
        {
            auto lane_detector = std::make_shared<cvedix_nodes::cvedix_lane_detector_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["model_path"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["model_config_path"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["labels_path"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["input_width"].get<int>(),
                jsonData["nodes"][countNode]["config"]["input_height"].get<int>(),
                jsonData["nodes"][countNode]["config"]["batch_size"].get<int>(),
                jsonData["nodes"][countNode]["config"]["class_id_offset"].get<int>(),
                jsonData["nodes"][countNode]["config"]["scale"].get<float>(),
                cv::Scalar(jsonData["nodes"][countNode]["config"]["mean_r"].get<double>(),
                           jsonData["nodes"][countNode]["config"]["mean_g"].get<double>(),
                           jsonData["nodes"][countNode]["config"]["mean_b"].get<double>()),
                cv::Scalar(jsonData["nodes"][countNode]["config"]["std_r"].get<double>(),
                           jsonData["nodes"][countNode]["config"]["std_g"].get<double>(),
                           jsonData["nodes"][countNode]["config"]["std_b"].get<double>()),
                jsonData["nodes"][countNode]["config"]["swap_rb"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["swap_chn"].get<bool>());
            nodes.push_back(lane_detector);
        }
        // else if (Node == "cvedix_mask_rcnn_detector_node")
        // {
        //     auto mask_rcnn_detector = std::make_shared<cvedix_nodes::cvedix_mask_rcnn_detector_node>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["model_path"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["model_config_path"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["labels_path"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["input_width"].get<int>(),
        //         jsonData["nodes"][countNode]["config"]["input_height"].get<int>(),
        //         jsonData["nodes"][countNode]["config"]["batch_size"].get<int>(),
        //         jsonData["nodes"][countNode]["config"]["class_id_offset"].get<int>(),
        //         jsonData["nodes"][countNode]["config"]["score_threshold"].get<float>(),
        //         jsonData["nodes"][countNode]["config"]["scale"].get<float>(),
        //         jsonData["nodes"][countNode]["config"]["mean"].get<cv::Scalar>(),
        //         jsonData["nodes"][countNode]["config"]["std"].get<cv::Scalar>(),
        //         jsonData["nodes"][countNode]["config"]["swap_rb"].get<bool>());
        // }
        // else if (Node == "cvedix_mllm_analyser_node")
        // {
        //     auto mllm_analyser = std::make_shared<cvedix_nodes::cvedix_mllm_analyser_node>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["model_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["prompt"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["api_base_url"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["api_key"].get<std::string>(),
        //         llmlib::LLMBackendType::Ollama);
        // }
        else if (Node == "cvedix_openpose_detector_node")
        {
            auto openpose_detector = std::make_shared<cvedix_nodes::cvedix_openpose_detector_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["model_path"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["model_config_path"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["labels_path"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["input_width"].get<int>(),
                jsonData["nodes"][countNode]["config"]["input_height"].get<int>(),
                jsonData["nodes"][countNode]["config"]["batch_size"].get<int>(),
                jsonData["nodes"][countNode]["config"]["class_id_offset"].get<int>(),
                jsonData["nodes"][countNode]["config"]["score_threshold"].get<float>(),
                static_cast<cvedix_objects::cvedix_pose_type>(jsonData["nodes"][countNode]["config"]["pose_type"].get<int>()),
                jsonData["nodes"][countNode]["config"]["scale"].get<float>(),
                cv::Scalar(jsonData["nodes"][countNode]["config"]["mean_r"].get<double>(),
                           jsonData["nodes"][countNode]["config"]["mean_g"].get<double>(),
                           jsonData["nodes"][countNode]["config"]["mean_b"].get<double>()),
                cv::Scalar(jsonData["nodes"][countNode]["config"]["std_r"].get<double>(),
                           jsonData["nodes"][countNode]["config"]["std_g"].get<double>(),
                           jsonData["nodes"][countNode]["config"]["std_b"].get<double>()),
                jsonData["nodes"][countNode]["config"]["swap_rb"].get<bool>());
            nodes.push_back(openpose_detector);
        }
        // else if (Node == "cvedix_ppocr_text_detector_node")
        // {
        //     auto ppocr_text_detector = std::make_shared<cvedix_nodes::cvedix_ppocr_text_detector_node>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["det_model_dir"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["cls_model_dir"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["rec_model_dir"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["rec_char_dict_path"].get<std::string>());
        // }
        else if (Node == "cvedix_restoration_node")
        {
            auto restoration = std::make_shared<cvedix_nodes::cvedix_restoration_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["realesrgan_bg_restoration_model"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["face_restoration_model"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["restoration_to_osd"].get<bool>());
            nodes.push_back(restoration);
        }
        // else if (Node == "cvedix_rknn_face_detector_node")
        // {
        //     auto rknn_face_detector = std::make_shared<cvedix_nodes::cvedix_rknn_face_detector_node>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["model_path"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["score_threshold"].get<float>(),
        //         jsonData["nodes"][countNode]["config"]["nms_threshold"].get<float>(),
        //         jsonData["nodes"][countNode]["config"]["top_k"].get<int>(),
        //         jsonData["nodes"][countNode]["config"]["input_width"].get<int>(),
        //         jsonData["nodes"][countNode]["config"]["input_height"].get<int>());
        // }
        //         else if (Node == "cvedix_rknn_yolov8_detector_node")
        //         {
        //             auto rknn_yolov8_detector = std::make_shared<cvedix_nodes::cvedix_rknn_yolov8_detector_node>(
        //                 jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //                 jsonData["nodes"][countNode]["config"]["model_path"].get<std::string>(),
        //                 jsonData["nodes"][countNode]["config"]["score_threshold"].get<float>(),
        //                 jsonData["nodes"][countNode]["config"]["nms_threshold"].get<float>(),
        //                 jsonData["nodes"][countNode]["config"]["input_width"].get<int>(),
        //                 jsonData["nodes"][countNode]["config"]["input_height"].get<int>(),
        //                 jsonData["nodes"][countNode]["config"]["num_classes"].get<int>(),
        //                 jsonData["nodes"][countNode]["config"]["labels_path"].get<std::string>(),
        //                 jsonData["nodes"][countNode]["config"]["class_id_offset"].get<int>());
        //         }
        else if (Node == "cvedix_sface_feature_encoder_node")
        {
            auto sface_feature_encoder = std::make_shared<cvedix_nodes::cvedix_sface_feature_encoder_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["model_path"].get<std::string>());
            nodes.push_back(sface_feature_encoder);
        }
        else if (Node == "cvedix_sort_track_node")
        {
            std::cout << "[DEBUG] Creating cvedix_sort_track_node" << std::endl;
            auto file = std::make_shared<cvedix_nodes::cvedix_sort_track_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>());
            nodes.push_back(file);
        }
        // else if (Node == "cvedix_track_node")
        // {
        //     auto file = std::make_shared<cvedix_nodes::cvedix_track_node>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         static_cast<cvedix_nodes::cvedix_track_for>(jsonData["nodes"][countNode]["config"]["track_for"].get<int>()));
        // }
        // else if (Node == "cvedix_trt_vehicle_color_classifier")
        // {
        //     auto trt_vehicle_color_classifier = std::make_shared<cvedix_nodes::cvedix_trt_vehicle_color_classifier>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["vehicle_color_cls_model_path"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["p_class_ids_applied_to"].get<std::vector<int>>(),
        //         jsonData["nodes"][countNode]["config"]["min_width_applied_to"].get<int>(),
        //         jsonData["nodes"][countNode]["config"]["min_height_applied_to"].get<int>());
        // }
        // else if (Node == "cvedix_trt_vehicle_detector")
        // {
        //     auto trt_vehicle_detector = std::make_shared<cvedix_nodes::cvedix_trt_vehicle_detector>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["vehicle_det_model_path"].get<std::string>());
        // }
        // else if (Node == "cvedix_trt_vehicle_feature_encoder")
        // {
        //     auto trt_vehicle_feature_encoder = std::make_shared<cvedix_nodes::cvedix_trt_vehicle_feature_encoder>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["vehicle_feature_model_path"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["p_class_ids_applied_to"].get<std::vector<int>>(),
        //         jsonData["nodes"][countNode]["config"]["min_width_applied_to"].get<int>(),
        //         jsonData["nodes"][countNode]["config"]["min_height_applied_to"].get<int>());
        // }
        // else if (Node == "cvedix_trt_vehicle_plate_detector")
        // {
        //     auto trt_vehicle_plate_detector = std::make_shared<cvedix_nodes::cvedix_trt_vehicle_plate_detector>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["plate_det_model_path"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["char_rec_model_path"].get<std::string>());
        // }
        // else if (Node == "cvedix_trt_vehicle_plate_detector_v2")
        // {
        //     auto trt_vehicle_plate_detector_v2 = std::make_shared<cvedix_nodes::cvedix_trt_vehicle_plate_detector_v2>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["plate_det_model_path"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["char_rec_model_path"].get<std::string>());
        // }
        // else if (Node == "cvedix_trt_vehicle_scanner")
        // {
        //     auto trt_vehicle_scanner = std::make_shared<cvedix_nodes::cvedix_trt_vehicle_scanner>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["vehicle_scan_model_path"].get<std::string>());
        // }
        //         else if (Node == "cvedix_trt_vehicle_type_classifier")
        //         {
        //             auto trt_vehicle_type_classifier = std::make_shared<cvedix_nodes::cvedix_trt_vehicle_type_classifier>(
        //                 jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //                 jsonData["nodes"][countNode]["config"]["vehicle_type_cls_model_path"].get<std::string>(),
        //                 jsonData["nodes"][countNode]["config"]["p_class_ids_applied_to"].get<std::vector<int>>(),
        //                 jsonData["nodes"][countNode]["config"]["min_width_applied_to"].get<int>(),
        //                 jsonData["nodes"][countNode]["config"]["min_height_applied_to"].get<int>());
        //         }
        // else if (Node == "cvedix_trt_yolov8_classifier")
        // {
        //     auto trt_yolov8_classifier = std::make_shared<cvedix_nodes::cvedix_trt_yolov8_classifier>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["model_path"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["labels_path"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["p_class_ids_applied_to"].get<std::vector<int>>(),
        //         jsonData["nodes"][countNode]["config"]["min_width_applied_to"].get<int>(),
        //         jsonData["nodes"][countNode]["config"]["min_height_applied_to"].get<int>());
        // }
        // else if (Node == "cvedix_trt_yolov8_detector")
        // {
        //     auto trt_yolov8_detector = std::make_shared<cvedix_nodes::cvedix_trt_yolov8_detector>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["model_path"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["labels_path"].get<std::string>());
        // }
        //         else if (Node == "cvedix_trt_yolov8_pose_detector")
        //         {
        //             auto trt_yolov8_pose_detector = std::make_shared<cvedix_nodes::cvedix_trt_yolov8_pose_detector>(
        //                 jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //                 jsonData["nodes"][countNode]["config"]["model_path"].get<std::string>());
        //         }
        //         else if (Node == "cvedix_trt_yolov8_seg_detector")
        //         {
        //             auto trt_yolov8_seg_detector = std::make_shared<cvedix_nodes::cvedix_trt_yolov8_seg_detector>(
        //                 jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //                 jsonData["nodes"][countNode]["config"]["model_path"].get<std::string>(),
        //                 jsonData["nodes"][countNode]["config"]["labels_path"].get<std::string>());
        //         }
        else if (Node == "cvedix_yolo_detector_node")
        {
            std::cout << "[DEBUG] Creating cvedix_yolo_detector_node" << std::endl;
            auto yolo_detector = std::make_shared<cvedix_nodes::cvedix_yolo_detector_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                "/opt/cvedix/model/yolov3-tiny-2022-0721_best.weights",
                "/opt/cvedix/model/yolov3-tiny-2022-0721.cfg",
                "/opt/cvedix/model/yolov3_tiny_5classes.txt",
                jsonData["nodes"][countNode]["config"]["input_width"].get<int>(),
                jsonData["nodes"][countNode]["config"]["input_height"].get<int>(),
                jsonData["nodes"][countNode]["config"]["batch_size"].get<int>(),
                jsonData["nodes"][countNode]["config"]["class_id_offset"].get<int>(),
                jsonData["nodes"][countNode]["config"]["score_threshold"].get<float>(),
                jsonData["nodes"][countNode]["config"]["confidence_threshold"].get<float>(),
                jsonData["nodes"][countNode]["config"]["nms_threshold"].get<float>(),
                jsonData["nodes"][countNode]["config"]["scale"].get<float>(),
                cv::Scalar(jsonData["nodes"][countNode]["config"]["mean_r"].get<double>(),
                           jsonData["nodes"][countNode]["config"]["mean_g"].get<double>(),
                           jsonData["nodes"][countNode]["config"]["mean_b"].get<double>()),
                cv::Scalar(jsonData["nodes"][countNode]["config"]["std_r"].get<double>(),
                           jsonData["nodes"][countNode]["config"]["std_g"].get<double>(),
                           jsonData["nodes"][countNode]["config"]["std_b"].get<double>()),
                jsonData["nodes"][countNode]["config"]["swap_rb"].get<bool>());

            nodes.push_back(yolo_detector);
        }
        else if (Node == "cvedix_yunet_face_detector_node")
        {
            auto yunet_face_detector = std::make_shared<cvedix_nodes::cvedix_yunet_face_detector_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                "../Model/sample.onnx");
            nodes.push_back(yunet_face_detector);
        }
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
        else if (Node == "cvedix_ba_crossline_osd_node")
        {
            std::cout << "[DEBUG] Creating cvedix_ba_crossline_osd_node" << std::endl;
            auto ba_crossline_osd = std::make_shared<cvedix_nodes::cvedix_ba_crossline_osd_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["font"].get<std::string>());
            nodes.push_back(ba_crossline_osd);
        }
        else if (Node == "cvedix_ba_jam_osd_node")
        {
            auto ba_jam_osd = std::make_shared<cvedix_nodes::cvedix_ba_jam_osd_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["font"].get<std::string>());
            nodes.push_back(ba_jam_osd);
        }
        else if (Node == "cvedix_ba_stop_osd_node")
        {
            auto ba_stop_osd = std::make_shared<cvedix_nodes::cvedix_ba_stop_osd_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["font"].get<std::string>());

            nodes.push_back(ba_stop_osd);
        }
        else if (Node == "cvedix_expr_osd_node")
        {
            auto expr_osd = std::make_shared<cvedix_nodes::cvedix_expr_osd_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["font"].get<std::string>());

            nodes.push_back(expr_osd);
        }
        else if (Node == "cvedix_face_osd_node")
        {
            face_osd = std::make_shared<cvedix_nodes::cvedix_face_osd_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>());
            nodes.push_back(face_osd);
        }
        else if (Node == "cvedix_face_osd_node_v2")
        {
            auto face_osd_v2 = std::make_shared<cvedix_nodes::cvedix_face_osd_node_v2>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>());
            nodes.push_back(face_osd_v2);
        }
        else if (Node == "cvedix_lane_osd_node")
        {
            auto lane_osd = std::make_shared<cvedix_nodes::cvedix_lane_osd_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>());
            nodes.push_back(lane_osd);
        }
        // else if (Node == "cvedix_mllm_osd_node")
        // {
        //     auto mllm_osd = std::make_shared<cvedix_nodes::cvedix_mllm_osd_node>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["font"].get<std::string>());
        // }
        else if (Node == "cvedix_osd_node")
        {
            auto osd = std::make_shared<cvedix_nodes::cvedix_osd_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["font"].get<std::string>());
            nodes.push_back(osd);
        }
        else if (Node == "cvedix_osd_node_v2")
        {
            auto osd_v2 = std::make_shared<cvedix_nodes::cvedix_osd_node_v2>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["font"].get<std::string>());
            nodes.push_back(osd_v2);
        }
        else if (Node == "cvedix_osd_node_v3")
        {
            auto osd_v3 = std::make_shared<cvedix_nodes::cvedix_osd_node_v3>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["font"].get<std::string>());
            nodes.push_back(osd_v3);
        }
        else if (Node == "cvedix_plate_osd_node")
        {
            auto plate_osd = std::make_shared<cvedix_nodes::cvedix_plate_osd_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["font"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["display_his"].get<bool>());
            nodes.push_back(plate_osd);
        }
        else if (Node == "cvedix_pose_osd_node")
        {
            auto pose_osd = std::make_shared<cvedix_nodes::cvedix_pose_osd_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>());
            nodes.push_back(pose_osd);
        }
        else if (Node == "cvedix_seg_osd_node")
        {
            auto seg_osd = std::make_shared<cvedix_nodes::cvedix_seg_osd_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["classes_file"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["colors_file"].get<std::string>());
            nodes.push_back(seg_osd);
        }
        else if (Node == "cvedix_text_osd_node")
        {
            auto text_osd = std::make_shared<cvedix_nodes::cvedix_text_osd_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["font"].get<std::string>());
            nodes.push_back(text_osd);
        }
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
        else if (Node == "cvedix_ba_socket_broker_node")
        {
            auto ba_socket_broker = std::make_shared<cvedix_nodes::cvedix_ba_socket_broker_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["des_ip"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["des_port"].get<int>(),
                static_cast<cvedix_nodes::cvedix_broke_for>(jsonData["nodes"][countNode]["config"]["broke_for"].get<int>()),
                jsonData["nodes"][countNode]["config"]["broking_cache_warn_threshold"].get<int>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_ignore_threshold"].get<int>());
            nodes.push_back(ba_socket_broker);
        }
        else if (Node == "cvedix_embeddings_properties_socket_broker_node")
        {
            auto embeddings_properties_socket_broker = std::make_shared<cvedix_nodes::cvedix_embeddings_properties_socket_broker_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["des_ip"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["des_port"].get<int>(),
                jsonData["nodes"][countNode]["config"]["cropped_dir"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["min_crop_width"].get<int>(),
                jsonData["nodes"][countNode]["config"]["min_crop_height"].get<int>(),
                static_cast<cvedix_nodes::cvedix_broke_for>(jsonData["nodes"][countNode]["config"]["broke_for"].get<int>()),
                jsonData["nodes"][countNode]["config"]["only_for_tracked"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_warn_threshold"].get<int>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_ignore_threshold"].get<int>());
            nodes.push_back(embeddings_properties_socket_broker);
        }
        else if (Node == "cvedix_embeddings_socket_broker_node")
        {
            auto embeddings_socket_broker = std::make_shared<cvedix_nodes::cvedix_embeddings_socket_broker_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["des_ip"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["des_port"].get<int>(),
                jsonData["nodes"][countNode]["config"]["cropped_dir"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["min_crop_width"].get<int>(),
                jsonData["nodes"][countNode]["config"]["min_crop_height"].get<int>(),
                static_cast<cvedix_nodes::cvedix_broke_for>(jsonData["nodes"][countNode]["config"]["broke_for"].get<int>()),
                jsonData["nodes"][countNode]["config"]["only_for_tracked"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_warn_threshold"].get<int>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_ignore_threshold"].get<int>());
            nodes.push_back(embeddings_socket_broker);
        }
        else if (Node == "cvedix_expr_socket_broker_node")
        {
            auto expr_socket_broker = std::make_shared<cvedix_nodes::cvedix_expr_socket_broker_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["des_ip"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["des_port"].get<int>(),
                jsonData["nodes"][countNode]["config"]["screenshot_dir"].get<std::string>(),
                static_cast<cvedix_nodes::cvedix_broke_for>(jsonData["nodes"][countNode]["config"]["broke_for"].get<int>()),
                jsonData["nodes"][countNode]["config"]["broking_cache_warn_threshold"].get<int>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_ignore_threshold"].get<int>());

            nodes.push_back(expr_socket_broker);
        }
        else if (Node == "cvedix_json_console_broker_node")
        {
            auto json_console_broker = std::make_shared<cvedix_nodes::cvedix_json_console_broker_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                static_cast<cvedix_nodes::cvedix_broke_for>(jsonData["nodes"][countNode]["config"]["broke_for"].get<int>()),
                jsonData["nodes"][countNode]["config"]["broking_cache_warn_threshold"].get<int>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_ignore_threshold"].get<int>());
            nodes.push_back(json_console_broker);
        }
        else if (Node == "cvedix_json_enhanced_console_broker_node")
        {
            auto json_enhanced_console_broker = std::make_shared<cvedix_nodes::cvedix_json_enhanced_console_broker_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                static_cast<cvedix_nodes::cvedix_broke_for>(jsonData["nodes"][countNode]["config"]["broke_for"].get<int>()),
                jsonData["nodes"][countNode]["config"]["broking_cache_warn_threshold"].get<int>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_ignore_threshold"].get<int>(),
                jsonData["nodes"][countNode]["config"]["encode_full_frame"].get<bool>());

            nodes.push_back(json_enhanced_console_broker);
        }
        // else if (Node == "cvedix_json_kafka_broker_node")
        // {
        //     auto json_kafka_broker = std::make_shared<cvedix_nodes::cvedix_json_kafka_broker_node>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["kafka_servers"].get<std::string>(),
        //         jsonData["nodes"][countNode]["config"]["topic_name"].get<std::string>(),
        //         static_cast<cvedix_nodes::cvedix_broke_for>(jsonData["nodes"][countNode]["config"]["broke_for"].get<int>()),
        //         jsonData["nodes"][countNode]["config"]["broking_cache_warn_threshold"].get<int>(),
        //         jsonData["nodes"][countNode]["config"]["broking_cache_ignore_threshold"].get<int>());
        // }
        else if (Node == "cvedix_json_mqtt_broker_node")
        {
            auto json_mqtt_broker = std::make_shared<cvedix_nodes::cvedix_json_mqtt_broker_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                static_cast<cvedix_nodes::cvedix_broke_for>(jsonData["nodes"][countNode]["config"]["broke_for"].get<int>()),
                jsonData["nodes"][countNode]["config"]["broking_cache_warn_threshold"].get<int>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_ignore_threshold"].get<int>());
            nodes.push_back(json_mqtt_broker);
        }
        // else if (Node == "cvedix_msg_broker_node")
        // {
        //     auto msg_broker = std::make_shared<cvedix_nodes::cvedix_msg_broker_node>(
        //         jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>());
        // }
        else if (Node == "cvedix_plate_socket_broker_node")
        {
            auto plate_socket_broker = std::make_shared<cvedix_nodes::cvedix_plate_socket_broker_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["des_ip"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["des_port"].get<int>(),
                jsonData["nodes"][countNode]["config"]["plates_dir"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["min_crop_width"].get<int>(),
                jsonData["nodes"][countNode]["config"]["min_crop_height"].get<int>(),
                static_cast<cvedix_nodes::cvedix_broke_for>(jsonData["nodes"][countNode]["config"]["broke_for"].get<int>()),
                jsonData["nodes"][countNode]["config"]["only_for_tracked"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_warn_threshold"].get<int>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_ignore_threshold"].get<int>());
            nodes.push_back(plate_socket_broker);
        }
        else if (Node == "cvedix_xml_file_broker_node")
        {
            auto xml_file_broker = std::make_shared<cvedix_nodes::cvedix_xml_file_broker_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                static_cast<cvedix_nodes::cvedix_broke_for>(jsonData["nodes"][countNode]["config"]["broke_for"].get<int>()),
                jsonData["nodes"][countNode]["config"]["file_path_and_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_warn_threshold"].get<int>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_ignore_threshold"].get<int>());
            nodes.push_back(xml_file_broker);
        }
        else if (Node == "cvedix_xml_socket_broker_node")
        {
            auto xml_socket_broker = std::make_shared<cvedix_nodes::cvedix_xml_socket_broker_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["des_ip"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["des_port"].get<int>(),
                static_cast<cvedix_nodes::cvedix_broke_for>(jsonData["nodes"][countNode]["config"]["broke_for"].get<int>()),
                jsonData["nodes"][countNode]["config"]["broking_cache_warn_threshold"].get<int>(),
                jsonData["nodes"][countNode]["config"]["broking_cache_ignore_threshold"].get<int>());

            nodes.push_back(xml_socket_broker);
        }
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
        else if (Node == "cvedix_cluster_node")
        {
            std::vector<std::string> s_labels_to_display;
            if (jsonData["nodes"][countNode]["config"].contains("s_labels_to_display"))
            {
                for (const auto &label : jsonData["nodes"][countNode]["config"]["s_labels_to_display"])
                {
                    s_labels_to_display.push_back(label.get<std::string>());
                }
            }
            auto cluster = std::make_shared<cvedix_nodes::cvedix_cluster_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["use_tSNE"].get<bool>(),
                s_labels_to_display,
                jsonData["nodes"][countNode]["config"]["sampling_frequency"].get<int>(),
                jsonData["nodes"][countNode]["config"]["min_sampling_width"].get<int>(),
                jsonData["nodes"][countNode]["config"]["min_sampling_height"].get<int>(),
                jsonData["nodes"][countNode]["config"]["max_sample_num_for_tsne"].get<int>(),
                jsonData["nodes"][countNode]["config"]["max_sample_num_per_category"].get<int>());
            nodes.push_back(cluster);
        }
        else if (Node == "cvedix_custom_data_transform_node")
        {
            auto custom_data_transform = std::make_shared<cvedix_nodes::cvedix_custom_data_transform_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>());

            nodes.push_back(custom_data_transform);
        }
        else if (Node == "cvedix_expr_check_node")
        {
            auto expr_check = std::make_shared<cvedix_nodes::cvedix_expr_check_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>());

            nodes.push_back(expr_check);
        }
        else if (Node == "cvedix_frame_fusion_node")
        {
            std::vector<cvedix_objects::cvedix_point> src_points;
            for (const auto &point : jsonData["nodes"][countNode]["config"]["src_points"])
            {
                src_points.push_back(cvedix_objects::cvedix_point{
                    point["x"].get<int>(),
                    point["y"].get<int>()});
            }
            std::vector<cvedix_objects::cvedix_point> des_points;
            for (const auto &point : jsonData["nodes"][countNode]["config"]["des_points"])
            {
                des_points.push_back(cvedix_objects::cvedix_point{
                    point["x"].get<int>(),
                    point["y"].get<int>()});
            }
            auto frame_fusion = std::make_shared<cvedix_nodes::cvedix_frame_fusion_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                src_points,
                des_points,
                jsonData["nodes"][countNode]["config"]["src_channel_index"].get<int>(),
                jsonData["nodes"][countNode]["config"]["des_channel_index"].get<int>());

            nodes.push_back(frame_fusion);
        }
        else if (Node == "cvedix_placeholder_node")
        {
            auto placeholder = std::make_shared<cvedix_nodes::cvedix_placeholder_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>());

            nodes.push_back(placeholder);
        }
        else if (Node == "cvedix_split_node")
        {
            auto split = std::make_shared<cvedix_nodes::cvedix_split_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["split_with_channel_index"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["split_with_deep_copy"].get<bool>());

            nodes.push_back(split);
        }
        else if (Node == "cvedix_sync_node")
        {
            auto sync = std::make_shared<cvedix_nodes::cvedix_sync_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                static_cast<cvedix_nodes::cvedix_sync_mode>(jsonData["nodes"][countNode]["config"]["mode"].get<int>()),
                jsonData["nodes"][countNode]["config"]["timeout"].get<int>());
            nodes.push_back(sync);
        }
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

        else if (Node == "cvedix_app_des_node")
        {
            auto app_des = std::make_shared<cvedix_nodes::cvedix_app_des_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["channel_index"].get<int>());
            nodes.push_back(app_des);
            des_node++;
        }
        else if (Node == "cvedix_fake_des_node")
        {
            auto fake_des = std::make_shared<cvedix_nodes::cvedix_fake_des_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["channel_index"].get<int>());
            nodes.push_back(fake_des);
            des_node++;
        }
        else if (Node == "cvedix_file_des_node")
        {
            auto file = std::make_shared<cvedix_nodes::cvedix_file_des_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["channel_index"].get<int>(),
                jsonData["nodes"][countNode]["config"]["save_dir"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["name_prefix"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["max_duration_for_single_file"].get<int>(),
                cvedix_objects::cvedix_size{
                    jsonData["nodes"][countNode]["config"]["resolution_width"].get<int>(),
                    jsonData["nodes"][countNode]["config"]["resolution_height"].get<int>()},
                jsonData["nodes"][countNode]["config"]["bitrate"].get<int>(),
                jsonData["nodes"][countNode]["config"]["osd"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["gst_encoder_name"].get<std::string>());
            nodes.push_back(file);
            des_node++;
        }
        else if (Node == "cvedix_image_des_node")
        {
            auto image_des = std::make_shared<cvedix_nodes::cvedix_image_des_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["channel_index"].get<int>(),
                jsonData["nodes"][countNode]["config"]["location"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["interval"].get<int>(),
                cvedix_objects::cvedix_size{
                    jsonData["nodes"][countNode]["config"]["resolution_width"].get<int>(),
                    jsonData["nodes"][countNode]["config"]["resolution_height"].get<int>()},
                jsonData["nodes"][countNode]["config"]["osd"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["gst_encoder_name"].get<std::string>());
            nodes.push_back(image_des);
            des_node++;
        }
        else if (Node == "cvedix_rtsp_des_node")
        {
            auto rtsp_des = std::make_shared<cvedix_nodes::cvedix_rtsp_des_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["channel_index"].get<int>(),
                jsonData["nodes"][countNode]["config"]["rtsp_port"].get<int>(),
                jsonData["nodes"][countNode]["config"]["rtsp_name"].get<std::string>(),
                cvedix_objects::cvedix_size{
                    jsonData["nodes"][countNode]["config"]["resolution_width"].get<int>(),
                    jsonData["nodes"][countNode]["config"]["resolution_height"].get<int>()},
                jsonData["nodes"][countNode]["config"]["bitrate"].get<int>(),
                jsonData["nodes"][countNode]["config"]["osd"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["gst_encoder_name"].get<std::string>());
            nodes.push_back(rtsp_des);
            des_node++;
        }
        else if (Node == "cvedix_rtmp_des_node")
        {
            std::cout << "[DEBUG] Creating cvedix_rtmp_des_node" << std::endl;
            auto rtmp_des = std::make_shared<cvedix_nodes::cvedix_rtmp_des_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["channel_index"].get<int>(),
                jsonData["nodes"][countNode]["config"]["rtmp_url"].get<std::string>(),
                cvedix_objects::cvedix_size{
                    jsonData["nodes"][countNode]["config"]["resolution_width"].get<int>(),
                    jsonData["nodes"][countNode]["config"]["resolution_height"].get<int>()},
                jsonData["nodes"][countNode]["config"]["bitrate"].get<int>(),
                jsonData["nodes"][countNode]["config"]["osd"].get<bool>(),
                jsonData["nodes"][countNode]["config"]["gst_encoder_name"].get<std::string>());
            nodes.push_back(rtmp_des);
            des_node++;
        }
        else if (Node == "cvedix_screen_des_node")
        {
            auto screen_des = std::make_shared<cvedix_nodes::cvedix_screen_des_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                jsonData["nodes"][countNode]["config"]["channel_index"].get<int>(),
                jsonData["nodes"][countNode]["config"]["osd"].get<bool>());
            nodes.push_back(screen_des);
            des_node++;
        }
        //----------------------------------------------------------------------------------------------------------------
        /*
                                ba
        */
        else if (Node == "cvedix_ba_crossline_node")
        {
            std::cout << "[DEBUG] Creating cvedix_ba_crossline_node" << std::endl;
            auto ba_crossline = std::make_shared<cvedix_nodes::cvedix_ba_crossline_node>(
                jsonData["nodes"][countNode]["config"]["node_name"].get<std::string>(),
                std::map<int, cvedix_objects::cvedix_line>{},
                true,
                false);
            nodes.push_back(ba_crossline);
            des_node++;
        }
    }

    //----------------------------------------------------------------------------------------------------------------
}

void MakeNode::MatchingPipeline()
{
    for (int i = 0; i < nodes.size(); i++)
    {
        int a = 0;
        int des_node_pointer = nodes.size() - des_node;
        if (i < des_node_pointer - 1)
        {
            nodes[i + 1]->attach_to({nodes[i]});
        }
        else if (i > 0)
        {
            nodes[i]->attach_to({nodes[des_node_pointer - 1]});
        }
    }
}

void MakeNode::StartPipeline()
{
    auto src_node = std::dynamic_pointer_cast<cvedix_nodes::cvedix_src_node>(nodes[0]);
    std::cout << "[INFO] Starting pipeline..." << std::endl;
    src_node->start();
    std::cout << "[INFO] Pipeline started successfully" << std::endl;
    // cvedix_utils::cvedix_analysis_board board({nodes[0]});
    // board.display(1, true);
}

void MakeNode::StopPipeline()
{
    auto src_node = std::dynamic_pointer_cast<cvedix_nodes::cvedix_src_node>(nodes[0]);
    std::cout << "[INFO] Stopping pipeline..." << std::endl;
    for (int i = nodes.size() - 1; i >= 0; i--)
    {
        nodes[i]->detach();
    }
    src_node->stop();
    std::cout << "[INFO] Pipeline stopped successfully" << std::endl;
}
