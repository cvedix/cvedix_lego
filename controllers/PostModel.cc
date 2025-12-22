#include "PostModel.h"

// using json = nlohmann::ordered_json;

void PostModel::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    drogon::MultiPartParser fileUpload;
    fileUpload.parse(req);
    const auto &files = fileUpload.getFiles();
    const auto &video = files[0];
    std::string save_path = "/opt/cvedix/model";
    video.save(save_path);
    std::filesystem::directory_iterator it(save_path);
    auto entry = *it;
    json resp;
    resp["status"] = "success";
    resp["message"] = "Model uploaded successfully.";
    auto httpResp = HttpResponse::newHttpResponse();
    httpResp->setBody(resp.dump());
    callback(httpResp);
}
