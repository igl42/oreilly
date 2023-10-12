#==================================================================================================
#
#  CMakeLists for the chapter "STL Algorithms" of the C++ Training
#
#  Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

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

add_executable(Fibonacci
   Fibonacci.cpp
   )

add_executable(IsEmailAddress
   IsEmailAddress.cpp
   )

add_executable(IsPalindrome
   IsPalindrome.cpp
   )

add_executable(IsPunct
   IsPunct.cpp
   )

add_executable(LongestStreak
   LongestStreak.cpp
   )

add_executable(Partition
   Partition.cpp
   )

add_executable(Ranges
   Ranges.cpp
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
   BadAccumulate
   BadCopy
   BadTransform
   ExtractStrings
   Fibonacci
   IsEmailAddress
   IsPalindrome
   IsPunct
   LongestStreak
   Partition
   Ranges
   STLintro
   STLpro
   Simpson
   SimpsonPro
   SortSubrange
   Trap
   PROPERTIES
   FOLDER "2_STL_Algorithms"
   )
