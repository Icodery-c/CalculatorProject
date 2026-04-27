#pragma once

#include <string>
#include <memory>

namespace logger {

class Logger {

    class Impl;
    std::unique_ptr<Impl> impl; 

    public:

        Logger();
        ~Logger() = default;

        Logger(const Logger&) = delete;
        Logger& operator=(const Logger&) = delete;

        static Logger& Initialize ();

        void trace (const std::string& msg);
        void debug (const std::string& msg);
        void info (const std::string& msg);
        void warn (const std::string& msg);
        void error (const std::string& msg);
        void critical (const std::string& msg);


};

}