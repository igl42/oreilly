/**************************************************************************************************
*
* \file IsConst.cpp
* \brief C++ Training - Easy Type Trait Example
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'is_const' type trait in the following example. The type trait should
*       determine if the given type is a const qualifed type. In case the given type is a const
*       qualified type, the type trait should inherit from 'std::true_type', else it should
*       derive from 'std::false_type'.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <type_traits>


// TODO: Implement the 'is_const' type trait to determine whether a given type is a const qualified type.


int main()
{
   /*
   using Type1 = int;
   using Type2 = int const;
   using Type3 = int*;
   using Type4 = int* const;

   constexpr bool result1 = is_const<Type1>::value;  // Should result in 'false'
   constexpr bool result2 = is_const<Type2>::value;  // Should result in 'true'
   constexpr bool result3 = is_const<Type3>::value;  // Should result in 'false'
   constexpr bool result4 = is_const<Type4>::value;  // Should result in 'true'

   std::cout << "\n"
             << " result1 = " << result1 << "\n"
             << " result2 = " << result2 << "\n"
             << " result3 = " << result3 << "\n"
             << " result4 = " << result4 << "\n"
             << "\n";
   */

   return EXIT_SUCCESS;
}

