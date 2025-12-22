#include <drogon/drogon.h>

int main()
{
    // Register CORS handler for all requests
    drogon::app().registerPostHandlingAdvice(
        [](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
            // Get origin from request
            auto &origin = req->getHeader("Origin");

            // Set CORS headers
            if (!origin.empty()) {
                resp->addHeader("Access-Control-Allow-Origin", origin);
            } else {
                resp->addHeader("Access-Control-Allow-Origin", "*");
            }

            resp->addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
            resp->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With");
            resp->addHeader("Access-Control-Allow-Credentials", "true");
            resp->addHeader("Access-Control-Max-Age", "3600");
        }
    );

    // Handle OPTIONS preflight requests before routing
    drogon::app().registerPreRoutingAdvice(
        [](const drogon::HttpRequestPtr &req,
           drogon::AdviceCallback &&acb,
           drogon::AdviceChainCallback &&accb) {
            if (req->method() == drogon::Options) {
                auto resp = drogon::HttpResponse::newHttpResponse();

                auto &origin = req->getHeader("Origin");
                if (!origin.empty()) {
                    resp->addHeader("Access-Control-Allow-Origin", origin);
                } else {
                    resp->addHeader("Access-Control-Allow-Origin", "*");
                }

                resp->addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
                resp->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With");
                resp->addHeader("Access-Control-Allow-Credentials", "true");
                resp->addHeader("Access-Control-Max-Age", "3600");
                resp->setStatusCode(drogon::k200OK);

                acb(resp);
                return;
            }
            accb();
        }
    );

    drogon::app()
        .loadConfigFile("../config.json")
        .addListener("0.0.0.0", 8090)
        .run();
    return 0;
}
