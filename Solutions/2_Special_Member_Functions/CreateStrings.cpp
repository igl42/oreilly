/**************************************************************************************************
*
* \file CreateStrings.cpp
* \brief C++ Training - Performance Optimization via Move Operations
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Improve the performance of the given code by refactoring. After each modification, first
*       predict how performance is affected and then benchmark the actual effect. Explain why
*       performance was affected accordingly. Note that we assume that the 'createStrings()'
*       function does not produce a predictable result!
*
**************************************************************************************************/

#include <array>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


std::array<std::string,3UL> createStrings()
{
   std::string s( "A long string with 32 characters" );

   std::array<std::string,3UL> strings{ s, s+s, s };

   return strings;
}


int main()
{
   const size_t N( 100000UL );

   std::vector<std::string> strings{};

   std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
   start = std::chrono::high_resolution_clock::now();

   for( size_t i=0UL; i<N; ++i ) {
      auto tmp{ createStrings() };
      strings.push_back( std::move( tmp[0] ) );
      strings.push_back( std::move( tmp[1] ) );
      strings.push_back( std::move( tmp[2] ) );
   }

   end = std::chrono::high_resolution_clock::now();
   const std::chrono::duration<double> elapsedTime( end - start );
   const double seconds( elapsedTime.count() );

   std::cout << " Runtime: " << seconds << "s\n\n";

   return EXIT_SUCCESS;
}

