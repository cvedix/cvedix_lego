#pragma once

#include <drogon/HttpSimpleController.h>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using namespace drogon;
using json = nlohmann::json;

<<<<<<<< HEAD:controllers/CheckFirmwareController.h
class CheckFirmwareController : public drogon::HttpSimpleController<CheckFirmwareController>
========
class HelloController : public drogon::HttpSimpleController<HelloController>
>>>>>>>> e314763982046527c1724916856a3e3c237bc505:controllers/HelloController.h
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
<<<<<<<< HEAD:controllers/CheckFirmwareController.h
  PATH_ADD("/api/check-firmware", drogon::Get);
========
  // list path definitions here;
  PATH_ADD("/api/hello", drogon::Get);
>>>>>>>> e314763982046527c1724916856a3e3c237bc505:controllers/HelloController.h
  PATH_LIST_END
};
