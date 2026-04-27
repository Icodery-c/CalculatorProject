#include <gtest/gtest.h>
#include <stdexcept>
#include "cache.h"

class CacheTest : public ::testing::Test {
protected:
    Cache cache;
    Data data;
};

// Пустой кеш — не содержит ключей
TEST_F(CacheTest, EmptyCacheDoesNotContainKey) {
    EXPECT_FALSE(cache.contains("5+3"));
}

// Добавление и проверка наличия
TEST_F(CacheTest, PutAndContainsWorks) {
    cache.put("5+3", 8);
    EXPECT_TRUE(cache.contains("5+3"));
}

// Получение значения
TEST_F(CacheTest, GetReturnsCorrectValue) {
    cache.put("5+3", 8);
    EXPECT_EQ(cache.get("5+3"), 8);
}

// Получение несуществующего ключа бросает исключение
TEST_F(CacheTest, GetNonExistentKeyThrows) {
    EXPECT_THROW(cache.get("missing"), std::runtime_error);
}

// Перезапись значения
TEST_F(CacheTest, PutOverwritesExistingValue) {
    cache.put("5+3", 8);
    cache.put("5+3", 99);
    EXPECT_EQ(cache.get("5+3"), 99);
}

// Ключ для сложения — коммутативный
TEST_F(CacheTest, MakeKeyAdditionIsCommutative) {
    data.num1 = 5; data.num2 = 3; data.op = Operation::Add;
    std::string key1 = Cache::makeKey(data);

    data.num1 = 3; data.num2 = 5; data.op = Operation::Add;
    std::string key2 = Cache::makeKey(data);

    EXPECT_EQ(key1, key2);
}

// Ключ для умножения — коммутативный
TEST_F(CacheTest, MakeKeyMultiplicationIsCommutative) {
    data.num1 = 5; data.num2 = 3; data.op = Operation::Multiply;
    std::string key1 = Cache::makeKey(data);

    data.num1 = 3; data.num2 = 5; data.op = Operation::Multiply;
    std::string key2 = Cache::makeKey(data);

    EXPECT_EQ(key1, key2);
}

// Ключ для вычитания — НЕ коммутативный
TEST_F(CacheTest, MakeKeySubtractionIsNotCommutative) {
    data.num1 = 5; data.num2 = 3; data.op = Operation::Subtract;
    std::string key1 = Cache::makeKey(data);

    data.num1 = 3; data.num2 = 5; data.op = Operation::Subtract;
    std::string key2 = Cache::makeKey(data);

    EXPECT_NE(key1, key2);
}

// Ключ для деления — НЕ коммутативный
TEST_F(CacheTest, MakeKeyDivisionIsNotCommutative) {
    data.num1 = 6; data.num2 = 3; data.op = Operation::Divide;
    std::string key1 = Cache::makeKey(data);

    data.num1 = 3; data.num2 = 6; data.op = Operation::Divide;
    std::string key2 = Cache::makeKey(data);

    EXPECT_NE(key1, key2);
}

// Ключ для факториала — только num1
TEST_F(CacheTest, MakeKeyFactorialUsesOnlyNum1) {
    data.num1 = 5; data.op = Operation::Factorial;
    std::string key = Cache::makeKey(data);

    EXPECT_EQ(key, "5!");
}

// Разные операции дают разные ключи
TEST_F(CacheTest, MakeKeyDifferentOperationsGiveDifferentKeys) {
    data.num1 = 5; data.num2 = 3;

    data.op = Operation::Add;
    std::string keyAdd = Cache::makeKey(data);

    data.op = Operation::Multiply;
    std::string keyMul = Cache::makeKey(data);

    EXPECT_NE(keyAdd, keyMul);
}