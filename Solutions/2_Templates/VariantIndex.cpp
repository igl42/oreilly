/**************************************************************************************************
*
* \file VariantIndex.cpp
* \brief C++ Training - Programming example for variadic templates and std::variant
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Write the 'variant_index' class template to evaluate the index of an alternative within
*       a given variant 'V'. In case the given type 'T' is found in the list of alternatives,
*       'variant_index' should return the index. Otherwise 'variant_index' should return
*       'std::variant_npos'.
*
**************************************************************************************************/

#include <cstdlib>
#include <string>
#include <type_traits>
#include <variant>


template< typename T, typename... Ts >
constexpr size_t variant_index_helper( const T*, const T*, const Ts*... )
{
   return 0UL;
}

template< typename T, typename U >
constexpr size_t variant_index_helper( const T*, const U* )
{
   return 1UL;
}

template< typename T, typename U, typename... Ts >
constexpr size_t variant_index_helper( const T* t, const U*, const Ts*... ts )
{
   return 1UL + variant_index_helper( t, ts... );
}


template< typename V, typename T >
struct variant_index;

template< typename... Ts, typename T >
struct variant_index< std::variant<Ts...>, T >
{
 private:
   static constexpr size_t size = std::variant_size_v< std::variant<Ts...> >;
   static constexpr size_t index =
      variant_index_helper( static_cast<T*>(nullptr), static_cast<Ts*>(nullptr)... );

   static_assert( index <= size, "Invalid index evaluation" );

 public:
   static constexpr size_t value = ( index < size ? index : std::variant_npos );
};

template< typename V, typename T >
constexpr size_t variant_index_v = variant_index<V,T>::value;


int main()
{
   using Variant = std::variant<int,double,std::string>;

   static_assert( variant_index_v<Variant,int>         == 0UL );
   static_assert( variant_index_v<Variant,double>      == 1UL );
   static_assert( variant_index_v<Variant,std::string> == 2UL );
   static_assert( variant_index_v<Variant,float>       == std::variant_npos );

   return EXIT_SUCCESS;
}
