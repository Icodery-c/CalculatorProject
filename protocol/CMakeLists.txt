cmake_minimum_required(VERSION 3.16)

project(protocol)

find_package(Boost REQUIRED COMPONENTS system)

add_library(protocol
    src/message_socket.cpp
)

target_include_directories(protocol PUBLIC include)
target_include_directories(protocol PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(protocol PUBLIC ${Boost_LIBRARIES})