#==================================================================================================
#
#  Makefile for subchapter "Command" of chapter "C++ Software Design"
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
default: Calculator_Command Command

Calculator_Command: Calculator_Command.cpp
	$(CXX) $(CXXFLAGS) -o Calculator_Command Calculator_Command.cpp

Command: Command.cpp
	$(CXX) $(CXXFLAGS) -o Command Command.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
