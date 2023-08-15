#==================================================================================================
#
#  CMakeLists for the chapter "The Special Member Functions" of the C++ Training
#
#  Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.8 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(CopyControl
   CopyControl.cpp
   )

add_executable(CreateStrings_Local
   CreateStrings_Local.cpp
   )

add_executable(EmailAddress
   EmailAddress.cpp
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

add_executable(MoveNoexcept
   MoveNoexcept.cpp
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

set_target_properties(
   CopyControl
   CreateStrings_Local
   EmailAddress
   MemberInitialization1
   MemberInitialization2
   MemberInitialization3
   MoveNoexcept
   ResourceOwner
   ResourceOwner_2
   ResourceOwner_3
   ResourceOwner_4
   RVO1
   RVO2
   PROPERTIES
   FOLDER "2_The_Special_Member_Functions"
   )
