include(CTest)

message(STATUS "Building tests")

set(TEST_PROJECT_NAME ${PROJECT_NAME}-test)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
set(SRC_TEST
    tests/Window-test.cpp
)

add_executable(${TEST_PROJECT_NAME} ${SRC_TEST} ${SRC})

target_link_libraries(${TEST_PROJECT_NAME} PRIVATE GTest::gtest_main ${ALL_LIBRARIES})

include(GoogleTest)
gtest_discover_tests(${TEST_PROJECT_NAME})