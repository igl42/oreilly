/**************************************************************************************************
*
* \file Sign2.cpp
* \brief C++ Training - Simple C++20 concepts programming task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Constrain the 'sign()' function to only integral data types by means of C++20 concepts.
*
**************************************************************************************************/

#include <concepts>
#include <iostream>
#include <string>
#include <type_traits>

using namespace std::string_literals;


//template< typename T >
//concept integral = std::is_integral_v<T>;


template< std::integral T >
constexpr T
   sign( T a ) noexcept
{
   return ( std::is_signed<T>::value )
          ? ( T{0} < a ) - ( a < T{0} )
          : ( T{0} < a );
}


int main()
{
   std::cout << "\n"
             << " sign(  5 ) = " << sign(  5 ) << "\n"
             << " sign(  0 ) = " << sign(  0 ) << "\n"
             << " sign( -5 ) = " << sign( -5 ) << "\n"
             << "\n";

   // This line should not compile
   //sign( "fourty-two"s );
}

