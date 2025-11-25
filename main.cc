#include <drogon/drogon.h>
using namespace drogon;

int main() {
    //Set HTTP listener address and port
    app().addListener("0.0.0.0", 5555);

    //Run HTTP framework
    app().run();
    return 0;
}
