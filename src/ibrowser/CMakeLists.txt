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
	ibrowsersingle.cpp
	global.cpp
	imainwindow.cpp
	ibrowserrenderer.cpp
	ibrowsertabwidget.cpp
	ibtabbar.cpp
	ibwidget.cpp
	signalsslots.cpp
   )

SET(IBROWSER_SOURCES 	imainwindow.cpp
						ibrowsertabwidget.cpp
						ibtabbar.cpp
						ibwidget.cpp 
						signalsslots.cpp) 
						
SET(IBROWSER_HEADERS 	${IBROWSER_SOURCE_DIR}/include/ibrowser/imainwindow.h
						${IBROWSER_SOURCE_DIR}/include/ibrowser/ibrowsertabwidget.h
						${IBROWSER_SOURCE_DIR}/include/ibrowser/ibtabbar.h 
						${IBROWSER_SOURCE_DIR}/include/ibrowser/ibwidget.h 
						${IBROWSER_SOURCE_DIR}/include/ibrowser/signalsslots.h) 
						
SET(IBROWSER_FORMS 		ibrowser.ui) 
SET(IBROWSER_RESOURCES 	ibrowser.qrc) 

QT4_WRAP_CPP(IBROWSER_HEADERS_MOC ${IBROWSER_HEADERS}) 
QT4_WRAP_UI(IBROWSER_FORMS_HEADERS ${IBROWSER_FORMS}) 
QT4_ADD_RESOURCES(IBROWSER_RESOURCES_RCC ${IBROWSER_RESOURCES}) 
   
include_directories(${IBROWSER_SOURCE_DIR}/include
					${IBROWSER_SOURCE_DIR}/include/cef
					${IBROWSER_SOURCE_DIR}/include/utils
					${IBROWSER_SOURCE_DIR}/src)

add_definitions(-DCURL_STATICLIB)

IF (WIN32)
add_executable(ibrowser WIN32 	${IBR_SRCS}
								${IBROWSER_HEADERS_MOC}
								${IBROWSER_FORMS_HEADERS}
								${IBROWSER_RESOURCES_RCC})
TARGET_LINK_LIBRARIES(ibrowser
	general
	#utils
	kernel32.lib
	user32.lib
	shell32.lib
	uuid.lib
	ole32.lib
	advapi32.lib
	ws2_32.lib
	gdi32.lib
	comdlg32.lib
	oleaut32.lib
	imm32.lib
	winmm.lib
	winspool.lib
	qtmaind.lib
	QtCored.lib
	QtGuid.lib
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
	add_executable(ibrowser 	${IBR_SRCS}
								${IBROWSER_HEADERS_MOC}
								${IBROWSER_FORMS_HEADERS}
								${IBROWSER_RESOURCES_RCC})
#Message(STATUS "OPENCL_LIBRARIES : ${OPENCL_INCLUDE_DIR}")
	TARGET_LINK_LIBRARIES(ibrowser)
ENDIF(WIN32)
