/**************************************************************************************************
*
* \file RVO2.cpp
* \brief C++ Training - Example for copy elision
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Estimate the number of special member function calls in the following two code examples.
*
**************************************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <utility>


struct S
{
   S() { std::puts( "S() - Default constructor" ); }

   S( S const& ) { std::puts( "S(S const&) - Copy constructor" ); }
   S& operator=( S const& ) { std::puts( "operator=(S const&) - Copy assignment operator" ); return *this; }

   S( S&& ) noexcept { std::puts( "S(S const&) - Move constructor" ); }
   S& operator=( S&& ) noexcept { std::puts( "operator=(S&&) - Move assignment operator" ); return *this; }

   ~S() { std::puts( "~S() - Destructor" ); }

   int value{};
};


//==== Example 1 ==================================================================================

void f( S s1, S s2 )
{}

int main()
{
   S s1{};
   s1.value = 42;

   S s2{};
   s2.value = 4711;

   f( std::move(s1), std::move(s2) );

   return EXIT_SUCCESS;
}


//==== Example 2 ==================================================================================

/*
void f( S s1, S s2 )
{}

int main()
{
   auto makeS = []( int value )
   {
      S s{};
      s.value = value;
      return s;
   };

   f( makeS(42), makeS(4711) );

   return EXIT_SUCCESS;
}
*/
