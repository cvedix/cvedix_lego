#pragma once

#include <drogon/HttpSimpleController.h>
#include <filesystem>
#include <fstream>
#include <sstream>

using namespace drogon;
namespace fs = std::filesystem;

class Api : public drogon::HttpSimpleController<Api, true>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req,
                              std::function<void(const HttpResponsePtr &)> &&callback) override;

  PATH_LIST_BEGIN
  PATH_ADD("/api/hello", drogon::Get);
  PATH_LIST_END
};
