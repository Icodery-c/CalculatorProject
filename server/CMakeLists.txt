cmake_minimum_required(VERSION 3.16)

project(server)

if(NOT TARGET protocol)
    add_subdirectory(../protocol ${CMAKE_BINARY_DIR}/protocol)
endif()

add_library(server
    src/server.cpp
)

target_include_directories(server PUBLIC include)
target_link_libraries(server PUBLIC protocol)