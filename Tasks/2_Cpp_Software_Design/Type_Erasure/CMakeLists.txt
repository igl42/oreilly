#==================================================================================================
#
#  CMakeLists for subchapter "Type Erasure" of chapter "C++ Software Design"
#
#  Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(Animal_TE
   Animal_TE.cpp
   )

add_executable(Any_1
   Any_1.cpp
   )

add_executable(Any_2
   Any_2.cpp
   )

add_executable(Function_1
   Function_1.cpp
   )

add_executable(Function_2
   Function_2.cpp
   )

add_executable(Function_Ref
   Function_Ref.cpp
   )

add_executable(InplaceAny
   InplaceAny.cpp
   )

add_executable(InplaceFunction
   InplaceFunction.cpp
   )

add_executable(PolymorphicAllocator
   PolymorphicAllocator.cpp
   )

add_executable(TypeErasure_1
   TypeErasure_1.cpp
   )

add_executable(TypeErasure_2
   TypeErasure_2.cpp
   )

add_executable(TypeErasure_MVF
   TypeErasure_MVF.cpp
   )

add_executable(TypeErasure_Ref
   TypeErasure_Ref.cpp
   )

add_executable(TypeErasure_SBO_1
   TypeErasure_SBO_1.cpp
   )

add_executable(TypeErasure_SBO_2
   TypeErasure_SBO_2.cpp
   )

add_executable(UniquePtr_TypeErasure
   UniquePtr_TypeErasure.cpp
   )

set_target_properties(
   Animal_TE
   Any_1
   Any_2
   Function_1
   Function_2
   Function_Ref
   InplaceAny
   InplaceFunction
   PolymorphicAllocator
   TypeErasure_1
   TypeErasure_2
   TypeErasure_MVF
   TypeErasure_Ref
   TypeErasure_SBO_1
   TypeErasure_SBO_2
   UniquePtr_TypeErasure
   PROPERTIES
   FOLDER "2_Cpp_Software_Design/Type_Erasure"
   )
