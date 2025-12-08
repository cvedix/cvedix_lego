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

#include "All_Node.h"
#include "NodeFactory.h"

using namespace drogon;
using json = nlohmann::json;

class LegoPost : public drogon::HttpController<LegoPost>
{
public:
  METHOD_LIST_BEGIN
  ADD_METHOD_TO(LegoPost::runPipeline, "/lego/post", Post);
  METHOD_LIST_END

  void runPipeline(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback);
};
