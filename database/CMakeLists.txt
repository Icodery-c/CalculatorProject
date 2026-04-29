cmake_minimum_required(VERSION 3.16)

project(database)

find_package(PostgreSQL REQUIRED)

add_library(database
    src/database.cpp
)

target_include_directories(database PUBLIC include)
target_include_directories(database PRIVATE ${PostgreSQL_INCLUDE_DIRS})
target_link_libraries(database PRIVATE ${PostgreSQL_LIBRARIES})
