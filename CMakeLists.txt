cmake_minimum_required(VERSION 2.8.12.2)
project(zephyr)
set(SOURCES src/main.cxx)
add_executable(zephyr ${SOURCES})
ADD_DEFINITIONS(
    -std=c++14
)
