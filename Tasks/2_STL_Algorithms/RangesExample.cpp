/**************************************************************************************************
*
* \file RangesExample.cpp
* \brief C++ Training - Example for the C++20 ranges library
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Modify the given example of the C++20 ranges library to compute the first four squares
*       of odd numbers.
*
**************************************************************************************************/

#include <algorithm>
#include <concepts>
#include <cstdlib>
#include <iostream>
#include <ranges>
#include <vector>


int compute( int i ) { return i*2; }
bool isEven( int i ) { return i%2==0; }
bool isOdd( int i ) { return i%2==1; }


void print( std::ranges::input_range auto&& range )
{
   std::cout << "\n (";
   std::ranges::for_each( range, []( const auto& value ){ std::cout << ' ' << value; } );
   std::cout << " )\n\n";
}


int main()
{
   // Note: std::views is a standard shortcut for std::ranges::views

   std::vector<int> numbers{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

   auto scaledEvenNumbers = numbers
                          | std::views::filter([](int n){ return isEven(n); })
                          | std::views::transform([](int n) { return compute(n); })
                          | std::views::take( 3UL );

   print( scaledEvenNumbers );

   return EXIT_SUCCESS;
}
