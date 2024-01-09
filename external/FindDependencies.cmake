
include(FetchContent)

set(IS_TESTING_TMP ${IS_TESTING})
set(IS_BUILDING_DOC_TMP ${IS_BUILDING_DOC})

set(IS_TESTING OFF)
set(IS_BUILDING_DOC OFF)

message(STATUS "Fetching external dependencies...")
include(external/FindCPUFeatures.cmake)
include(external/FindLua.cmake)
include(external/FindLuacpp.cmake)
include(external/FindNlohmannCpp.cmake)
include(external/FindGlad.cmake)
include(external/FindGLM.cmake)
include(external/FindGLFW.cmake)
include(external/FindGTest.cmake)
include(external/FindRTypeECS.cmake)
include(external/FindFreetype.cmake)
include(external/FindSoloud.cmake)

set(IS_TESTING ${IS_TESTING_TMP})
set(IS_BUILDING_DOC ${IS_BUILDING_DOC_TMP})
