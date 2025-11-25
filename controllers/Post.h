#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class VideoUpload : public drogon::HttpSimpleController<VideoUpload, true>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  PATH_ADD("/api/video-file", drogon::Post);
  PATH_LIST_END
};
