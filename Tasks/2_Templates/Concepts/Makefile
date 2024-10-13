#==================================================================================================
#
#  Makefile for subchapter "Concepts" of chapter "C++ Templates"
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
default: AssociativeContainer Constraints2 IsPalindrome_Concepts Max_Concept \
         NarrowConversion2 Optional_Cpp20 Optional_Trivial_1 Optional_Trivial_2 \
         PassingConcepts SequenceContainer Sign2 UniquePtr_Concepts

AssociativeContainer: AssociativeContainer.cpp
	$(CXX) $(CXXFLAGS) -o AssociativeContainer AssociativeContainer.cpp

Constraints2: Constraints2.cpp
	$(CXX) $(CXXFLAGS) -o Constraints2 Constraints2.cpp

IsPalindrome_Concepts: IsPalindrome_Concepts.cpp
	$(CXX) $(CXXFLAGS) -o IsPalindrome_Concepts IsPalindrome_Concepts.cpp

Max_Concept: Max_Concept.cpp
	$(CXX) $(CXXFLAGS) -o Max_Concept Max_Concept.cpp

NarrowConversion2: NarrowConversion2.cpp
	$(CXX) $(CXXFLAGS) -o NarrowConversion2 NarrowConversion2.cpp

Optional_Cpp20: Optional_Cpp20.cpp
	$(CXX) $(CXXFLAGS) -o Optional_Cpp20 Optional_Cpp20.cpp

Optional_Trivial_1: Optional_Trivial_1.cpp
	$(CXX) $(CXXFLAGS) -o Optional_Trivial_1 Optional_Trivial_1.cpp

Optional_Trivial_2: Optional_Trivial_2.cpp
	$(CXX) $(CXXFLAGS) -o Optional_Trivial_2 Optional_Trivial_2.cpp

PassingConcepts: PassingConcepts.cpp
	$(CXX) $(CXXFLAGS) -o PassingConcepts PassingConcepts.cpp

SequenceContainer: SequenceContainer.cpp
	$(CXX) $(CXXFLAGS) -o SequenceContainer SequenceContainer.cpp

Sign2: Sign2.cpp
	$(CXX) $(CXXFLAGS) -o Sign2 Sign2.cpp

UniquePtr_Concepts: UniquePtr_Concepts.cpp
	$(CXX) $(CXXFLAGS) -o UniquePtr_Concepts UniquePtr_Concepts.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
