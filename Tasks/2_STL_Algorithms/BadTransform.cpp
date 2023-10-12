/**************************************************************************************************
*
* \file BadTransform.cpp
* \brief C++ Training - Standard Library Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Explain the error in the following program.
*
**************************************************************************************************/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>


int transmogrify( int x )
{
   return x * x;
}


int main()
{
   std::vector<int> values( 4UL );
   values[0] = 1;
   values[1] = 2;
   values[2] = 3;
   values[3] = 4;

   std::vector<int> results;

   // Apply 'transmogrify' to each object in values, appending the return values to results
   transform( values.begin(), values.end(), results.end(), transmogrify );

   std::copy( results.begin(), results.end(), std::ostream_iterator<int>( std::cout, "\n" ) );

   return EXIT_SUCCESS;
}

