#==================================================================================================
#
#  CMakeLists for the chapter "The Special Member Functions" of the C++ Training
#
#  Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)

add_executable(CopyControl
   CopyControl.cpp
   )

add_executable(CopyOperations
   CopyOperations.cpp
   )

add_executable(CreateStrings
   CreateStrings.cpp
   )

add_executable(MemberInitialization1
   MemberInitialization1.cpp
   )

add_executable(MemberInitialization2
   MemberInitialization2.cpp
   )

add_executable(MemberInitialization3
   MemberInitialization3.cpp
   )

add_executable(Move1
   Move1.cpp
   )

add_executable(Move2
   Move2.cpp
   )

add_executable(Move3
   Move3.cpp
   )

add_executable(Move4
   Move4.cpp
   )

add_executable(MoveNoexcept
   MoveNoexcept.cpp
   )

add_executable(MoveReview
   MoveReview.cpp
   )

add_executable(ResourceOwner
   ResourceOwner.cpp
   )

add_executable(ResourceOwner_2
   ResourceOwner_2.cpp
   )

add_executable(ResourceOwner_3
   ResourceOwner_3.cpp
   )

add_executable(ResourceOwner_4
   ResourceOwner_4.cpp
   )

add_executable(RVO1
   RVO1.cpp
   )

add_executable(RVO2
   RVO2.cpp
   )

add_executable(STLMax
   STLMax.cpp
   )

add_executable(StrongType_Move
   StrongType_Move.cpp
   )

set_target_properties(
   CopyControl
   CopyOperations
   CreateStrings
   MemberInitialization1
   MemberInitialization2
   MemberInitialization3
   Move1
   Move2
   Move3
   Move4
   MoveNoexcept
   MoveReview
   ResourceOwner
   ResourceOwner_2
   ResourceOwner_3
   ResourceOwner_4
   RVO1
   RVO2
   STLMax
   StrongType_Move
   PROPERTIES
   FOLDER "2_The_Special_Member_Functions"
   )
