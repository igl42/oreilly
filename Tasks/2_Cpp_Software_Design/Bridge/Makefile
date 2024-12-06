#==================================================================================================
#
#  Makefile for subchapter "Bridge" of chapter "C++ Software Design"
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
default: Bridge Car_Bridge Car_Strategy FastPimpl

Bridge: Bridge.cpp
	$(CXX) $(CXXFLAGS) -o Bridge Bridge.cpp

Car_Bridge: Car_Bridge.cpp
	$(CXX) $(CXXFLAGS) -o Car_Bridge Car_Bridge.cpp

Car_Strategy: Car_Strategy.cpp
	$(CXX) $(CXXFLAGS) -o Car_Strategy Car_Strategy.cpp

FastPimpl: FastPimpl.cpp
	$(CXX) $(CXXFLAGS) -o FastPimpl FastPimpl.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
