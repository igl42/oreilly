/**************************************************************************************************
*
* \file SequenceContainer.cpp
* \brief C++ Training - C++20 concepts programming task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Define the 'SequenceContainer' concept to constrain the 'addElement()' function
*         such that for sequence containers the 'push_back()' function is used and for
*         associative containers the 'insert()' function. The concept should pose the following
*         requirements on the given type:
*           - the type should be a regular class type;
*           - the type has a nested type 'value_type';
*           - the type has a nested type 'iterator';
*           - the type has a nested type 'const_iterator';
*           - the type has a member function 'size()', which result in something convertible to 'size_t';
*           - the type has a member function 'empty()', which results in 'bool';
*           - the type has a member function 'begin()', which results in 'iterator';
*           - the type has a member function 'end()', which results in 'iterator';
*           - the type has a member function 'cbegin()', which results in 'const_iterator';
*           - the type has a member function 'cend()', which results in 'const_iterator';
*           - the type has a member function 'push_back()';
*           - the const type has a member function 'begin()', which results in 'const_iterator';
*           - the const type has a member function 'end()', which results in 'const_iterator'.
*
* Step 2: Define the type trait 'IsSequenceContainer', including the according variable template
*
**************************************************************************************************/

#include <concepts>
#include <cstdlib>
#include <iostream>
#include <set>
#include <type_traits>
#include <vector>


// Step 1: Define the 'SequenceContainer' concept
// TODO


// Step 2: Define the 'IsSequenceContainer' type trait, including the according variable template
// TODO


// Step 1: Constrain the 'addElement()' functions such that for sequence containers the
//         'push_back()' function is used and for associative containers the 'insert()' function.
/*
template< typename T, typename V >
void addElement( T& container, V const& value )
{
   // TODO: Add elements to the container with either 'push_back()' or 'insert()'
}
*/


template< typename T >
void print( T const& container )
{
   std::cout << "\n (";
   for( auto const& element : container ) {
      std::cout << " " << element;
   }
   std::cout << " )\n\n";
}


int main()
{
   /*
   std::vector<int> v{};
   std::set<int> s{};

   for( int i=0; i<10; ++i ) {
      addElement( v, i );
      addElement( s, i );
   }

   print( v );
   print( s );
   */

   return EXIT_SUCCESS;
}

