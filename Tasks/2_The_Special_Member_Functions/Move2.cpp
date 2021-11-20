/**************************************************************************************************
*
* \file Move2.cpp
* \brief C++ Training - Example for Move Semantics
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Which of the following three functions is called in the subsequent function call?
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>


struct X {};

void f( X&       ) { std::cout << "\n Call to function (1)\n"; };  // (1)
void f( const X& ) { std::cout << "\n Call to function (2)\n"; };  // (2)
void f( X&&      ) { std::cout << "\n Call to function (3)\n"; };  // (3)


int main()
{
   X x;
   f( x );

   f( X{} );

   return EXIT_SUCCESS;
}

