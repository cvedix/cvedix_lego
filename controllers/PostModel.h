#pragma once

#include <drogon/HttpSimpleController.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include "All_Node.h"

using namespace drogon;
using json = nlohmann::json;

class PostModel : public drogon::HttpSimpleController<PostModel>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  PATH_ADD("/lego/postmodel", Post);
  PATH_LIST_END
};
