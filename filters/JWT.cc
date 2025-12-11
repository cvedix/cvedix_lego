#include "JWT.h"
#include <jwt-cpp/jwt.h>
#include <json/json.h>

using namespace drogon;

void JWT::doFilter(const HttpRequestPtr &req,
                   FilterCallback &&fcb,
                   FilterChainCallback &&fccb)
{
    try
    {
        auto auth = req->getHeader("Authorization");

        if (auth.substr(0, 7) != "Bearer ")
            throw std::runtime_error("Invalid Authorization header");

        std::string token = auth.substr(7);

        auto decoded = jwt::decode(token);

        auto verifier =
            jwt::verify()
                .allow_algorithm(jwt::algorithm::hs256{"MY_SECRET_KEY"})
                .with_issuer("cvedix_backend");

        verifier.verify(decoded);

        req->getAttributes()->insert("username", decoded.get_subject());

        fccb(); // success
    }
    catch (const std::exception &e)
    {
        Json::Value err;
        err["error"] = e.what();

        auto resp = HttpResponse::newHttpJsonResponse(err);
        resp->setStatusCode(k401Unauthorized);
        fcb(resp);
    }
}
