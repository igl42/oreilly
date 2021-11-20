/**************************************************************************************************
*
* \file RVO1.cpp
* \brief C++ Training - Example for copy elision (aka Return Value Optimization; RVO)
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Investigate, which of the special member functions are called when ...
*       1) ... creating a default 'S';
*       2) ... creating an instance of 'S' via the copy constructor;
*       3) ... creating an instance of 'S' via a function returning an 'S'.
*
**************************************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <utility>


struct S
{
   S() { std::puts( "S()" ); }
   S( const S& ) { std::puts( "S(const S&)" ); }
   S& operator=( const S& ) { std::puts( "operator=(const S&)" ); return *this; }
   ~S() { std::puts( "~S()" ); }
};


int main()
{
   S s{};

   return EXIT_SUCCESS;
}
