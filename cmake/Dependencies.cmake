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

include(FindPkgMacros)
getenv_path(IBROWSER_DEP_DIRS)

#######################################################################
# Core dependencies
#######################################################################

# Find threading library
FIND_PACKAGE(Threads REQUIRED)

message(STATUS "BOOST_SEARCH_PATH: " ${BOOST_SEARCH_PATH})

# Find Boost
set(Boost_USE_STATIC_LIBS       ON)
set(Boost_USE_MULTITHREADED     ON)
set(Boost_USE_STATIC_RUNTIME    ON)
set(BOOST_ROOT                  "${BOOST_SEARCH_PATH}")
#set(Boost_DEBUG                 ON)
set(Boost_MINIMUM_VERSION       "1.44.0")

set(Boost_ADDITIONAL_VERSIONS "1.53.0" "1.47.0" "1.46.1" "1.46" "1.46.0" "1.45" "1.45.0" "1.44" "1.44.0")

set(IBROWSER_BOOST_COMPONENTS locale thread filesystem system program_options regex)
find_package(Boost ${Boost_MINIMUM_VERSION} COMPONENTS ${IBROWSER_BOOST_COMPONENTS})
if (NOT Boost_FOUND)
        # Try again with the other type of libs
        if(Boost_USE_STATIC_LIBS)
                set(Boost_USE_STATIC_LIBS)
        else()
                set(Boost_USE_STATIC_LIBS OFF)
        endif()
        find_package(Boost ${Boost_MINIMUM_VERSION} COMPONENTS ${IBROWSER_BOOST_COMPONENTS})
endif()

if (Boost_FOUND)
	include_directories(SYSTEM ${Boost_INCLUDE_DIRS})
	link_directories(${Boost_LIBRARY_DIRS})
	# Don't use old boost versions interfaces
	ADD_DEFINITIONS(-DBOOST_FILESYSTEM_NO_DEPRECATED)
endif ()

#message(STATUS "start find_package wxWidgets")
#set(wxWidgets_USE_STATIC 1)
#find_package(wxWidgets 2.8.0 COMPONENTS aui stc html adv core base REQUIRED)
#message(STATUS "wxWidgets_FOUND: " ${wxWidgets_FOUND})
#if (wxWidgets_FOUND)
#    set(wxUSE_UNICODE_DEFINE "wxUSE_UNICODE=1")
#    set(wxUSE_STATIC_DEFINE "wxUSE_STATIC=1")
# 	IF(MSVC)
# 		include_directories( ${wxWidgets_ROOT_DIR}/include/msvc )
# 	ENDIF(MSVC)
#   	include_directories(SYSTEM ${wxWidgets_INCLUDE_DIRS})

#	if(WIN32)
#		set(wxWidgets_LIBRARY_DIRS "${wxWidgets_ROOT_DIR}/lib/vc_lib")
#	endif()
#	link_directories(${wxWidgets_LIBRARY_DIRS})
#
#	STRING(REGEX REPLACE ";" ";-D" wxWidgets_DEFINITIONS "${wxWidgets_DEFINITIONS}")
#	SET(wxWidgets_DEFINITIONS "-D${wxWidgets_DEFINITIONS}")
#    Message(STATUS "wxWidgets_DEFINITIONS : ${wxWidgets_DEFINITIONS}")
#    Message(STATUS "wxWidgets_LIBRARY : ${wxWidgets_LIBRARIES}")
#    mark_as_advanced(wxWidgets_LIBRARIES)
	# Don't use old boost versions interfaces
#	ADD_DEFINITIONS(${wxWidgets_DEFINITIONS})
#	ADD_DEFINITIONS(-D${wxUSE_UNICODE_DEFINE})
#	ADD_DEFINITIONS(-D${wxUSE_STATIC_DEFINE})
#endif ()

#find_package(curl)

#if (CURL_FOUND)
#	include_directories(${CURL_INCLUDE_DIR})
#endif ()
