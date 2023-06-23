/**************************************************************************************************
*
* \file Adapter_2.cpp
* \brief C++ Training - Example for the Adapter Design Pattern
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Implement the given 'accumulate()' algorithm such that it also works flawlessly
*         in combination with a built-in array.
*
* Step 2: Identify a second example for the Adapter design patterns in the given code snippet.
*         Explain why it serves as an adapter in this context.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <numeric>
#include <utility>
#include <type_traits>
#include <vector>


//---- <Algorithm.h> ------------------------------------------------------------------------------

template< typename InputIt >
decltype(auto) accumulate( InputIt first, InputIt last )
{
   using value_type = typename InputIt::value_type;
   using return_type = decltype( std::declval<value_type>() + std::declval<value_type>() );

   return std::accumulate( first, last, return_type{} );
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // std::vector<int>
   {
      std::vector<int> v{ 1, 2, 3, 4 };

      auto const result = accumulate( std::begin(v), std::end(v) );

      std::cout << " result = " << result << "\n";
   }

   // Built-in array
   /*
   {
      int array[] = { 1, 2, 3, 4 };

      auto const result = accumulate( std::begin(array), std::end(array) );

      std::cout << " result = " << result << "\n";
   }
   */

   return EXIT_SUCCESS;
}

