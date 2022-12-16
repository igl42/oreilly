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

add_executable(AcyclicVisitor
   AcyclicVisitor.cpp
   )

add_executable(Adapter
   Adapter.cpp
   )

add_executable(Any
   Any.cpp
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

add_executable(Decorator_Creature
   Decorator_Creature.cpp
   )

add_executable(Decorator_Item
   Decorator_Item.cpp
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

add_executable(Strategy_Benchmark_Full
   Strategy_Benchmark_Full.cpp
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

add_executable(Visitor_Benchmark_Full
   Visitor_Benchmark_Full.cpp
   )

set_target_properties(
   AcyclicVisitor
   Adapter
   Any
   Bridge
   Car_Bridge
   Car_Strategy
   Decorator_Creature
   Decorator_Item
   ExternalPolymorphism
   Function1
   Function2
   Function_Ref
   InplaceAny
   InplaceFunction
   ObjectOriented
   PolymorphicAllocator
   Procedural
   Prototype
   Strategy
   Strategy_Benchmark
   Strategy_Benchmark_Full
   TypeErasure
   TypeErasure_Ref
   UniquePtr_TypeErasure
   Variant
   Visitor
   Visitor_Benchmark
   Visitor_Benchmark_Full
   PROPERTIES
   FOLDER "2_Cpp_Software_Design"
   )
