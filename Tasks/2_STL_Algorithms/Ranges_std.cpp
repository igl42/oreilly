/**************************************************************************************************
*
* \file Ranges_std.cpp
* \brief C++ Training - Example for the C++20 ranges library
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Modify the given example of the C++20 ranges library to compute the first four squares
*       of odd numbers.
*
**************************************************************************************************/

#include <iostream>
#include <vector>
#include <ranges>


int main()
{
   std::vector<int> numbers{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

   auto evenNumbers = numbers | std::ranges::views::filter([](int n){ return n % 2 == 0; })
                              | std::ranges::views::transform([](int n) { return n * 2; })
                              | std::ranges::views::take( 3UL );

   std::cout << "\n (";
   for( int i : evenNumbers )
      std::cout << " " << i;
   std::cout << " )\n\n";

   return EXIT_SUCCESS;
}
