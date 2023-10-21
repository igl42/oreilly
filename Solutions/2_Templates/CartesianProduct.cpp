/**************************************************************************************************
*
* \file CartesianProduct.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the following 'cartesian_product()' function to determine the cartesian
*       product of several given input ranges. For example, the given 'main()' function should
*       result in the following output:
*
*       1-a
*       1-b
*       2-a
*       2-b
*       3-a
*       3-b
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>
#include <type_traits>
#include <vector>


template< typename Func, typename... Ranges >
void cartesian_product( Func func, Ranges const&... ranges )
{
   // TODO: Implement the 'cartesian_product()' function to determine the cartesian
   //       product of several given input ranges.
}


int main()
{
   std::vector<int> v1{ 1, 2, 3 };
   std::vector<char> v2{ 'a', 'b' };
   std::vector<std::string> v3{ "red", "blue" };

   // Cartesian product with a single range
   //cartesian_product( []( auto const& e1 ){
   //   std::cout << e1 << '\n';
   //}, v1 );

   // Cartesian product with two ranges
   cartesian_product( []( auto const& e1, auto const& e2 ){
      std::cout << e1 << '-' << e2 << '\n';
   }, v1, v2 );

   // Cartesian product with three ranges
   //cartesian_product( []( auto const& e1, auto const& e2, auto const& e3 ){
   //   std::cout << e1 << '-' << e2 << '-' << e3 << '\n';
   //}, v1, v2, v3 );

   return EXIT_SUCCESS;
}
