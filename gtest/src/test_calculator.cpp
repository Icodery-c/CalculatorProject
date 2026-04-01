#include <gtest/gtest.h>
#include <stdexcept>
#include <climits>
#include "calculator.h"

class CalculatorTest : public ::testing::Test {
protected:
    Calculator calculator;
    Data data;
};

// Сложение
TEST_F(CalculatorTest, AdditionReturnsCorrectResult) {
    data.num1 = 5; data.num2 = 3; data.op = '+';
    EXPECT_EQ(calculator.calculate(data), 8);
}

TEST_F(CalculatorTest, AdditionOverflowThrows) {
    data.num1 = INT_MAX; data.num2 = 1; data.op = '+';
    EXPECT_THROW(calculator.calculate(data), std::overflow_error);
}

// Вычитание
TEST_F(CalculatorTest, SubtractionReturnsCorrectResult) {
    data.num1 = 5; data.num2 = 3; data.op = '-';
    EXPECT_EQ(calculator.calculate(data), 2);
}

TEST_F(CalculatorTest, SubtractionOverflowThrows) {
    data.num1 = INT_MIN; data.num2 = 1; data.op = '-';
    EXPECT_THROW(calculator.calculate(data), std::overflow_error);
}

// Умножение
TEST_F(CalculatorTest, MultiplicationReturnsCorrectResult) {
    data.num1 = 5; data.num2 = 3; data.op = '*';
    EXPECT_EQ(calculator.calculate(data), 15);
}

TEST_F(CalculatorTest, MultiplicationOverflowThrows) {
    data.num1 = INT_MAX; data.num2 = 2; data.op = '*';
    EXPECT_THROW(calculator.calculate(data), std::overflow_error);
}

// Деление
TEST_F(CalculatorTest, DivisionReturnsCorrectResult) {
    data.num1 = 6; data.num2 = 3; data.op = '/';
    EXPECT_EQ(calculator.calculate(data), 2);
}

TEST_F(CalculatorTest, DivisionByZeroThrows) {
    data.num1 = 5; data.num2 = 0; data.op = '/';
    EXPECT_THROW(calculator.calculate(data), std::runtime_error);
}

// Возведение в степень
TEST_F(CalculatorTest, PowerReturnsCorrectResult) {
    data.num1 = 2; data.num2 = 8; data.op = '^';
    EXPECT_EQ(calculator.calculate(data), 256);
}

TEST_F(CalculatorTest, PowerOverflowThrows) {
    data.num1 = INT_MAX; data.num2 = 2; data.op = '^';
    EXPECT_THROW(calculator.calculate(data), std::overflow_error);
}

// Факториал
TEST_F(CalculatorTest, FactorialReturnsCorrectResult) {
    data.num1 = 5; data.op = '!';
    EXPECT_EQ(calculator.calculate(data), 120);
}

TEST_F(CalculatorTest, FactorialOfZeroReturnsOne) {
    data.num1 = 0; data.op = '!';
    EXPECT_EQ(calculator.calculate(data), 1);
}

TEST_F(CalculatorTest, FactorialNegativeThrows) {
    data.num1 = -1; data.op = '!';
    EXPECT_THROW(calculator.calculate(data), std::runtime_error);
}

TEST_F(CalculatorTest, FactorialOverflowThrows) {
    data.num1 = 20; data.op = '!';
    EXPECT_THROW(calculator.calculate(data), std::overflow_error);
}

// Неизвестный оператор
TEST_F(CalculatorTest, UnknownOperatorThrows) {
    data.num1 = 5; data.num2 = 3; data.op = '?';
    EXPECT_THROW(calculator.calculate(data), std::logic_error);
}