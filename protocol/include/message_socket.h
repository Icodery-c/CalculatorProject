#pragma once

#include <string>
#include <boost/asio.hpp>

namespace protocol {

class MessageSocket {

    boost::asio::ip::tcp::socket& socket;

    public:
        MessageSocket(boost::asio::ip::tcp::socket& s);
        ~MessageSocket() = default;

        MessageSocket(const MessageSocket&)            = delete;
        MessageSocket& operator=(const MessageSocket&) = delete;

        MessageSocket(MessageSocket&&)            = delete;
        MessageSocket& operator=(MessageSocket&&) = delete;

        std::string read();
        void write(const std::string& message);

};

}