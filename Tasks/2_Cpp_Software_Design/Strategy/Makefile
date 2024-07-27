#==================================================================================================
#
#  Makefile for subchapter "Strategy" of chapter "C++ Software Design"
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
default: FixedVector_Strategy Strategy Strategy_Benchmark Strategy_Static UniquePtr_Strategy

FixedVector_Strategy: FixedVector_Strategy.cpp
	$(CXX) $(CXXFLAGS) -o FixedVector_Strategy FixedVector_Strategy.cpp

Strategy: Strategy.cpp
	$(CXX) $(CXXFLAGS) -o Strategy Strategy.cpp

Strategy_Benchmark: Strategy_Benchmark.cpp
	$(CXX) $(CXXFLAGS) -o Strategy_Benchmark Strategy_Benchmark.cpp

Strategy_Static: Strategy_Static.cpp
	$(CXX) $(CXXFLAGS) -o Strategy_Static Strategy_Static.cpp

UniquePtr_Strategy: UniquePtr_Strategy.cpp
	$(CXX) $(CXXFLAGS) -o UniquePtr_Strategy UniquePtr_Strategy.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
