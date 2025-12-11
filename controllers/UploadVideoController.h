#pragma once

#include <drogon/HttpSimpleController.h>
#include <filesystem>
#include <fstream>
using namespace drogon;

class UploadVideoController : public drogon::HttpSimpleController<UploadVideoController>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  PATH_ADD("/api/upload-video", drogon::Post);
  PATH_LIST_END
};
