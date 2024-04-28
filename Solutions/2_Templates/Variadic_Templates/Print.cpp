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
#include <type_traits>


//=== Task 1 ======================================================================================

// Solution 1: Tail recursion with function overloading (possible since C++11)
/*
template< typename T >
void println( std::ostream& os, T const& value )
{
   os << value << '\n';
}

template< typename T, typename... Ts >
void println( std::ostream& os, T const& value, Ts const&... values )
{
   os << value;
   println( os, values... );
}
*/


// Solution 2: Tail recursion with 'if constexpr' (since C++17)
/*
template< typename T, typename... Ts >
void println( std::ostream& os, T const& value, Ts const&... values )
{
   os << value;
   if constexpr( sizeof...(Ts) > 0 ) {
      println( os, values... );
   }
   else {
      os << '\n';
   }
}
*/


// Solution 3: Fold expressions (possible since C++17)
template< typename... Ts >
void println( std::ostream& os, Ts const&... values )
{
   ( os << ... << values ) << '\n';
}


//=== Task 2 ======================================================================================

/*
template< typename Format, typename... Ts >
void println( std::ostream& os, Format format, Ts const&... values )
{
   ( os << ... << format(values) ) << '\n';
}

auto capitalize()
{
   return []<typename T>( T const& v )
   {
      if constexpr( std::is_arithmetic_v<T> )
      {
         return v;
      }
      else {
         std::string tmp{v};
         for( char& c : tmp ) {
            c = std::toupper(c);
         }
         return tmp;
      }
   };
}
*/


int main()
{
   // Task 1
   println( std::cout, 42 );
   println( std::cout, "Hello" );
   println( std::cout, "Two ", "words" );
   println( std::cout, 1, 2, 3 );
   println( std::cout, "Three ", "different ", "words" );
   println( std::cout, "Numbers: ", 1, ", ", 1.2F, ", ", 2.4 );

   // Task 2
   //println( std::cout, capitalize(), "Numbers: ", 1, ", ", 1.2F, ", ", 2.4 );

   return EXIT_SUCCESS;
}
