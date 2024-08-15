/**************************************************************************************************
*
* \file RangesRefactoring_4.cpp
* \brief C++ Training - Refactoring Task from Imperative to Declarative Code
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Understand the code of the 'main()' function: what does the final output print?
*
* Step 2: Improve readability by choosing better names for the variables.
*
* Step 3: Refactor the 'main()' function from an imperative to a declarative style by means
*         of C++20 ranges.
*
**************************************************************************************************/


//---- <ranges> -----------------------------------------------------------------------------------

#include <concepts>
#include <ranges>
#include <type_traits>

// Simplified implementation of C++23 'std::ranges::to<>()'
template< template<typename...> class C >
struct to_range
{};

template< template<typename...> class C, std::ranges::input_range R >
constexpr auto to( R&& range )
{
   using T = std::ranges::range_value_t<R>;
   static_assert( !std::is_reference_v<T> );
   return C<T>( std::ranges::begin(range), std::ranges::end(range) );
}

template< template<typename...> class C >
constexpr auto to()
{
   return to_range<C>{};
}

template< std::ranges::input_range R, template<typename...> class C >
auto operator|( R&& range, to_range<C> )
{
   return to<C>(range);
}


//---- <Animal.h> ---------------------------------------------------------------------------------

#include <iomanip>
#include <ostream>
#include <string>

struct Animal
{
   std::string name;
   double size{};    // size in cm
   double weight{};  // weight in kg
   double speed{};   // speed in km/h

   friend std::ostream& operator<<( std::ostream& os, Animal const& animal )
   {
      os << std::setw(24) << std::left << animal.name
         << ": size=" << std::setw(5) << std::right << animal.size
         << ", weight=" << std::setw(7)  << std::right << animal.weight
         << ", speed=" << std::setw(4)  << std::right << animal.speed;
      return os;
   }
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

#include <algorithm>
#include <cassert>
#include <iostream>
#include <map>
#include <numeric>
#include <ranges>
#include <string>
#include <vector>

using namespace std::string_literals;


int main()
{
   std::map<std::string,std::vector<Animal>> books
      { std::make_pair( "Fantastic Animals and Where to Find Them"s,
         std::vector{ Animal{ "Lion", 250.0, 270.0, 80.0 }
                    , Animal{ "King Cobra", 550.0, 20.0, 18.0 }
                    , Animal{ "Housefly", 0.8, 0.0001, 10.0 }
                    , Animal{ "Giant Kangaroo", 140.0, 55.0, 80.0 }
                    , Animal{ "Mosquito", 0.6, 0.000002, 2.5 }
                    , Animal{ "Polar Bear", 280.0, 1000.0, 40.0 } } )
      , std::make_pair( "Animals Around the World"s,
         std::vector{ Animal{ "Dragonfly", 8.0, 0.001, 50.0 }
                    , Animal{ "Komodo Dragon", 304.0, 91.0, 20.0 }
                    , Animal{ "Great Anaconda", 900.0, 250.0, 27.0 }
                    , Animal{ "Red Garden Ant", 0.6, 0.00001, 0.9 } } )
      , std::make_pair( "TODO",
         std::vector{ Animal{ "Gorilla", 180.0, 220.0, 35.0 }
                    /*, Animal{ "Nile Crocodile", 650.0, 1000.0, 0.5 }*/
                    , Animal{ "Bee", 1.8, 0.0003, 28.0 }
                    , Animal{ "Galapagos Giant Tortoise", 180.0, 300.0, 0.5 }
                    , Animal{ "African Elephant", 750.0, 6000.0, 40.0 } } )
      };


   // Manual solution (imperative style)

   std::vector<Animal> animals{};

   for( auto const& book : books )
   {
      for( auto const& animal : book.second )
      {
         auto pos = begin(animals);

         while( pos != end(animals) && pos->size > animal.size )
            ++pos;

         animals.insert( pos, animal );
      }
   }

   assert( animals.size() >= 5U );

   bool result1{ true };
   {
      auto pos1{ begin(animals) };
      for( auto pos2=pos1+1; pos2!=begin(animals)+5; ++pos1, ++pos2 )
      {
         if( pos1->speed < pos2->speed ) {
            result1 = false;
            break;
         }
      }
   }

   for( auto pos1=begin(animals); pos1!=begin(animals)+5; ++pos1 )
   {
      for( auto pos2=pos1+1; pos2!=begin(animals)+5; ++pos2 )
      {
         if( pos1->speed < pos2->speed ) {
            auto tmp{ *pos1 };
            *pos1 = *pos2;
            *pos2 = tmp;
         }
      }
   }

   bool result2{ true };
   {
      auto pos1{ begin(animals) };
      for( auto pos2=pos1+1; pos2!=begin(animals)+5; ++pos1, ++pos2 )
      {
         if( pos1->weight < pos2->weight ) {
            result2 = false;
            break;
         }
      }
   }

   auto const result3 = begin(animals)+2;

   auto result4 = 0.0;
   for( auto pos=begin(animals); pos!=begin(animals)+5; ++pos )
   {
      result4 += pos->speed;
   }
   result4 /= 5.0;

   for( auto const& animal : animals ) {
      std::cout << animal << '\n';
   }

   std::cout << "\n"
                "Size and speed correlated   = " << result1 << "\n"
                "Weight and speed correlated = " << result2 << "\n"
                "Median speed  = " << result3->speed << "\n"
                "Average speed = " << result4 << "\n"
                "\n";


   // C++20 ranges solution (declarative style)
   // TODO: Refactor the above functionality from an imperative to a declarative style
   //       by means of C++20 ranges.


   return EXIT_SUCCESS;
}
