/**************************************************************************************************
*
* \file SortSubrange.cpp
* \brief C++ Training - Algorithm Programming Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'sort_subrange' algorithm in the following example. The algorithm should
*       take four iterators, which specify the total range of elements and the subrange to be
*       sorted.
*
**************************************************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>


template< typename RandomAccessIt, typename Pred >
void sort_subrange( RandomAccessIt first, RandomAccessIt last,
                    RandomAccessIt sub_first, RandomAccessIt sub_last, Pred p )
{
   if( sub_first == sub_last ) return;  // the empty sub-range is already sorted.

   if( sub_first != first ) {  // sub-range is at the start, don't need to partition
  	   std::nth_element( first, sub_first, last, p );
  	   ++sub_first;
  	}

   std::partial_sort( sub_first, sub_last, last, p );
}


template< typename RandomAccessIt >
void sort_subrange( RandomAccessIt first, RandomAccessIt last,
                    RandomAccessIt sub_first, RandomAccessIt sub_last )
{
   sort_subrange( first, last, sub_first, sub_last, std::less<>() );
}


int main()
{
   std::vector<int> v{ 3, 2, 11, 5, 4, 6, 12, 7, 8, 9, 1, 10 };

   // Sort the subrange [begin+2,begin+6) within the range [begin,end) in ascending order
   sort_subrange( v.begin(), v.end(), v.begin()+2, v.begin()+6 );

   std::cout << "\n (";
   for( int i : v )
      std::cout << ' ' << i;
   std::cout << " )\n\n";

   // Sort the subrange [begin+3,begin+7) within the range [begin,end) in descending order
   sort_subrange( v.begin(), v.end(), v.begin()+3, v.begin()+7, std::greater<>() );

   std::cout << "\n (";
   for( int i : v )
      std::cout << ' ' << i;
   std::cout << " )\n\n";
}
