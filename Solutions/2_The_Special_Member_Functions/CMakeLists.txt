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

add_executable(CreateStrings
   CreateStrings.cpp
   )

add_executable(MoveReview
   MoveReview.cpp
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

add_executable(STLMax
   STLMax.cpp
   )

add_executable(StrongType_Move
   StrongType_Move.cpp
   )

set_target_properties(
   CopyControl
   CreateStrings
   MoveReview
   ResourceOwner_2
   ResourceOwner_3
   ResourceOwner_4
   STLMax
   StrongType_Move
   PROPERTIES
   FOLDER "2_The_Special_Member_Functions"
   )
