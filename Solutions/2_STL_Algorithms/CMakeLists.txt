#==================================================================================================
#
#  CMakeLists for the chapter "STL Algorithms" of the C++ Training
#
#  Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

add_executable(Accumulate
   Accumulate.cpp
   )

add_executable(BadAccumulate
   BadAccumulate.cpp
   )

add_executable(BadCopy
   BadCopy.cpp
   )

add_executable(BadTransform
   BadTransform.cpp
   )

add_executable(ExtractStrings
   ExtractStrings.cpp
   )

add_executable(IsPalindrome
   IsPalindrome.cpp
   )

add_executable(LongestStreak
   LongestStreak.cpp
   )

add_executable(Partition
   Partition.cpp
   )

add_executable(STLintro
   STLintro.cpp
   )

add_executable(STLpro
   STLpro.cpp
   )

add_executable(Simpson
   Simpson.cpp
   )

add_executable(SimpsonPro
   SimpsonPro.cpp
   )

add_executable(SortSubrange
   SortSubrange.cpp
   )

add_executable(Trap
   Trap.cpp
   )

set_target_properties(
   Accumulate
   BadAccumulate
   BadCopy
   BadTransform
   ExtractStrings
   IsPalindrome
   LongestStreak
   Partition
   STLintro
   STLpro
   Simpson
   SimpsonPro
   SortSubrange
   Trap
   PROPERTIES
   FOLDER "2_STL_Algorithms"
   )
