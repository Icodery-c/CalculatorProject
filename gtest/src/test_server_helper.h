#pragma once

#include "runner.h"
#include <thread>
#include <chrono>
#include <atomic>

class TestServer {
    
    Runner runner;
    std::thread serverThread;
    std::atomic<bool> ready{false};

    public:
        TestServer() {
            serverThread = std::thread([this]() {
                ready = true;
                runner.run();
            });

            // Busy-wait пока сервер не будет готов (вместо sleep_for!)
            auto start = std::chrono::steady_clock::now();
            while (!ready) {
                if (std::chrono::steady_clock::now() - start > std::chrono::seconds(2)) {
                    throw std::runtime_error("Server failed to start");
                }
                std::this_thread::yield();
            }

            // Дополнительная небольшая пауза busy-wait для acceptor
            auto acceptorWait = std::chrono::steady_clock::now();
            while (std::chrono::steady_clock::now() - acceptorWait < std::chrono::milliseconds(100)) {
                std::this_thread::yield();
            }
        }

        ~TestServer() {
            runner.stop();
            if (serverThread.joinable()) {
                serverThread.join();
            }
        }

        TestServer(const TestServer&)            = delete;
        TestServer& operator=(const TestServer&) = delete;

        TestServer(TestServer&&)            = delete;
        TestServer& operator=(TestServer&&) = delete;

};