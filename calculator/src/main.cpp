#include "runner.h"
#include "signal_handler.h"
#include "logger.h"

#include <iostream>
#include <thread>

int main() {
    try {
        auto& log = logger::Logger::Initialize();
        log.info("Starting calculator service");

        Runner runner;
        signal_handler::SignalHandler signals;

        // При получении SIGTERM/SIGINT — останавливаем сервер
        signals.onShutdown([&runner, &log]() {
            log.info("Shutdown signal received");
            runner.stop();
        });

        // Поток 1: обработка сигналов
        std::thread signalThread([&signals]() {
            signals.run();
        });

        // Поток 2 (главный): обработка сетевых запросов
        runner.run();

        // Ждём завершения потока сигналов
        if (signalThread.joinable()) {
            signalThread.join();
        }

        log.info("Service stopped");
    }
    catch (const std::exception& e) {
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}