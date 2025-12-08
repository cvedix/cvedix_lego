#pragma once

#include <drogon/HttpSimpleController.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using namespace drogon;
using json = nlohmann::json;

class CheckFirmwareController : public drogon::HttpSimpleController<CheckFirmwareController>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  PATH_ADD("/api/check-firmware", drogon::Get);
  PATH_LIST_END
};
