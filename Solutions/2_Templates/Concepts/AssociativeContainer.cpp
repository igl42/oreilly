/**************************************************************************************************
*
* \file AssociativeContainer.cpp
* \brief C++ Training - C++20 concepts programming task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Define the 'AssociativeContainer' concept to constrain the 'addElement()' function
*         such that for associative containers the 'insert()' function is used and for
*         sequence containers the 'push_back()' function. The concept should pose the following
*         requirements on the given type:
*           - the type should be a regular class type;
*           - the type has a nested type 'value_type';
*           - the type has a nested type 'key_type';
*           - the type has a nested type 'iterator';
*           - the type has a nested type 'const_iterator';
*           - the type has a member function 'size()', which result in something convertible to 'size_t';
*           - the type has a member function 'empty()', which results in 'bool';
*           - the type has a member function 'begin()', which results in 'iterator';
*           - the type has a member function 'end()', which results in 'iterator';
*           - the type has a member function 'cbegin()', which results in 'const_iterator';
*           - the type has a member function 'cend()', which results in 'const_iterator';
*           - the type has a member function 'insert()', which takes a 'value_type';
*           - the type has a member function 'find()', which takes a 'key_type';
*           - the const type has a member function 'begin()', which results in 'const_iterator';
*           - the const type has a member function 'end()', which results in 'const_iterator'.
*
* Step 2: Define the type trait 'IsAssociativeContainer', including the according variable template
*
**************************************************************************************************/

#include <concepts>
#include <cstdlib>
#include <iostream>
#include <set>
#include <type_traits>
#include <vector>


// Step 1: Define the 'AssociativeContainer' concept
template< typename T >
concept AssociativeContainer =
   std::is_class_v<T> &&
   std::regular<T> &&
   requires {
      typename T::value_type;
      typename T::key_type;
      typename T::iterator;
      typename T::const_iterator;
   } &&
   requires ( T cont, T::value_type value ) {  // the typename keyword is optional in this context
      { cont.begin() } -> std::same_as<typename T::iterator>;
      { cont.end() } -> std::same_as<typename T::iterator>;
      cont.insert( value );
      cont.find( std::declval<typename T::key_type>() );
   } &&
   requires ( T const cont ) {
      { cont.size() } -> std::convertible_to<size_t>;  // or alternatively std::integral
      { cont.empty() } -> std::same_as<bool>;
      { cont.begin() } -> std::same_as<typename T::const_iterator>;
      { cont.end() } -> std::same_as<typename T::const_iterator>;
      { cont.cbegin() } -> std::same_as<typename T::const_iterator>;
      { cont.cend() } -> std::same_as<typename T::const_iterator>;
   };


// Step 2: Define the 'IsAssociativeContainer' type trait, including the according variable template
template< typename T >
struct IsAssociativeContainer
   : std::bool_constant< AssociativeContainer<T> >
{};

template< typename T >
constexpr bool IsAssociativeContainer_v = IsAssociativeContainer<T>::value;


// Step 1: Constrain the 'addElement()' functions such that for associative containers the
//         'insert()' function is used and for sequential containers the 'push_back()' function.

// Solution 1: Use the 'AssociativeContainer' concept to constrain (and specialize) the function
//             for associative containers (best match).
template< typename T, typename V >
void addElement( T& container, V const& value )
{
   container.push_back( value );
}

template< typename T, typename V >
   requires AssociativeContainer<T>
void addElement( T& container, V const& value )
{
   container.insert( value );
}

// Solution 2: Use the 'AssociativeContainer' concept as conditional for 'if constexpr' (first match).
/*
template< typename T, typename V >
void addElement( T& container, V const& value )
{
   if constexpr( AssociativeContainer<T> ) {
      container.insert( value );

   }
   else {
      container.push_back( value );
   }
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
   std::vector<int> v{};
   std::set<int> s{};

   for( int i=0; i<10; ++i ) {
      addElement( v, i );
      addElement( s, i );
   }

   print( v );
   print( s );

   return EXIT_SUCCESS;
}

