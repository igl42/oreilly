#==================================================================================================
#
#  Makefile for subchapter "Class Templates" of chapter "Templates"
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
default: FixedVector1 UniquePtr1 Vector1 Vector2

FixedVector1: FixedVector1.cpp
	$(CXX) $(CXXFLAGS) -o FixedVector1 FixedVector1.cpp

UniquePtr1: UniquePtr1.cpp
	$(CXX) $(CXXFLAGS) -o UniquePtr1 UniquePtr1.cpp

Vector1: Vector1.cpp
	$(CXX) $(CXXFLAGS) -o Vector1 Vector1.cpp

Vector2: Vector2.cpp
	$(CXX) $(CXXFLAGS) -o Vector2 Vector2.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
