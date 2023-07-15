/**************************************************************************************************
*
* \file Fibonacci.cpp
* \brief C++ Training - Algorithm Programming Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Write the fibonacci() algorithm, which fills the given range with the Fibonacci
*       numbers (see https://simple.wikipedia.org/wiki/Fibonacci_number). Note that you
*       are not allowed to use any for, while, or do-while loops!
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>


// Write the fibonacci() algorithm, which fills the given range with the Fibonacci
// numbers (see https://simple.wikipedia.org/wiki/Fibonacci_number). Note that you
// are not allowed to use any for, while, or do-while loops!
//template< std::bidirectional_iterator BiDirIt >  // C++20
template< typename BiDirIt >
void fibonacci( BiDirIt first, BiDirIt last )
{
   // TODO
}


//template< std::input_iterator InputIt >  // C++20
template< typename InputIt >
void print( InputIt first, InputIt last )
{
   std::cout << '(';
   for( ; first!=last; ++first ) {
      std::cout << ' ' << *first;
   }
   std::cout << " )\n";
}


int main()
{
   std::vector<int> vector{ 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
   std::vector<int> result{ 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597 };

   fibonacci( vector.begin(), vector.end() );

   print( vector.begin(), vector.end() );
   print( result.begin(), result.end() );

   return EXIT_SUCCESS;
}
