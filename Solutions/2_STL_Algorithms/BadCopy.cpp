/**************************************************************************************************
*
* \file BadCopy.cpp
* \brief C++ Training - Idiomatic C++ Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Explain the error in the following program.
*
**************************************************************************************************/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>


int main()
{
   std::vector<int> vec;
   std::list<int> lst;
   int i( 0 );

   while ( std::cin >> i ) {
      lst.push_back( i );
   }

   std::copy( lst.begin(), lst.end(), std::back_inserter( vec ) );

   std::copy( vec.begin(), vec.end(), std::ostream_iterator<int>( std::cout, "\n" ) );
}

