#==================================================================================================
#
#  Makefile for the chapter "C++ Software Design" of the C++ Training
#
#  Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
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
default: AcyclicVisitor Adapter_1 Adapter_2 Adapter_3 Animal_EP Animal_TE Any_1 Any_2 \
         Bridge Calculator_Command Calculator_Strategy Car_Bridge Car_Strategy Command \
         ExternalPolymorphism FastPimpl Function_1 Function_2 \
         Function_Ref InplaceAny InplaceFunction ObjectOriented PolymorphicAllocator \
         Procedural Prototype Strategy Strategy_Benchmark TypeErasure TypeErasure_MVF \
         TypeErasure_Ref TypeErasure_SBO UniquePtr_TypeErasure Variant Visitor \
         Visitor_Benchmark

AcyclicVisitor: AcyclicVisitor.cpp
	$(CXX) $(CXXFLAGS) -o AcyclicVisitor AcyclicVisitor.cpp

Adapter_1: Adapter_1.cpp
	$(CXX) $(CXXFLAGS) -o Adapter_1 Adapter_1.cpp

Adapter_2: Adapter_2.cpp
	$(CXX) $(CXXFLAGS) -o Adapter_2 Adapter_2.cpp

Adapter_3: Adapter_3.cpp
	$(CXX) $(CXXFLAGS) -o Adapter_3 Adapter_3.cpp

Animal_EP: Animal_EP.cpp
	$(CXX) $(CXXFLAGS) -o Animal_EP Animal_EP.cpp

Animal_TE: Animal_TE.cpp
	$(CXX) $(CXXFLAGS) -o Animal_TE Animal_TE.cpp

Any_1: Any_1.cpp
	$(CXX) $(CXXFLAGS) -o Any_1 Any_1.cpp

Any_2: Any_2.cpp
	$(CXX) $(CXXFLAGS) -o Any_2 Any_2.cpp

Bridge: Bridge.cpp
	$(CXX) $(CXXFLAGS) -o Bridge Bridge.cpp

Calculator_Command: Calculator_Command.cpp
	$(CXX) $(CXXFLAGS) -o Calculator_Command Calculator_Command.cpp

Calculator_Strategy: Calculator_Strategy.cpp
	$(CXX) $(CXXFLAGS) -o Calculator_Strategy Calculator_Strategy.cpp

Car_Bridge: Car_Bridge.cpp
	$(CXX) $(CXXFLAGS) -o Car_Bridge Car_Bridge.cpp

Car_Strategy: Car_Strategy.cpp
	$(CXX) $(CXXFLAGS) -o Car_Strategy Car_Strategy.cpp

Command: Command.cpp
	$(CXX) $(CXXFLAGS) -o Command Command.cpp

ExternalPolymorphism: ExternalPolymorphism.cpp
	$(CXX) $(CXXFLAGS) -o ExternalPolymorphism ExternalPolymorphism.cpp

FastPimpl: FastPimpl.cpp
	$(CXX) $(CXXFLAGS) -o FastPimpl FastPimpl.cpp

Function_1: Function_1.cpp
	$(CXX) $(CXXFLAGS) -o Function_1 Function_1.cpp

Function_2: Function_2.cpp
	$(CXX) $(CXXFLAGS) -o Function_2 Function_2.cpp

Function_Ref: Function_Ref.cpp
	$(CXX) $(CXXFLAGS) -o Function_Ref Function_Ref.cpp

InplaceAny: InplaceAny.cpp
	$(CXX) $(CXXFLAGS) -o InplaceAny InplaceAny.cpp

InplaceFunction: InplaceFunction.cpp
	$(CXX) $(CXXFLAGS) -o InplaceFunction InplaceFunction.cpp

ObjectOriented: ObjectOriented.cpp
	$(CXX) $(CXXFLAGS) -o ObjectOriented ObjectOriented.cpp

Persistence: Persistence.cpp
	$(CXX) $(CXXFLAGS) -o Persistence Persistence.cpp

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

TypeErasure: TypeErasure.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure TypeErasure.cpp

TypeErasure_MVF: TypeErasure_MVF.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_MVF TypeErasure_MVF.cpp

TypeErasure_Ref: TypeErasure_Ref.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_Ref TypeErasure_Ref.cpp

TypeErasure_SBO: TypeErasure_SBO.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_SBO TypeErasure_SBO.cpp

UniquePtr_TypeErasure: UniquePtr_TypeErasure.cpp
	$(CXX) $(CXXFLAGS) -o UniquePtr_TypeErasure UniquePtr_TypeErasure.cpp

Variant: Variant.cpp
	$(CXX) $(CXXFLAGS) -o Variant Variant.cpp

Visitor: Visitor.cpp
	$(CXX) $(CXXFLAGS) -o Visitor Visitor.cpp

Visitor_Benchmark: Visitor_Benchmark.cpp
	$(CXX) $(CXXFLAGS) -o Visitor_Benchmark Visitor_Benchmark.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
