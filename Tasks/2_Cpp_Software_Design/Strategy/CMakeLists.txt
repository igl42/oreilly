#==================================================================================================
#
#  CMakeLists for subchapter "Strategy" of chapter "C++ Software Design"
#
#  Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(FixedVector_Strategy
   FixedVector_Strategy.cpp
   )

add_executable(MultipleStrategies
   MultipleStrategies.cpp
   )

add_executable(Strategy_Benchmark
   Strategy_Benchmark.cpp
   )

add_executable(Strategy_Classic
   Strategy_Classic.cpp
   )

add_executable(Strategy_Refactoring
   Strategy_Refactoring.cpp
   )

add_executable(Strategy_Static
   Strategy_Static.cpp
   )

add_executable(UniquePtr_Strategy
   UniquePtr_Strategy.cpp
   )

set_target_properties(
   FixedVector_Strategy
   MultipleStrategies
   Strategy_Benchmark
   Strategy_Classic
   Strategy_Refactoring
   Strategy_Static
   UniquePtr_Strategy
   PROPERTIES
   FOLDER "2_Cpp_Software_Design/Strategy"
   )
