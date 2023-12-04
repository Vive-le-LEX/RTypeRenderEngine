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
# glob_recurse from pwd ./include/RTypeEngine
file(GLOB_RECURSE RTYPE_HEADERS include/RTypeEngine/*.hpp)

set_target_properties(
    ${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION}
    SOVERSION 1
    PUBLIC_HEADER "${RTYPE_HEADERS}"
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
)
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
