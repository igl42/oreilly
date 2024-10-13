#==================================================================================================
#
#  CMakeLists for subchapter "Variadic Templates" of chapter "Templates"
#
#  Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(AddSub
   AddSub.cpp
   )

add_executable(VariadicCartesianProduct
   VariadicCartesianProduct.cpp
   )

add_executable(HigherOrder
   HigherOrder.cpp
   )

add_executable(MakeUnique
   MakeUnique.cpp
   )

add_executable(Print
   Print.cpp
   )

add_executable(PrintTuple
   PrintTuple.cpp
   )

add_executable(Sum
   Sum.cpp
   )

add_executable(VariadicMax
   VariadicMax.cpp
   )

add_executable(VariadicMinMax
   VariadicMinMax.cpp
   )

add_executable(VariantIndex
   VariantIndex.cpp
   )

set_target_properties(
   AddSub
   HigherOrder
   MakeUnique
   Print
   PrintTuple
   Sum
   VariadicCartesianProduct
   VariadicMax
   VariadicMinMax
   VariantIndex
   PROPERTIES
   FOLDER "2_Templates/Variadic_Templates"
   )
