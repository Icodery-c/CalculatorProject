#include <gtest/gtest.h>
#include <stdexcept>
#include "checker.h"

class CheckerTest : public ::testing::Test {
protected:
    Checker checker;
    Data data;
};

TEST_F(CheckerTest, ValidAdditionDoesNotThrow) {
    data.num1 = 5; data.num2 = 3; data.op = Operation::Add;
    EXPECT_NO_THROW(checker.check(data));
}

TEST_F(CheckerTest, ValidSubtractionDoesNotThrow) {
    data.num1 = 5; data.num2 = 3; data.op = Operation::Subtract;
    EXPECT_NO_THROW(checker.check(data));
}

TEST_F(CheckerTest, ValidMultiplicationDoesNotThrow) {
    data.num1 = 5; data.num2 = 3; data.op = Operation::Multiply;
    EXPECT_NO_THROW(checker.check(data));
}

TEST_F(CheckerTest, ValidDivisionDoesNotThrow) {
    data.num1 = 6; data.num2 = 3; data.op = Operation::Divide;
    EXPECT_NO_THROW(checker.check(data));
}

TEST_F(CheckerTest, ValidPowerDoesNotThrow) {
    data.num1 = 2; data.num2 = 8; data.op = Operation::Power;
    EXPECT_NO_THROW(checker.check(data));
}

TEST_F(CheckerTest, ValidFactorialDoesNotThrow) {
    data.num1 = 5; data.op = Operation::Factorial;
    EXPECT_NO_THROW(checker.check(data));
}

// TEST_F(CheckerTest, UnknownOperatorThrows) {
//     data.num1 = 5; data.num2 = 3; data.op = '?';
//     EXPECT_THROW(checker.check(data), std::runtime_error);
// }

// TEST_F(CheckerTest, LetterOperatorThrows) {
//     data.num1 = 5; data.num2 = 3; data.op = 'x';
//     EXPECT_THROW(checker.check(data), std::runtime_error);
// }