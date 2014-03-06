###########################################################################
#   Copyright (C) 2013 by sanpolo CO.LTD                                  #
#                                                                         #
#   This file is part of GUtil.                                           #
#                                                                         #
#   GUtil is private software.                                            #
#                                                                         #
#   GUtil is distributed as the integration with glue.used for software   #
#   interact with glue.                                                   #
#                                                                         #
#   You should have received a copy of the GLUE License along with this   #
#   program.  If not, see <http://www.render001.com/licenses>.            #
#                                                                         #
#   GUtil website: http://www.render001.com/gutil                         #
###########################################################################

###########################################################################
#
# Binary samples directory
#
###########################################################################

IF (WIN32)
	
  # For MSVC moving exe files gets done automatically
  # If there is someone compiling on windows and
  # not using msvc (express is free) - feel free to implement

ELSE (WIN32)
	set(CMAKE_INSTALL_PREFIX .)

ENDIF(WIN32)