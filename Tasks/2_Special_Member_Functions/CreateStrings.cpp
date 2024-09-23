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
* Step 1: Copy-and-paste the following code into 'quick-bench.com'. Benchmark the given code
*         example to create a performance base line.
*
* Step 2: Improve the performance of the given code by refactoring. After each modification, first
*         predict how performance is affected and then benchmark the actual effect. Explain why
*         performance was affected accordingly. Note that we assume that the 'createStrings()'
*         function does not produce a predictable result!
*
**************************************************************************************************/

#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


//---- Benchmark configuration --------------------------------------------------------------------

constexpr size_t N( 100000UL );


//---- Baseline Benchmark -------------------------------------------------------------------------

std::vector<std::string> createStrings_1()
{
   std::vector<std::string> strings{};
   strings.reserve( 3 );

   std::string s( "A long string with 32 characters" );

   strings.push_back( s );
   strings.push_back( s + s );
   strings.push_back( s );

   return strings;
}

static void benchmarkBaseline( benchmark::State& state )
{
   for( auto _ : state )
   {
      std::vector<std::string> strings{};

      for( size_t i=0UL; i<N; ++i ) {
         std::vector<std::string> tmp{};
         tmp = createStrings_1();
         strings.push_back( tmp[0] );
         strings.push_back( tmp[1] );
         strings.push_back( tmp[2] );
      }
   }
}
BENCHMARK(benchmarkBaseline);


//---- Optimized Benchmark ------------------------------------------------------------------------

std::vector<std::string> createStrings_2()
{
   std::vector<std::string> strings{};
   strings.reserve( 3 );

   std::string s( "A long string with 32 characters" );

   strings.push_back( s );
   strings.push_back( s + s );
   strings.push_back( s );

   return strings;
}

static void benchmarkOptimization( benchmark::State& state )
{
   for( auto _ : state )
   {
      std::vector<std::string> strings{};

      for( size_t i=0UL; i<N; ++i ) {
         std::vector<std::string> tmp{};
         tmp = createStrings_2();
         strings.push_back( tmp[0] );
         strings.push_back( tmp[1] );
         strings.push_back( tmp[2] );
      }
   }
}
//BENCHMARK(benchmarkOptimization);

