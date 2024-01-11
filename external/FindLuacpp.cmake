find_library(LUACPP_LIB luacpp)

if (NOT LUACPP_LIB)
    message(STATUS "Fetching LuaCpp...")
    FetchContent_Declare(
        luacpp
        GIT_REPOSITORY https://github.com/QuentinBriand/luacpp.git
        GIT_TAG        origin/main
        SOURCE_SUBDIR  Source
    )
    FetchContent_MakeAvailable(luacpp)

else()
    message(STATUS "Found LuaCPP: ${LUACPP_LIB}")
endif()
