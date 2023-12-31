#==================================================================================================
#
#  CMakeLists for chapter "C++ Software Design" of the C++ Training
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

add_executable(Bridge
   Bridge.cpp
   )

add_executable(Car_Bridge
   Car_Bridge.cpp
   )

add_executable(Car_Strategy
   Car_Strategy.cpp
   )

add_executable(Command
   Command.cpp
   )

add_executable(DataOriented
   DataOriented.cpp
   )

add_executable(ExpressionTemplates
   ExpressionTemplates.cpp
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

add_executable(Function_Ref
   Function_Ref.cpp
   )

add_executable(InplaceAny
   InplaceAny.cpp
   )

add_executable(InplaceFunction
   InplaceFunction.cpp
   )

add_executable(ObjectOriented
   ObjectOriented.cpp
   )

add_executable(PolymorphicAllocator
   PolymorphicAllocator.cpp
   )

add_executable(Procedural
   Procedural.cpp
   )

add_executable(Prototype
   Prototype.cpp
   )

add_executable(Strategy
   Strategy.cpp
   )

add_executable(Strategy_Benchmark
   Strategy_Benchmark.cpp
   )

add_executable(TypeErasure
   TypeErasure.cpp
   )

add_executable(TypeErasure_Ref
   TypeErasure_Ref.cpp
   )

add_executable(UniquePtr_TypeErasure
   UniquePtr_TypeErasure.cpp
   )

add_executable(Variant
   Variant.cpp
   )

add_executable(Visitor
   Visitor.cpp
   )

add_executable(Visitor_Benchmark
   Visitor_Benchmark.cpp
   )

set_target_properties(
   AcyclicVisitor
   Animal_EP
   Animal_TE
   Any_1
   Any_2
   Bridge
   Car_Bridge
   Car_Strategy
   Command
   DataOriented
   ExpressionTemplates
   ExternalPolymorphism
   FastPimpl
   Function_1
   Function_2
   Function_Ref
   InplaceAny
   InplaceFunction
   ObjectOriented
   PolymorphicAllocator
   Procedural
   Prototype
   Strategy
   Strategy_Benchmark
   TypeErasure
   TypeErasure_Ref
   UniquePtr_TypeErasure
   Variant
   Visitor
   Visitor_Benchmark
   PROPERTIES
   FOLDER "2_Cpp_Software_Design"
   )
