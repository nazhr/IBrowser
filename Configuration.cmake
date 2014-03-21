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

###########################################################################
#
# Configuration
#
# Use cmake "-DIBROWSER_CUSTOM_CONFIG=YouFileCName" To define your personal settings
# where YouFileCName.cname must exist in one of the cmake include directories
# best to use cmake/SpecializedConfig/
#
# To not load defaults before loading custom values define
# -DIBROWSER_NO_DEFAULT_CONFIG=true
#
# WARNING: These variables will be cached like any other
#
###########################################################################

IF (NOT IBROWSER_NO_DEFAULT_CONFIG)

  # Disable Boost automatic linking
  # ADD_DEFINITIONS(-DBOOST_ALL_NO_LIB)

  IF (WIN32)

    MESSAGE(STATUS "Using default WIN32 Configuration settings")

    IF(MSVC)

      STRING(REGEX MATCH "(Win64)" _carch_x64 ${CMAKE_GENERATOR})
      IF(_carch_x64)
        SET(WINDOWS_ARCH "x64")
      ELSE(_carch_x64)
        SET(WINDOWS_ARCH "x86")
      ENDIF(_carch_x64)
      MESSAGE(STATUS "Building for target ${WINDOWS_ARCH}")

      SET(MSVC_RT_DEBUG_FIX 1)

    ELSE(MSVC)

    ENDIF(MSVC)

    IF(DEFINED ENV{IBROWSER_DEP_DIRS})
        SET(IBROWSER_DEP_DIRS $ENV{IBROWSER_DEP_DIRS})
        MESSAGE(STATUS "iBrowser build environment variables found")
        SET(BOOST_SEARCH_PATH       		"${IBROWSER_DEP_DIRS}/boost_1_53_0")
        SET(QT_DEP_DIR       				"D:/Source/depends/MT/Qt-4.8.5")
		#SET(wxWidgets_ROOT_DIR       		"${IBROWSER_DEP_DIRS}/wxWidgets-2.9.4")
		#SET(CURL_SEARCH_PATH       			"${IBROWSER_DEP_DIRS}/curl-7.34.0")
    ENDIF(DEFINED ENV{IBROWSER_DEP_DIRS})

  ELSE(WIN32)
    IF(DEFINED ENV{IBROWSER_DEP_DIRS})
        SET(IBROWSER_DEP_DIRS $ENV{IBROWSER_DEP_DIRS})
        MESSAGE(STATUS "iBrowser build environment variables found")
        SET(EIGEN_INCLUDE_DIR              "/usr/include")
    ENDIF(DEFINED ENV{IBROWSER_DEP_DIRS})
  ENDIF(WIN32)

ELSE(NOT IBROWSER_NO_DEFAULT_CONFIG)

  MESSAGE(STATUS "IBROWSER_NO_DEFAULT_CONFIG defined - not using default configuration values.")

ENDIF(NOT IBROWSER_NO_DEFAULT_CONFIG)

# Setup libraries output directory
SET (LIBRARY_OUTPUT_PATH
   ${PROJECT_BINARY_DIR}/lib
   CACHE PATH
   "Single Directory for all Libraries"
   )

# Setup binaries output directory
SET (CMAKE_RUNTIME_OUTPUT_DIRECTORY
	${PROJECT_BINARY_DIR}/bin
   CACHE PATH
   "Single Directory for all binaries"
	)

#
# Overwrite defaults with Custom Settings
#

IF (IBROWSER_CUSTOM_CONFIG)
	MESSAGE(STATUS "Using custom build config: ${IBROWSER_CUSTOM_CONFIG}")
	INCLUDE(${IBROWSER_CUSTOM_CONFIG})
ENDIF (IBROWSER_CUSTOM_CONFIG)


