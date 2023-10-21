/**************************************************************************************************
*
* \file Print.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Extend the given 'print()' function by variadic templates to enable an arbitrary
*       number of function arguments.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>


// Solution 1: Tail recursion with function overloading (possible since C++11)
/*
template< typename T >
void print( std::ostream& os, const T& value )
{
   os << value;
}

template< typename T, typename... Ts >
void print( std::ostream& os, const T& value, const Ts&... values )
{
   print( os, value );
   print( os, values... );
}
*/


// Solution 2: Tail recursion with 'if constexpr' (since C++17)
/*
template< typename T, typename... Ts >
void print( std::ostream& os, const T& value, const Ts&... values )
{
   os << value;
   if constexpr( sizeof...(Ts) > 0 ) {
      print( os, values... );
   }
}
*/


// Solution 3: Fold expressions (possible since C++17)
template< typename T, typename... Ts >
void print( std::ostream& os, const T& value, const Ts&... values )
{
   ( ( os << value ) << ... << values );
}


int main()
{
   print( std::cout, "Hello\n" );
   print( std::cout, "Two ", "words\n" );
   print( std::cout, "Three ", "different ", "words\n" );
   print( std::cout, "Numbers: ", 1, ' ', 1.2, ' ', '\n' );

   return EXIT_SUCCESS;
}
