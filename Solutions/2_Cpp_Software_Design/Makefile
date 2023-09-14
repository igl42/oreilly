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
default: Adapter_2 Adapter_3 Animal_EP Animal_TE Any_1 Any_2 Bridge_1 Bridge_2 \
         Bridge_3 Bridge_Static Calculator_Command Command ExternalPolymorphism \
         FastPimpl Function_1 Function_2 Function_Ref_1 Function_Ref_2 \
         PolymorphicAllocator Strategy TypeErasure TypeErasure_MVF \
         TypeErasure_PolicyBased TypeErasure_Ref_1 TypeErasure_Ref_2 TypeErasure_SBO \
         TypeErasure_SBO_MVF Variant Visitor

Adapter_2: Adapter_2.cpp
	$(CXX) $(CXXFLAGS) -o Adapter_2 Adapter_2.cpp

Adapter_3: Adapter_3.cpp
	$(CXX) $(CXXFLAGS) -o Adapter_3 Adapter_3.cpp

Any_1: Any_1.cpp
	$(CXX) $(CXXFLAGS) -o Any_1 Any_1.cpp

Any_2: Any_2.cpp
	$(CXX) $(CXXFLAGS) -o Any_2 Any_2.cpp

Animal_EP: Animal_EP.cpp
	$(CXX) $(CXXFLAGS) -o Animal_EP Animal_EP.cpp

Animal_TE: Animal_TE.cpp
	$(CXX) $(CXXFLAGS) -o Animal_TE Animal_TE.cpp

Bridge_1: Bridge_1.cpp
	$(CXX) $(CXXFLAGS) -o Bridge_1 Bridge_1.cpp

Bridge_2: Bridge_2.cpp
	$(CXX) $(CXXFLAGS) -o Bridge_2 Bridge_2.cpp

Bridge_3: Bridge_3.cpp
	$(CXX) $(CXXFLAGS) -o Bridge_3 Bridge_3.cpp

Bridge_Static: Bridge_Static.cpp
	$(CXX) $(CXXFLAGS) -o Bridge_Static Bridge_Static.cpp

Calculator_Command: Calculator_Command.cpp
	$(CXX) $(CXXFLAGS) -o Calculator_Command Calculator_Command.cpp

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

Function_Ref_1: Function_Ref_1.cpp
	$(CXX) $(CXXFLAGS) -o Function_Ref_1 Function_Ref_1.cpp

Function_Ref_2: Function_Ref_2.cpp
	$(CXX) $(CXXFLAGS) -o Function_Ref_2 Function_Ref_2.cpp

PolymorphicAllocator: PolymorphicAllocator.cpp
	$(CXX) $(CXXFLAGS) -o PolymorphicAllocator PolymorphicAllocator.cpp

Strategy: Strategy.cpp
	$(CXX) $(CXXFLAGS) -o Strategy Strategy.cpp

TypeErasure: TypeErasure.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure TypeErasure.cpp

TypeErasure_MVF: TypeErasure_MVF.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_MVF TypeErasure_MVF.cpp

TypeErasure_Ref_1: TypeErasure_Ref_1.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_Ref_1 TypeErasure_Ref_1.cpp

TypeErasure_Ref_2: TypeErasure_Ref_2.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_Ref_2 TypeErasure_Ref_2.cpp

TypeErasure_PolicyBased: TypeErasure_PolicyBased.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_PolicyBased TypeErasure_PolicyBased.cpp

TypeErasure_SBO: TypeErasure_SBO.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_SBO TypeErasure_SBO.cpp

TypeErasure_SBO_MVF: TypeErasure_SBO_MVF.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_SBO_MVF TypeErasure_SBO_MVF.cpp

Variant: Variant.cpp
	$(CXX) $(CXXFLAGS) -o Variant Variant.cpp

Visitor: Visitor.cpp
	$(CXX) $(CXXFLAGS) -o Visitor Visitor.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
