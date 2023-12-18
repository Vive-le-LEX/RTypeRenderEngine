set(GLAD_SRC ${CMAKE_CURRENT_SOURCE_DIR}/external/glad)

add_library(glad ${GLAD_SRC}/include/glad/glad.h ${GLAD_SRC}/src/glad.c)
target_include_directories(glad PUBLIC ${GLAD_SRC}/include/)