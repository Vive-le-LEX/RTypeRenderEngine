if (NOT FREETYPE_LIB)
    message(STATUS "Fetching Freetype...")
    FetchContent_Declare(
        freetype
        URL https://download.savannah.gnu.org/releases/freetype/freetype-2.13.1.tar.gz
        DOWNLOAD_EXTRACT_TIMESTAMP true
    )
    FetchContent_MakeAvailable(freetype)
    set(FREETYPE_LIB freetype)
else()
    message(STATUS "Found Freetype: ${FREETYPE_LIB}")
endif()
