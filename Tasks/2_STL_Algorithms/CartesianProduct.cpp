/**************************************************************************************************
*
* \file CartesianProduct.cpp
* \brief C++ Training - Algorithm Programming Example
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Write the cartesian_product() algorithm, which combines every element of the first range
//      with every element of the second range (see https://en.wikipedia.org/wiki/Cartesian_product).
//      By default, the two elements should be combined in a 'std::tuple', but it should be
//      possible to configure the binary operation.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
//#include <ranges>  // C++20
#include <string>
#include <tuple>
#include <vector>


//---- <PrintTuple.h> -----------------------------------------------------------------------------

template< class Tuple, std::size_t... Is >
void print_tuple( std::ostream& os, const Tuple& t, std::index_sequence<Is...> )
{
   os << '(';

   // C++17 fold expression based on the comma operator
   ( ( os << ( Is == 0 ?  "" : "," ) << std::get<Is>(t) ), ... );

   os << ')';
}

template< typename... Args >
std::ostream& operator<<( std::ostream& os, std::tuple<Args...> const& tuple )
{
   print_tuple( os, tuple, std::make_index_sequence<sizeof...(Args)>{} );
   return os;
}


//---- <Algorithm.h> ------------------------------------------------------------------------------

struct MakeTuple
{
   template< typename... Args >
   auto operator()( Args&... args ) const
   {
      return std::make_tuple( std::forward<Args>(args)... );
   };
};


// Write the cartesian_product() algorithm, which combines every element of the first range
// with every element of the second range (see https://en.wikipedia.org/wiki/Cartesian_product).
// By default, the two elements should be combined in a 'std::tuple', but it should be possible
// to configure the binary operation.

/*
template< ... >
void cartesian_product( ... )
{

}
*/


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


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // Cartesian product to create tuples for the full set of all combinations of integers
   {
      std::vector<int> v1{ 1, 2 };
      std::vector<int> v2{ 1, 2, 3 };

      using Ints = std::tuple<int,int>;

      std::vector<Ints> expected_result{ {1,1}, {1,2}, {1,3}, {2,1}, {2,2}, {2,3} };
      std::vector<Ints> result( 6 );

      // cartesian_product( ... );

      print( result.begin(), result.end() );
      print( expected_result.begin(), expected_result.end() );
   }

   // Cartesian product to compute the product of all combinations of integers
   {
      std::vector<int> v1{ 1, 2, 3 };
      std::vector<int> v2{ 1, 2, 3, 4 };

      std::vector<int> expected_result{ 1, 2, 3, 4, 2, 4, 6, 8, 3, 6, 9, 12 };
      std::vector<int> result( 12, 0 );

      // cartesian_product( ... );

      print( result.begin(), result.end() );
      print( expected_result.begin(), expected_result.end() );
   }

   return EXIT_SUCCESS;
}
