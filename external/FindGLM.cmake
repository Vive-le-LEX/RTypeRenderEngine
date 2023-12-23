# find_library(GLM_LIB glm)

# if(NOT GLM_LIB)
message(STATUS "Fetching GLM...")

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 0.9.8
)

FetchContent_MakeAvailable(glm)
# else()
#     message(STATUS "GLM library found at ${GLM_LIB}")
# endif()
