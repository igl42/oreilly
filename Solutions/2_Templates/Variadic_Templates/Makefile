#==================================================================================================
#
#  Makefile for subchapter "Variadic Templates" of chapter "Templates"
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
default: AddSub HigherOrder MakeUnique Print PrintTuple Sum \
         VariadicCartesianProduct VariadicMax VariadicMinMax VariantIndex

AddSub: AddSub.cpp
	$(CXX) $(CXXFLAGS) -o AddSub AddSub.cpp

HigherOrder: HigherOrder.cpp
	$(CXX) $(CXXFLAGS) -o HigherOrder HigherOrder.cpp

MakeUnique: MakeUnique.cpp
	$(CXX) $(CXXFLAGS) -o MakeUnique MakeUnique.cpp

Print: Print.cpp
	$(CXX) $(CXXFLAGS) -o Print Print.cpp

PrintTuple: PrintTuple.cpp
	$(CXX) $(CXXFLAGS) -o PrintTuple PrintTuple.cpp

Sum: Sum.cpp
	$(CXX) $(CXXFLAGS) -o Sum Sum.cpp

VariadicCartesianProduct: VariadicCartesianProduct.cpp
	$(CXX) $(CXXFLAGS) -o VariadicCartesianProduct VariadicCartesianProduct.cpp

VariadicMax: VariadicMax.cpp
	$(CXX) $(CXXFLAGS) -o VariadicMax VariadicMax.cpp

VariadicMinMax: VariadicMinMax.cpp
	$(CXX) $(CXXFLAGS) -o VariadicMinMax VariadicMinMax.cpp

VariantIndex: VariantIndex.cpp
	$(CXX) $(CXXFLAGS) -o VariantIndex VariantIndex.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
