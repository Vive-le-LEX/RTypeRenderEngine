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

option(BUILD_TESTS_FOR_FETCHED_CONTENT "Build tests for fetched content" OFF)

include(external/CMakeLists.txt)

set(SRC_MAIN

)

set(SRC
        src/Window.cpp
)

add_library(${PROJECT_NAME} SHARED
        src/Window.cpp
        include/RTypeEngine/Graphics/Texture.inl
        include/RTypeEngine/Graphics/Shader.inl
        include/RTypeEngine/Graphics/Transform.inl
        include/RTypeEngine/Graphics/Rect.inl
        include/RTypeEngine/Graphics/Mesh.inl
        include/RTypeEngine/Graphics/Sprite.inl
)

file(GLOB . RELATIVE ${PROJECT_SOURCE_DIR} "include/RTypeEngine/*.h*")
target_link_libraries(${PROJECT_NAME} PRIVATE ${ALL_LIBRARIES} glad)

target_include_directories(${PROJECT_NAME} PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/RTypeEngine>
        $<INSTALL_INTERFACE:include>
        PRIVATE src
        ${GLAD_INCLUDE_DIRS}
)

set_target_properties(${PROJECT_NAME} PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION 1
)

install(TARGETS ${ALL_LIBRARIES} ${PROJECT_NAME} ${ALL_LIBRARIES} EXPORT rtype-engine
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if (IS_TESTING AND NOT WIN32)
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

    target_include_directories(${TEST_PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include/RTypeEngine)
    target_include_directories(${TEST_PROJECT_NAME} PRIVATE ${rtype-ecs_SOURCE_DIR}/include)

    include(GoogleTest)
    gtest_discover_tests(${TEST_PROJECT_NAME})
endif ()
