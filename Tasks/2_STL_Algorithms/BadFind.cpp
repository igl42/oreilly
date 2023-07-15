/**************************************************************************************************
*
* \file BadFind.cpp
* \brief C++ Training - Standard Library Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Explain the problem in the following program.
*
**************************************************************************************************/

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <numeric>
#include <set>
#include <vector>


int main()
{
   constexpr size_t size( 20'000 );

   std::vector<int> v( size );

   std::iota( begin(v), end(v), 0 );

   std::set<int> s( begin(v), end(v) );


   std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
   start = std::chrono::high_resolution_clock::now();

   for( int i=0; i<size; ++i )
   {
      const auto pos = std::find( std::begin(s), std::end(s), i );

      if( pos == std::end(s) ) {
         std::cerr << "\nERROR!!!\n\n";
      }
   }

   end = std::chrono::high_resolution_clock::now();
   const std::chrono::duration<double> elapsedTime( end - start );
   const double seconds( elapsedTime.count() );

   std::cout << " Runtime: " << seconds << "s\n\n";

   return EXIT_SUCCESS;
}

