message(STATUS "Fetching SoLoud...")

FetchContent_Declare(
    SOLOUD
    GIT_REPOSITORY git@github.com:jarikomppa/soloud.git
    GIT_TAG master
)

set(SOLOUD_STATIC ON CACHE BOOL "" FORCE)
set(SOLOUD_BACKEND_SDL2 OFF CACHE BOOL "" FORCE)
set(SOLOUD_C_API ON CACHE BOOL "" FORCE)
set(SOLOUD_BACKEND_NULL OFF CACHE BOOL "" FORCE)

if(UNIX AND NOT APPLE)
  set(SOLOUD_BACKEND_ALSA ON CACHE BOOL "" FORCE)
elseif (APPLE)
  set(SOLOUD_BACKEND_COREAUDIO ON CACHE BOOL "" FORCE)
else()
  set(SOLOUD_BACKEND_WINMM ON CACHE BOOL "" FORCE)
endif()


FetchContent_GetProperties(SOLOUD)
if(NOT SOLOUD_POPULATED)
  FetchContent_Populate(SOLOUD)
  add_subdirectory(${soloud_SOURCE_DIR}/contrib ${soloud_BINARY_DIR})
  set(SOLOUD_INCLUDE_DIR ${soloud_SOURCE_DIR}/include)
endif()
