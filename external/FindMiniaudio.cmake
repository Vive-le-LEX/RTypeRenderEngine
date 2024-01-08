find_library(MINIAUDIO_LIB miniaudio)

if(NOT MINIAUDIO_LIB)
    message(STATUS "Fetching Miniaudio...")

    FetchContent_Declare(
        miniaudio
        URL https://raw.githubusercontent.com/mackron/miniaudio/master/miniaudio.h
        BUILD_COMMAND ""
        CONFIGURE_COMMAND ""
    )

    FetchContent_Populate(miniaudio)
else()
    message(STATUS "Miniaudio library found at ${MINIAUDIO_LIB}")
endif()
