/**************************************************************************************************
*
* \file Move4.cpp
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


class Person
{
 public:
   template< typename T >
   explicit Person( T&& ) { std::cout << "\n Calls function (1)\n"; }     // (1)

   explicit Person( int id ) { std::cout << "\n Calls function (2)\n"; }  // (2)

   Person( const Person& ) { std::cout << "\n Calls function (3)\n"; }    // (3)
};


int main()
{
   Person p1( "Nancy" );
   Person p2( 4 );
   Person p3( 5UL );
   Person p4( p3 );

   return EXIT_SUCCESS;
}

