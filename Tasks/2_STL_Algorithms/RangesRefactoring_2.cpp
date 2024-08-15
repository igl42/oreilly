/**************************************************************************************************
*
* \file RangesRefactoring_2.cpp
* \brief C++ Training - Refactoring Task from Imperative to Declarative Code
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Understand the code of the 'main()' function: what does the final output print?
*
* Step 2: Refactor the 'main()' function from an imperative to a declarative style by means
*         of C++20/23 ranges.
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


//---- <Recipe.h> --------------------------------------------------------------------------------

#include <ostream>
#include <string>

struct Recipe
{
   std::string name{};
   unsigned int number_of_eggs{};

   friend std::ostream& operator<<( std::ostream& os, Recipe const& recipe )
   {
      return os << recipe.name << ", Eggs: " << recipe.number_of_eggs;
   }
};


//---- <Cookbook.h> ------------------------------------------------------------------------------

//#include <Recipe.h>
#include <string>
#include <vector>

struct Cookbook
{
   std::string name{};
   std::vector<Recipe> recipes;

   friend std::ostream& operator<<( std::ostream& os, Cookbook const& cookbook )
   {
      os << cookbook.name << '\n';
      for( const auto& recipe : cookbook.recipes ) {
         os << recipe << '\n';
      }
      return os;
   }
};


//---- <CartesianProduct.h> -----------------------------------------------------------------------

#include <tuple>
#include <utility>

struct MakeTuple
{
   template< typename... Args >
   auto operator()( Args&&... args ) const
   {
      return std::make_tuple( std::forward<Args>(args)... );
   };
};

template< typename ForwardIt_1, typename Sentinel_1
        , typename ForwardIt_2, typename Sentinel_2
        , typename ForwardIt_3
        , typename BinaryStrategy = MakeTuple >
void cartesian_product( ForwardIt_1 first_1, Sentinel_1 last_1
                      , ForwardIt_2 first_2, Sentinel_2 last_2
                      , ForwardIt_3 result
                      , BinaryStrategy op = {} )
{
   for( ; first_1!=last_1; ++first_1 ) {
      for( auto it_2=first_2; it_2!=last_2; ++it_2 ) {
         *result = op( *first_1, *it_2 );
         ++result;
      }
   }
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Cookbook.h>
#include <cstdlib>
#include <iostream>
#include <ranges>

int main()
{
   std::vector<Cookbook> cookbooks
      { Cookbook{ "European Delicacies",
         { Recipe{ "Nusskuchen", 4U }
         , Recipe{ "Kaiserschmarrn", 4U }
         , Recipe{ "Potato Fritter", 3U }
         , Recipe{ "Quiche Lorraine", 1U } } }
      , Cookbook{ "Enjoying the World",
         { Recipe{ "Pancakes", 2U }
         , Recipe{ "Brownies", 3U }
         , Recipe{ "Omlette", 4U } } }
      , Cookbook{ "Italian Cuisine",
         { Recipe{ "Pizza", 0U }
         , Recipe{ "Spaghetti Carbonara", 3U }
         , Recipe{ "Spaghetti Bolognese", 0U } } }
      , Cookbook{ "Asian Food",
         { Recipe{ "Pad Thai", 2U }
         , Recipe{ "Chicken Tikka Masala", 0U } } }
      };


   // Manual solution (imperative style)
   std::vector<Recipe> recipes_with_egg{};

   for( auto const& cookbook : cookbooks ) {
      for( auto const& recipe : cookbook.recipes ) {
         if( recipe.number_of_eggs > 0U ) {
            recipes_with_egg.push_back( recipe );
         }
      }
   }

   std::vector<std::tuple<Recipe,Recipe>> combinations{};

   for( auto const& recipe1 : recipes_with_egg ) {
      for( auto const& recipe2 : recipes_with_egg ) {
         if( ( recipe1.number_of_eggs + recipe2.number_of_eggs ) == 5U ) {
            combinations.push_back( std::make_tuple( recipe1, recipe2 ) );
         }
      }
   }

   std::cout << "Reasonable combinations:\n";
   for( auto const& combi : combinations ) {
      std::cout << get<0>(combi).name << " and " << get<1>(combi).name << '\n';
   }


   // C++23 ranges solution (declarative style)
   // TODO: Refactor the above functionality from an imperative to a declarative style
   //       by means of C++20/23 ranges.


   return EXIT_SUCCESS;
}
