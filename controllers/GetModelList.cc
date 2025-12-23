#include "GetModelList.h"

void GetModelList::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    json resp;
    resp["models"] = json::array();
    std::string list_path = "/opt/cvedix/model";
    for (std::filesystem::directory_iterator it(list_path);; ++it)
    {
        json item;
        if (it == std::filesystem::directory_iterator{})
            break;
        const auto &entry = *it;
        item["name"] = entry.path().filename().string();
        item["size"] = std::filesystem::file_size(entry.path());
        resp["models"].push_back(item);
    }
    auto httpResp = HttpResponse::newHttpResponse();
    httpResp->setContentTypeCode(CT_APPLICATION_JSON);
    httpResp->setBody(resp.dump());
    callback(httpResp);
}

void DeleteModel::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    json jsonData = json::parse(req->body());
    std::string model_name = jsonData.value("model_name", "");
    if (model_name == "yolov3-tiny-2022-0721_best.weights" || model_name == "yolov3-tiny-2022-0721.cfg" || model_name == "yolov3_tiny_5classes.txt")
    {
        json res;
        res["status"] = "ERROR";
        res["message"] = "Cannot delete default models";
        auto httpResp = HttpResponse::newHttpResponse();
        httpResp->setContentTypeCode(CT_APPLICATION_JSON);
        httpResp->setBody(res.dump());
        callback(httpResp);
        return;
    }
    std::string model_path = "/opt/cvedix/model/" + model_name;
    if (std::filesystem::exists(model_path))
    {
        std::filesystem::remove(model_path);
        json res;
        res["status"] = "SUCCESS";
        res["message"] = "Model deleted successfully";
        auto httpResp = HttpResponse::newHttpResponse();
        httpResp->setContentTypeCode(CT_APPLICATION_JSON);
        httpResp->setBody(res.dump());
        callback(httpResp);
    }
}