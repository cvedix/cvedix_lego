// #include "NodeFactory.h"

// // Register file_src
// NodeRegister file_src_register("cvedix_file_src_node", [](const json &config) -> std::shared_ptr<cvedix_nodes::cvedix_node>
//                                { return std::make_shared<cvedix_nodes::cvedix_file_src_node>(
//                                      config["node_name"].get<std::string>(),
//                                      config["channel_index"].get<int>(),
//                                      config["file_path"].get<std::string>(),
//                                      config["resize_ratio"].get<float>(), // Changed to float
//                                      config["cycle"].get<bool>(),
//                                      config["gst_decoder_name"].get<std::string>(),
//                                      config["skip_interval"].get<int>()); });

// // Register udp_src
// NodeRegister udp_src_register("cvedix_udp_src_node", [](const json &config) -> std::shared_ptr<cvedix_nodes::cvedix_node>
//                               { return std::make_shared<cvedix_nodes::cvedix_udp_src_node>(
//                                     config["node_name"].get<std::string>(),
//                                     config["channel_index"].get<int>(),
//                                     config["port"].get<int>(),
//                                     config["resize_ratio"].get<float>(), // Changed to float
//                                     config["gst_decoder_name"].get<std::string>(),
//                                     config["skip_interval"].get<int>()); });

// // Register rtsp_src - Need to complete based on actual constructor
// // Assuming similar params to file_src
// NodeRegister rtsp_src_register("cvedix_rtsp_src_node", [](const json &config) -> std::shared_ptr<cvedix_nodes::cvedix_node>
//                                { return std::make_shared<cvedix_nodes::cvedix_rtsp_src_node>(
//                                      config["node_name"].get<std::string>(),
//                                      config["channel_index"].get<int>(),
//                                      config["rtsp_url"].get<std::string>(),
//                                      config["resize_ratio"].get<float>(),
//                                      config["gst_decoder_name"].get<std::string>(),
//                                      config["skip_interval"].get<int>()); });

// // Add more src nodes as needed...