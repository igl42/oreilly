#==================================================================================================
#
#  Makefile for subchapter "Algorithms" of chapter "Concepts and the STL"
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
default: AlgorithmPerformance1 BadAccumulate BadCopy BadFind BadRemove BadTransform \
         CartesianProduct EqualRange ExtractStrings Fibonacci IsEmailAddress IsPalindrome \
         IsPunct LongestStreak MajorityVote Median NthElement Partition RangesExample \
         RangesRefactoring_1 RangesRefactoring_2 RangesRefactoring_3 \
         RangesRefactoring_4 Simpson SimpsonPro SortSubrange STLintro STLpro Trap

AlgorithmPerformance1: AlgorithmPerformance1.cpp
	$(CXX) $(CXXFLAGS) -o AlgorithmPerformance1 AlgorithmPerformance1.cpp

BadAccumulate: BadAccumulate.cpp
	$(CXX) $(CXXFLAGS) -o BadAccumulate BadAccumulate.cpp

BadCopy: BadCopy.cpp
	$(CXX) $(CXXFLAGS) -o BadCopy BadCopy.cpp

BadFind: BadFind.cpp
	$(CXX) $(CXXFLAGS) -o BadFind BadFind.cpp

BadRemove: BadRemove.cpp
	$(CXX) $(CXXFLAGS) -o BadRemove BadRemove.cpp

BadTransform: BadTransform.cpp
	$(CXX) $(CXXFLAGS) -o BadTransform BadTransform.cpp

CartesianProduct: CartesianProduct.cpp
	$(CXX) $(CXXFLAGS) -o CartesianProduct CartesianProduct.cpp

EqualRange: EqualRange.cpp
	$(CXX) $(CXXFLAGS) -o EqualRange EqualRange.cpp

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

MajorityVote: MajorityVote.cpp
	$(CXX) $(CXXFLAGS) -o MajorityVote MajorityVote.cpp

Median: Median.cpp
	$(CXX) $(CXXFLAGS) -o Median Median.cpp

NthElement: NthElement.cpp
	$(CXX) $(CXXFLAGS) -o NthElement NthElement.cpp

Partition: Partition.cpp
	$(CXX) $(CXXFLAGS) -o Partition Partition.cpp

RangesExample: RangesExample.cpp
	$(CXX) $(CXXFLAGS) -o RangesExample RangesExample.cpp

RangesRefactoring_1: RangesRefactoring_1.cpp
	$(CXX) $(CXXFLAGS) -o RangesRefactoring_1 RangesRefactoring_1.cpp

RangesRefactoring_2: RangesRefactoring_2.cpp
	$(CXX) $(CXXFLAGS) -o RangesRefactoring_2 RangesRefactoring_2.cpp

RangesRefactoring_3: RangesRefactoring_3.cpp
	$(CXX) $(CXXFLAGS) -o RangesRefactoring_3 RangesRefactoring_3.cpp

RangesRefactoring_4: RangesRefactoring_4.cpp
	$(CXX) $(CXXFLAGS) -o RangesRefactoring_4 RangesRefactoring_4.cpp

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

Trap: Trap.cpp
	$(CXX) $(CXXFLAGS) -o Trap Trap.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
