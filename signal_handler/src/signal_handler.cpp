#include "signal_handler.h"

#include <boost/asio.hpp>
#include <memory>

namespace signal_handler {

struct SignalHandler::Impl {
    boost::asio::io_context ioContext;
    boost::asio::signal_set signals;
    std::function<void()> shutdownCallback;

    Impl() : signals(ioContext, SIGINT, SIGTERM) {}
};

SignalHandler::SignalHandler() : impl(std::make_unique<Impl>()) {}

SignalHandler::~SignalHandler() = default;

void SignalHandler::onShutdown(std::function<void()> callback) {
    impl->shutdownCallback = std::move(callback);
}

void SignalHandler::run() {

    impl->signals.async_wait(
        [this](const boost::system::error_code& ec, int signal_number) {
            if (!ec && impl->shutdownCallback) {
                impl->shutdownCallback();
            }
        }
    );

    impl->ioContext.run();
}

} 