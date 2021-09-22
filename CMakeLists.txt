cmake_minimum_required(VERSION 3.18)
project(json_parse)

set(CMAKE_CXX_STANDARD 17)

add_executable(json_parse main.cpp JsonParser.cpp JsonParser.h)