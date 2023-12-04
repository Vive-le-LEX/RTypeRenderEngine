cmake_minimum_required(VERSION 3.9)
project(rtype-render-engine VERSION 1.0.0 DESCRIPTION "RTypeRenderEngine")

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(external/CMakeLists.txt)

add_library(${PROJECT_NAME} SHARED
    src/Window.cpp
)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER RTypeRenderEngine.hpp
)


target_include_directories(${PROJECT_NAME} PRIVATE
    include/RTypeEngine
    src
    ${glad_SOURCE_DIR}/include
    ${glfw_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE glfw glad glm)

install(TARGETS ${PROJECT_NAME}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
