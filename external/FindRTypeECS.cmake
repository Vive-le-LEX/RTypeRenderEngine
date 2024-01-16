find_library(RTYPE-ECS_LIB rtype-ecs)

if(NOT RTYPE-ECS_LIB)
    message(STATUS "Fetching RTypeECS...")

    add_subdirectory(/home/qbriand/delivery/RType/RTypeECS RTypeECS)
    # FetchContent_Declare(
    #     rtype-ecs
    #     GIT_REPOSITORY https://github.com/Vive-le-LEX/RTypeECS.git
    #     GIT_TAG main
    # )

    # FetchContent_MakeAvailable(rtype-ecs)
else()
    message(STATUS "RTypeECS library found at ${RTYPE-ECS_LIB}")
endif()
