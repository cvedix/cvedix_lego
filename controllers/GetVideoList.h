#pragma once

#include <drogon/HttpSimpleController.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace drogon;
using json = nlohmann::json;

class GetVideoList : public drogon::HttpSimpleController<GetVideoList>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  PATH_ADD("/lego/getvideolist", Get);
  PATH_LIST_END
};

class DeleteVideo : public drogon::HttpSimpleController<DeleteVideo>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  PATH_ADD("/lego/deletevideo", Post);
  PATH_LIST_END
};

