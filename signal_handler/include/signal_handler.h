#pragma once

#include <functional>
#include <memory>

namespace signal_handler {

class SignalHandler {

    struct Impl;
    std::unique_ptr<Impl> impl;

    public:
        SignalHandler();
        ~SignalHandler();

        SignalHandler(const SignalHandler&)            = delete;
        SignalHandler& operator=(const SignalHandler&) = delete;

        SignalHandler(SignalHandler&&)            = delete;
        SignalHandler& operator=(SignalHandler&&) = delete;

        // Регистрирует callback который будет вызван при получении сигнала
        void onShutdown(std::function<void()> callback);

        // Запускает обработку (блокирующий вызов — пускать в отдельном потоке)
        void run();

};

} 