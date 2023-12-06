cmake_minimum_required(VERSION 3.10)

message(STATUS "Going to search for tests in : ${CMAKE_SOURCE_DIR}/build")
set(build_dir ${CMAKE_CURRENT_SOURCE_DIR}/build)

if (NOT EXISTS ${build_dir})
    file(MAKE_DIRECTORY ${build_dir})
endif()

execute_process(
    COMMAND ${CMAKE_COMMAND} ..
    WORKING_DIRECTORY ${build_dir}
)

execute_process(
    COMMAND ${CMAKE_COMMAND} --build .
    WORKING_DIRECTORY ${build_dir}
)

set(ENV{GTEST_COLOR} 1)
execute_process(
    COMMAND ctest -VV
    WORKING_DIRECTORY ${build_dir}
    RESULT_VARIABLE test_result
)

if (${test_result})
    message(FATAL_ERROR "Tests failed")
endif()
