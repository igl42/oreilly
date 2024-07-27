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
default: Bridge_1 Bridge_2 Bridge_3 Bridge_Static FastPimpl

Bridge_1: Bridge_1.cpp
	$(CXX) $(CXXFLAGS) -o Bridge_1 Bridge_1.cpp

Bridge_2: Bridge_2.cpp
	$(CXX) $(CXXFLAGS) -o Bridge_2 Bridge_2.cpp

Bridge_3: Bridge_3.cpp
	$(CXX) $(CXXFLAGS) -o Bridge_3 Bridge_3.cpp

Bridge_Static: Bridge_Static.cpp
	$(CXX) $(CXXFLAGS) -o Bridge_Static Bridge_Static.cpp

FastPimpl: FastPimpl.cpp
	$(CXX) $(CXXFLAGS) -o FastPimpl FastPimpl.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
