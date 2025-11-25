#include "Get.h"

void Api::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    Json::Value json;
    json["message"] = "Hello from Drogon!";
    json["status"] = "success";
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}
