/**************************************************************************************************
*
* \file IsPunct_Benchmark.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Copy-and-paste the following code into 'quick-bench.com'. Benchmark the time to remove
*       the punctation characters from a string by means of different approaches.
*
**************************************************************************************************/

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>


//---- Benchmark configuration --------------------------------------------------------------------

constexpr size_t stringSize( 5000 );  // Size of the generated string
constexpr double percentage( 0.1 );  // Percentage of punctation characters (0..1)


//---- Auxiliary functionality --------------------------------------------------------------------

std::string generateString()
{
   std::string s( stringSize, 'a' );

   const size_t num( stringSize * percentage );
   std::fill_n( begin(s), num, '!' );

   std::random_device rd{};
   std::mt19937 mt{ rd() };
   std::shuffle( begin(s), end(s), mt );

   return s;
}

const std::string init( generateString() );


//---- Benchmarks ---------------------------------------------------------------------------------

static void SecondString_1a( benchmark::State& state )
{
   for( auto _ : state )
   {
      state.PauseTiming();
      std::string s{ init };
      std::string tmp{};
      state.ResumeTiming();

      for( size_t i=0UL; i<s.size(); ++i ) {
         if( !ispunct( s[i] ) ) {
            tmp.push_back( s[i] );
         }
      }

      s = tmp;
      benchmark::DoNotOptimize(s);
   }
}
BENCHMARK(SecondString_1a);


static void SecondString_1b( benchmark::State& state )
{
   for( auto _ : state )
   {
      state.PauseTiming();
      std::string s{ init };
      std::string tmp{};
      state.ResumeTiming();

      for( char c : s ) {
         if( !ispunct( c ) ) {
            tmp.push_back( c );
         }
      }

      s = tmp;
      benchmark::DoNotOptimize(s);
   }
}
BENCHMARK(SecondString_1b);


static void SingleElementErase_2a( benchmark::State& state )
{
   for( auto _ : state )
   {
      state.PauseTiming();
      std::string s{ init };
      std::string tmp{};
      state.ResumeTiming();

      for( size_t i=0UL; i<s.size(); )
      {
         if( std::ispunct( s[i] ) ) {
            s.erase( i, 1UL );
         }
         else {
            ++i;
         }
      }

      benchmark::DoNotOptimize(s);
   }
}
BENCHMARK(SingleElementErase_2a);


static void SingleElementErase_2b( benchmark::State& state )
{
   for( auto _ : state )
   {
      state.PauseTiming();
      std::string s{ init };
      std::string tmp{};
      state.ResumeTiming();

      for( auto pos=s.begin(); pos!=s.end(); )
      {
         if( std::ispunct(*pos) ) {
            pos = s.erase( pos );
         }
         else {
            ++pos;
         }
      }

      benchmark::DoNotOptimize(s);
   }
}
BENCHMARK(SingleElementErase_2b);


static void TwoCursors_3a( benchmark::State& state )
{
   for( auto _ : state )
   {
      state.PauseTiming();
      std::string s{ init };
      std::string tmp{};
      state.ResumeTiming();

      size_t read{}, write{};
      for( ; read!=s.size(); ++read ) {
         if( !ispunct( s[read] ) ) {
            s[write] = s[read];
            ++write;
         }
      }
      s.resize( write );

      benchmark::DoNotOptimize(s);
   }
}
BENCHMARK(TwoCursors_3a);


static void TwoCursors_3b( benchmark::State& state )
{
   for( auto _ : state )
   {
      state.PauseTiming();
      std::string s{ init };
      std::string tmp{};
      state.ResumeTiming();

      auto reader( s.begin() );
      auto writer( s.begin() );
      for( ; reader!=s.end(); ++reader ) {
         if( !ispunct( *reader ) ) {
            *writer = *reader;
            ++writer;
         }
      }
      s.erase( writer, reader );

      benchmark::DoNotOptimize(s);
   }
}
BENCHMARK(TwoCursors_3b);


static void RemoveEraseIdiom_4( benchmark::State& state )
{
   for( auto _ : state )
   {
      state.PauseTiming();
      std::string s{ init };
      std::string tmp{};
      state.ResumeTiming();

      s.erase( std::remove_if( begin(s), end(s), ispunct ), end(s) );

      benchmark::DoNotOptimize(s);
   }
}
BENCHMARK(RemoveEraseIdiom_4);

