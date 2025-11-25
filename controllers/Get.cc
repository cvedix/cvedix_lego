#include "Get.h"

void Api::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
    Json::Value json;
    json["message"] = "Hello from Drogon!";
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}
