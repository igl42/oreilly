/**************************************************************************************************
*
* \file PackEnumeration.cpp
* \brief C++ Training - Variadic Template Programming Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'enumerate_pack()' function, which calls the given callable for each
*       element of the parameter pack along with the according pack index.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>

using namespace std::string_literals;


template< typename Fn, size_t... Is, typename... Ts >
void enumerate_pack_helper( Fn fn, std::index_sequence<Is...>, Ts&&... values )
{
   ( fn( Is, std::forward<Ts>(values) ), ... );
}


template< typename Fn, typename... Ts >
void enumerate_pack( Fn fn, Ts&&... values )
{
   // C++17 solution
   enumerate_pack_helper( fn, std::make_index_sequence<sizeof...(Ts)>{}, std::forward<Ts>(values)... );

   // C++20 solution
   /*
   [&]<size_t... Is>( std::index_sequence<Is...> ){
      ( fn( Is, values ), ... );
   }( std::make_index_sequence<sizeof...(Ts)>{} );
   */
}


int main()
{
   enumerate_pack(
      []( size_t index, const auto& value ) {
         std::cout << ' ' << index << ": " << value << '\n';
      },
      42, 3.14, "Hello"s );

   return EXIT_SUCCESS;
}
