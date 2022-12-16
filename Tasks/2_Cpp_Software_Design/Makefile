#==================================================================================================
#
#  Makefile for the chapter "C++ Software Design" of the C++ Training
#
#  Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================


# Compiler settings
CXX = g++
CXXFLAGS = -std=c++20


# Setting the source and binary files
SRC = $(wildcard *.cpp)
BIN = $(SRC:.cpp=)


# Rules
default: AcyclicVisitor Adapter Any Bridge Car_Bridge Car_Strategy Decorator_Creature \
         Decorator_Item ExternalPolymorphism Function1 Function2 Function_Ref \
         InplaceAny InplaceFunction ObjectOriented PolymorphicAllocator Procedural \
         Prototype Strategy Strategy_Benchmark Strategy_Benchmark_Full TypeErasure \
         TypeErasure_Ref UniquePtr_TypeErasure Variant Visitor Visitor_Benchmark \
         Visitor_Benchmark_Full

AcyclicVisitor: AcyclicVisitor.cpp
	$(CXX) $(CXXFLAGS) -o AcyclicVisitor AcyclicVisitor.cpp

Adapter: Adapter.cpp
	$(CXX) $(CXXFLAGS) -o Adapter Adapter.cpp

Any: Any.cpp
	$(CXX) $(CXXFLAGS) -o Any Any.cpp

Bridge: Bridge.cpp
	$(CXX) $(CXXFLAGS) -o Bridge Bridge.cpp

Car_Bridge: Car_Bridge.cpp
	$(CXX) $(CXXFLAGS) -o Car_Bridge Car_Bridge.cpp

Car_Strategy: Car_Strategy.cpp
	$(CXX) $(CXXFLAGS) -o Car_Strategy Car_Strategy.cpp

Decorator_Creature: Decorator_Creature.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_Creature Decorator_Creature.cpp

Decorator_Item: Decorator_Item.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_Item Decorator_Item.cpp

ExternalPolymorphism: ExternalPolymorphism.cpp
	$(CXX) $(CXXFLAGS) -o ExternalPolymorphism ExternalPolymorphism.cpp

Function1: Function1.cpp
	$(CXX) $(CXXFLAGS) -o Function1 Function1.cpp

Function2: Function2.cpp
	$(CXX) $(CXXFLAGS) -o Function2 Function2.cpp

Function_Ref: Function_Ref.cpp
	$(CXX) $(CXXFLAGS) -o Function_Ref Function_Ref.cpp

InplaceAny: InplaceAny.cpp
	$(CXX) $(CXXFLAGS) -o InplaceAny InplaceAny.cpp

InplaceFunction: InplaceFunction.cpp
	$(CXX) $(CXXFLAGS) -o InplaceFunction InplaceFunction.cpp

ObjectOriented: ObjectOriented.cpp
	$(CXX) $(CXXFLAGS) -o ObjectOriented ObjectOriented.cpp

PolymorphicAllocator: PolymorphicAllocator.cpp
	$(CXX) $(CXXFLAGS) -o PolymorphicAllocator PolymorphicAllocator.cpp

Procedural: Procedural.cpp
	$(CXX) $(CXXFLAGS) -o Procedural Procedural.cpp

Prototype: Prototype.cpp
	$(CXX) $(CXXFLAGS) -o Prototype Prototype.cpp

Strategy: Strategy.cpp
	$(CXX) $(CXXFLAGS) -o Strategy Strategy.cpp

Strategy_Benchmark: Strategy_Benchmark.cpp
	$(CXX) $(CXXFLAGS) -o Strategy_Benchmark Strategy_Benchmark.cpp

Strategy_Benchmark_Full: Strategy_Benchmark_Full.cpp
	$(CXX) $(CXXFLAGS) -o Strategy_Benchmark_Full Strategy_Benchmark_Full.cpp

TypeErasure: TypeErasure.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure TypeErasure.cpp

TypeErasure_Ref: TypeErasure_Ref.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_Ref TypeErasure_Ref.cpp

UniquePtr_TypeErasure: UniquePtr_TypeErasure.cpp
	$(CXX) $(CXXFLAGS) -o UniquePtr_TypeErasure UniquePtr_TypeErasure.cpp

Variant: Variant.cpp
	$(CXX) $(CXXFLAGS) -o Variant Variant.cpp

Visitor: Visitor.cpp
	$(CXX) $(CXXFLAGS) -o Visitor Visitor.cpp

Visitor_Benchmark: Visitor_Benchmark.cpp
	$(CXX) $(CXXFLAGS) -o Visitor_Benchmark Visitor_Benchmark.cpp

Visitor_Benchmark_Full: Visitor_Benchmark_Full.cpp
	$(CXX) $(CXXFLAGS) -o Visitor_Benchmark_Full Visitor_Benchmark_Full.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
