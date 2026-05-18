#include "client.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " '<json-request>'" << std::endl;
        return 1;
    }

    try {
        client::Client cli("localhost", 5555);
        std::string response = cli.sendRequest(argv[1]);
        std::cout << response << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}