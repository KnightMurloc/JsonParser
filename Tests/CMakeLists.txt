project(Catch_tests)

add_compile_options(-Winvalid-pch)
add_compile_options(-O2)
include_directories("../JsonParser_Lib")
include_directories(Catch2)

add_executable(CatchTest_run tests_valid_json.cpp tests_unvalid_json.cpp)
target_link_libraries(CatchTest_run JsonParser)

add_custom_command(TARGET CatchTest_run POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/Tests/test_Files $<TARGET_FILE_DIR:CatchTest_run>/test_Files)
