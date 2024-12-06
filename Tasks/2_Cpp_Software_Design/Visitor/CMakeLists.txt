#==================================================================================================
#
#  CMakeLists for subchapter "Visitor" of chapter "C++ Software Design"
#
#  Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(AcyclicVisitor
   AcyclicVisitor.cpp
   )

add_executable(Variant
   Variant.cpp
   )

add_executable(Visitor_Benchmark
   Visitor_Benchmark.cpp
   )

add_executable(Visitor_Classic
   Visitor_Classic.cpp
   )

add_executable(Visitor_Refactoring
   Visitor_Refactoring.cpp
   )

set_target_properties(
   AcyclicVisitor
   Variant
   Visitor_Benchmark
   Visitor_Classic
   Visitor_Refactoring
   PROPERTIES
   FOLDER "2_Cpp_Software_Design/Visitor"
   )
