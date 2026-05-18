#include "client.h"
#include "message_socket.h"

#include <boost/asio.hpp>
#include <memory>
#include <string>

namespace client {

using boost::asio::ip::tcp;

struct Client::Impl {
    boost::asio::io_context ioContext;
    std::string host;
    unsigned short port;

    Impl(const std::string& h, unsigned short p) : host(h), port(p) {}
};

Client::Client(const std::string& host, unsigned short port)
    : impl(std::make_unique<Impl>(host, port))
{}

Client::~Client() = default;

std::string Client::sendRequest(const std::string& request) {

    tcp::socket socket(impl->ioContext);

    // Резолвим адрес
    tcp::resolver resolver(impl->ioContext);
    auto endpoints = resolver.resolve(impl->host, std::to_string(impl->port));

    // Подключаемся
    boost::asio::connect(socket, endpoints);

    // Используем тот же протокол что и сервер
    protocol::MessageSocket conn(socket);
    conn.write(request);
    return conn.read();
}

}