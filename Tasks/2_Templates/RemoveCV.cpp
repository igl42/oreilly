/**************************************************************************************************
*
* \file RemoveCV.cpp
* \brief C++ Training - Moderate Type Trait Example
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'remove_cv' type trait in the following example. The type trait should
*       remove any top level cv qualifier from the given type.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <type_traits>


// TODO: Implement the 'remove_cv' type trait to remove cv qualifiers from the given type.


int main()
{
   /*
   using Type1  = int;
   using Type2  = int const;
   using Type3  = int volatile;
   using Type4  = int const volatile;
   using Type5  = int*;
   using Type6  = int* const;
   using Type7  = int* volatile;
   using Type8  = int* const volatile;
   using Type9  = int&;
   using Type10 = int const&;
   using Type11 = int volatile&;
   using Type12 = int const volatile&;

   static_assert( std::is_same< remove_cv_t<Type1>, int >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_cv_t<Type2>, int >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_cv_t<Type3>, int >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_cv_t<Type4>, int >::value, "Invalid type detected" );

   static_assert( std::is_same< remove_cv_t<Type5>, int* >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_cv_t<Type6>, int* >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_cv_t<Type7>, int* >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_cv_t<Type8>, int* >::value, "Invalid type detected" );

   static_assert( std::is_same< remove_cv_t<Type9 >, int&                >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_cv_t<Type10>, int const&          >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_cv_t<Type11>, int volatile&       >::value, "Invalid type detected" );
   static_assert( std::is_same< remove_cv_t<Type12>, int const volatile& >::value, "Invalid type detected" );
   */

   return EXIT_SUCCESS;
}
