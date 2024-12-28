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
default: CopyControl CopyOperations CreateStrings_Local EmailAddress \
         MemberInitialization1 MemberInitialization2 MemberInitialization3 \
         MoveNoexcept ResourceOwner ResourceOwner_2 ResourceOwner_3 ResourceOwner_4 \
         RVO1 RVO2 RVO3

CopyControl: CopyControl.cpp
	$(CXX) $(CXXFLAGS) -o CopyControl CopyControl.cpp

CopyOperations: CopyOperations.cpp
	$(CXX) $(CXXFLAGS) -o CopyOperations CopyOperations.cpp

CreateStrings_Local: CreateStrings_Local.cpp
	$(CXX) $(CXXFLAGS) -o CreateStrings_Local CreateStrings_Local.cpp

EmailAddress: EmailAddress.cpp
	$(CXX) $(CXXFLAGS) -o EmailAddress EmailAddress.cpp

MemberInitialization1: MemberInitialization1.cpp
	$(CXX) $(CXXFLAGS) -o MemberInitialization1 MemberInitialization1.cpp

MemberInitialization2: MemberInitialization2.cpp
	$(CXX) $(CXXFLAGS) -o MemberInitialization2 MemberInitialization2.cpp

MemberInitialization3: MemberInitialization3.cpp
	$(CXX) $(CXXFLAGS) -o MemberInitialization3 MemberInitialization3.cpp

MoveNoexcept: MoveNoexcept.cpp
	$(CXX) $(CXXFLAGS) -o MoveNoexcept MoveNoexcept.cpp

ResourceOwner: ResourceOwner.cpp
	$(CXX) $(CXXFLAGS) -o ResourceOwner ResourceOwner.cpp

ResourceOwner_2: ResourceOwner_2.cpp
	$(CXX) $(CXXFLAGS) -o ResourceOwner_2 ResourceOwner_2.cpp

ResourceOwner_3: ResourceOwner_3.cpp
	$(CXX) $(CXXFLAGS) -o ResourceOwner_3 ResourceOwner_3.cpp

ResourceOwner_4: ResourceOwner_4.cpp
	$(CXX) $(CXXFLAGS) -o ResourceOwner_4 ResourceOwner_4.cpp

RVO1: RVO1.cpp
	$(CXX) $(CXXFLAGS) -o RVO1 RVO1.cpp

RVO2: RVO2.cpp
	$(CXX) $(CXXFLAGS) -o RVO2 RVO2.cpp

RVO3: RVO3.cpp
	$(CXX) $(CXXFLAGS) -o RVO3 RVO3.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
