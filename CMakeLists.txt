###############################################################################
#
# A generalized cmake file for developing cross-platform games.
#
# Copyright (C) 2010 Sarah Eris Horsley Caffee
#
# This is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
#
# Instructions:
# This cmake file assumes that your source files are laid in out in the 
# following manner:
#
#   project_dir\		Top level directory of the project.
#     |---include\		Header files are here.
#     |---src\			Source files are here.
#     |---test\			Test files are here.
#     |---build\		Binaries/objects go here.  Run cmake from here.
#     !---cmake\
#     |     |---modules\        Custom cmake include files, if any, go here.
#     |---CMakeLists.txt	This file.
#
# You may have more directories, of course, but these are assumed.  You probably
# want more than one build directory.  I normally have build-linux\ 
# and build-windows\ directories.
#
# Set the App_Name variable, below, to the name of your application and you
# are ready to start.  Run ccmake, or cmake-gui from within your build
# directory, choose the options you need, such as enabling SDL, and you 
# should be good to go.
#
# You can uncomment the "SET (CMAKE_VERBOSE_MAKEFILE ON) command if you
# need to debug the actual makefile that is generated.
#
# On windows, you may need to set the SDLDIR environment variable to the location
# of your SDL installation before you run cmake-gui.
#
# When writing path names on Windows, such as when manually specifiying a 
# file or directory name, either use unix-style forward slashes '/' in the
# path names or use double backslashes. If you use a single backslash as the
# path name seperator, then cmake will interpret  it as an esacpe sequence.
# Thus, write "C:/source" or "C:\\source" instead of "C:\source".  It's
# probably best to use forward slashes in case to ever have a situation
# where cmake needs to do recursive processing: each level of cmake will
# strip out one of the slashes, so if there are two lev3els of cmake you
# need to write \\\, three levels requires \\\\, etc.
#
# Note that some of the cmake support scripts that find libraries for you
# can be controlled by environment variables.  For example, you can set the
# SDLDIR environment variable before running cmake in order to point to
# a different version of SDL than your systems default copy. This is useful
# for trying out cutting edge versions of libraries without installing them
# system wide.

cmake_minimum_required (VERSION 2.6 FATAL_ERROR)
#set (CMAKE_VERBOSE_MAKEFILE ON)

# Name your program!
set (App_Name "Math")
if (App_Name STREQUAL "") 
  message (FATAL_ERROR "You must set the App_Name variable!")
endif ()

# Every project must have a name.
project (${App_Name})


# You may specify an application description, too.  This will be passed to
# Doxygen, if you use that.
set (App_Description "3D math library for games.")


################################################################################
# Special options


################################################################################
# Ensure that we are not building in our source directories.

set (Build_Dir_OK "TRUE")
string (REGEX MATCH "^${CMAKE_SOURCE_DIR}" In_Sub_Dir ${CMAKE_BINARY_DIR})
if (In_Sub_Dir)
  string (REGEX MATCH "^${CMAKE_SOURCE_DIR}/build" In_Build_Dir ${CMAKE_BINARY_DIR})
  if (NOT In_Build_Dir)
    set (Build_Dir_OK "FALSE")
  endif ()
endif ()

if (NOT Build_Dir_OK)
  message (FATAL_ERROR "You must run cmake from a directory that is not in your source tree, or that is in a special subdirectory of the tree whose name begins with 'build'.")
endif ()


################################################################################
# Set up the basic build environment
# A build type defines which options are passed to the compiler, and there are
# several that CMake defines by default. It does not set one by default, though
# so we need to set the build type manually here, and we are setting it to the
# generally useful "Release with debug info"

if (CMAKE_BUILD_TYPE STREQUAL "")
  # CMake defaults to leaving CMAKE_BUILD_TYPE empty. This messes up
  # differentiation between debug and release builds.               
  set (CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif ()


################################################################################
# When using GCC turn on lots of warnings.
# Some other options to consider:
#   C++  -Weffc++
#   C    -std=gnu99 -std=c99

if (CMAKE_COMPILER_IS_GNUCXX)
  add_definitions( -std=gnu++11 )
#  add_definitions(-pedantic -Wall)
endif ()

################################################################################
# Other miscellaneous compiler options

#if (CMAKE_COMPILER_IS_GNUCXX)
#  # Allow anonymous structs
#  add_definitions(-fms-extensions)
#endif ()

################################################################################
# Build for profiling.

option(Option_Profile_Program "Build for gprof profiling." OFF)
if (Option_Profile_Program)
  add_definitions(-pg)
  set (CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pg")
endif ()


################################################################################
# The core project files 

 
# Not GLOBing here so that I can explicitly list main.cpp later as part of the 
# test driver.  Also, it just seems good practice to explicitly list things since
# it avoids accidental inclusion of things that ought not to be included.
set (SRCS_${App_Name}
  include/Math.h
  include/Vector.h
  include/Matrix.h
)

include_directories (
  ${PROJECT_SOURCE_DIR}/include
)

# Build both static and shared libraries
# The target properties are needed because, by default, the output name
# will be the name in the add_library command, and we need to have different
# names in the two commands for the shared and static versions, even though
# we want the final files to have the same names with different extensions.
#
# The prefix is needed mostly in case we build on windows, which has no prefix
# by default.
# 
# The clean_direct_output option makes sure that the two lib builds don't
# clobber each others temp files since they are being built from the same
# sources.

#add_library (${App_Name} SHARED
#  ${SRCS_${App_Name}}
#)
#set_target_properties (${App_Name} PROPERTIES OUTPUT_NAME ${App_Name})
#set_target_properties (${App_Name} PROPERTIES PREFIX "lib")
#set_target_properties (${App_Name} PROPERTIES CLEAN_DIRECT_OUTPUT 1)
#
#add_library (${App_Name}-static STATIC
#  ${SRCS_${App_Name}}
#)
#set_target_properties (${App_Name}-static PROPERTIES OUTPUT_NAME ${App_Name})
#set_target_properties (${App_Name}-static PROPERTIES PREFIX "lib")
#set_target_properties (${App_Name}-static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

# Build a test application.
    set (GTEST_INCLUDE_DIR "/home/eris/gamedev/deps/gtest/current/include")
    set (GTEST_LIB_DIR "/home/eris/gamedev/deps/gtest/current/build")

link_directories (
  ${GTEST_LIB_DIR}
  )

include_directories (
  ${CMAKE_SOURCE_DIR}/include
  ${GTEST_INCLUDE_DIR}
  )

add_executable (${App_Name}-test
  test/main.cpp
)

target_link_libraries (${App_Name}-test
  libgtest.a
  pthread
)

################################################################################
# Doxygen documentation
#
# - Create a directory named docs to hold your Doxygen config and standalone
#   (.dox) files.
# - Name your Doxyfile config as "docs/Doxyfile.in".
# - In that file, set the following variables as shown, adjusting INPUT as
#   needed to reflect the actual location of the fiels you wnat processed.
#
# PROJECT_NAME           = "@App_Name@"
# PROJECT_BRIEF          = "@App_Description@"
# STRIP_FROM_PATH        = @CMAKE_CURRENT_SOURCE_DIR@
# INPUT                  = @CMAKE_CURRENT_SOURCE_DIR@/src/ @CMAKE_CURRENT_SOURCE_DIR@/include/ @CMAKE_CURRENT_SOURCE_DIR@/docs/
#
# Then you can generate the docs with "make docs" and this will create a "docs" directory under your build directory.
# 

option(Option_Doxygen "Generate Doxygen documentation." ON)

if (Option_Doxygen)

  find_package(Doxygen)
  if (NOT DOXYGEN_FOUND)
    message (FATAL_ERROR "Doxygen not found!")
  endif ()

  configure_file (${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile @ONLY)

  add_custom_target(docs
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/docs/Doxyfile
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating API documentation with Doxygen" VERBATIM
    )

endif ()

################################################################################
# Google Test C++ Unit testing framework

option (Option_GTEST "Google Test" ON)

if (Option_GTEST)
    set (GTEST_INCLUDE_DIR "/home/eris/gamedev/deps/gtest/current/include")
    set (GTEST_LIB_DIR "/home/eris/gamedev/deps/gtest/current/build")
endif ()

