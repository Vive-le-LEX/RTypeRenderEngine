include(FetchContent)

if(IS_TESTING)
  message(STATUS "Testing mode enabled => Fetching GTest")
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
  )

  set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(googletest)
endif()

message(STATUS "Fetching dependencies...")
FetchContent_Declare(
    glad
    GIT_REPOSITORY https://github.com/Dav1dde/glad.git
    GIT_TAG master
)

set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile" FORCE)
message(STATUS "Finished fetching glad dependencies")

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

message(STATUS "Finished fetching glfw dependencies")

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG master
)

message(STATUS "Finished fetching glm dependencies")

FetchContent_Declare(
  rtype-ecs
  GIT_REPOSITORY https://github.com/Vive-le-LEX/RTypeECS
  GIT_TAG main
)

set(ALL_LIBRARIES glad glfw glm rtype-ecs)

foreach(lib IN LISTS ALL_LIBRARIES)
    if(BUILD_TESTS_FOR_FETCHED_CONTENT)
        FetchContent_MakeAvailable(${lib})
    else()
        FetchContent_Populate(${lib})
        add_subdirectory(${${lib}_SOURCE_DIR} EXCLUDE_FROM_ALL)
    endif()
endforeach()
