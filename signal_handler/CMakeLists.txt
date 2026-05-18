cmake_minimum_required(VERSION 3.16)

project(signal_handler)

find_package(Boost REQUIRED COMPONENTS system)

add_library(signal_handler
    src/signal_handler.cpp
)

target_include_directories(signal_handler PUBLIC include)
target_include_directories(signal_handler PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(signal_handler PUBLIC ${Boost_LIBRARIES})