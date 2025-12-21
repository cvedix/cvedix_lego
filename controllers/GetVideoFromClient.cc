#include "GetVideoFromClient.h"

using json = nlohmann::ordered_json;

void GetVideoFromClient::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{

    drogon::MultiPartParser fileUpload;
    fileUpload.parse(req);
    const auto &files = fileUpload.getFiles();
    const auto &video = files[0];

    std::string save_path ="../../../../../opt/cvedix/media";
    // std::string save_path ="../Video";
    std::filesystem::remove_all(save_path);
    std::filesystem::create_directories(save_path);
    video.save(save_path);
    std::filesystem::directory_iterator it(save_path);
    auto entry = *it;
    json resp;
    resp["status"] = "success";
    resp["message"] = "Video uploaded successfully.";
    auto httpResp = HttpResponse::newHttpResponse();
    httpResp->setBody(resp.dump());
    callback(httpResp);
}
