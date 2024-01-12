string(ASCII 27 Esc)
set(ColourReset "${Esc}[m")
set(ColourBold  "${Esc}[1m")
set(Red         "${Esc}[31m")
set(Green       "${Esc}[32m")
set(Yellow      "${Esc}[33m")
set(Blue        "${Esc}[34m")
set(Magenta     "${Esc}[35m")
set(Cyan        "${Esc}[36m")
set(White       "${Esc}[37m")
set(BoldRed     "${Esc}[1;31m")
set(BoldGreen   "${Esc}[1;32m")
set(BoldYellow  "${Esc}[1;33m")
set(BoldBlue    "${Esc}[1;34m")
set(BoldMagenta "${Esc}[1;35m")
set(BoldCyan    "${Esc}[1;36m")
set(BoldWhite   "${Esc}[1;37m")

MACRO (PRINT_OPTION_STATUS OPTION TEXT)
	SET (PREPEND "")
	IF (${ARGC} GREATER 2)
		IF (${ARGV2} GREATER 0)
			FOREACH (A RANGE 1 ${ARGV2})
				SET (PREPEND "${PREPEND} ")
			ENDFOREACH (A)
		ENDIF (${ARGV2} GREATER 0)
	ENDIF (${ARGC} GREATER 2)
	IF (${OPTION})
		MESSAGE ("${PREPEND} [${BoldGreen}✓${ColourReset}] ${TEXT} ${Green}enabled${ColourReset}")
	ELSE (${OPTION})
		MESSAGE ("${PREPEND} [${BoldRed}✗${ColourReset}] ${TEXT} ${Red}disabled${ColourReset}")
	ENDIF (${OPTION})
ENDMACRO (PRINT_OPTION_STATUS)

message(STATUS "Configuration for ${PROJECT_NAME} ${PROJECT_VERSION}:")
option(RTYPE_BUILD_SHARED_LIBS "Set to ON to build shared libraries" OFF)
print_option_status (RTYPE_BUILD_SHARED_LIBS "Build shared libraries")

option(RTYPE_CORE "Set to ON to build core module" ON)
print_option_status (RTYPE_CORE "Build core module")

option(RTYPE_GRAPHICS "Set to ON to build graphics module" ON)
print_option_status (RTYPE_GRAPHICS "Build graphics module")

option(RTYPE_AUDIO "Set to ON to build audio module" ON)
print_option_status (RTYPE_AUDIO "Build audio module")

option(RTYPE_ANIMATION "Set to ON to build animation module" ON)
print_option_status (RTYPE_ANIMATION "Build animation module")

option(RTYPE_BUILD_TESTS "Set to ON to build tests" OFF)
print_option_status (RTYPE_BUILD_TESTS "Build tests")

option(RTYPE_BUILD_DOC "Set to ON to build documentation" OFF)
print_option_status (RTYPE_BUILD_DOC "Build documentation")
