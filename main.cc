#include <drogon/drogon.h>

int main()
{
    drogon::app()
        .loadConfigFile("../config.json")
        .addListener("0.0.0.0", 8090)
        .run();

    return 0;
}
