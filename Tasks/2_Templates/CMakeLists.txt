#==================================================================================================
#
#  CMakeLists for the chapter "Templates" of the C++ Training
#
#  Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
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

add_executable(AddSub
   AddSub.cpp
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

add_executable(IsConst
   IsConst.cpp
   )

add_executable(IsPointer
   IsPointer.cpp
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

add_executable(Print
   Print.cpp
   )

add_executable(RemoveConst
   RemoveConst.cpp
   )

add_executable(RemoveCV
   RemoveCV.cpp
   )

add_executable(StringViewAdd
   StringViewAdd.cpp
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

add_executable(Vector2
   Vector2.cpp
   )

set_target_properties(
   Accumulate
   AddSub
   ArraySize
   Compare
   Find
   IsConst
   IsPointer
   MakeUnique
   Max
   MinMax
   Print
   RemoveConst
   RemoveCV
   StringViewAdd
   Sum
   UniquePtr1
   VariadicMax
   VariadicMinMax
   VariantIndex
   Vector2
   PROPERTIES
   FOLDER "2_Templates"
   )
