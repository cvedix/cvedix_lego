#include "LoginUser.h"

inline std::string sha256(const std::string &str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char *>(str.c_str()), str.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

    return ss.str();
}

void LoginUser::asyncHandleHttpRequest(const HttpRequestPtr &req,
                                       std::function<void(const HttpResponsePtr &)> &&callback)
{
    json jsonData;
    jsonData = json::parse(req->body());

    std::string username = jsonData.value("username", "");
    std::string password_plain = jsonData.value("password", "");
    std::string password_hashed_input = sha256(password_plain);

    if (username.empty() || password_plain.empty())
    {
        json res;
        res["status"] = "ERROR";
        res["message"] = "username and password required";
        callback(HttpResponse::newHttpJsonResponse(res.dump(4)));
        return;
    }

    auto db = app().getDbClient();
    if (!db)
    {
        json res;
        res["status"] = "ERROR";
        res["message"] = "Database not available";
        callback(HttpResponse::newHttpJsonResponse(res.dump(4)));
        return;
    }

    db->execSqlAsync(
        "SELECT password FROM users WHERE username=$1",
        [callback, password_hashed_input](const orm::Result &r)
        {
            json res;
            if (r.size() == 0)
            {
                res["status"] = "ERROR";
                res["message"] = "User not found";
                callback(HttpResponse::newHttpJsonResponse(res.dump(4)));
                return;
            }

            std::string password_hash_db = r[0]["password"].as<std::string>();

            if (password_hashed_input == password_hash_db)
            {
                res["status"] = "OK";
                res["message"] = "Login successful";
            }
            else
            {
                res["status"] = "ERROR";
                res["message"] = "Wrong password";
            }

            callback(HttpResponse::newHttpJsonResponse(res.dump(4)));
        },
        [callback](const orm::DrogonDbException &e)
        {
            json res;
            res["status"] = "ERROR";
            res["message"] = e.base().what();
            callback(HttpResponse::newHttpJsonResponse(res.dump(4)));
        },
        username);
}
