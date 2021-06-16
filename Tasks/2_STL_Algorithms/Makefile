#==================================================================================================
#
#  Makefile for the chapter "STL Algorithms" of the C++ Training
#
#  Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================


# Compiler settings
CXX = g++
CXXFLAGS = -std=c++17


# Setting the source and binary files
SRC = $(wildcard *.cpp)
BIN = $(SRC:.cpp=)


# Rules
default: Accumulate BadAccumulate BadCopy BadRemove BadTransform EqualRange ExtractStrings \
         LongestStreak Ranges Ranges_std Simpson SimpsonPro SortSubrange STLintro STLpro

Accumulate: Accumulate.cpp
	$(CXX) $(CXXFLAGS) -o Accumulate Accumulate.cpp

BadAccumulate: BadAccumulate.cpp
	$(CXX) $(CXXFLAGS) -o BadAccumulate BadAccumulate.cpp

BadCopy: BadCopy.cpp
	$(CXX) $(CXXFLAGS) -o BadCopy BadCopy.cpp

BadRemove: BadRemove.cpp
	$(CXX) $(CXXFLAGS) -o BadRemove BadRemove.cpp

BadTransform: BadTransform.cpp
	$(CXX) $(CXXFLAGS) -o BadTransform BadTransform.cpp

EqualRange: EqualRange.cpp
	$(CXX) $(CXXFLAGS) -o EqualRange EqualRange.cpp

ExtractStrings: ExtractStrings.cpp
	$(CXX) $(CXXFLAGS) -o ExtractStrings ExtractStrings.cpp

LongestStreak: LongestStreak.cpp
	$(CXX) $(CXXFLAGS) -o LongestStreak LongestStreak.cpp

Ranges: Ranges.cpp
	$(CXX) $(CXXFLAGS) -o Ranges Ranges.cpp

Ranges_std: Ranges_std.cpp
	$(CXX) $(CXXFLAGS) -o Ranges_std Ranges_std.cpp

Simpson: Simpson.cpp
	$(CXX) $(CXXFLAGS) -o Simpson Simpson.cpp

SimpsonPro: SimpsonPro.cpp
	$(CXX) $(CXXFLAGS) -o SimpsonPro SimpsonPro.cpp

SortSubrange: SortSubrange.cpp
	$(CXX) $(CXXFLAGS) -o SortSubrange SortSubrange.cpp

STLintro: STLintro.cpp
	$(CXX) $(CXXFLAGS) -o STLintro STLintro.cpp

STLpro: STLpro.cpp
	$(CXX) $(CXXFLAGS) -o STLpro STLpro.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
