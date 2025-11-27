#pragma once

#include <drogon/HttpSimpleController.h>

using namespace drogon;

class HelloController : public drogon::HttpSimpleController<HelloController>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  // list path definitions here;
  PATH_ADD("/api/hello", drogon::Get);
  PATH_LIST_END
};
