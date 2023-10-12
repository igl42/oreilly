#==================================================================================================
#
#  Makefile for the chapter "STL Algorithms" of the C++ Training
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
default: BadAccumulate BadCopy BadTransform ExtractStrings Fibonacci IsEmailAddress \
         IsPalindrome IsPunct LongestStreak Partition Ranges \
         STLintro STLpro Simpson SimpsonPro SortSubrange Trap

BadAccumulate: BadAccumulate.cpp
	$(CXX) $(CXXFLAGS) -o BadAccumulate BadAccumulate.cpp

BadCopy: BadCopy.cpp
	$(CXX) $(CXXFLAGS) -o BadCopy BadCopy.cpp

BadTransform: BadTransform.cpp
	$(CXX) $(CXXFLAGS) -o BadTransform BadTransform.cpp

ExtractStrings: ExtractStrings.cpp
	$(CXX) $(CXXFLAGS) -o ExtractStrings ExtractStrings.cpp

Fibonacci: Fibonacci.cpp
	$(CXX) $(CXXFLAGS) -o Fibonacci Fibonacci.cpp

IsEmailAddress: IsEmailAddress.cpp
	$(CXX) $(CXXFLAGS) -o IsEmailAddress IsEmailAddress.cpp

IsPalindrome: IsPalindrome.cpp
	$(CXX) $(CXXFLAGS) -o IsPalindrome IsPalindrome.cpp

IsPunct: IsPunct.cpp
	$(CXX) $(CXXFLAGS) -o IsPunct IsPunct.cpp

LongestStreak: LongestStreak.cpp
	$(CXX) $(CXXFLAGS) -o LongestStreak LongestStreak.cpp

Partition: Partition.cpp
	$(CXX) $(CXXFLAGS) -o Partition Partition.cpp

Ranges: Ranges.cpp
	$(CXX) $(CXXFLAGS) -o Ranges Ranges.cpp

STLintro: STLintro.cpp
	$(CXX) $(CXXFLAGS) -o STLintro STLintro.cpp

STLpro: STLpro.cpp
	$(CXX) $(CXXFLAGS) -o STLpro STLpro.cpp

Simpson: Simpson.cpp
	$(CXX) $(CXXFLAGS) -o Simpson Simpson.cpp

SimpsonPro: SimpsonPro.cpp
	$(CXX) $(CXXFLAGS) -o SimpsonPro SimpsonPro.cpp

SortSubrange: SortSubrange.cpp
	$(CXX) $(CXXFLAGS) -o SortSubrange SortSubrange.cpp

Trap: Trap.cpp
	$(CXX) $(CXXFLAGS) -o Trap Trap.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
