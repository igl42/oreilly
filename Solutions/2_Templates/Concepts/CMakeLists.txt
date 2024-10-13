#==================================================================================================
#
#  CMakeLists for subchapter "Concepts" of chapter "C++ Templates"
#
#  Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(AssociativeContainer
   AssociativeContainer.cpp
   )

add_executable(Constraints2
   Constraints2.cpp
   )

add_executable(IsPalindrome_Concepts
   IsPalindrome_Concepts.cpp
   )

add_executable(Max_Concept
   Max_Concept.cpp
   )

add_executable(NarrowConversion2
   NarrowConversion2.cpp
   )

add_executable(Optional_Cpp20
   Optional_Cpp20.cpp
   )

add_executable(Optional_Trivial_1
   Optional_Trivial_1.cpp
   )

add_executable(SequenceContainer
   SequenceContainer.cpp
   )

add_executable(Sign2
   Sign2.cpp
   )

add_executable(UniquePtr_Concepts
   UniquePtr_Concepts.cpp
   )

set_target_properties(
   AssociativeContainer
   Constraints2
   IsPalindrome_Concepts
   Max_Concept
   NarrowConversion2
   Optional_Cpp20
   Optional_Trivial_1
   SequenceContainer
   Sign2
   UniquePtr_Concepts
   PROPERTIES
   FOLDER "2_Templates/Concepts"
   )
