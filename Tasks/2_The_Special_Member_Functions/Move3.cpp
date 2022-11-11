/**************************************************************************************************
*
* \file Move3.cpp
* \brief C++ Training - Example for Move Semantics
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Which of the following three functions is called in the subsequent function call?
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>


template< typename T >
void f( T   ) { std::cout << "\n Call to function (1)\n"; };  // (1)

template< typename T >
void f( T&  ) { std::cout << "\n Call to function (2)\n"; };  // (2)

template< typename T >
void f( T&& ) { std::cout << "\n Call to function (3)\n"; };  // (3)


int main()
{
   f( 0 );

   int x = 0;
   f( x );

   return EXIT_SUCCESS;
}

