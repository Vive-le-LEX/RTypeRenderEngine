message(STATUS "Fetching dependencies...")
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG master
)
set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile" FORCE)

FetchContent_MakeAvailable(glad)

message(STATUS "Finished fetching glad dependencies")
