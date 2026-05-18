#include <gtest/gtest.h>
#include <stdexcept>
#include "parser.h"

static Data parseJson(const std::string& json) {
    Parser parser;
    return parser.parse(json);
}

TEST(ParserTest, ParsesAdditionCorrectly) {
    Data data = parseJson(R"({"num1":5,"num2":3,"op":"+"})");
    EXPECT_EQ(data.num1, 5);
    EXPECT_EQ(data.num2, 3);
    EXPECT_EQ(data.op, Operation::Add);
}

TEST(ParserTest, ParsesFactorialCorrectly) {
    Data data = parseJson(R"({"num1":5,"op":"!"})");
    EXPECT_EQ(data.num1, 5);
    EXPECT_EQ(data.op, Operation::Factorial);
}

TEST(ParserTest, ParsesNegativeNumbersCorrectly) {
    Data data = parseJson(R"({"num1":-5,"num2":-3,"op":"+"})");
    EXPECT_EQ(data.num1, -5);
    EXPECT_EQ(data.num2, -3);
}

TEST(ParserTest, EmptyStringThrows) {
    Parser parser;
    EXPECT_THROW(parser.parse(""), std::runtime_error);
}

TEST(ParserTest, MissingOpThrows) {
    EXPECT_THROW(parseJson(R"({"num1":5,"num2":3})"), std::runtime_error);
}

TEST(ParserTest, MissingNum1Throws) {
    EXPECT_THROW(parseJson(R"({"num2":3,"op":"+"})"), std::runtime_error);
}

TEST(ParserTest, MissingNum2ForBinaryOpThrows) {
    EXPECT_THROW(parseJson(R"({"num1":5,"op":"+"})"), std::runtime_error);
}

TEST(ParserTest, Num1OverflowThrows) {
    EXPECT_THROW(parseJson(R"({"num1":99999999999,"num2":3,"op":"+"})"), std::runtime_error);
}

TEST(ParserTest, Num1FloatThrows) {
    EXPECT_THROW(parseJson(R"({"num1":3.14,"num2":3,"op":"+"})"), std::runtime_error);
}

TEST(ParserTest, InvalidJsonThrows) {
    EXPECT_THROW(parseJson("not a json"), std::exception);
}

TEST(ParserTest, UnknownOperatorThrows) {
    EXPECT_THROW(parseJson(R"({"num1":5,"num2":3,"op":"?"})"), std::invalid_argument);
}