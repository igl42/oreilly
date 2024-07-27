#==================================================================================================
#
#  Makefile for subchapter "Type Erasures" of chapter "C++ Software Design"
#
#  Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================


# Compiler settings
CXX = g++
CXXFLAGS = -std=c++20 -Wall


# Setting the source and binary files
SRC = $(wildcard *.cpp)
BIN = $(SRC:.cpp=)


# Rules
default: Animal_TE Any_1 Any_2 Function_1 Function_2 Function_Ref_1 Function_Ref_2 \
         PolymorphicAllocator TypeErasure_1 TypeErasure_2 TypeErasure_MVF \
         TypeErasure_PolicyBased TypeErasure_Ref_1 TypeErasure_Ref_2 TypeErasure_SBO \
         TypeErasure_SBO_MVF

Animal_TE: Animal_TE.cpp
	$(CXX) $(CXXFLAGS) -o Animal_TE Animal_TE.cpp

Any_1: Any_1.cpp
	$(CXX) $(CXXFLAGS) -o Any_1 Any_1.cpp

Any_2: Any_2.cpp
	$(CXX) $(CXXFLAGS) -o Any_2 Any_2.cpp

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

TypeErasure_1: TypeErasure_1.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_1 TypeErasure_1.cpp

TypeErasure_2: TypeErasure_2.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_2 TypeErasure_2.cpp

#TypeErasure_dyno: TypeErasure_dyno.cpp
#	$(CXX) $(CXXFLAGS) -o TypeErasure_dyno TypeErasure_dyno.cpp

TypeErasure_MVF: TypeErasure_MVF.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_MVF TypeErasure_MVF.cpp

TypeErasure_PolicyBased: TypeErasure_PolicyBased.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_PolicyBased TypeErasure_PolicyBased.cpp

TypeErasure_Ref_1: TypeErasure_Ref_1.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_Ref_1 TypeErasure_Ref_1.cpp

TypeErasure_Ref_2: TypeErasure_Ref_2.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_Ref_2 TypeErasure_Ref_2.cpp

TypeErasure_SBO: TypeErasure_SBO.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_SBO TypeErasure_SBO.cpp

TypeErasure_SBO_MVF: TypeErasure_SBO_MVF.cpp
	$(CXX) $(CXXFLAGS) -o TypeErasure_SBO_MVF TypeErasure_SBO_MVF.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
