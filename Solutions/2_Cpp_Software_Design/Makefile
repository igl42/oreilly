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
default: Bridge_1 Bridge_2 Bridge_3 Bridge_Static Decorator_Creature_1 \
         Decorator_Creature_2 Decorator_Item_1 Decorator_Item_2 ExternalPolymorphism \
         Function1 Function2 Function_Ref PolymorphicAllocator Strategy TypeErasure \
         TypeErasure_Manual TypeErasure_PolicyBased TypeErasure_Ref_1 TypeErasure_Ref_2 \
         TypeErasure_SBO TypeErasure_SBO_Manual Variant Visitor

Bridge_1: Bridge_1.cpp
	$(CXX) $(CXXFLAGS) -o Bridge_1 Bridge_1.cpp

Bridge_2: Bridge_2.cpp
	$(CXX) $(CXXFLAGS) -o Bridge_2 Bridge_2.cpp

Bridge_3: Bridge_3.cpp
	$(CXX) $(CXXFLAGS) -o Bridge_3 Bridge_3.cpp

Bridge_Static: Bridge_Static.cpp
	$(CXX) $(CXXFLAGS) -o Bridge_Static Bridge_Static.cpp

Decorator_Creature_1: Decorator_Creature_1.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_Creature_1 Decorator_Creature_1.cpp

Decorator_Creature_2: Decorator_Creature_2.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_Creature_2 Decorator_Creature_2.cpp

Decorator_Item_1: Decorator_Item_1.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_Item_1 Decorator_Item_1.cpp

Decorator_Item_2: Decorator_Item_2.cpp
	$(CXX) $(CXXFLAGS) -o Decorator_Item_2 Decorator_Item_2.cpp

ExternalPolymorphism: ExternalPolymorphism.cpp
	$(CXX) $(CXXFLAGS) -o ExternalPolymorphism ExternalPolymorphism.cpp

Function1: Function1.cpp
	$(CXX) $(CXXFLAGS) -o Function1 Function1.cpp

Function2: Function2.cpp
	$(CXX) $(CXXFLAGS) -o Function2 Function2.cpp

Function_Ref: Function_Ref.cpp
	$(CXX) $(CXXFLAGS) -o Function_Ref Function_Ref.cpp

PolymorphicAllocator: PolymorphicAllocator.cpp
	$(CXX) $(CXXFLAGS) -o PolymorphicAllocator PolymorphicAllocator.cpp

Strategy: Strategy.cpp
	$(CXX) $(CXXFLAGS) -o Strategy Strategy.cpp

TypeErasure: TypeErasure.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure TypeErasure.cpp

TypeErasure_Manual: TypeErasure_Manual.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_Manual TypeErasure_Manual.cpp

TypeErasure_Ref_1: TypeErasure_Ref_1.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_Ref_1 TypeErasure_Ref_1.cpp

TypeErasure_Ref_2: TypeErasure_Ref_2.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_Ref_2 TypeErasure_Ref_2.cpp

TypeErasure_PolicyBased: TypeErasure_PolicyBased.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_PolicyBased TypeErasure_PolicyBased.cpp

TypeErasure_SBO: TypeErasure_SBO.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_SBO TypeErasure_SBO.cpp

TypeErasure_SBO_Manual: TypeErasure_SBO_Manual.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_SBO_Manual TypeErasure_SBO_Manual.cpp

Variant: Variant.cpp
	$(CXX) $(CXXFLAGS) -o Variant Variant.cpp

Visitor: Visitor.cpp
	$(CXX) $(CXXFLAGS) -o Visitor Visitor.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
