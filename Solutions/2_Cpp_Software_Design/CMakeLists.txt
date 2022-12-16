#==================================================================================================
#
#  CMakeLists for the chapter "C++ Software Design" of the C++ Training
#
#  Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(Bridge_1
   Bridge_1.cpp
   )

add_executable(Bridge_2
   Bridge_2.cpp
   )

add_executable(Bridge_3
   Bridge_3.cpp
   )

add_executable(Bridge_Static
   Bridge_Static.cpp
   )

add_executable(Decorator_Creature_1
   Decorator_Creature_1.cpp
   )

add_executable(Decorator_Creature_2
   Decorator_Creature_2.cpp
   )

add_executable(Decorator_Item_1
   Decorator_Item_1.cpp
   )

add_executable(Decorator_Item_2
   Decorator_Item_2.cpp
   )

add_executable(ExternalPolymorphism
   ExternalPolymorphism.cpp
   )

add_executable(Function1
   Function1.cpp
   )

add_executable(Function2
   Function2.cpp
   )

add_executable(Function_Ref
   Function_Ref.cpp
   )

add_executable(PolymorphicAllocator
   PolymorphicAllocator.cpp
   )

add_executable(Strategy
   Strategy.cpp
   )

add_executable(TypeErasure
   TypeErasure.cpp
   )

add_executable(TypeErasure_Manual
   TypeErasure_Manual.cpp
   )

add_executable(TypeErasure_PolicyBased
   TypeErasure_PolicyBased.cpp
   )

add_executable(TypeErasure_Ref_1
   TypeErasure_Ref_1.cpp
   )

add_executable(TypeErasure_Ref_2
   TypeErasure_Ref_2.cpp
   )

add_executable(TypeErasure_SBO
   TypeErasure_SBO.cpp
   )

add_executable(TypeErasure_SBO_Manual
   TypeErasure_SBO_Manual.cpp
   )

add_executable(Variant
   Variant.cpp
   )

add_executable(Visitor
   Visitor.cpp
   )

set_target_properties(
   Bridge_1
   Bridge_2
   Bridge_3
   Bridge_Static
   Decorator_Creature_1
   Decorator_Creature_2
   Decorator_Item_1
   Decorator_Item_2
   ExternalPolymorphism
   Function1
   Function2
   Function_Ref
   PolymorphicAllocator
   Strategy
   TypeErasure
   TypeErasure_Manual
   TypeErasure_Ref_1
   TypeErasure_Ref_2
   TypeErasure_PolicyBased
   TypeErasure_SBO
   TypeErasure_SBO_Manual
   Variant
   Visitor
   PROPERTIES
   FOLDER "2_Cpp_Software_Design"
   )
