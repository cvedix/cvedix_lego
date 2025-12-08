#include "CheckFirmwareController.h"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

void CheckFirmwareController::asyncHandleHttpRequest(
    const HttpRequestPtr &req,
    std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto path = req->path();

    if (path != "/api/check-firmware")
    {
        auto resp = HttpResponse::newNotFoundResponse();
        callback(resp);
        return;
    }

    std::ifstream file("../TestBox/firmware.json");
    if (!file.is_open())
    {
        auto resp = HttpResponse::newHttpJsonResponse(Json::Value("Cannot open firmware.json"));
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
        return;
    }

    json data;
    try
    {
        file >> data;
    }
    catch (...)
    {
        auto resp = HttpResponse::newHttpJsonResponse(Json::Value("Invalid JSON format"));
        resp->setStatusCode(k500InternalServerError);
        callback(resp);
        return;
    }
    file.close();

    std::string version = data.value("version", "unknown");
    std::string release_date = data.value("release_date", "unknown");
    std::string description = data.value("description", "No description");
    int size = data.value("size", 0);

    Json::Value result;
    result["version"] = version;
    result["release_date"] = release_date;
    result["description"] = description;
    result["size"] = size;

    auto resp = HttpResponse::newHttpJsonResponse(result);
    callback(resp);
}
