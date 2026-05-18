#include "server.h"
#include "message_socket.h"

#include <boost/asio.hpp>
#include <iostream>
#include <memory>
#include <atomic>
#include <functional>

namespace server {

using boost::asio::ip::tcp;

struct Server::Impl {
    boost::asio::io_context ioContext;
    tcp::acceptor acceptor;
    RequestHandler handler;
    std::atomic<bool> running{false};  // ← было bool

    Impl(unsigned short port, RequestHandler h)
        : acceptor(ioContext, tcp::endpoint(tcp::v4(), port))
        , handler(std::move(h))
    {}
};

Server::Server(unsigned short port, RequestHandler handler)
    : impl(std::make_unique<Impl>(port, std::move(handler)))
{}

Server::~Server() = default;

void Server::run() {
    impl->running = true;

    std::function<void(const boost::system::error_code&, tcp::socket)> handler;
    handler = [this, &handler](const boost::system::error_code& ec, tcp::socket socket) {
        if (!impl->running) {
            return;
        }

        if (!ec) {
            try {
                protocol::MessageSocket conn(socket);
                std::string request = conn.read();
                std::string response = impl->handler(request);
                conn.write(response);
            } catch (const std::exception& e) {
                std::cerr << "Connection error: " << e.what() << std::endl;
            }
        }

        if (impl->running) {
            impl->acceptor.async_accept(handler);
        }
    };

    impl->acceptor.async_accept(handler);
    impl->ioContext.run();
}

void Server::stop() {
    impl->running = false;
    boost::asio::post(impl->ioContext, [this]() {
        impl->acceptor.close();
        impl->ioContext.stop();
    });
}

}