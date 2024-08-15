#==================================================================================================
#
#  CMakeLists for subchapter "Algorithms" of chapter "Concepts and the STL"
#
#  Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
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

add_executable(CartesianProduct
   CartesianProduct.cpp
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

add_executable(MajorityVote
   MajorityVote.cpp
   )

add_executable(Median
   Median.cpp
   )

add_executable(Partition
   Partition.cpp
   )

add_executable(RangesRefactoring_1
   RangesRefactoring_1.cpp
   )

add_executable(RangesRefactoring_2
   RangesRefactoring_2.cpp
   )

add_executable(RangesRefactoring_3
   RangesRefactoring_3.cpp
   )

add_executable(RangesRefactoring_4
   RangesRefactoring_4.cpp
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

add_executable(STLintro
   STLintro.cpp
   )

add_executable(STLpro
   STLpro.cpp
   )

add_executable(Trap
   Trap.cpp
   )

set_target_properties(
   BadAccumulate
   BadCopy
   BadTransform
   CartesianProduct
   ExtractStrings
   Fibonacci
   IsEmailAddress
   IsPalindrome
   IsPunct
   LongestStreak
   MajorityVote
   Median
   Partition
   RangesRefactoring_1
   RangesRefactoring_2
   RangesRefactoring_3
   RangesRefactoring_4
   Simpson
   SimpsonPro
   SortSubrange
   STLintro
   STLpro
   Trap
   PROPERTIES
   FOLDER "3_Concepts_and_STL/Algorithms"
   )
