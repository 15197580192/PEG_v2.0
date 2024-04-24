#include <crow.h>

int main()
{
    crow::SimpleApp app;
    // 测试
    CROW_ROUTE(app, "/test")
    ([]()
     { return "Hello world"; });
    app.port(18888).multithreaded().run();
}

----------------------------136210691946286116791892
Content-Disposition: form-data; name="b"

123
----------------------------136210691946286116791892
Content-Disposition: form-data; name="c"

321
----------------------------136210691946286116791892
Content-Disposition: form-data; name="d"

123456
