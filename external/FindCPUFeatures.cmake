message(STATUS "Fetching CPU Features...")

FetchContent_Declare(
    cpu_features_lib
    GIT_REPOSITORY https://github.com/google/cpu_features.git
    GIT_TAG v0.9.0
)

FetchContent_GetProperties(cpu_features_lib)
if(NOT cpu_features_lib_POPULATED)
    FetchContent_Populate(cpu_features_lib)
    add_subdirectory(${cpu_features_lib_SOURCE_DIR} ${cpu_features_lib_BINARY_DIR})
endif()
