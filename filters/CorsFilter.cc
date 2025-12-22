#include "CorsFilter.h"

void CorsFilter::doFilter(const HttpRequestPtr &req,
                          FilterCallback &&fcb,
                          FilterChainCallback &&fccb)
{
    // Get origin from request
    auto &origin = req->getHeader("Origin");

    // Create response for CORS
    auto resp = HttpResponse::newHttpResponse();

    // Set CORS headers
    if (!origin.empty())
    {
        resp->addHeader("Access-Control-Allow-Origin", origin);
    }
    else
    {
        resp->addHeader("Access-Control-Allow-Origin", "*");
    }

    resp->addHeader("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    resp->addHeader("Access-Control-Allow-Headers", "Content-Type, Authorization, X-Requested-With");
    resp->addHeader("Access-Control-Allow-Credentials", "true");
    resp->addHeader("Access-Control-Max-Age", "3600");

    // Handle OPTIONS preflight request
    if (req->method() == Options)
    {
        resp->setStatusCode(k200OK);
        fcb(resp);
        return;
    }

    // For non-OPTIONS requests, continue to next handler
    fccb();
}
