#pragma once

#include <drogon/HttpSimpleController.h>
#include <nlohmann/json.hpp>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>

using json = nlohmann::json;
using namespace drogon;

class LoginUser : public drogon::HttpSimpleController<LoginUser>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  PATH_ADD("/lego/login", Post);
  PATH_LIST_END
};
