#==================================================================================================
#
#  Makefile for subchapter "Special Member Functions" of chapter "Class Design"
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
default: CopyControl CreateStrings EmailAddress ResourceOwner_2 ResourceOwner_3 ResourceOwner_4

CopyControl: CopyControl.cpp
	$(CXX) $(CXXFLAGS) -o CopyControl CopyControl.cpp

CreateStrings: CreateStrings.cpp
	$(CXX) $(CXXFLAGS) -o CreateStrings CreateStrings.cpp

EmailAddress: EmailAddress.cpp
	$(CXX) $(CXXFLAGS) -o EmailAddress EmailAddress.cpp

ResourceOwner_2: ResourceOwner_2.cpp
	$(CXX) $(CXXFLAGS) -o ResourceOwner_2 ResourceOwner_2.cpp

ResourceOwner_3: ResourceOwner_3.cpp
	$(CXX) $(CXXFLAGS) -o ResourceOwner_3 ResourceOwner_3.cpp

ResourceOwner_4: ResourceOwner_4.cpp
	$(CXX) $(CXXFLAGS) -o ResourceOwner_4 ResourceOwner_4.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
