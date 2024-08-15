/**************************************************************************************************
*
* \file Trap.cpp
* \brief C++ Training - Algorithm Programming Example
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the following 'trap()' algorithm for a given vector of non-negative integers.
*       The given vector represents an elevation map, where the width of each bar is 1. The
*       'trap()' algorithm should compute how much water can be trapped in between the peaks.
*
*       Example: For the following elevation map, 'trap()' should compute a result of 6.
*
*                   x                      x
*               x   xx x      =>       x---xx-x
*             x xx xxxxxx            x-xx-xxxxxx
*       ----------------------------------------------
*
**************************************************************************************************/

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <numeric>
#include <vector>


// Generic wrapper around the std::max() algorithm; can be conveniently passed to algorithms.
struct Max
{
   template< typename T >
   decltype(auto) operator()( T const& a, T const& b ) const
   {
      using std::max;
      return max( a, b );
   }
};

// Alternative: function returning a lambda
/*
auto max()
{
   return []( auto const& a, auto const& b ) -> decltype(auto)
   {
      using std::max;
      return max(a,b);
   };
}
*/


// Creates a reverse iterator from the given random access iterator
template< typename RandomAccessIter >
decltype(auto) rev( RandomAccessIter pos )
{
   return std::reverse_iterator<RandomAccessIter>( pos );
}


int trap( std::vector<int> const& v )
{
   auto const pos = std::max_element( begin(v), end(v) );

   std::vector<int> u( std::size(v), 0 );
   std::inclusive_scan( begin(v), std::next(pos), begin(u), Max{} );
   std::inclusive_scan( rbegin(v), rev(pos), rbegin(u), Max{} );

   return std::transform_reduce( begin(u), end(u), begin(v), int{}, std::plus{}, std::minus{} );
}


int main()
{
   // Represent the following elevation map; expected result is 6.
   //
   //        x                      x
   //    x   xx x      =>       x---xx-x
   //  x xx xxxxxx            x-xx-xxxxxx
   //-------------------------------------------------------------------
   //
   {
      std::vector<int> v{ 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
      auto const result = trap( v );
      std::cout << "\n Example 1: trapped water: " << result << " (expected: 6)\n\n";
   }


   // Represent the following elevation map; expected result is 9.
   //
   //         x                        x
   //    x   xx                   x---xx
   //    x x xxx x       =>       x-x-xxx-x
   //  x xxx xxxxx x            x-xxx-xxxxx-x
   //-------------------------------------------------------------------
   //
   {
      std::vector<int> v{ 1, 0, 3, 1, 2, 0, 3, 4, 2, 1, 2, 0, 1 };
      auto const result = trap( v );
      std::cout << "\n Example 2: trapped water: " << result << " (expected: 9)\n\n";
   }


   // Represent the following elevation map; expected result is 9.
   //
   //         x  x                     x---x
   //    x   xx  xx                x---xx--xx
   //    x x xxx xx       =>       x-x-xxx-xx
   //  x xxx xxxxxx x            x-xxx-xxxxxx-x
   //-------------------------------------------------------------------
   //
   {
      std::vector<int> v{ 1, 0, 3, 1, 2, 0, 4, 3, 2, 1, 4, 3, 0, 1 };
      auto const result = trap( v );
      std::cout << "\n Example 3: trapped water: " << result << " (expected: 14)\n\n";
   }

   return EXIT_SUCCESS;
}
