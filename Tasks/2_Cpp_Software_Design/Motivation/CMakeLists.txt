#==================================================================================================
#
#  CMakeLists for subchapter "Motivation" of chapter "C++ Software Design"
#
#  Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(DataOriented
   DataOriented.cpp
   )

add_executable(ObjectOriented
   ObjectOriented.cpp
   )

add_executable(Procedural
   Procedural.cpp
   )

set_target_properties(
   DataOriented
   ObjectOriented
   Procedural
   PROPERTIES
   FOLDER "2_Cpp_Software_Design/Motivation"
   )
