cmake_minimum_required(VERSION 3.10)
project(rtype-engine
    VERSION 1.0.0
    DESCRIPTION "RTypeEngine"
    LANGUAGES CXX)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

include(external/CMakeLists.txt)

set(SRC_MAIN

)

set(SRC
    src/Window.cpp
)


add_library(${PROJECT_NAME} SHARED
    src/Window.cpp
)

file(GLOB RTYPE_PUBLIC_HEADERS RELATIVE ${PROJECT_SOURCE_DIR} "include/RTypeEngine/*.h*")

target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/RTypeEngine>
    $<INSTALL_INTERFACE:include>
    PRIVATE src
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION 1
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad glm)

install(TARGETS ${PROJECT_NAME} EXPORT rtype-engine
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT rtype-engine DESTINATION share/rtype-engine/cmake)

export(TARGETS ${PROJECT_NAME} FILE rtype-engine.cmake)

if (IS_TESTING)
    include(CTest)

    message(STATUS "Building tests")
    set(TEST_PROJECT_NAME ${PROJECT_NAME}-test)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fprofile-arcs -ftest-coverage")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
    set(SRC_TEST
        tests/Window-test.cpp
    )
    add_executable(${TEST_PROJECT_NAME} ${SRC_TEST} ${SRC})

    target_link_libraries(${TEST_PROJECT_NAME} PRIVATE GTest::gtest_main rtype-engine)

    target_include_directories(${TEST_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/RTypeEngine)

    include(GoogleTest)
    gtest_discover_tests(${TEST_PROJECT_NAME})
endif()
