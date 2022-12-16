/**************************************************************************************************
*
* \file BridgedMembers.cpp
* \brief C++ Training - Data Members Performance Benchmark
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Copy-and-paste the following code into 'quick-bench.com'. Benchmark the time to determine
*       the oldest person contained in a std::vector of Persons.
*
**************************************************************************************************/

#include <memory>
#include <numeric>
#include <random>
#include <string>
#include <vector>


//---- Benchmark configuration --------------------------------------------------------------------

constexpr size_t size( 10000 );  // Size of the generated container
constexpr size_t iterations( 1000 );  // Number of benchmark iterations

#define BENCHMARK_PERSON1 1
#define BENCHMARK_PERSON2 0
#define BENCHMARK_PERSON3 0
#define BENCHMARK_PERSON4 0
#define BENCHMARK_PERSON5 0
#define BENCHMARK_PERSON6 0


//---- Random Number Setup ------------------------------------------------------------------------

std::random_device rd{};
const unsigned int seed( rd() );

std::mt19937 rng{};
std::uniform_int_distribution<int> dist( 1957, 2004 );

int get_random_year_of_birth()
{
   return dist( rd );
}

std::vector<int> get_random_years_of_birth()
{
   std::vector<int> years{ size };
   std::generate( begin(years), end(years), [](){
      return get_random_year_of_birth();
   } );
   return years;
}


//---- Person implementations ---------------------------------------------------------------------

struct Person1
{
   std::string forename{ "Homer" };
   std::string surname{ "Simpson" };
   std::string address{ "712 Red Bark Lane" };
   std::string zip{ "89011" };
   std::string city{ "Henderson" };
   std::string state{ "Nevada" };
   int year_of_birth{ get_random_year_of_birth() };
};

struct Person2
{
   struct Pimpl {
      std::string forename{ "Homer" };
      std::string surname{ "Simpson" };
      std::string address{ "712 Red Bark Lane" };
      std::string zip{ "89011" };
      std::string city{ "Henderson" };
      std::string state{ "Nevada" };
      int year_of_birth{ get_random_year_of_birth() };
   };

   std::unique_ptr<Pimpl> pimpl{ new Pimpl{} };
};

struct Person3
{
   std::string forename{ "Homer" };
   std::string surname{ "Simpson" };
   int year_of_birth{ get_random_year_of_birth() };

   struct Pimpl {
      std::string address{ "712 Red Bark Lane" };
      std::string zip{ "89011" };
      std::string city{ "Henderson" };
      std::string state{ "Nevada" };
   };

   std::unique_ptr<Pimpl> pimpl{ new Pimpl{} };
};

struct Person4
{
   int year_of_birth{ get_random_year_of_birth() };

   struct Pimpl {
      std::string forename{ "Homer" };
      std::string surname{ "Simpson" };
      std::string address{ "712 Red Bark Lane" };
      std::string zip{ "89011" };
      std::string city{ "Henderson" };
      std::string state{ "Nevada" };
   };

   std::unique_ptr<Pimpl> pimpl{ new Pimpl{} };
};

struct Pimpl5
{
   std::string forename{ "Homer" };
   std::string surname{ "Simpson" };
   int year_of_birth{ get_random_year_of_birth() };
   std::string address{ "712 Red Bark Lane" };
   std::string zip{ "89011" };
   std::string city{ "Henderson" };
   std::string state{ "Nevada" };
};

template< typename Pimpl >
struct Person5
{
   Pimpl pimpl;
};

struct Person6
{
   static std::vector<int> years_of_birth;
   size_t id{};

   struct Pimpl {
      std::string forename{ "Homer" };
      std::string surname{ "Simpson" };
      std::string address{ "712 Red Bark Lane" };
      std::string zip{ "89011" };
      std::string city{ "Henderson" };
      std::string state{ "Nevada" };
   };

   std::unique_ptr<Pimpl> pimpl{ new Pimpl{} };
};

std::vector<int> Person6::years_of_birth( get_random_years_of_birth() );


//---- Benchmark for Person1 ----------------------------------------------------------------------

static void determineOldestPerson1(benchmark::State& state)
{
   std::vector<Person1> persons( size );

   for( auto _ : state )
   {
      benchmark::DoNotOptimize(
         std::min_element( begin(persons), end(persons), []( auto const& p1, auto const& p2 ){
            return p1.year_of_birth < p2.year_of_birth;
         } )
      );
   }
}
#if BENCHMARK_PERSON1
BENCHMARK(determineOldestPerson1)->Iterations(iterations);
#endif


//---- Benchmark for Person2 ----------------------------------------------------------------------

static void determineOldestPerson2(benchmark::State& state)
{
   std::vector<Person2> persons( size );

   for( auto _ : state )
   {
      benchmark::DoNotOptimize(
         std::min_element( begin(persons), end(persons), []( auto const& p1, auto const& p2 ){
            return p1.pimpl->year_of_birth < p2.pimpl->year_of_birth;
         } )
      );
   }
}
#if BENCHMARK_PERSON2
BENCHMARK(determineOldestPerson2)->Iterations(iterations);
#endif


//---- Benchmark for Person3 ----------------------------------------------------------------------

static void determineOldestPerson3(benchmark::State& state)
{
   std::vector<Person3> persons( size );

   for( auto _ : state )
   {
      benchmark::DoNotOptimize(
         std::min_element( begin(persons), end(persons), []( auto const& p1, auto const& p2 ){
            return p1.year_of_birth < p2.year_of_birth;
         } )
      );
   }
}
#if BENCHMARK_PERSON3
BENCHMARK(determineOldestPerson3)->Iterations(iterations);
#endif


//---- Benchmark for Person4 ----------------------------------------------------------------------

static void determineOldestPerson4(benchmark::State& state)
{
   std::vector<Person4> persons( size );

   for( auto _ : state )
   {
      benchmark::DoNotOptimize(
         std::min_element( begin(persons), end(persons), []( auto const& p1, auto const& p2 ){
            return p1.year_of_birth < p2.year_of_birth;
         } )
      );
   }
}
#if BENCHMARK_PERSON4
BENCHMARK(determineOldestPerson4)->Iterations(iterations);
#endif


//---- Benchmark for Person5 ----------------------------------------------------------------------

static void determineOldestPerson5(benchmark::State& state)
{
   std::vector<Person5<Pimpl5>> persons( size );

   for( auto _ : state )
   {
      benchmark::DoNotOptimize(
         std::min_element( begin(persons), end(persons), []( auto const& p1, auto const& p2 ){
            return p1.pimpl.year_of_birth < p2.pimpl.year_of_birth;
         } )
      );
   }
}
#if BENCHMARK_PERSON5
BENCHMARK(determineOldestPerson5)->Iterations(iterations);
#endif


//---- Benchmark for Person6 ----------------------------------------------------------------------

static void determineOldestPerson6(benchmark::State& state)
{
   std::vector<Person6> persons( size );
   for( size_t i=0; i<size; ++i ) {
      persons[i].id = i;
   }

   for( auto _ : state )
   {
      benchmark::DoNotOptimize(
         std::distance( begin(Person6::years_of_birth)
                      , std::min_element( begin(Person6::years_of_birth), end(Person6::years_of_birth) ) )
      );
   }
}
#if BENCHMARK_PERSON6
BENCHMARK(determineOldestPerson6)->Iterations(iterations);
#endif

