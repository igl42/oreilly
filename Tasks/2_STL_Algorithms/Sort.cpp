/**************************************************************************************************
*
* \file Sort.cpp
* \brief C++ Training - Container Performance Benchmark
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Copy-and-paste the following code into 'quick-bench.com'. Benchmark the time to build
*       a sorted standard container.
*
**************************************************************************************************/

#include <algorithm>
#include <deque>
#include <iostream>
#include <list>
#include <numeric>
#include <random>
#include <set>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <vector>


//---- Benchmark configuration --------------------------------------------------------------------

constexpr size_t size( 200 );  // Size of the generated container
constexpr size_t iterations( 1000 );  // Number of benchmark iterations
using Type = int;  // Type of the elements (an arithmetic type or std::string)

#define BENCHMARK_VECTOR         1
#define BENCHMARK_DEQUE          1
#define BENCHMARK_LIST           1
#define BENCHMARK_SET            1
#define BENCHMARK_UNORDERED_SET  1


//---- Benchmark setup ----------------------------------------------------------------------------

std::random_device rd{};
std::mt19937 mt{ rd() };

template< typename T >
std::vector<T> generateOrder()
{
   std::vector<T> v( size );

   if constexpr( std::is_arithmetic_v<T> )
   {
      std::iota( begin(v), end(v), T{} );
      std::shuffle( begin(v), end(v), mt );
   }
   else if constexpr( std::is_same_v<T,std::string> )
   {
      size_t counter( 0UL );
      std::generate( begin(v), end(v), [&counter](){
         return std::to_string(counter++);
      } );
      std::shuffle( begin(v), end(v), mt );
   }
   else
   {
      throw std::invalid_argument( "Unsupported type" );
   }

   return v;
}

const std::vector<Type> initOrder( generateOrder<Type>() );


//---- Benchmark for vectors ----------------------------------------------------------------------

static void Vector(benchmark::State& state)
{
   for( auto _ : state )
   {
      std::vector<Type> data{};
      data.reserve( size );

      for( const auto& item : initOrder ) {
         data.push_back( item );
      }
      std::sort( begin(data), end(data) );

      if( data.size() != size ) std::cerr << " ERROR!!!\n";
   }
}
#if BENCHMARK_VECTOR
BENCHMARK(Vector)->Iterations(iterations);
#endif


//---- Benchmark for deques -----------------------------------------------------------------------

static void Deque(benchmark::State& state)
{
   for( auto _ : state )
   {
      std::deque<Type> data{};

      for( const auto& item : initOrder ) {
         data.push_back( item );
      }
      std::sort( begin(data), end(data) );

      if( data.size() != size ) std::cerr << " ERROR!!!\n";
   }
}
#if BENCHMARK_DEQUE
BENCHMARK(Deque)->Iterations(iterations);
#endif


//---- Benchmark for sorted lists -----------------------------------------------------------------

static void List(benchmark::State& state)
{
   for( auto _ : state )
   {
      std::list<Type> data{};

      for( const auto& item : initOrder ) {
         data.push_back( item );
      }
      data.sort();

      if( data.size() != size ) std::cerr << " ERROR!!!\n";
   }
}
#if BENCHMARK_LIST
BENCHMARK(List)->Iterations(iterations);
#endif


//---- Benchmark for sets -------------------------------------------------------------------------

static void Set(benchmark::State& state)
{
   for( auto _ : state )
   {
      std::set<Type> data{};

      for( const auto& item : initOrder ) {
         data.insert( item );
      }

      if( data.size() != size ) std::cerr << " ERROR!!!\n";
   }
}
#if BENCHMARK_SET
BENCHMARK(Set)->Iterations(iterations);
#endif


//---- Benchmark for unordered sets ---------------------------------------------------------------

static void UnorderedSet(benchmark::State& state)
{
   for( auto _ : state )
   {
      std::unordered_set<Type> data{};

      for( const auto& item : initOrder ) {
         data.insert( item );
      }

      if( data.size() != size ) std::cerr << " ERROR!!!\n";
   }
}
#if BENCHMARK_UNORDERED_SET
BENCHMARK(UnorderedSet)->Iterations(iterations);
#endif
