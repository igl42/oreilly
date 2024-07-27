#==================================================================================================
#
#  Makefile for subchapter "External Polymorphism" of chapter "C++ Software Design"
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
default: Animal_EP ExternalPolymorphism_1 ExternalPolymorphism_2

Animal_EP: Animal_EP.cpp
	$(CXX) $(CXXFLAGS) -o Animal_EP Animal_EP.cpp

ExternalPolymorphism_1: ExternalPolymorphism_1.cpp
	$(CXX) $(CXXFLAGS) -o ExternalPolymorphism_1 ExternalPolymorphism_1.cpp

ExternalPolymorphism_2: ExternalPolymorphism_2.cpp
	$(CXX) $(CXXFLAGS) -o ExternalPolymorphism_2 ExternalPolymorphism_2.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
