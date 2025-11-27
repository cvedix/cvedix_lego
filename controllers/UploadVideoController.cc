#include "UploadVideoController.h"
#include <regex>
#include <algorithm>

void UploadVideoController::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    MultiPartParser fileUpload;
    fileUpload.parse(req);

    auto &files = fileUpload.getFiles();
    if (files.empty())
    {
        Json::Value json;
        json["error"] = "No file uploaded";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    auto &file = files[0];
    std::string fileName = file.getFileName();

    // Check file extension
    std::string extension;
    size_t dotPos = fileName.find_last_of('.');
    if (dotPos != std::string::npos)
    {
        extension = fileName.substr(dotPos);
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
    }

    if (extension != ".mp4" && extension != ".jpeg" && extension != ".jpg")
    {
        Json::Value json;
        json["error"] = "Only .mp4, .jpeg, .jpg files are allowed";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    // Check filename format (snake_case: lowercase letters, numbers, underscores)
    std::string nameWithoutExt = fileName.substr(0, dotPos);
    std::regex snakeCaseRegex("^[a-z0-9_]+$");
    if (!std::regex_match(nameWithoutExt, snakeCaseRegex))
    {
        Json::Value json;
        json["error"] = "Filename must be in snake_case (lowercase letters, numbers, underscores only)";
        json["example"] = "my_video_file.mp4";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    // Check file size (max 1GB)
    if (file.fileLength() > 1024 * 1024 * 1024)
    {
        Json::Value json;
        json["error"] = "File size exceeds 1GB limit";
        auto resp = HttpResponse::newHttpJsonResponse(json);
        resp->setStatusCode(k413RequestEntityTooLarge);
        callback(resp);
        return;
    }

    std::filesystem::create_directories("./uploads");

    std::string savePath = "./uploads/" + fileName;
    file.saveAs(savePath);

    Json::Value result;
    result["success"] = true;
    result["filename"] = fileName;
    result["path"] = savePath;
    result["size"] = static_cast<Json::Int64>(file.fileLength());

    callback(HttpResponse::newHttpJsonResponse(result));
}
