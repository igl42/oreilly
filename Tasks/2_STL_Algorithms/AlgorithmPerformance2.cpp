/**************************************************************************************************
*
* \file AlgorithmPerformance2.cpp
* \brief C++ Training - STL Algorithm Performance Analysis
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Copy-and-paste the following code into 'quick-bench.com'. Benchmark the time to sort
*       a std::vector of integers.
*
**************************************************************************************************/

#include <algorithm>
#include <numeric>
#include <random>
#include <vector>


//---- Benchmark configuration --------------------------------------------------------------------

constexpr size_t size( 10000 );  // Size of the generated container
constexpr size_t iterations( 1000 );  // Number of benchmark iterations


//---- NO_INLINE macro ----------------------------------------------------------------------------

#if defined(__GNUC__)
#  define NO_INLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#  define NO_INLINE __declspec(noinline)
#else
#  define NO_INLINE
#endif


//---- ALWAYS_INLINE macro ------------------------------------------------------------------------

#if ALWAYS_INLINE && defined(__GNUC__)
#  define ALWAYS_INLINE __attribute__((always_inline)) inline
#elif ( defined(_MSC_VER) || defined(__INTEL_COMPILER) )
#  define ALWAYS_INLINE __forceinline
#else
#  define ALWAYS_INLINE inline
#endif


//---- Benchmark setup ----------------------------------------------------------------------------

std::random_device rd{};
std::mt19937 mt{ rd() };

std::vector<int> generateOrder()
{
   std::vector<int> v( size );
   std::iota( begin(v), end(v), int{} );
   std::shuffle( begin(v), end(v), mt );
   return v;
}

const std::vector<int> initOrder( generateOrder() );


//---- Benchmark for std::sort with lambda --------------------------------------------------------

static void sort1( benchmark::State& state )
{
   std::vector<int> values( size );

   for( auto _ : state )
   {
      state.PauseTiming();
      values = initOrder;
      state.ResumeTiming();

      std::sort( begin(values), end(values), std::less<>{} );
   }
}
BENCHMARK(sort1)->Iterations(iterations);


//---- Benchmark for std::sort with function pointer ----------------------------------------------

NO_INLINE bool compare( int x, int y )
{
   return x < y;
}

static void sort2( benchmark::State& state )
{
   std::vector<int> values( size );

   for( auto _ : state )
   {
      state.PauseTiming();
      values = initOrder;
      state.ResumeTiming();

      std::sort( begin(values), end(values), compare );
   }
}
BENCHMARK(sort2)->Iterations(iterations);


//---- Benchmark for std::qsort -------------------------------------------------------------------

int int_compare( const void* x, const void* y )
{
   const int arg1 = *static_cast<const int*>(x);
   const int arg2 = *static_cast<const int*>(y);

   if( arg1 < arg2 )
      return -1;
   else if( arg2 < arg1 )
      return 1;
   else
      return 0;
}

static void sort3( benchmark::State& state )
{
   std::vector<int> values( size );

   for( auto _ : state )
   {
      state.PauseTiming();
      values = initOrder;
      state.ResumeTiming();

      std::qsort( values.data(), values.size(), sizeof(int), int_compare );
   }
}
BENCHMARK(sort3)->Iterations(iterations);

