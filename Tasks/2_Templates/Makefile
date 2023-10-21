#==================================================================================================
#
#  Makefile for chapter "Templates" of the C++ Training
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
default: Accumulate AddSub ArraySize CartesianProduct Compare Find FixedVector \
         FoldExpressions HigherOrder MakeUnique Max MinMax PackEnumeration PackIndexing \
         Print StringViewAdd Sum UniquePtr1 VariadicMax VariadicMinMax VariantIndex \
         Vector1 Vector2

Accumulate: Accumulate.cpp
	$(CXX) $(CXXFLAGS) -o Accumulate Accumulate.cpp

AddSub: AddSub.cpp
	$(CXX) $(CXXFLAGS) -o AddSub AddSub.cpp

ArraySize: ArraySize.cpp
	$(CXX) $(CXXFLAGS) -o ArraySize ArraySize.cpp

CartesianProduct: CartesianProduct.cpp
	$(CXX) $(CXXFLAGS) -o CartesianProduct CartesianProduct.cpp

Compare: Compare.cpp
	$(CXX) $(CXXFLAGS) -o Compare Compare.cpp

Find: Find.cpp
	$(CXX) $(CXXFLAGS) -o Find Find.cpp

FixedVector: FixedVector.cpp
	$(CXX) $(CXXFLAGS) -o FixedVector FixedVector.cpp

FoldExpressions: FoldExpressions.cpp
	$(CXX) $(CXXFLAGS) -o FoldExpressions FoldExpressions.cpp

HigherOrder: HigherOrder.cpp
	$(CXX) $(CXXFLAGS) -o HigherOrder HigherOrder.cpp

MakeUnique: MakeUnique.cpp
	$(CXX) $(CXXFLAGS) -o MakeUnique MakeUnique.cpp

Max: Max.cpp
	$(CXX) $(CXXFLAGS) -o Max Max.cpp

MinMax: MinMax.cpp
	$(CXX) $(CXXFLAGS) -o MinMax MinMax.cpp

PackEnumeration: PackEnumeration.cpp
	$(CXX) $(CXXFLAGS) -o PackEnumeration PackEnumeration.cpp

PackIndexing: PackIndexing.cpp
	$(CXX) $(CXXFLAGS) -o PackIndexing PackIndexing.cpp

Print: Print.cpp
	$(CXX) $(CXXFLAGS) -o Print Print.cpp

StringViewAdd: StringViewAdd.cpp
	$(CXX) $(CXXFLAGS) -o StringViewAdd StringViewAdd.cpp

Sum: Sum.cpp
	$(CXX) $(CXXFLAGS) -o Sum Sum.cpp

UniquePtr1: UniquePtr1.cpp
	$(CXX) $(CXXFLAGS) -o UniquePtr1 UniquePtr1.cpp

VariadicMax: VariadicMax.cpp
	$(CXX) $(CXXFLAGS) -o VariadicMax VariadicMax.cpp

VariadicMinMax: VariadicMinMax.cpp
	$(CXX) $(CXXFLAGS) -o VariadicMinMax VariadicMinMax.cpp

VariantIndex: VariantIndex.cpp
	$(CXX) $(CXXFLAGS) -o VariantIndex VariantIndex.cpp

Vector1: Vector1.cpp
	$(CXX) $(CXXFLAGS) -o Vector1 Vector1.cpp

Vector2: Vector2.cpp
	$(CXX) $(CXXFLAGS) -o Vector2 Vector2.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
