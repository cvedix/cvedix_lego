#include "LegoGet.h"

using json = nlohmann::ordered_json;

void LegoGet::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    std::ifstream file("../JSON/lego_config.json");
    json jsonData;
    file >> jsonData;
    auto resp = HttpResponse::newHttpResponse();
    resp->setContentTypeCode(CT_APPLICATION_JSON);
    resp->setBody(jsonData.dump(4));
    callback(resp);
}
