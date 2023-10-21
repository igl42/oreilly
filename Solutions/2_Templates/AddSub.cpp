/**************************************************************************************************
*
* \file AddSub.cpp
* \brief C++ Training - Variadic Templates Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'addsub()' function, which performs an alternating addition/subtraction
*       of the given arguments. Examples:
*
*             addsub( 10, 9, 8, 7, 6 )    => 10 - 9 + 8 - 7 + 6     = 8
*             addsub( 10, 9, 8, 7, 6, 5 ) => 10 - 9 + 8 - 7 + 6 - 5 = 3
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>


template< typename T >
auto addsub( const T& a )
{
   return a;
}

template< typename T >
auto subadd( const T& a )
{
   return -a;
}

template< typename T, typename... Ts >
auto addsub( const T& a, const Ts&... args );

template< typename T, typename... Ts >
auto subadd( const T& a, const Ts&... args )
{
   return -a + addsub( args... );
}

template< typename T, typename... Ts >
auto addsub( const T& a, const Ts&... args )
{
   return a + subadd( args... );
}



int main()
{
   std::cout << "\n"
             << " addsub( 10, 9, 8, 7, 6    ) = " << addsub( 10, 9, 8, 7, 6    ) << " (expected: 8)\n"
             << " addsub( 10, 9, 8, 7, 6, 5 ) = " << addsub( 10, 9, 8, 7, 6, 5 ) << " (expected: 3)\n"
             << "\n";

   return EXIT_SUCCESS;
}

