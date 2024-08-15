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
#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <ranges>

auto to_recipes()
{
   return []( Cookbook const& cookbook ) -> std::vector<Recipe> const&
   {
      return cookbook.recipes;
   };
}

auto needs_eggs()
{
   return []( Recipe const& recipe ){ return recipe.number_of_eggs > 0U; };
}

auto need_eggs( size_t number )
{
   return [number]( std::tuple<Recipe,Recipe> const& combi )
   {
      return ( get<0>(combi).number_of_eggs + get<1>(combi).number_of_eggs ) == 5U;
   };
}

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
   /*
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
   */


   // C++17 algorithm solution
   std::vector<Recipe> recipes_with_egg{};

   for( auto const& cookbook : cookbooks )
   {
      std::copy_if( begin(cookbook.recipes), end(cookbook.recipes)
                  , std::back_inserter(recipes_with_egg), needs_eggs() );
   }

   std::vector<std::tuple<Recipe,Recipe>> combinations{};

   cartesian_product( begin(recipes_with_egg), end(recipes_with_egg)
                    , begin(recipes_with_egg), end(recipes_with_egg)
                    , std::back_inserter(combinations) );

   combinations.erase(
      std::remove_if( begin(combinations), end(combinations), std::not_fn( need_eggs(5) ) ),
      std::end(combinations) );

   std::cout << "Reasonable combinations:\n";
   for( auto const& combi : combinations ) {
      std::cout << get<0>(combi).name << " and " << get<1>(combi).name << '\n';
   }


   // C++23 ranges solution (declarative style)
   /*
   auto const recipes_with_egg = cookbooks
                               | std::views::transform( to_recipes() )
                               | std::views::join
                               | std::views::filter( needs_eggs() )
                               | to<std::vector>();

   auto combinations =
        std::views::cartesian_product( recipes_with_egg, recipes_with_egg )
      | std::views::filter( need_eggs(5) );

   std::cout << "Reasonable combinations:\n";
   for( auto const& combi : combinations ) {
      std::cout << get<0>(combi).name << " and " << get<1>(combi).name << '\n';
   }
   */

   return EXIT_SUCCESS;
}
