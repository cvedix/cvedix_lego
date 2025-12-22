#pragma once
#include <drogon/HttpController.h>
#include <nlohmann/json.hpp>
#include <drogon/drogon.h>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <map>
#include <filesystem>
#include <fstream>
#include <ctime>
#include <iostream>
#include <atomic>
#include <termios.h>
#include <unistd.h>

#include "All_Node.h"
#include <cvedix/utils/analysis_board/cvedix_analysis_board.h>
#include "NodeFactory.h"

using namespace drogon;
using json = nlohmann::json;
static std::atomic<bool> g_stopPipeline{false};

class ControlPanel : public drogon::HttpController<ControlPanel>
{
public:
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(ControlPanel::runPipeline, "/lego/startpipeline", Post);
  ADD_METHOD_TO(ControlPanel::stopPipeline, "/lego/stoppipeline", Post);
  METHOD_LIST_END

  void runPipeline(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback);
  void stopPipeline(const HttpRequestPtr &req,
                    std::function<void(const HttpResponsePtr &)> &&callback);
};
