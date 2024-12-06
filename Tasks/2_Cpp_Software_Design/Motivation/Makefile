#==================================================================================================
#
#  Makefile for subchapter "Motivation" of chapter "C++ Software Design"
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
default: DataOriented ObjectOriented Procedural

DataOriented: DataOriented.cpp
	$(CXX) $(CXXFLAGS) -o DataOriented DataOriented.cpp

ObjectOriented: ObjectOriented.cpp
	$(CXX) $(CXXFLAGS) -o ObjectOriented ObjectOriented.cpp

Procedural: Procedural.cpp
	$(CXX) $(CXXFLAGS) -o Procedural Procedural.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
