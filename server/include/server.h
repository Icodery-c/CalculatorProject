#pragma once

#include <string>
#include <memory>
#include <functional>

namespace server {

using RequestHandler = std::function<std::string(const std::string&)>;

class Server {

    struct Impl;
    std::unique_ptr<Impl> impl;

    public:

        Server(unsigned short port, RequestHandler handler);
        ~Server();

        Server(const Server&)            = delete;
        Server& operator=(const Server&) = delete;

        Server(Server&&)            = default;
        Server& operator=(Server&&) = default;

        void run();
        void stop();    
};

} 