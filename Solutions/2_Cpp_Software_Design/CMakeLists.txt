#==================================================================================================
#
#  CMakeLists for the chapter "C++ Software Design" of the C++ Training
#
#  Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(Adapter_2
   Adapter_2.cpp
   )

add_executable(Adapter_3
   Adapter_3.cpp
   )

add_executable(Animal_EP
   Animal_EP.cpp
   )

add_executable(Animal_TE
   Animal_TE.cpp
   )

add_executable(Any_1
   Any_1.cpp
   )

add_executable(Any_2
   Any_2.cpp
   )

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

add_executable(Calculator_Command
   Calculator_Command.cpp
   )

add_executable(Command
   Command.cpp
   )

add_executable(ExternalPolymorphism
   ExternalPolymorphism.cpp
   )

add_executable(FastPimpl
   FastPimpl.cpp
   )

add_executable(Function_1
   Function_1.cpp
   )

add_executable(Function_2
   Function_2.cpp
   )

add_executable(Function_Ref_1
   Function_Ref_1.cpp
   )

add_executable(Function_Ref_2
   Function_Ref_2.cpp
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

add_executable(TypeErasure_MVF
   TypeErasure_MVF.cpp
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

add_executable(TypeErasure_SBO_MVF
   TypeErasure_SBO_MVF.cpp
   )

add_executable(Variant
   Variant.cpp
   )

add_executable(Visitor
   Visitor.cpp
   )

set_target_properties(
   Adapter_2
   Adapter_3
   Animal_EP
   Animal_TE
   Any_1
   Any_2
   Bridge_1
   Bridge_2
   Bridge_3
   Bridge_Static
   Calculator_Command
   Command
   ExternalPolymorphism
   FastPimpl
   Function_1
   Function_2
   Function_Ref_1
   Function_Ref_2
   PolymorphicAllocator
   Strategy
   TypeErasure
   TypeErasure_MVF
   TypeErasure_Ref_1
   TypeErasure_Ref_2
   TypeErasure_PolicyBased
   TypeErasure_SBO
   TypeErasure_SBO_MVF
   Variant
   Visitor
   PROPERTIES
   FOLDER "2_Cpp_Software_Design"
   )
