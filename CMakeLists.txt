cmake_minimum_required(VERSION 3.18)
project(json_parse)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(JsonParserLib)
add_subdirectory(Tests)

add_executable(json_parse main.cpp)
target_link_libraries(json_parse JsonParser)