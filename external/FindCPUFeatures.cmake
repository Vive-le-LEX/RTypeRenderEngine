message(STATUS "Fetching CPU Features...")

FetchContent_Declare(
    cpu_features_lib
    GIT_REPOSITORY git@github.com:google/cpu_features.git
    GIT_TAG v0.9.0
)

FetchContent_MakeAvailable(cpu_features_lib)
