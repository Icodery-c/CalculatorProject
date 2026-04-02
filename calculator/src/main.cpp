#include "runner.h"
#include <iostream>

int main(int argc, char** argv) {
    try {
        Runner runner;
        runner.run(argc, argv);
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}