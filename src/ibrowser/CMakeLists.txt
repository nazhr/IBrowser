###########################################################################
#   Copyright (C) 2014 by Jerry			                                  #
#                                                                         #
#   This file is part of IBrowser.                                        #
#                                                                         #
#   IBrowser is private software.                                         #
#   program.  If not, see <https://github.com/jerrykk/IBrowser>.          #
#                                                                         #
#   IBrowser website: https://github.com/jerrykk/IBrowser                 #
###########################################################################


#############################################################################
#
# IBrowser binary
#
#############################################################################
set(IBR_SRCS
	main.cpp
	ibrowserapp.cpp
	ibrowserhandler.cpp
	ibrowserclient.cpp
	ibrowserwindow.cpp
	global.cpp
   )

include_directories(${IBROWSER_SOURCE_DIR}/include
					${IBROWSER_SOURCE_DIR}/include/cef
					${IBROWSER_SOURCE_DIR}/include/utils
					${IBROWSER_SOURCE_DIR}/src)

add_definitions(-DCURL_STATICLIB)

IF (WIN32)
add_executable(ibrowser WIN32 ${IBR_SRCS})
TARGET_LINK_LIBRARIES(ibrowser
	general
	#utils
	ws2_32.lib
	${IBROWSER_SOURCE_DIR}/lib/libcef.lib
	debug
	${IBROWSER_SOURCE_DIR}/lib/libcef_dll_wrapper_debug.lib
	optimized
	${IBROWSER_SOURCE_DIR}/lib/libcef_dll_wrapper_release.lib
)

ADD_CUSTOM_COMMAND(
    TARGET ibrowser
    POST_BUILD
    COMMAND cmake -E copy_directory ${IBROWSER_SOURCE_DIR}/Resources/
$<TARGET_FILE_DIR:ibrowser>
	COMMAND cmake -E copy_directory ${IBROWSER_SOURCE_DIR}/dll/$<CONFIGURATION>/
$<TARGET_FILE_DIR:ibrowser>
)

#set_target_properties(ibrowser PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /subsystem:windows") 
ELSE(WIN32)
add_executable(ibrowser ${IBR_SRCS})
#Message(STATUS "OPENCL_LIBRARIES : ${OPENCL_INCLUDE_DIR}")
TARGET_LINK_LIBRARIES(ibrowser)
ENDIF(WIN32)
