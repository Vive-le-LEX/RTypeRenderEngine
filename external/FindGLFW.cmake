find_library(GLFW_LIB glfw)

if(NOT GLFW_LIB)
    message(STATUS "Fetching GLFW...")
    FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
    )

    set(GLFW_INSTALL OFF)
    set(GLFW_BUILD_EXAMPLES OFF)
    set(GLFW_BUILD_TESTS OFF)
    set(GLFW_BUILD_DOCS OFF)
    set(GLFW_INSTALL OFF)

    FetchContent_MakeAvailable(glfw)
else()
    message(STATUS "GLFW library found at ${GLFW_LIB}")
endif()
