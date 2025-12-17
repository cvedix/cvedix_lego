#pragma once

#include <drogon/HttpSimpleController.h>
#include <nlohmann/json.hpp>
#include <openssl/sha.h>
#include <sstream>
#include <iomanip>
#include <string>

using json = nlohmann::json;
using namespace drogon;

class RegisterUser : public drogon::HttpSimpleController<RegisterUser>
{
public:
  void asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) override;
  PATH_LIST_BEGIN
  PATH_ADD("/lego/register", Post);
  PATH_LIST_END
};
