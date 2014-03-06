###########################################################################
#   Copyright (C) 2013 by sanpolo CO.LTD                                  #
#                                                                         #
#   This file is part of IBrowser.                                           #
#                                                                         #
#   IBrowser is private software.                                            #
###########################################################################


#############################################################################
#
# IBrowser binary
#
#############################################################################
set(IBR_SRCS
	main.cpp
	myframe.cpp
   )

include_directories(${IBROWSER_SOURCE_DIR}/include
					#${IBROWSER_SOURCE_DIR}/include/cefclient
					${IBROWSER_SOURCE_DIR}/src)

add_definitions(-DCURL_STATICLIB)

IF (WIN32)
add_executable(ibrowser WIN32 ${IBR_SRCS})
TARGET_LINK_LIBRARIES(ibrowser
	general
	#cefclient
	#utils
	ws2_32.lib
	#debug
	#${IBROWSER_SOURCE_DIR}/lib/debug/libcef.lib
	#debug
	#${IBROWSER_SOURCE_DIR}/lib/debug/libcef_dll_wrapper.lib
	#optimized
	#${IBROWSER_SOURCE_DIR}/lib/release/libcef.lib
	#optimized
	#${IBROWSER_SOURCE_DIR}/lib/release/libcef_dll_wrapper.lib
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
TARGET_LINK_LIBRARIES(ibrowser
 # cefclient
)
ENDIF(WIN32)