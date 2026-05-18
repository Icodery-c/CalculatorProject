#include "message_socket.h"

namespace protocol {

MessageSocket::MessageSocket(boost::asio::ip::tcp::socket& s) : socket(s) {}

std::string MessageSocket::read() {
    boost::asio::streambuf buffer;
    boost::asio::read_until(socket, buffer, '\n');

    std::istream input(&buffer);
    std::string message;
    std::getline(input, message);
    return message;
}

void MessageSocket::write(const std::string& message) {
    std::string framed = message + '\n';
    boost::asio::write(socket, boost::asio::buffer(framed));
}

} 