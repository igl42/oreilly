/**************************************************************************************************
*
* \file LongestStreak.cpp
* \brief C++ Training - Algorithm Programming Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Determine the longest streak of consecutive equal values in the given range of elements.
*       Examples:
*          {} -> longest streak: 0
*          { 0 } -> longest streak: 1
*          { 0, 0 } -> longest streak: 2
*          { 0, 1 } -> longest streak: 1
*          { 0, 0, 1 } -> longest streak: 2
*          { 0, 1, 1 } -> longest streak: 2
*          { 0, 0, 0, 1 } -> longest streak: 3
*          { 0, 0, 0, 1, 1, 1, 1 } -> longest streak: 4
*          { 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0 } -> longest streak: 8
*
**************************************************************************************************/

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>


template< typename InputIterator >
size_t longest_streak( InputIterator first, InputIterator last )
{
   if( first == last )
      return 0UL;

   size_t streak{};
   std::inner_product( first, last-1, first+1, size_t{}
                     , [&streak]( size_t maxStreak, const auto& currentStreak ) {
                          if( currentStreak == size_t{1} ) {
                             streak = std::max( streak, maxStreak+1UL );
                             return maxStreak+1UL;
                          }
                          else {
                             streak = std::max( streak, maxStreak );
                             return size_t{};
                          }
                       }
                     , []( const auto& a, const auto& b ) -> size_t {
                          return ( a == b ) ? 1 : 0;
                       }
                     );
   return streak+1UL;
}


int main()
{
   std::vector<int> v1{};
   std::vector<int> v2{ 0 };
   std::vector<int> v3{ 0, 0 };
   std::vector<int> v4{ 0, 1 };
   std::vector<int> v5{ 0, 0, 1 };
   std::vector<int> v6{ 0, 1, 1 };
   std::vector<int> v7{ 0, 0, 0, 1 };
   std::vector<int> v8{ 0, 0, 0, 1, 1, 1, 1 };
   std::vector<int> v9{ 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0 };

   // Determine the longest streak in v1 to v9
   const auto streak1 = longest_streak( v1.begin(), v1.end() );
   const auto streak2 = longest_streak( v2.begin(), v2.end() );
   const auto streak3 = longest_streak( v3.begin(), v3.end() );
   const auto streak4 = longest_streak( v4.begin(), v4.end() );
   const auto streak5 = longest_streak( v5.begin(), v5.end() );
   const auto streak6 = longest_streak( v6.begin(), v6.end() );
   const auto streak7 = longest_streak( v7.begin(), v7.end() );
   const auto streak8 = longest_streak( v8.begin(), v8.end() );
   const auto streak9 = longest_streak( v9.begin(), v9.end() );

   std::cout << " The longest streak in v1 is " << streak1 << " (expected: 0)\n";
   std::cout << " The longest streak in v2 is " << streak2 << " (expected: 1)\n";
   std::cout << " The longest streak in v3 is " << streak3 << " (expected: 2)\n";
   std::cout << " The longest streak in v4 is " << streak4 << " (expected: 1)\n";
   std::cout << " The longest streak in v5 is " << streak5 << " (expected: 2)\n";
   std::cout << " The longest streak in v6 is " << streak6 << " (expected: 2)\n";
   std::cout << " The longest streak in v7 is " << streak7 << " (expected: 3)\n";
   std::cout << " The longest streak in v8 is " << streak8 << " (expected: 4)\n";
   std::cout << " The longest streak in v9 is " << streak9 << " (expected: 8)\n";
}
