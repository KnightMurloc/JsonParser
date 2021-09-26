cmake_minimum_required(VERSION 3.18)
project(json_parser_example)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(JsonParser_Lib)
add_subdirectory(Tests)

add_executable(json_parser_example main.cpp)
target_link_libraries(json_parser_example JsonParser)