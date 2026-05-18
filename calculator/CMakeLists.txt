cmake_minimum_required(VERSION 3.16)

project(calculator)

include(FetchContent)

find_program(CLANG_TIDY clang-tidy)

if(CLANG_TIDY)
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY})
endif()

find_program(CLANG_FORMAT clang-format)

file(GLOB_RECURSE ALL_SOURCE_FILES
    src/*.cpp
    include/*.h
)

if(CLANG_FORMAT)
    add_custom_target(
        format
        COMMAND ${CLANG_FORMAT} -i ${ALL_SOURCE_FILES}
    )
endif()

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

add_executable(calculator
    src/calculator.cpp
    src/checker.cpp
    src/main.cpp
    src/parser.cpp
    src/printer.cpp
    src/runner.cpp
    src/cache.cpp
    src/config.cpp

)

target_include_directories(calculator PRIVATE include)

target_include_directories(calculator PRIVATE
    ${mathlib_SOURCE_DIR}/include
)

add_subdirectory(../database ${CMAKE_BINARY_DIR}/database)

add_subdirectory(../server ${CMAKE_BINARY_DIR}/server)

add_subdirectory(../signal_handler ${CMAKE_BINARY_DIR}/signal_handler)

add_subdirectory(../client ${CMAKE_BINARY_DIR}/client_app)

target_link_libraries(calculator PRIVATE mathlib nlohmann_json::nlohmann_json logger database server signal_handler)

install(TARGETS calculator DESTINATION /usr/local/bin)

# Установка дополнительных файлов
install(FILES ${CMAKE_SOURCE_DIR}/../systemd/calculator.service
        DESTINATION /etc/systemd/system)

install(FILES ${CMAKE_SOURCE_DIR}/../config/calculator.conf
        DESTINATION /etc/calculator)

install(TARGETS calculator-client
        DESTINATION /usr/local/bin
        OPTIONAL)

# CPack конфигурация
set(CPACK_GENERATOR "DEB")
set(CPACK_PACKAGE_NAME "calculator")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_CONTACT "ilnur-islamov@example.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Calculator TCP service with PostgreSQL backend")

set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Ilnur Islamov")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-system1.83.0, libpq5, postgresql")
set(CPACK_DEBIAN_PACKAGE_SECTION "utils")
set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
set(CPACK_DEBIAN_PACKAGE_ARCHITECTURE "amd64")

# Постустановочный скрипт — перезагрузить systemd
set(CPACK_DEBIAN_PACKAGE_CONTROL_EXTRA
    "${CMAKE_CURRENT_SOURCE_DIR}/../debian/postinst;${CMAKE_CURRENT_SOURCE_DIR}/../debian/prerm")

include(CPack)