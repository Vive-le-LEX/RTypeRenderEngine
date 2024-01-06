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

set(SRC-GRAPHICS
    src/Window/Window.cpp
    src/Window/WindowConsole.cpp
    src/Window/EventHandler.cpp
    src/Window/Events/KeyboardHandler.cpp
    src/Window/Events/MouseHandler.cpp
    src/Window/Events/GamepadHandler.cpp
    src/Window/Events/Gamepad.cpp
)

set(SRC-CORE
    src/System/Core.cpp
    src/System/VirtualMouse.cpp
)

add_library(${PROJECT_NAME}-graphics SHARED
    ${SRC-GRAPHICS}
)

add_library(${PROJECT_NAME}-core SHARED
    ${SRC-CORE}
)

include(external/FindDependencies.cmake)

target_include_directories(${PROJECT_NAME}-graphics PUBLIC include)
target_include_directories(${PROJECT_NAME}-graphics PRIVATE ${LUACPP_INCLUDE_DIR} external/glad/include/)

target_link_libraries(${PROJECT_NAME}-graphics INTERFACE freetype-interface rtype-ecs)
target_link_libraries(${PROJECT_NAME}-graphics PRIVATE glad glfw glm freetype ${LUACPP_LIB})


target_include_directories(${PROJECT_NAME}-core PUBLIC include)
target_include_directories(${PROJECT_NAME}-core INTERFACE ${LUACPP_INCLUDE_DIR})
target_include_directories(${PROJECT_NAME}-core PRIVATE external/glad/include/)

target_link_libraries(${PROJECT_NAME}-core INTERFACE freetype-interface rtype-ecs ${LUACPP_LIB})
target_link_libraries(${PROJECT_NAME}-core PRIVATE glfw glm freetype rtype-ecs)

if (IS_TESTING AND NOT WIN32)
    include(tests/BuildTests.cmake)
endif()

if (IS_BUILDING_DOC)
    include(docs/BuildDocs.cmake)
endif()
