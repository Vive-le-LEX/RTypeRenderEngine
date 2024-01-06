find_library(LUACPP_LIB luacpp)

if (NOT LUACPP_LIB)
    message(STATUS "Fetching LuaCpp")
    FetchContent_Declare(
        luacpp
        GIT_REPOSITORY git@github.com:jordanvrtanoski/luacpp.git
        GIT_TAG        origin/main
        SOURCE_SUBDIR  Source
    )
    FetchContent_GetProperties(luacpp)
    if(NOT luacpp_POPULATED)
        FetchContent_Populate(luacpp)

        add_subdirectory(${luacpp_SOURCE_DIR}/Source EXCLUDE_FROM_ALL)
        add_dependencies(luacpp luacpp)
    endif()

    set(LUACPP_LIB luacpp)
    set(LUACPP_INCLUDE_DIR ${luacpp_SOURCE_DIR}/Source)
else()
    message(STATUS "Found LuaCPP: ${LUACPP_LIB}")
endif()
