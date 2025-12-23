#include "GetVideoList.h"

void GetVideoList::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    json resp;
    resp["media"] = json::array();
    std::string list_path = "/opt/cvedix/media";
    for (std::filesystem::directory_iterator it(list_path);; ++it)
    {
        json item;
        if (it == std::filesystem::directory_iterator{})
            break;
        const auto &entry = *it;
        item["name"] = entry.path().filename().string();
        item["size"] = std::filesystem::file_size(entry.path());
        resp["media"].push_back(item);
    }
    auto httpResp = HttpResponse::newHttpResponse();
    httpResp->setContentTypeCode(CT_APPLICATION_JSON);
    httpResp->setBody(resp.dump());
    callback(httpResp);
}

void DeleteVideo::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    json jsonData = json::parse(req->body());
    std::string video_name = jsonData.value("video_name", "");
    if (video_name == "vehicle_stop.mp4" || video_name == "face_person.mp4" || video_name == "vehicle_count.mp4" ||
        video_name == "pose.mp4" || video_name == "face.mp4" || video_name == "vid-1.mp4")
    {
        json res;
        res["status"] = "ERROR";
        res["message"] = "Cannot delete default videos";
        auto httpResp = HttpResponse::newHttpResponse();
        httpResp->setContentTypeCode(CT_APPLICATION_JSON);
        httpResp->setBody(res.dump());
        callback(httpResp);
        return;
    }

    std::string video_path = "/opt/cvedix/media/" + video_name;
    if (std::filesystem::exists(video_path))
    {
        std::filesystem::remove(video_path);
        json res;
        res["status"] = "SUCCESS";
        res["message"] = "Video deleted successfully";
        auto httpResp = HttpResponse::newHttpResponse();
        httpResp->setContentTypeCode(CT_APPLICATION_JSON);
        httpResp->setBody(res.dump());
        callback(httpResp);
    }
}