#==================================================================================================
#
#  Makefile for the chapter "The Special Member Functions" of the C++ Training
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
default: CopyControl CreateStrings MoveReview ResourceOwner_2 ResourceOwner_3 ResourceOwner_4 \
         STLMax StrongType_Move

CopyControl: CopyControl.cpp
	$(CXX) $(CXXFLAGS) -o CopyControl CopyControl.cpp

CreateStrings: CreateStrings.cpp
	$(CXX) $(CXXFLAGS) -o CreateStrings CreateStrings.cpp

MoveReview: MoveReview.cpp
	$(CXX) $(CXXFLAGS) -o MoveReview MoveReview.cpp

ResourceOwner_2: ResourceOwner_2.cpp
	$(CXX) $(CXXFLAGS) -o ResourceOwner_2 ResourceOwner_2.cpp

ResourceOwner_3: ResourceOwner_3.cpp
	$(CXX) $(CXXFLAGS) -o ResourceOwner_3 ResourceOwner_3.cpp

ResourceOwner_4: ResourceOwner_4.cpp
	$(CXX) $(CXXFLAGS) -o ResourceOwner_4 ResourceOwner_4.cpp

STLMax: STLMax.cpp
	$(CXX) $(CXXFLAGS) -o STLMax STLMax.cpp

StrongType_Move: StrongType_Move.cpp
	$(CXX) $(CXXFLAGS) -o StrongType_Move StrongType_Move.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
