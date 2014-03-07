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

MESSAGE(STATUS "CMAKE VERSION DETECTED " ${CMAKE_VERSION})
###########################################################################
#
# Check and configure cmake
#
###########################################################################

cmake_minimum_required(VERSION 2.8)
cmake_policy(VERSION 2.8)
#Remove the following when the version check is at least 2.8.4
SET(CMAKE_LEGACY_CYGWIN_WIN32 0)

project(iBrowser)

# Dont overconfigure
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE STRING "limit configs" FORCE)

###########################################################################
#
# Include necessary submodules
#
###########################################################################

set(CMAKE_MODULE_PATH
	"${PROJECT_SOURCE_DIR}"
	"${PROJECT_SOURCE_DIR}/cmake"
	"${PROJECT_SOURCE_DIR}/cmake/Utils"
	"${PROJECT_SOURCE_DIR}/cmake/Packages"
	"${PROJECT_SOURCE_DIR}/cmake/SpecializedConfig"
)

INCLUDE(Configuration)
INCLUDE(PlatformSpecific)

# Install CMake modules
#add_subdirectory(CMake)


SET(IBROWSER_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
SET(IBROWSER_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}")

SET(IBROWSER_INCLUDE_DIR "${IBROWSER_SOURCE_DIR}/include")
include_directories("${IBROWSER_INCLUDE_DIR}")
include_directories("${IBROWSER_BUILD_DIR}/include")

# When using single configuration generators like make
# cmake does need to know which of the possible configurations
# to generate
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)
SET(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "assure config" FORCE) # makes sure type is shown in cmake gui

message(STATUS "Building mode: " ${CMAKE_BUILD_TYPE})

# Find dependencies
include(Dependencies)

if (NOT Boost_FOUND)
	MESSAGE(FATAL_ERROR "--> Could not locate required Boost files - Please check ${BOOST_SEARCH_PATH}")
endif()

#if (NOT wxWidgets_FOUND)
#	MESSAGE(FATAL_ERROR "--> Could not locate required wxWidgets files - Please check ${wxWidgets_ROOT_DIR}")
#endif()

set(IBROWSER_VERSION_MAJOR 0)
set(IBROWSER_VERSION_MINOR 1)

# Configure a header file to pass some of the CMake settings
# to the source code
configure_file(
  "${IBROWSER_SOURCE_DIR}/include/config.h.in"
  "${IBROWSER_BUILD_DIR}/include/config.h"
  )

IF (NOT WIN32)
    STRING(REGEX MATCH "Release" _build_release ${CMAKE_BUILD_TYPE})
    if(_build_release)
        add_definitions( -DNDEBUG )
    else()
        add_definitions( -D_DEBUG )
    endif()
endif(NOT WIN32)

add_subdirectory(src/ibrowser)
#add_subdirectory(src/utils)

###########################################################################
#
# For non win32 we'll have to copy everything to a single dir
#
###########################################################################

INCLUDE(AssembleBinDirs)
