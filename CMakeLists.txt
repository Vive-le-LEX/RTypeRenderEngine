cmake_minimum_required(VERSION 3.10)
project(rtype-engine
        VERSION 1.0.0
        DESCRIPTION "RTypeEngine"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC-GRAPHICS
    src/Window/Window.cpp
    src/Window/WindowConsole.cpp
    src/Window/WindowDebugger.cpp
    src/Window/EventHandler.cpp
    src/Window/Events/KeyboardHandler.cpp
    src/Window/Events/MouseHandler.cpp
    src/Window/Events/GamepadHandler.cpp
    src/Window/Events/Gamepad.cpp
    src/System/VirtualMouse.cpp
)

set(SRC-CORE
    src/System/Core.cpp
)

set(SRC-AUDIO
    src/Audio/SoloudEngine.cpp
    src/Audio/Music.cpp
    src/Audio/Sound.cpp
)

set(SRC-ANIMATION
    src/Animation/Sequence.cpp
)

set(OSBiteness 32)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(OSBiteness 64)
    endif()

set(OutputDir ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}-x${OSBiteness}/${CMAKE_BUILD_TYPE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OutputDir})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OutputDir})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OutputDir}/statics)

include(Configure.cmake)
list(APPEND CMAKE_MESSAGE_INDENT "${ColourBold}RTypeEngine${ColourReset}: ")
set(BUILD_SHARED_LIBS OFF)

if (${RTYPE_BUILD_SHARED_LIBS})
    set(RTYPE_LIB_TYPE SHARED)
    message(STATUS "Building shared libraries")
else()
    set(RTYPE_LIB_TYPE STATIC)
    message(STATUS "Building static libraries")
endif()

set(POSITION_INDEPENDENT_CODE ${RTYPE_BUILD_SHARED_LIBS})
if (MSVC)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ${RTYPE_BUILD_SHARED_LIBS})
endif()

if (EXISTS "${CMAKE_SOURCE_DIR}/.embeds")
    include(external/BundleResources.cmake)

    SetupResourceEmbed()

    set(RESOURCES_FILES "")
    file(READ "${CMAKE_SOURCE_DIR}/.embeds" EMBEDS)

    string(REPLACE "\n" ";" EMBEDS ${EMBEDS})
    list (REMOVE_DUPLICATES EMBEDS)
    foreach(EMBED ${EMBEDS})
        string(STRIP ${EMBED} EMBED)
        if (NOT EMBED STREQUAL "")
            list(APPEND RESOURCES_FILES ${EMBED})
        endif()
    endforeach()

    file(GLOB_RECURSE ALL_FILES *)
    set(FINAL_FILES "")
    foreach(FILE ${ALL_FILES})
        foreach(RESOURCE ${RESOURCES_FILES})
            set(FILENAME_ONLY ${FILE})
            get_filename_component(FILENAME_ONLY ${FILENAME_ONLY} NAME)
            if (FILENAME_ONLY STREQUAL RESOURCE)
                list(APPEND FINAL_FILES ${FILE})
            endif()
        endforeach()
    endforeach()

    list(APPEND FINAL_FILES "${CMAKE_CURRENT_SOURCE_DIR}/INTERNAL_COMIC.TTF")

    set(finalEmbeds "")
    foreach(RESOURCE_FILE ${FINAL_FILES})
        AddEmbededResource(${RESOURCE_FILE} outfile)
        list(APPEND finalEmbeds ${outfile})
    endforeach()

    FinishEmbededResources("${finalEmbeds}")
else()
    message(STATUS "${BoldRed}No .embeds found${ColourReset}")
endif()

include(external/FindDependencies.cmake)

add_library(${PROJECT_NAME}-core ${RTYPE_LIB_TYPE}
    ${SRC-CORE}
)
target_include_directories(${PROJECT_NAME}-core PUBLIC include)
target_link_libraries(${PROJECT_NAME}-core
    PUBLIC
    rtype-ecs
    luacpp_static
    glm::glm
    nlohmann_json::nlohmann_json
    ResourceEmbeds
)

add_library(${PROJECT_NAME}-graphics ${RTYPE_LIB_TYPE}
    ${SRC-GRAPHICS}
)
target_include_directories(${PROJECT_NAME}-graphics PUBLIC include)
target_link_libraries(${PROJECT_NAME}-graphics
    PUBLIC
    rtype-ecs
    glad
    glm::glm
    glfw
    luacpp_static
    freetype
    cpu_features
)

add_library(${PROJECT_NAME}-audio ${RTYPE_LIB_TYPE}
    ${SRC-AUDIO}
)
target_include_directories(${PROJECT_NAME}-audio PUBLIC include ${SOLOUD_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME}-audio
    PUBLIC
    rtype-ecs
    glm::glm
    soloud
)

add_library(${PROJECT_NAME}-animation ${RTYPE_LIB_TYPE}
    ${SRC-ANIMATION}
)
set_target_properties(${PROJECT_NAME}-animation PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME}-animation PUBLIC include)
target_link_libraries(${PROJECT_NAME}-animation
    PUBLIC
    rtype-ecs
    nlohmann_json::nlohmann_json
)

if (APPLE)
    target_link_libraries(${PROJECT_NAME}-graphics PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit")
    target_link_libraries(${PROJECT_NAME}-core PRIVATE "-framework OpenGL" "-framework Cocoa" "-framework IOKit")
endif()


if (RTYPE_BUILD_TESTS AND NOT WIN32)
    include(tests/BuildTests.cmake)
endif()
if (RTYPE_BUILD_DOC)
    file(GLOB_RECURSE ALL_MARKDOWNS "${CMAKE_CURRENT_SOURCE_DIR}/docs/*.md")
    include(docs/BuildDocs.cmake)
endif()
