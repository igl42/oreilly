#==================================================================================================
#
#  CMakeLists for subchapter "Class Templates" of chapter "Templates"
#
#  Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(FixedVector1
   FixedVector1.cpp
   )

add_executable(UniquePtr1
   UniquePtr1.cpp
   )

add_executable(Vector1
   Vector1.cpp
   )

add_executable(Vector2
   Vector2.cpp
   )

set_target_properties(
   FixedVector1
   UniquePtr1
   Vector1
   Vector2
   PROPERTIES
   FOLDER "2_Templates/Class_Templates"
   )
