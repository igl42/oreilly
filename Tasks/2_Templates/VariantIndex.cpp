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



// TODO: Implement the 'variant_index' class template to query the index of the given type
//       'T' within the given variant 'V'.
template< typename V, typename T >
struct variant_index;


int main()
{
   /*
   using Variant = std::variant<int,double,std::string>;

   static_assert( variant_index_v<Variant,int>         == 0UL );
   static_assert( variant_index_v<Variant,double>      == 1UL );
   static_assert( variant_index_v<Variant,std::string> == 2UL );
   static_assert( variant_index_v<Variant,float>       == std::variant_npos );
   */

   return EXIT_SUCCESS;
}
