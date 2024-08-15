/**************************************************************************************************
*
* \file RangesRefactoring_3.cpp
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


//---- <Country.h> --------------------------------------------------------------------------------

#include <iomanip>
#include <ostream>
#include <string>

struct Country
{
   std::string name{};     // Name of the country
   std::string capital{};  // Name of the capital
   unsigned int area{};    // Area in square kilometer
   float residents{};      // Number of residents in millions

   friend std::ostream& operator<<( std::ostream& os, Country const& country )
   {
      os << std::setw(13) << std::left << country.name
         << std::setw(13) << std::left << country.capital
         << std::setw(7)  << std::right << country.area
         << std::setw(6)  << std::right << country.residents;
      return os;
   }
};


//---- <Continent.h> ------------------------------------------------------------------------------

//#include <Country.h>
#include <string>
#include <vector>

struct Continent
{
   std::string name{};                // Name of the continent
   std::vector<Country> countries{};  // Countries of the continent
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Continent.h>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <ranges>

int main()
{
   std::vector<Continent> continents
      { Continent{ "South America",
         { Country{ "Brasil", "Brasilia", 8'515'877U, 208.4F }
         , Country{ "Argentina", "Buenos Aires", 2'780'400U, 44.7F }
         , Country{ "Peru", "Lima", 1'285'216U, 31.2F }
         , Country{ "Colombia", "Bogota", 1'138'910U, 48.3F }
         , Country{ "Bolivia", "Sucre", 1'098'581U, 11.1F } } }
      , Continent{ "Europe",
         { Country{ "France", "Paris", 543'965U, 67.0F }
         , Country{ "Spain", "Madrid", 505'970U, 47.1F }
         , Country{ "Sweden", "Stockholm", 447'420U, 10.3F }
         , Country{ "Norway", "Oslo", 385'199U, 5.4F }
         , Country{ "Germany", "Berlin", 357'376U, 83.2F } } }
      , Continent{ "Africa",
         { Country{ "Algeria", "Algiers", 2'381'741U, 43.0F }
         , Country{ "DR Kongo", "Kinshasa", 2'344'858U, 85.3F }
         , Country{ "Mali", "Bamako", 1'240'192U, 19.4F }
         , Country{ "Libya", "Tripoli", 1'775'500U, 6.8F }
         , Country{ "South Africa", "Pretoria", 1'221'037U, 57.7F } } }
      , Continent{ "North America",
         { Country{ "Canada", "Ottawa", 9'984'670U, 37.9F }
         , Country{ "USA", "Washington", 9'826'675U, 328.0F }
         , Country{ "Mexico", "Mexico City", 1'972'550U, 124.6F } } }
      , Continent{ "Asia",
         { Country{ "China", "Beijing", 9'596'961U, 1400.0F }
         , Country{ "India", "New Delhi", 3'287'469U, 1380.0F }
         , Country{ "Kazakhstan", "Astana", 2'724'900U, 18.6F }
         , Country{ "Saudi Arabia", "Riyadh", 2'149'690U, 33.9F }
         , Country{ "Indonesia", "Jakarta", 1'904'569U, 264.2F } } }
      };


   // Manual solution (imperative style)
   std::vector<Country> tmp{};

   for( auto const& continent : continents ) {
      for( auto const& country : continent.countries )
      {
         auto pos = begin(tmp);

         while( pos != end(tmp) && pos->area > country.area )
            ++pos;

         tmp.insert( pos, country );
      }
   }

   assert( tmp.size() >= 5U );

   std::vector<Country> countries{ begin(tmp), begin(tmp)+5 };

   for( size_t i=0U; i<4U; ++i )
   {
      auto& country1 = countries[i];
      for( size_t j=i+1; j<5U; ++j ) {
         auto& country2 = countries[j];
         if( country1.residents < country2.residents ) {
            Country tmp{ country1 };
            country1 = country2;
            country2 = tmp;
         }
      }
   }

   for( auto const& country : countries ) {
      std::cout << country << '\n';
   }


   // C++20 ranges solution (declarative style)
   // TODO: Refactor the above functionality from an imperative to a declarative style
   //       by means of C++20 ranges.


   return EXIT_SUCCESS;
}
