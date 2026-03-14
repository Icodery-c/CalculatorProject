
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

add_executable(calculator

  src/calculator.cpp
  src/checker.cpp
  src/main.cpp
  src/parser.cpp
  src/printer.cpp
  src/runner.cpp

)

target_include_directories(calculator PRIVATE include)

target_include_directories(calculator PRIVATE
    ${mathlib_SOURCE_DIR}/include
)

install(TARGETS calculator DESTINATION /usr/local/bin)
