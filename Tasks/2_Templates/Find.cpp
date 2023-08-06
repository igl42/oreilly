/**************************************************************************************************
*
* \file Find.cpp
* \brief C++ Training - Function Template Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task 1: Write a function template that acts like the standard library 'find()' algorithm. The
*         function needs two template type parameters: One represents the function's iterator
*         parameters, one represents the type of the value to find. Use your function to find a
*         given value in a 'std::vector<int>' and a 'std::list<std::string>'.
*
* Task 2: Write a function template that acts like the standard library 'find_if()' algorithm.
*         The function needs two template type parameters: One represents the function's iterator
*         parameters, one represents the type of a unary predicate used to examine the value.
*         Use your function to find an even value in a 'std::vector<int>' and a string containing
*         an 'x' in a 'std::list<std::string>'.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std::string_literals;


// Task 1: Write a function template that acts like the standard library 'find()' algorithm. The
//         function needs two template type parameters: One represents the function's iterator
//         parameters, one represents the type of the value to find. Use your function to find a
//         given value in a 'std::vector<int>' and a 'std::list<std::string>'.


// Task 2: Write a function template that acts like the standard library 'find_if()' algorithm.
//         The function needs two template type parameters: One represents the function's iterator
//         parameters, one represents the type of a unary predicate used to examine the value.
//         Use your function to find an even value in a 'std::vector<int>' and a string containing
//         an 'x' in a 'std::list<std::string>'.


int main()
{
   /*
   std::vector<int> v{ 3, 5, 2, 7, 5, 4, 3 };
   std::list<std::string> l{ "Herb"s, "Bjarne"s, "Alex"s, "Nicolai"s };

   // Find a value in a std::vector<int>
   {
      auto it = ::find( begin(v), end(v), 7 );

      if( it != end(v) ) {
         std::cout << "Found the value 7 in the vector!\n";
      }
   }

   // Find a value in a std::list<std::string>
   {
      auto it = ::find( begin(l), end(l), "Bjarne"s );

      if( it != end(l) ) {
         std::cout << "Found 'Bjarne' in the list!\n";
      }
   }
   */

   /*
   // Find the first even value in a std::vector<int>
   {
      auto it = ::find_if( begin(v), end(v), []( int i )
      {
         return i%2==0;
      } );

      if( it != end(v) ) {
         std::cout << "Found the even value " << *it << " in the vector!\n";
      }
   }

   // Find the first value containing an 'x' in a std::list<std::string>
   {
      auto it = ::find_if( begin(l), end(l), []( std::string const& s )
      {
         return s.find('x') != std::string::npos;
      } );

      if( it != end(l) ) {
         std::cout << "Found '" << *it << "' in the list!\n";
      }
   }
   */

   return EXIT_SUCCESS;
}
