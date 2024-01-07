message(STATUS "Fecthing nlohmann_json 3.2.0...")

find_package(nlohmann_json 3.2.0 QUIET)

if (nlohmann_json_FOUND)
    message(STATUS "nlohmann_json found")
else()
    message(STATUS "nlohmann_json not found, fetching from source...")
    FetchContent_Declare(
        nlohmann_json
        GIT_REPOSITORY git@github.com:nlohmann/json.git
        GIT_TAG v3.11.3
    )
    FetchContent_MakeAvailable(nlohmann_json)
endif()
