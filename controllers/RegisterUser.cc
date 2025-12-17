#include "RegisterUser.h"

inline std::string sha256(const std::string &str)
{
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256(reinterpret_cast<const unsigned char *>(str.c_str()), str.size(), hash);

    std::stringstream ss;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];

    return ss.str();
}

void RegisterUser::asyncHandleHttpRequest(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback)
{
    // write your application logic here
    json jsonData = json::parse(req->body());

    const json &body = jsonData;

    if (!body.contains("username") || !body.contains("password"))
    {
        json res;
        res["status"] = "ERROR";
        res["message"] = "username and password are required";

        auto resp = HttpResponse::newHttpJsonResponse(res.dump());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    std::string username = body.value("username", "");
    std::string password_plain = body.value("password", "");
    std::string password_hashed_input = sha256(password_plain);
    std::string email = body.value("email", "");

    if (username.empty() || password_plain.empty())
    {
        json res;
        res["status"] = "ERROR";
        res["message"] = "username or password empty";

        auto resp = HttpResponse::newHttpJsonResponse(res.dump());
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    auto db = app().getDbClient();
    db->execSqlAsync(
        "INSERT INTO users(username, password, email) VALUES($1, $2, $3)",
        // SUCCESS
        [callback](const orm::Result &)
        {
            json res;
            res["status"] = "OK";
            res["message"] = "User registered successfully";

            auto resp = HttpResponse::newHttpJsonResponse(res.dump());
            callback(resp);
        },
        // ERROR
        [callback](const orm::DrogonDbException &e)
        {
            json res;
            res["status"] = "ERROR";
            res["message"] = e.base().what();

            auto resp = HttpResponse::newHttpJsonResponse(res.dump());
            resp->setStatusCode(k500InternalServerError);
            callback(resp);
        },
        username,
        password_hashed_input,
        email);
}
