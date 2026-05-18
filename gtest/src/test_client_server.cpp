#include <gtest/gtest.h>
#include <nlohmann/json.hpp>
#include "client.h"
#include "test_server_helper.h"

using json = nlohmann::json;

class ClientServerTest : public ::testing::Test {
protected:
    static TestServer* server;

    static void SetUpTestSuite() {
        server = new TestServer();
    }

    static void TearDownTestSuite() {
        delete server;
        server = nullptr;
    }
};

TestServer* ClientServerTest::server = nullptr;

TEST_F(ClientServerTest, AdditionReturnsCorrectResult) {
    client::Client cli("localhost", 5555);
    std::string response = cli.sendRequest(R"({"num1":5, "num2":3, "op":"+"})");

    json j = json::parse(response);
    EXPECT_EQ(j["status"], 0);
    EXPECT_EQ(j["result"], 8);
}

TEST_F(ClientServerTest, MultiplicationReturnsCorrectResult) {
    client::Client cli("localhost", 5555);
    std::string response = cli.sendRequest(R"({"num1":6, "num2":7, "op":"*"})");

    json j = json::parse(response);
    EXPECT_EQ(j["status"], 0);
    EXPECT_EQ(j["result"], 42);
}

TEST_F(ClientServerTest, FactorialReturnsCorrectResult) {
    client::Client cli("localhost", 5555);
    std::string response = cli.sendRequest(R"({"num1":5, "op":"!"})");

    json j = json::parse(response);
    EXPECT_EQ(j["status"], 0);
    EXPECT_EQ(j["result"], 120);
}

TEST_F(ClientServerTest, DivisionByZeroReturnsError) {
    client::Client cli("localhost", 5555);
    std::string response = cli.sendRequest(R"({"num1":5, "num2":0, "op":"/"})");

    json j = json::parse(response);
    EXPECT_EQ(j["status"], 1);
    EXPECT_TRUE(j.contains("error"));
}

TEST_F(ClientServerTest, UnknownOperatorReturnsError) {
    client::Client cli("localhost", 5555);
    std::string response = cli.sendRequest(R"({"num1":5, "num2":3, "op":"?"})");

    json j = json::parse(response);
    EXPECT_EQ(j["status"], 1);
}

TEST_F(ClientServerTest, OverflowReturnsError) {
    client::Client cli("localhost", 5555);
    std::string response = cli.sendRequest(R"({"num1":2147483647, "num2":1, "op":"+"})");

    json j = json::parse(response);
    EXPECT_EQ(j["status"], 1);
}

TEST_F(ClientServerTest, CommutativeOperationHitsCache) {
    client::Client cli("localhost", 5555);

    // Первый запрос — посчитается и закешируется
    std::string r1 = cli.sendRequest(R"({"num1":100, "num2":200, "op":"+"})");
    json j1 = json::parse(r1);
    EXPECT_EQ(j1["result"], 300);

    // Второй запрос — обратный порядок, должен взяться из кеша
    std::string r2 = cli.sendRequest(R"({"num1":200, "num2":100, "op":"+"})");
    json j2 = json::parse(r2);
    EXPECT_EQ(j2["result"], 300);
}