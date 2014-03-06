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

IF (WIN32)
	FIND_PATH( CURL_INCLUDE_PATH curl/curl.h
		${CURL_SEARCH_PATH}/include
		DOC "The directory where curl/curl.h resides")
	FIND_LIBRARY( CURL_LIBRARY
		NAMES curl
		PATHS
		${CURL_SEARCH_PATH}/lib/Debug
		${CURL_SEARCH_PATH}/lib/Release
		DOC "The curl library")
ELSE (WIN32)
	FIND_PATH( CURL_INCLUDE_PATH curl/curl.h
		/usr/include
		/usr/local/include
		/sw/include
		/opt/local/include
		DOC "The directory where curl/curl.h resides")
	FIND_LIBRARY( CURL_LIBRARY
		NAMES curl
		PATHS
		/usr/lib64
		/usr/lib
		/usr/local/lib64
		/usr/local/lib
		/sw/lib
		/opt/local/lib
		DOC "The curl library")
ENDIF (WIN32)

IF (CURL_INCLUDE_PATH)
	SET( CURL_FOUND 1 CACHE STRING "Set to 1 if curl is found, 0 otherwise")
ELSE (CURL_INCLUDE_PATH)
	SET( CURL_FOUND 0 CACHE STRING "Set to 1 if curl is found, 0 otherwise")
ENDIF (CURL_INCLUDE_PATH)

MARK_AS_ADVANCED( CURL_FOUND )