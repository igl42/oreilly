/**************************************************************************************************
*
* \file BadAccumulate.cpp
* \brief C++ Training - Standard Library Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Using a std::vector with double precision floating point values, what, if anything,
*       is wrong with the following call to the 'accumulate' function?
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <numeric>
#include <vector>


int main()
{
   std::vector<double> vec( 4U );
   vec[0] = 1.2;
   vec[1] = 3.1;
   vec[2] = 0.4;
   vec[3] = 1.5;

   const double sum = std::accumulate( vec.begin(), vec.end(), 0 );

   std::cout << "\n"
             << " Sum of all values = " << sum << "\n"
             << " Expected sum      = 6.2\n\n";

   return EXIT_SUCCESS;
}

