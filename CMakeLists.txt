cmake_minimum_required(VERSION 3.10)
project(rtype-engine
        VERSION 1.0.0
        DESCRIPTION "RTypeEngine"
        LANGUAGES CXX)

option(IS_TESTING "Enable testing" OFF)
option(IS_BUILDING_DOC "Enable documentation" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

include(GNUInstallDirs)
include(external/FindDependencies.cmake)

set(SRC
    src/Window/Window.cpp
    src/Window/EventHandler.cpp
    src/Window/Events/KeyboardHandler.cpp
    src/Window/Events/MouseHandler.cpp
)

add_library(${PROJECT_NAME} SHARED
    ${SRC}
)
target_include_directories(${PROJECT_NAME} PUBLIC external/glad/include/)
target_link_libraries(${PROJECT_NAME} INTERFACE freetype-interface)
target_include_directories(${PROJECT_NAME} PUBLIC include)
target_link_libraries(${PROJECT_NAME} INTERFACE rtype-ecs)
target_link_libraries(${PROJECT_NAME} PRIVATE glad glfw glm freetype)

if (IS_TESTING AND NOT WIN32)
    include(tests/BuildTests.cmake)
endif()

if (IS_BUILDING_DOC)
    include(docs/BuildDocs.cmake)
endif()
