
include(FetchContent)

set(IS_TESTING_TMP ${IS_TESTING})
set(IS_BUILDING_DOC_TMP ${IS_BUILDING_DOC})

set(IS_TESTING OFF)
set(IS_BUILDING_DOC OFF)

include(external/FindGlad.cmake)
include(external/FindGLM.cmake)
include(external/FindGLFW.cmake)
include(external/FindGTest.cmake)
include(external/FindRTypeECS.cmake)

set(IS_TESTING ${IS_TESTING_TMP})
set(IS_BUILDING_DOC ${IS_BUILDING_DOC_TMP})
