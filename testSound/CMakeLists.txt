cmake_minimum_required(VERSION 3.9)
project(game VERSION 1.0.0 DESCRIPTION "MyGame")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LIBRARIES
    rtype-engine
)

set(SRC
    main.cpp
)

add_custom_target(src ALL DEPENDS ${PROJECT_NAME})

add_executable(${PROJECT_NAME} ${SRC})

target_link_libraries(${PROJECT_NAME} rtype-engine)
