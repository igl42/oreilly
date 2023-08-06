#==================================================================================================
#
#  CMakeLists for the chapter "Templates" of the C++ Training
#
#  Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
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

add_executable(AddSub
   AddSub.cpp
   )

add_executable(ArraySize
   ArraySize.cpp
   )

add_executable(CartesianProduct
   CartesianProduct.cpp
   )

add_executable(Compare
   Compare.cpp
   )

add_executable(Find
   Find.cpp
   )

add_executable(FixedVector
   FixedVector.cpp
   )

add_executable(MakeUnique
   MakeUnique.cpp
   )

add_executable(Max
   Max.cpp
   )

add_executable(MinMax
   MinMax.cpp
   )

add_executable(PackEnumeration
   PackEnumeration.cpp
   )

add_executable(PackIndexing
   PackIndexing.cpp
   )

add_executable(Print
   Print.cpp
   )

add_executable(Sum
   Sum.cpp
   )

add_executable(UniquePtr1
   UniquePtr1.cpp
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

add_executable(Vector1
   Vector1.cpp
   )

add_executable(Vector2
   Vector2.cpp
   )

set_target_properties(
   Accumulate
   AddSub
   ArraySize
   CartesianProduct
   Compare
   Find
   FixedVector
   MakeUnique
   Max
   MinMax
   PackEnumeration
   PackIndexing
   Print
   Sum
   UniquePtr1
   VariadicMax
   VariadicMinMax
   VariantIndex
   Vector1
   Vector2
   PROPERTIES
   FOLDER "2_Templates"
   )
