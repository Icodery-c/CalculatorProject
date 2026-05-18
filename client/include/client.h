#pragma once

#include <string>
#include <memory>

namespace client {

class Client {

    struct Impl;
    std::unique_ptr<Impl> impl;

    public:

        Client(const std::string& host, unsigned short port);
        ~Client();

        Client(const Client&)            = delete;
        Client& operator=(const Client&) = delete;

        Client(Client&&)            = default;
        Client& operator=(Client&&) = default;

        std::string sendRequest(const std::string& request);

};

}