#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class Api : public drogon::HttpSimpleController<Api, true>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req,
                              std::function<void(const HttpResponsePtr &)> &&callback) override;

  PATH_LIST_BEGIN
  PATH_ADD("/api/hello", drogon::Get);
  PATH_LIST_END
};
