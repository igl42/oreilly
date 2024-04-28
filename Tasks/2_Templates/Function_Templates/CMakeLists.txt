#==================================================================================================
#
#  CMakeLists for subchapter "Function Templates" of chapter "Templates"
#
#  Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(Accumulate
   Accumulate.cpp
   )

add_executable(ArraySize
   ArraySize.cpp
   )

add_executable(Compare
   Compare.cpp
   )

add_executable(Find
   Find.cpp
   )

add_executable(Max
   Max.cpp
   )

add_executable(MinMax
   MinMax.cpp
   )

add_executable(StringViewAdd
   StringViewAdd.cpp
   )

set_target_properties(
   Accumulate
   ArraySize
   Compare
   Find
   Max
   MinMax
   StringViewAdd
   PROPERTIES
   FOLDER "2_Templates/Function_Templates"
   )
