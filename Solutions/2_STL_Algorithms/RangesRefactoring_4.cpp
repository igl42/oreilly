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


auto is_bigger()
{
   return []( Animal const& animal1, Animal const& animal2 )
   {
      return animal1.size > animal2.size;
   };
}

auto is_faster()
{
   return []( Animal const& animal1, Animal const& animal2 )
   {
      return animal1.speed > animal2.speed;
   };
}

auto is_heavier()
{
   return []( Animal const& animal1, Animal const& animal2 )
   {
      return animal1.weight > animal2.weight;
   };
}

auto fold_animal_by_speed()
{
   return []( double accu, Animal const& animal )
   {
      return accu + animal.speed;
   };
}


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
   /*
   std::vector<Animal> largest_animals{};

   for( auto const& book : books )
   {
      for( auto const& animal : book.second )
      {
         auto pos = begin(largest_animals);

         while( pos != end(largest_animals) && pos->size > animal.size )
            ++pos;

         largest_animals.insert( pos, animal );
      }
   }

   assert( largest_animals.size() >= 5U );

   bool size_and_speed_correlated{ true };
   {
      auto pos1{ begin(largest_animals) };
      for( auto pos2=pos1+1; pos2!=begin(largest_animals)+5; ++pos1, ++pos2 )
      {
         if( pos1->speed < pos2->speed ) {
            size_and_speed_correlated = false;
            break;
         }
      }
   }

   for( auto pos1=begin(largest_animals); pos1!=begin(largest_animals)+5; ++pos1 )
   {
      for( auto pos2=pos1+1; pos2!=begin(largest_animals)+5; ++pos2 )
      {
         if( pos1->speed < pos2->speed ) {
            auto tmp{ *pos1 };
            *pos1 = *pos2;
            *pos2 = tmp;
         }
      }
   }

   bool weight_and_speed_correlated{ true };
   {
      auto pos1{ begin(largest_animals) };
      for( auto pos2=pos1+1; pos2!=begin(largest_animals)+5; ++pos1, ++pos2 )
      {
         if( pos1->weight < pos2->weight ) {
            weight_and_speed_correlated = false;
            break;
         }
      }
   }

   auto const pos_median_speed = begin(largest_animals)+2;

   auto average_speed = 0.0;
   for( auto pos=begin(largest_animals); pos!=begin(largest_animals)+5; ++pos )
   {
      average_speed += pos->speed;
   }
   average_speed /= 5.0;

   for( auto const& animal : largest_animals ) {
      std::cout << animal << '\n';
   }

   std::cout << "\n"
                "Size and speed correlated   = " << size_and_speed_correlated << "\n"
                "Weight and speed correlated = " << weight_and_speed_correlated << "\n"
                "Median speed  = " << pos_median_speed->speed << "\n"
                "Average speed = " << average_speed << "\n"
                "\n";
   */


   // C++17 algorithms solution (declarative style)
   std::vector<Animal> largest_animals{};

   for( auto const& book : books )
   {
      std::copy( begin(book.second), end(book.second), std::back_inserter(largest_animals) );
   }

   assert( largest_animals.size() >= 5U );

   auto const begin_largest = begin(largest_animals);
   auto const end_largest = end(largest_animals);
   auto const begin_largest_five = begin_largest;
   auto const end_largest_five = begin_largest+5;

   std::partial_sort( begin_largest, end_largest_five, end_largest, is_bigger() );

   auto const size_and_speed_correlated =
      std::is_sorted( begin_largest_five, end_largest_five, is_faster() );

   std::sort( begin_largest_five, end_largest_five, is_faster() );

   auto const weight_and_speed_correlated =
      std::is_sorted( begin_largest_five, end_largest_five, is_heavier() );

   auto const pos_median_speed = begin(largest_animals)+2;

   auto const average_speed =
      std::accumulate( begin_largest_five, end_largest_five, double{}, fold_animal_by_speed() ) / 5.0;

   for( auto const& animal : largest_animals ) {
      std::cout << animal << '\n';
   }

   std::cout << "\n"
                "Size and speed correlated   = " << size_and_speed_correlated << "\n"
                "Weight and speed correlated = " << weight_and_speed_correlated << "\n"
                "Median speed  = " << pos_median_speed->speed << "\n"
                "Average speed = " << average_speed << "\n"
                "\n";


   // C++20 ranges solution (declarative style)
   /*
   auto animals = books
                | std::views::values
                | std::views::join
                | to<std::vector>();

   std::ranges::partial_sort( animals, begin(animals)+5, is_bigger() );

   auto largest_animals = animals | std::views::take(5);

   auto const size_and_speed_correlated =
      std::ranges::is_sorted( largest_animals, is_faster() );

   std::ranges::sort( largest_animals, is_faster() );

   auto const weight_and_speed_correlated =
      std::ranges::is_sorted( largest_animals, is_heavier() );

   auto const pos_median_speed = begin(largest_animals)+2;

   auto const average_speed =
      std::ranges::fold_left( largest_animals, double{}, fold_animal_by_speed() ) / largest_animals.size();

   for( auto const& animal : animals ) {
      std::cout << animal << '\n';
   }

   std::cout << "\n"
                "Size and speed correlated   = " << size_and_speed_correlated << "\n"
                "Weight and speed correlated = " << weight_and_speed_correlated << "\n"
                "Median speed  = " << pos_median_speed->speed << "\n"
                "Average speed = " << average_speed << "\n"
                "\n";
   */


   return EXIT_SUCCESS;
}
