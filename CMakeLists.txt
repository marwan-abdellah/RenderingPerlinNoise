#####################################################################
# Copyright © 2011-2012,
# Marwan Abdellah: <abdellah.marwan@gmail.com>
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation.

# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.

# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
# MA 02110-1301, USA.
#####################################################################

#########################################################
#! Minimum required CMake version
#########################################################
cmake_minimum_required(VERSION 2.6)

#########################################################
#! Project name
#########################################################
PROJECT(MultiGLContexts)

#########################################################
#! Add CMake customized modules
#########################################################
SET(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

#########################################################
#! Find packages
#########################################################
# @FFTW
# INCLUDE(Find_FFTW)

# @CUDA
#INCLUDE(Find_CUDA)

# @CUDA GPU Computing SDK
#INCLUDE(Find_CUDA_SDK)

# @Cocoa for Apple
#INCLUDE(Find_Cocoa)

# @OpenGL
INCLUDE(Find_OpenGL)

# @GLUT
INCLUDE(Find_GLUT)

# @GLEW
INCLUDE(Find_GLEW)

# @X11 supporting libraries
INCLUDE(Find_X11)

# @Cg NVIDIA
#INCLUDE(Find_Cg)

# @OpenMP
INCLUDE(Find_OpenMP)

# @ImageMagick
#INCLUDE(Find_ImageMagick)

# @Boost
#INCLUDE(Find_Boost)

# Include directories 
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

#########################################################
#! Compiler Flags
#########################################################
set(CMAKE_C_FLAGS " -DUSE_EXPORT_KEYWORD -fpermissive -fPIC -pthread -pipe -DLINUX -D_BOOL -DREQUIRE_IOSTREAM -Wno-deprecated -fno-gnu-keywords -w")
set(CMAKE_CXX_FLAGS "${CMAKE_C_FLAGS}")

#########################################################
#! Link the executable against the cuYURI library
#########################################################
ADD_EXECUTABLE(runMWindow MultiWindow.cpp)
ADD_EXECUTABLE(runMWidget MultiWidget.cpp)

