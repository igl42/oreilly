/**************************************************************************************************
*
* \file Median.cpp
* \brief C++ Training - Algorithm Programming Example
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'median()' algorithm that computes the median of a given range of arithmetic
*       values (i.e. integral or floating point values). The algorithm should take a pair of
*       random access iterators or a range and return an optional representing the result.
*
*       Note: Useful tools from the standard library:
*        - std::midpoint(): https://en.cppreference.com/w/cpp/numeric/midpoint
*        - std::iter_value_t: https://en.cppreference.com/w/cpp/iterator/iter_t
*        - std::conditional_t: https://en.cppreference.com/w/cpp/types/conditional
*
**************************************************************************************************/

#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iterator>
#include <numeric>
#include <optional>
#include <type_traits>
#include <vector>


//---- <Numeric.cpp> ------------------------------------------------------------------------------

template< typename RandomAccessIterator >
auto median( RandomAccessIterator first, RandomAccessIterator last )
{
   // TODO
}

template< typename Range >
auto median( Range&& range )
{
   // TODO
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   /*
   assert( median( std::vector{ 1, 2, 3, 4, 5 } ) == 3.0 );
   assert( median( std::vector{ 1, 2, 3, 4, 5, 6 } ) == 3.5 );
   assert( median( std::vector{ 1.0F, 3.0F, 5.0F } ) == 3.0F );
   assert( median( std::vector{ 1.0F, 3.0F, 5.0F, 7.0F } ) == 4.0F );
   assert( median( std::vector{ 1.1, 1.2, 1.3 } ) == 1.2 );
   assert( median( std::vector{ 1.1, 1.2, 1.3, 1.4 } ) == 1.25 );
   */

   return EXIT_SUCCESS;
}
