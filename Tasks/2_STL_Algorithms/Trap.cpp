/**************************************************************************************************
*
* \file Trap.cpp
* \brief C++ Training - Algorithm Programming Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
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


int trap( const std::vector<int>& v )
{
   // TODO: Implement the 'trap()' algorithm
   return 0;
}


int main()
{
   // Represent the following mountainous range; expected result is 6
   //
   //        x                      x
   //    x   xx x      =>       x---xx-x
   //  x xx xxxxxx            x-xx-xxxxxx
   //-------------------------------------------------------------------
   //
   {
      std::vector<int> v{ 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
      const auto result = trap( v );
      std::cout << "\n Example 1: trapped water: " << result << " (expected: 6)\n\n";
   }


   // Represent the following mountainous range; expected result is 9
   //
   //         x                        x
   //    x   xx                   x---xx
   //    x x xxx x       =>       x-x-xxx-x
   //  x xxx xxxxx x            x-xxx-xxxxx-x
   //-------------------------------------------------------------------
   //
   {
      std::vector<int> v{ 1, 0, 3, 1, 2, 0, 3, 4, 2, 1, 2, 0, 1 };
      const auto result = trap( v );
      std::cout << "\n Example 2: trapped water: " << result << " (expected: 9)\n\n";
   }

   return EXIT_SUCCESS;
}
