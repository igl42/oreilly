/**************************************************************************************************
*
* \file Compare.cpp
* \brief C++ Training - Function Template Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Write a generic 'compare()' function that returns a negative number if the left-hand
*         side argument is smaller, 0 if both arguments are equal, and a positive number if the
*         left-hand side argument is larger.
*
* Step 2: Specialize the 'compare()' function for pointers to char.
*
**************************************************************************************************/

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>


// Step 1: Write a generic 'compare()' function that returns a negative number if the left-hand
//         side argument is smaller, 0 if both arguments are equal, and a positive number if the
//         left-hand side argument is larger.
template< typename T >
int compare( T const& a, T const& b )
{
   if( a < b )
      return -1;
   else if( b < a )
      return 1;
   else
      return 0;
}


// Step 2: Specialize the 'compare()' function for pointers to char.
template<>
int compare( char const* const& a, char const* const& b )
{
   return std::strcmp( a, b );
}


// Overload of 'compare()'
//int compare( const char* pa, const char* pb )
//{
//   return std::strcmp( pa, pb );
//}


int main()
{
   {
      const int i1 = 1;
      const int i2 = 2;

      if( compare( i1, i2 ) >= 0 || compare( i2, i1 ) <= 0 || compare( i1, i1 ) != 0 ) {
         std::cerr << "Error during the comparison of 'int' detected!\n";
      }
      else {
         std::cout << "compare( int, int ) works!\n";
      }
   }

   {
      const std::string s1( "Bjarne" );
      const std::string s2( "Herb" );

      if( compare( s1, s2 ) >= 0 || compare( s2, s1 ) <= 0 || compare( s1, s1 ) != 0 ) {
         std::cerr << "Error during the comparison of 'std::string' detected!\n";
      }
      else {
         std::cout << "compare( std::string, std::string ) works!\n";
      }
   }

   {
      const char* s1 = "Bjarne";
      const char* s2 = "Herb";

      if( compare( s1, s2 ) >= 0 || compare( s2, s1 ) <= 0 || compare( s1, s1 ) != 0 ) {
         std::cerr << "Error during the comparison of 'const char*' detected!\n";
      }
      else {
         std::cout << "compare( const char*, const char* ) works!\n";
      }
   }

   return EXIT_SUCCESS;
}








