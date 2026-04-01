#pragma once

#include "data.h"
#include <string>

class Printer {

    public:

        void printResult (int result);

        void printError (const std::string& msg);

        void printHelp ();

};
