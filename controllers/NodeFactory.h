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
    //----------------------------------------------------------------------------------------------------------------

    std::shared_ptr<cvedix_nodes::cvedix_yunet_face_detector_node> yunet_face_detector;
    std::shared_ptr<cvedix_nodes::cvedix_face_osd_node> face_osd;
    std::shared_ptr<cvedix_nodes::cvedix_rtmp_des_node> rtmp_des;
    std::shared_ptr<cvedix_nodes::cvedix_screen_des_node> screen_des;

    // Vector to hold all created nodes
    std::vector<std::shared_ptr<cvedix_nodes::cvedix_node>> nodes;
    void MatchingPipeline();
    void NodeRegister(json &jsonData);
    void StartPipeline();
    void StopPipeline();

private:
    int des_node = 0;
    std::string Node;
};
