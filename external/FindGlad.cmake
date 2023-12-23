message(STATUS "Fetching dependencies...")
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG master
)

FetchContent_MakeAvailable(glad)

set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile" FORCE)
message(STATUS "Finished fetching glad dependencies")
