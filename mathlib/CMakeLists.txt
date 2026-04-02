cmake_minimum_required(VERSION 3.16)

project(mathlib)

add_library(mathlib INTERFACE)

target_include_directories(mathlib INTERFACE include)
