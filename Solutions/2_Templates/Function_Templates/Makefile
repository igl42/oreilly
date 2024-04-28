#==================================================================================================
#
#  Makefile for subchapter "Function Templates" of chapter "Templates"
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
default: Accumulate ArraySize Compare Find Max MinMax

Accumulate: Accumulate.cpp
	$(CXX) $(CXXFLAGS) -o Accumulate Accumulate.cpp

ArraySize: ArraySize.cpp
	$(CXX) $(CXXFLAGS) -o ArraySize ArraySize.cpp

Compare: Compare.cpp
	$(CXX) $(CXXFLAGS) -o Compare Compare.cpp

Find: Find.cpp
	$(CXX) $(CXXFLAGS) -o Find Find.cpp

Max: Max.cpp
	$(CXX) $(CXXFLAGS) -o Max Max.cpp

MinMax: MinMax.cpp
	$(CXX) $(CXXFLAGS) -o MinMax MinMax.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
