/**************************************************************************************************
*
* \file Print.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
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
std::ostream& print( std::ostream& os, const T& value )
{
   return os << value;
}

template< typename T, typename... Ts >
std::ostream& print( std::ostream& os, const T& value, const Ts&... values )
{
   print( os, value );
   print( os, values... );
   return os;
}
*/

// Solution 2: Tail recursion with constexpr if (since C++17)
/*
template< typename T, typename... Ts >
std::ostream& print( std::ostream& os, const T& value, const Ts&... values )
{
   std::cout << value;
   if constexpr( sizeof...(Ts) > 0 ) {
      print( os, values... );
   }
   return os;
}
*/

// Solution 3: Fold expressions (possible since C++17)
template< typename T, typename... Ts >
std::ostream& print( std::ostream& os, const T& value, const Ts&... values )
{
   std::cout << value;
   return ( std::cout << ... << values );
}


int main()
{
   print( std::cout, "Hallo\n" );
   print( std::cout, "Two ", "words\n" );
   print( std::cout, "Numbers: ", 1, ' ', 1.2, ' ', '\n' );

   return EXIT_SUCCESS;
}
