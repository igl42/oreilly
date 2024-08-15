/**************************************************************************************************
*
* \file MajorityVote.cpp
* \brief C++ Training - Algorithm Programming Example
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the Boyer-Moore majority vote algorithm [1], which determines the majority of
*       a sequence of elements (that is, an element that occurs repeatedly for more than half
*       of the elements of the input). The algorithm should take two iterators or a range and
*       return an optional representing the majority vote, if there is one.
*
*       [1] https://en.wikipedia.org/wiki/Boyer–Moore_majority_vote_algorithm
*
**************************************************************************************************/

#include <algorithm>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <iterator>
#include <numeric>
#include <optional>
#include <random>
#include <vector>


//---- <Algorithm.cpp> ----------------------------------------------------------------------------

template< typename ForwardIterator >
std::optional<typename std::iterator_traits<ForwardIterator>::value_type>
   majority_vote( ForwardIterator first, ForwardIterator last )
{
   // TODO

   return std::nullopt;
}

template< typename Range >
auto majority_vote( Range&& range )
{
   return majority_vote( begin(range), end(range) );
}




//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   assert( *majority_vote( std::vector{0} ) == 0 );
   assert( *majority_vote( std::vector{-1} ) == -1 );
   assert( *majority_vote( std::vector{0,1,1} ) == 1 );
   assert( *majority_vote( std::vector{1,0,1} ) == 1 );
   assert( *majority_vote( std::vector{1,1,2,1,2,3,3,2,2,2,1,2,2,3,2,2} ) == 2 );
   assert( *majority_vote( std::vector{INT_MIN,INT_MAX,INT_MAX,INT_MIN,INT_MIN} ) == INT_MIN );

   std::vector<int> v(100);
   std::iota( v.begin(), v.end(), 0 );
   std::fill_n( std::back_inserter(v), 101, 999 );
   std::shuffle( begin(v), end(v), std::random_device{} );
   assert( majority_vote(v) == 999 );

   return EXIT_SUCCESS;
}
