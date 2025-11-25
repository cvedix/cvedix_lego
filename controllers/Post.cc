#include "Post.h"

void VideoUpload::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    MultiPartParser fileUpload;
    fileUpload.parse(req);

    auto &file = fileUpload.getFiles()[0];
    file.saveAs(file.getFileName());

    Json::Value json;
    json["success"] = true;
    json["filename"] = file.getFileName();
    auto resp = HttpResponse::newHttpJsonResponse(json);
    callback(resp);
}
