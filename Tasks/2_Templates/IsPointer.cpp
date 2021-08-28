/**************************************************************************************************
*
* \file IsPointer.cpp
* \brief C++ Training - Easy Type Trait Example
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'is_pointer' type trait in the following example. The type trait should
*       determine if the given type is a pointer type. In case the given type is a pointer type,
*       the type trait should inherit from 'std::true_type', else it should derive from
*       'std::false_type'.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <type_traits>


// TODO: Implement the 'is_pointer' type trait to determine whether a given type is a pointer type.


int main()
{
   /*
   using Type1 = int;
   using Type2 = int const;
   using Type3 = int volatile;
   using Type4 = int const volatile;
   using Type5 = int*;
   using Type6 = int* const;
   using Type7 = int* volatile;
   using Type8 = int* const volatile;

   static_assert( !is_pointer_v<Type1> );
   static_assert( !is_pointer_v<Type2> );
   static_assert( !is_pointer_v<Type3> );
   static_assert( !is_pointer_v<Type4> );
   static_assert(  is_pointer_v<Type5> );
   static_assert(  is_pointer_v<Type6> );
   static_assert(  is_pointer_v<Type7> );
   static_assert(  is_pointer_v<Type8> );
   */

   return EXIT_SUCCESS;
}
