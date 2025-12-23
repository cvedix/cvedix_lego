#pragma once

#include <drogon/HttpSimpleController.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <filesystem>
#include <fstream>

using namespace drogon;
using json = nlohmann::json;

class GetModelList : public drogon::HttpSimpleController<GetModelList>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  PATH_ADD("/lego/getmodellist", Get);
  PATH_LIST_END
};

class DeleteModel : public drogon::HttpSimpleController<DeleteModel>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  PATH_ADD("/lego/deletemodel", Post);
  PATH_LIST_END
};