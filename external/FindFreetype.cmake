if (NOT FREETYPE_LIB)
    message(STATUS "Fetching Freetype...")
    FetchContent_Declare(
        freetype
        URL https://download.savannah.gnu.org/releases/freetype/freetype-2.13.1.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP true
    )

    set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(freetype)
else()
    message(STATUS "Found Freetype: ${FREETYPE_LIB}")
endif()
