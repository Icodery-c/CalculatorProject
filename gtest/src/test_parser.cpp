#include <gtest/gtest.h>
#include <stdexcept>
#include "parser.h"

static Data parseJson(const std::string& json) {
    const char* argv[] = {"calculator", json.c_str()};
    Parser parser;
    return parser.parse(2, const_cast<char**>(argv));
}

// Корректный парсинг
TEST(ParserTest, ParsesAdditionCorrectly) {
    Data data = parseJson(R"({"num1":5,"num2":3,"op":"+"})");
    EXPECT_EQ(data.num1, 5);
    EXPECT_EQ(data.num2, 3);
    EXPECT_EQ(data.op, '+');
}

TEST(ParserTest, ParsesFactorialCorrectly) {
    Data data = parseJson(R"({"num1":5,"op":"!"})");
    EXPECT_EQ(data.num1, 5);
    EXPECT_EQ(data.op, '!');
}

TEST(ParserTest, ParsesHelpCorrectly) {
    Data data = parseJson(R"({"op":"h"})");
    EXPECT_EQ(data.op, 'h');
}

TEST(ParserTest, ParsesNegativeNumbersCorrectly) {
    Data data = parseJson(R"({"num1":-5,"num2":-3,"op":"+"})");
    EXPECT_EQ(data.num1, -5);
    EXPECT_EQ(data.num2, -3);
}

// Отсутствие аргументов
TEST(ParserTest, NoArgumentsThrows) {
    const char* argv[] = {"calculator"};
    Parser parser;
    EXPECT_THROW(parser.parse(1, const_cast<char**>(argv)), std::runtime_error);
}

// Отсутствие обязательных полей
TEST(ParserTest, MissingOpThrows) {
    EXPECT_THROW(parseJson(R"({"num1":5,"num2":3})"), std::runtime_error);
}

TEST(ParserTest, MissingNum1Throws) {
    EXPECT_THROW(parseJson(R"({"num2":3,"op":"+"})"), std::runtime_error);
}

TEST(ParserTest, MissingNum2ForBinaryOpThrows) {
    EXPECT_THROW(parseJson(R"({"num1":5,"op":"+"})"), std::runtime_error);
}

// Переполнение типов
TEST(ParserTest, Num1OverflowThrows) {
    EXPECT_THROW(parseJson(R"({"num1":99999999999,"num2":3,"op":"+"})"), std::runtime_error);
}

TEST(ParserTest, Num1FloatThrows) {
    EXPECT_THROW(parseJson(R"({"num1":3.14,"num2":3,"op":"+"})"), std::runtime_error);
}

// Невалидный JSON
TEST(ParserTest, InvalidJsonThrows) {
    EXPECT_THROW(parseJson("not a json"), std::exception);
}