#include "HelloController.h"

void HelloController::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
    auto path = req->path();
    std::string message;
    if (path == "/api/hello")
    {
        message = "Hello, World!";
    }
    auto resp = HttpResponse::newHttpResponse();
    resp->setBody(message);
    callback(resp);
}
