#include "ServerApp.h"
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        ServerApp app;
        app.run(argc, argv);
        return 0;
    } catch (std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}
