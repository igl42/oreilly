/**************************************************************************************************
*
* \file Print.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task 1: Extend the given 'println()' function by variadic templates to enable an arbitrary
*         number of function arguments.
*
* Task 2: Extend the 'println()' function with a parameter to format the given values.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>


// TODO: Extend the given 'println()' function by variadic templates to enable an arbitrary
//       number of function arguments.
template< typename T >
void println( std::ostream& os, T const& value )
{
   os << value << '\n';
}


int main()
{
   // Task 1
   //println( std::cout, 42 );
   //println( std::cout, "Hello" );
   //println( std::cout, "Two ", "words" );
   //println( std::cout, 1, 2, 3 );
   //println( std::cout, "Three ", "different ", "words" );
   //println( std::cout, "Numbers: ", 1, ", ", 1.2F, ", ", 2.4 );

   // Task 2
   //println( std::cout, capitalize(), "Numbers: ", 1, ", ", 1.2F, ", ", 2.4 );

   return EXIT_SUCCESS;
}
