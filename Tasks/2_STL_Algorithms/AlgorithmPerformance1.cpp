/**************************************************************************************************
*
* \file AlgorithmPerformance1.cpp
* \brief C++ Training - STL Algorithm Performance Analysis
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Copy-and-paste the following code into 'godbolt.org'. Compare the generated assembly
*       code for the following three different solutions:
*         - an iterator-based manual for loop;
*         - the STL 'accumulate()' algorithm;
*         - an index-based manual for loop;
*
**************************************************************************************************/

#include <cstdlib>
#include <numeric>
#include <vector>


double sum( std::vector<double> const& values )
{
   double s{};

   // Solution 1: Range-based manual for loop
   for( double d : values ) {
      s += d;
   }

   // Solution 2: STL algorithm
   //s = std::accumulate( begin(values), end(values), double{} );

   // Solution 3: Index-based manual for loop
   //for( size_t i=0UL; i<values.size(); ++i ) {
   //   s += values[i];
   //}

   return s;
}


int main()
{
   return EXIT_SUCCESS;
}
