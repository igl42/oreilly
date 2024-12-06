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
default: FixedVector_Strategy MultipleStrategies_1 MultipleStrategies_2 MultipleStrategies_3 \
         Strategy_Classic Strategy_Refactoring Strategy_Refactoring_Static UniquePtr_Strategy

FixedVector_Strategy: FixedVector_Strategy.cpp
	$(CXX) $(CXXFLAGS) -o FixedVector_Strategy FixedVector_Strategy.cpp

MultipleStrategies_1: MultipleStrategies_1.cpp
	$(CXX) $(CXXFLAGS) -o MultipleStrategies_1 MultipleStrategies_1.cpp

MultipleStrategies_2: MultipleStrategies_2.cpp
	$(CXX) $(CXXFLAGS) -o MultipleStrategies_2 MultipleStrategies_2.cpp

MultipleStrategies_3: MultipleStrategies_3.cpp
	$(CXX) $(CXXFLAGS) -o MultipleStrategies_3 MultipleStrategies_3.cpp

Strategy_Classic: Strategy_Classic.cpp
	$(CXX) $(CXXFLAGS) -o Strategy_Classic Strategy_Classic.cpp

Strategy_Refactoring: Strategy_Refactoring.cpp
	$(CXX) $(CXXFLAGS) -o Strategy_Refactoring Strategy_Refactoring.cpp

Strategy_Refactoring_Static: Strategy_Refactoring_Static.cpp
	$(CXX) $(CXXFLAGS) -o Strategy_Refactoring_Static Strategy_Refactoring_Static.cpp

UniquePtr_Strategy: UniquePtr_Strategy.cpp
	$(CXX) $(CXXFLAGS) -o UniquePtr_Strategy UniquePtr_Strategy.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
