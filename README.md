# Cvedix Lego

Một giải pháp nền tảng low-code giúp kết nối công nghệ AI (như các thuật toán học sâu) với các ứng dụng thực tế trong công nghiệp. Nền tảng này giúp đơn giản hóa việc tích hợp các hệ thống như Robot Operating System (ROS), cho phép người dùng thiết kế quy trình làm việc bằng ngôn ngữ lập trình dạng khối, giảm thiểu nhu cầu lập trình thủ công.

Một số đặc điểm nổi bật của CvedixLego:

- Giao diện kéo-thả lập trình hóa các quy trình xử lý.
- Kết nối được với nhiều thiết bị ngoại vi như Modbus/TCP, Arduino I/O, cổng Serial, camera IP, webcam...
- Lưu trữ, chú thích dữ liệu phục vụ huấn luyện AI.
- Hỗ trợ huấn luyện mô hình AI bằng cả CPU/GPU.
- Truyền dữ liệu tới các hệ thống khác thông qua MQTT hoặc REST API, hoặc phát trực tuyến bằng RTSP.
- Tạo giao diện người dùng cơ bản với các thành phần như nút bấm, hình ảnh, chữ led.
- Thiết kế các quy trình xử lý song song hoặc tuần tự.
- Tương thích đa hệ điều hành, dễ dàng sử dụng cho nhiều đối tượng.

Tóm lại, CvedixLego là nền tảng công nghệ cốt lõi giúp doanh nghiệp và ngành công nghiệp triển khai, ứng dụng AI vào tự động hóa, nhận diện và điều khiển thiết bị một cách dễ dàng và hiệu quả.

---
## 🎯 Tạo Project
### Tạo project mới
```bash
# Di chuyển đến thư mục làm việc
cd /path/to/workspace

# Tạo project mới
drogon_ctl create project your_project_name

# Di chuyển vào project
cd your_project_name
```

### Khởi tạo build
```bash
mkdir build
cd build
cmake ..
make
```






---

## 📁 Cấu trúc thư mục

```
your_project_name/
├── controllers/      # HTTP API handlers
├── filters/          # Middleware (auth, validation, logging)
├── models/           # Database ORM models
├── plugins/          # Background services
├── views/            # HTML templates
├── config.json       # Server configuration
├── main.cc           # Entry point
└── CMakeLists.txt    # Build configuration






```

## 🔧 Drogon CLI Commands

| Command | Description |
|---------|-------------|
| `drogon_ctl create project <name>` | Tạo project mới |
| `drogon_ctl create controller -s <name>` | Tạo Simple Controller |
| `drogon_ctl create controller -h <name>` | Tạo HTTP Controller |
| `drogon_ctl create filter <name>` | Tạo Filter |
| `drogon_ctl create model <folder>` | Tạo ORM models từ DB |
| `drogon_ctl create view <name>` | Tạo View template |
| `drogon_ctl create plugin <name>` | Tạo Plugin |




---


## 🎮 Controllers
**Nơi xử lý HTTP API requests**

### Tạo Simple Controller (một endpoint đơn giản)
```bash
drogon_ctl create controller -s YourControllerName
```

**Ví dụ: Simple Controller**
```cpp
class Api : public HttpSimpleController<Api, true>
{
public:
    void asyncHandleHttpRequest(
        const HttpRequestPtr &req,
        std::function<void(const HttpResponsePtr &)> &&callback
    ) override;

    PATH_LIST_BEGIN
    PATH_ADD("/api/hello", drogon::Get);
    PATH_ADD("/api/data", drogon::Post);
    PATH_LIST_END
};
```

### Tạo HTTP Controller (nhiều methods trong một class)
```bash
drogon_ctl create controller -h UserController
```

**Ví dụ: HTTP Controller**
```cpp
class UserController : public HttpController<UserController>
{
public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(UserController::login, "/login", Post);
    ADD_METHOD_TO(UserController::getUser, "/user/{1}", Get);
    ADD_METHOD_TO(UserController::updateUser, "/user/{1}", Put);
    ADD_METHOD_TO(UserController::deleteUser, "/user/{1}", Delete);
    METHOD_LIST_END

    void login(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback);
    void getUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, int userId);
    void updateUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, int userId);
    void deleteUser(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, int userId);
};
```

**📌 Lưu ý:**
- Template parameter thứ 2 phải là `true` để auto-register
- Class name không được trùng với HTTP methods (Get, Post, Put, Delete)











---

## 🛡️ Filters
**Middleware để xử lý auth, validation, logging...**

### Tạo Filter
```bash
drogon_ctl create filter FilterName
```

**Ví dụ: Authentication Filter**
```cpp
class AuthFilter : public HttpFilter<AuthFilter>
{
public:
    void doFilter(
        const HttpRequestPtr &req,
        FilterCallback &&fcb,
        FilterChainCallback &&fccb
    ) override
    {
        std::string token = req->getHeader("Authorization");
        
        if (!token.empty() && token == "Bearer valid-token")
        {
            fccb(); // ✅ Cho phép tiếp tục
        }
        else
        {
            // ❌ Chặn request
            Json::Value json;
            json["error"] = "Unauthorized";
            auto resp = HttpResponse::newHttpJsonResponse(json);
            resp->setStatusCode(k401Unauthorized);
            fcb(resp);
        }
    }
};
```

### Sử dụng Filter trong Controller
```cpp
PATH_ADD("/api/protected", "AuthFilter", drogon::Get);
```

**Các use case phổ biến:**
- ✅ Auth token validation
- ✅ JWT verification
- ✅ Request logging
- ✅ CORS headers
- ✅ Rate limiting
- ✅ Body validation














---

## 💾 Models
**ORM để làm việc với Database**

### Cấu hình Database trong config.json
```json
{
    "db_clients": [
        {
            "name": "default",
            "rdbms": "postgresql",
            "host": "127.0.0.1",
            "port": 5432,
            "dbname": "mydb",
            "user": "postgres",
            "password": "password",
            "connection_number": 3
        }
    ]
}
```

### Tạo Model từ Database
```bash
# Tạo model từ database table
drogon_ctl create model models
```

File `models/model.json`:
```json
{
    "rdbms": "postgresql",
    "host": "127.0.0.1",
    "port": 5432,
    "dbname": "mydb",
    "user": "postgres",
    "password": "password",
    "tables": ["users", "posts", "comments"]
}
```

### Sử dụng ORM
```cpp
auto db = drogon::app().getDbClient();

// SELECT
auto result = db->execSqlSync("SELECT * FROM users WHERE id = $1", userId);

// INSERT
db->execSqlSync("INSERT INTO users (name, email) VALUES ($1, $2)", "John", "john@example.com");
```
















---

## 🔌 Plugins
**Background services chạy song song với server**

### Tạo Plugin
```bash
drogon_ctl create plugin PluginName
```

**Ví dụ: Redis Client Plugin**
```cpp
class RedisPlugin : public Plugin<RedisPlugin>
{
public:
    void initAndStart(const Json::Value &config) override
    {
        LOG_INFO << "Redis Plugin started";
        // Khởi tạo Redis connection
    }

    void shutdown() override
    {
        LOG_INFO << "Redis Plugin shutdown";
        // Cleanup
    }
};
```

**Các use case:**
- ✅ Redis/Memcached client
- ✅ Message queue consumer (Kafka, RabbitMQ)
- ✅ Scheduled tasks
- ✅ Cache management
- ✅ Logging service
- ✅ WebSocket manager

















---

## 🎨 Views
**Template HTML cho server-side rendering**

### Tạo View
```bash
drogon_ctl create view ViewName
```

Drogon hỗ trợ template engine CSP (C++ Server Pages).

**Ví dụ:**
```html
<!DOCTYPE html>
<html>
<head>
    <title><%c++ $$<<"Hello"; %></title>
</head>
<body>
    <h1>User: <%c++ $$<<get<std::string>("username"); %></h1>
</body>
</html>
```














---

## ⚙️ Configuration
**File: `config.json`**

```json
{
    "listeners": [
        {
            "address": "0.0.0.0",
            "port": 5555,
            "https": false
        }
    ],
    "threads_num": 16,
    "log": {
        "log_path": "./logs",
        "logfile_base_name": "drogon",
        "log_size_limit": 100000000,
        "log_level": "INFO"
    },
    "app": {
        "max_connections": 100000,
        "document_root": "./",
        "upload_path": "uploads",
        "session_timeout": 1200,
        "enable_session": true,
        "enable_gzip": true
    },
    "db_clients": []
}
```













---

## 🏗️ Build & Run

### Build project
```bash
cd build
cmake ..
make -j4
```








### Chạy server
```bash
./your_project_name
```








### Test với curl
```bash
# GET request
curl http://localhost:5555/api/hello

# POST JSON
curl -X POST http://localhost:5555/api/data \
  -H "Content-Type: application/json" \
  -d '{"key":"value"}'

# File upload
curl -X POST http://localhost:5555/api/upload \
  -F "file=@image.jpg"
```

---




