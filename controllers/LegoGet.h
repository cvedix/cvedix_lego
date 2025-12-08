#pragma once

#include <drogon/HttpSimpleController.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "All_Node.h"

using namespace drogon;

class LegoGet : public drogon::HttpSimpleController<LegoGet>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  PATH_ADD("/lego/get", Get);
  PATH_LIST_END
};
