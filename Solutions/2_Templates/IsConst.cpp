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

#include <complex>
#include <cstdlib>
#include <iostream>
#include <type_traits>


template< typename T >
struct is_const
   : public std::false_type
{};

template< typename T >
struct is_const<T const>
   : public std::true_type
{};

template< typename T >
constexpr bool is_const_v = is_const<T>::value;


int main()
{
   using Type1 = int;
   using Type2 = int const;
   using Type5 = std::complex<float>;
   using Type6 = std::complex<float> const;
   using Type3 = int*;
   using Type4 = int* const;

   constexpr bool result1 = is_const_v<Type1>;  // Should result in 'false'
   constexpr bool result2 = is_const_v<Type2>;  // Should result in 'true'
   constexpr bool result3 = is_const_v<Type3>;  // Should result in 'false'
   constexpr bool result4 = is_const_v<Type4>;  // Should result in 'true'
   constexpr bool result5 = is_const_v<Type5>;  // Should result in 'false'
   constexpr bool result6 = is_const_v<Type6>;  // Should result in 'true'

   std::cout << "\n"
             << " result1 = " << result1 << "\n"
             << " result2 = " << result2 << "\n"
             << " result3 = " << result3 << "\n"
             << " result4 = " << result4 << "\n"
             << " result5 = " << result5 << "\n"
             << " result6 = " << result6 << "\n"
             << "\n";

   return EXIT_SUCCESS;
}

