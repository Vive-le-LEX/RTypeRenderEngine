cmake_minimum_required(VERSION 3.9)
project(rtype-engine VERSION 1.0.0 DESCRIPTION "RTypeEngine")

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(external/CMakeLists.txt)

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
