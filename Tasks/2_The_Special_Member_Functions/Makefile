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
default: CopyControl CopyOperations CreateStrings MemberInitialization1 MemberInitialization2 \
         MemberInitialization3 Move1 Move2 Move3 Move4 MoveNoexcept MoveReview ResourceOwner \
         ResourceOwner_2 ResourceOwner_3 ResourceOwner_4 RVO1 RVO2 STLMax StrongType_Move

CopyControl: CopyControl.cpp
	$(CXX) $(CXXFLAGS) -o CopyControl CopyControl.cpp

CopyOperations: CopyOperations.cpp
	$(CXX) $(CXXFLAGS) -o CopyOperations CopyOperations.cpp

CreateStrings: CreateStrings.cpp
	$(CXX) $(CXXFLAGS) -o CreateStrings CreateStrings.cpp

MemberInitialization1: MemberInitialization1.cpp
	$(CXX) $(CXXFLAGS) -o MemberInitialization1 MemberInitialization1.cpp

MemberInitialization2: MemberInitialization2.cpp
	$(CXX) $(CXXFLAGS) -o MemberInitialization2 MemberInitialization2.cpp

MemberInitialization3: MemberInitialization3.cpp
	$(CXX) $(CXXFLAGS) -o MemberInitialization3 MemberInitialization3.cpp

Move1: Move1.cpp
	$(CXX) $(CXXFLAGS) -o Move1 Move1.cpp

Move2: Move2.cpp
	$(CXX) $(CXXFLAGS) -o Move2 Move2.cpp

Move3: Move3.cpp
	$(CXX) $(CXXFLAGS) -o Move3 Move3.cpp

Move4: Move4.cpp
	$(CXX) $(CXXFLAGS) -o Move4 Move4.cpp

MoveNoexcept: MoveNoexcept.cpp
	$(CXX) $(CXXFLAGS) -o MoveNoexcept MoveNoexcept.cpp

MoveReview: MoveReview.cpp
	$(CXX) $(CXXFLAGS) -o MoveReview MoveReview.cpp

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

STLMax: STLMax.cpp
	$(CXX) $(CXXFLAGS) -o STLMax STLMax.cpp

StrongType_Move: StrongType_Move.cpp
	$(CXX) $(CXXFLAGS) -o StrongType_Move StrongType_Move.cpp

clean:
	@$(RM) $(BIN)


# Setting the independent commands
.PHONY: default clean
