message(STATUS "Fetching external dependencies...")

include(FetchContent)

include(external/FindRTypeECS.cmake)

include(external/FindLua.cmake)
include(external/FindLuacpp.cmake)

include(external/FindGLM.cmake)

include(external/FindNlohmannCpp.cmake)

include(external/FindGlad.cmake)
include(external/FindGLFW.cmake)

include(external/FindFreetype.cmake)
include(external/FindCPUFeatures.cmake)

include(external/FindSoloud.cmake)
include(external/FindGTest.cmake)
