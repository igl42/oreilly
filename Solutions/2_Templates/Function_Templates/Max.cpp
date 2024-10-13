/**************************************************************************************************
*
* \file Max.cpp
* \brief C++ Training - Function Template C++ Example
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Write a 'max()' function template that takes a single template parameter for its two
*         function parameters.
*
* Step 2: Write a 'max()' function template that takes two template parameters instead of one
*         (one for each function parameter).
*
* Step 3: Overload the 'max()' function template for integers.
*
* Step 4: Specialize the 'max()' function template(s) for integers.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <type_traits>


// Step 1: Definition of the 'max()' function template with a single template argument
//         Note that this 'max()' can only be called with two arguments of the same type.
//         Using arguments of different types results in a compilation error.
//         When 'max()' is called with two arguments of the same type, this overload has
//         preference to the second overload.
template< typename T >
inline T max( T const& a, T const& b )
{
   return ( a < b ? b : a );
}


// Step 2: Definition of the 'max()' function template with two template arguments
//         Note that this overload uses return type deduction, i.e. lets the compiler
//         determine the return type via 'auto' (available since C++14).
template< typename T1, typename T2 >
inline auto max( T1 const& a, T2 const& b )
   // -> typename std::common_type<T,Ts...>::type    // Trailing return type necessary for C++11
{
   return ( a < b ? b : a );
}


// Step 3: Overload of the 'max()' function
//         Note that this (non-template) overload has preference over the two function
//         templates when called with two integers.
inline int max( int a, int b )
{
   return ( a < b ? b : a );
}


// Step 4: Specialization of the 'max()' function template with a single template argument
//         Note that the specialization exactly matches the base template: 'const&'
//         parameters and an 'int' return type.
//         This specialization can only be called if the first function template is selected
//         and if 'T' is deduced to be 'int'.
template<>
inline int max<int>( int const& a, int const& b )
{
   return ( a < b ? b : a );
}


// Step 4: Specialization of the 'max()' function template with two template arguments
//         Note that the specialization exactly matches the base template: 'const&'
//         parameters and an 'auto' return type.
//         This specialization can only be called if the second function template is
//         selected and if both 'T1' and 'T2' are deduced to be 'int'.
template<>
inline auto max<int,int>( int const& a, int const& b )
{
   return ( a < b ? b : a );
}


int main()
{
   std::cout << "\n"
                " max( 1, 5 )     = " << max( 1, 5 ) << "\n"
                " max( 3, 2 )     = " << max( 3, 2 ) << "\n"
                " max( 1.2, 2.3 ) = " << max( 1.2, 2.3 ) << "\n"
                " max( 1.2, -4 )  = " << max( 1.2, -4 ) << "\n"
                " max( 1, 2.8 )   = " << max( 1, 2.8 ) << "\n"
                "\n";

   return EXIT_SUCCESS;
}
