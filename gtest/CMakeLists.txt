cmake_minimum_required(VERSION 3.16)

project(calculator_tests)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
    mathlib
    GIT_REPOSITORY https://github.com/Icodery-c/mathlib.git
    GIT_TAG main
)
FetchContent_MakeAvailable(mathlib)

add_subdirectory(../logger ${CMAKE_BINARY_DIR}/logger)

FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

add_executable(calculator_tests
    src/test_calculator.cpp
    src/test_checker.cpp
    src/test_parser.cpp
    ../calculator/src/calculator.cpp
    ../calculator/src/checker.cpp
    ../calculator/src/parser.cpp
)

target_include_directories(calculator_tests PRIVATE
    ../calculator/include
)

target_link_libraries(calculator_tests PRIVATE
    GTest::gtest_main
    mathlib
    nlohmann_json::nlohmann_json
    logger
)

enable_testing()
add_test(NAME calculator_tests COMMAND calculator_tests)