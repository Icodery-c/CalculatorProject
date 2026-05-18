cmake_minimum_required(VERSION 3.16)

project(client)

if(NOT TARGET protocol)
    add_subdirectory(../protocol ${CMAKE_BINARY_DIR}/protocol)
endif()

add_library(client
    src/client.cpp
)

target_include_directories(client PUBLIC include)
target_link_libraries(client PUBLIC protocol)

add_executable(calculator-client
    app/main.cpp
)

target_link_libraries(calculator-client PRIVATE client)

install(TARGETS calculator-client DESTINATION /usr/local/bin)