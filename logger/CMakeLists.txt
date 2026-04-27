cmake_minimum_required(VERSION 3.16)

project(logger)

include(FetchContent)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog.git
    GIT_TAG v1.14.1
)

FetchContent_MakeAvailable(spdlog)

add_library(logger
    src/logger.cpp
)

target_include_directories(logger PUBLIC include)

target_link_libraries(logger PRIVATE spdlog::spdlog)