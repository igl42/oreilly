#==================================================================================================
#
#  CMakeLists for subchapter "Special Member Functions" of chapter "Class Design"
#
#  Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
#
#  This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
#  context of the C++ training or with explicit agreement by Klaus Iglberger.
#
#==================================================================================================

cmake_minimum_required(VERSION 3.10 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 20)

add_executable(CopyControl
   CopyControl.cpp
   )

add_executable(CreateStrings
   CreateStrings.cpp
   )

add_executable(EmailAddress
   EmailAddress.cpp
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

set_target_properties(
   CopyControl
   CreateStrings
   EmailAddress
   ResourceOwner_2
   ResourceOwner_3
   ResourceOwner_4
   PROPERTIES
   FOLDER "4_Class_Design/Special_Member_Functions"
   )
