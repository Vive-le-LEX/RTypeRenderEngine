find_package(Lua)

if (LUA_FOUND)
    message(STATUS "Found local Lua")
else()
    message(STATUS "Fetching Lua...")

    FetchContent_Declare(
        lua
        GIT_REPOSITORY git@github.com:walterschell/Lua.git
        GIT_TAG        master
    )
    set(LUA_BUILD_BINARY OFF CACHE BOOL "" FORCE)
    set(LUA_BUILD_COMPILER OFF CACHE BOOL "" FORCE)
    set(LUA_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(lua)
    set(LUA_INCLUDE_DIR ${lua_SOURCE_DIR}/src)
    set(LUA_LIBRARIES lua)
endif()
