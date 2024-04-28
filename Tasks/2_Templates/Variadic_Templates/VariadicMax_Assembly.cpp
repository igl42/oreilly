/**************************************************************************************************
*
* \file VariadicMax.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Copy-and-paste the following code into Compiler Explorer (i.e. 'godbolt.org').
*       Analyse the resulting assembly code of the given 'max()' implementations with
*       different compilers and a high optimization level (e.g. -O3 or /O2).
*
**************************************************************************************************/

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <type_traits>


//== Explicit max() implementation with 3 parameters ==============================================

template< typename T1, typename T2, typename T3 >
constexpr auto max( T1 const& a, T2 const& b, T3 const& c )
{
   return ( a < b
            ? ( b < c ? c : b )
            : ( a < c ? c : a ) );
}


//== Explicit max() implementation with 4 parameters ==============================================
/*
template< typename T1, typename T2, typename T3, typename T4 >
constexpr auto max( T1 const& a, T2 const& b, T3 const& c, T4 const& d )
{
   return ( a < b
            ? b < c
              ? c < d ? d : c
              : b < d ? d : b
            : a < c
              ? c < d ? d : c
              : a < d ? d : a );
}
*/


//== max() for 1 or more parameter ================================================================

// Solution 1: Tail recursion with function overloading (possible since C++11)
/*
template< typename T >
constexpr T const& max( T const& a )
{
   return a;
}

template< typename T, typename... Ts >
constexpr auto max( T const& a, Ts const&... args )
   -> typename std::common_type<T,Ts...>::type    // Trailing return type necessary for C++11
{
   auto const b = max( args... );
   return ( a < b ? b : a );
}
*/


// Solution 2: Tail recursion with 'if constexpr' (since C++17)
/*
template< typename T, typename... Ts >
constexpr auto max( T const& a, Ts const&... args )
{
   if constexpr( sizeof...(Ts) == 0U ) {
      return a;
   }
   else {
      auto const b = max( args... );
      return ( a < b ? b : a );
   }
}
*/


// Solution 3: Fold expressions
/*
template< typename T >
struct MaxHelper { T const& value; };

template< typename T >
MaxHelper(T) -> MaxHelper<T>;

template< typename T1, typename T2 >
constexpr auto operator+( MaxHelper<T1> a, MaxHelper<T2> b )
{
   return MaxHelper{ a.value < b.value ? b.value : a.value };
}

template< typename T, typename... Ts >
constexpr auto max( T const& a, Ts const&... args )
{
   return ( MaxHelper{a} + ... + MaxHelper{args} ).value;
}
*/


//== max() for 2 or more parameter ================================================================

// Solution 1: Tail recursion with function overloading (possible since C++11)
/*
// Definition of the 'max()' function template
template< typename T1, typename T2 >
constexpr auto max( T1 const& a, T2 const& b )
//   -> typename std::common_type<T1,T2>::type    // Trailing return type necessary for C++11
{
   return ( a < b ) ? b : a;
}

// 'max()' function template for an arbitrary number of elements
template< typename T1, typename... Ts >
constexpr auto max( T1 const& a, Ts const&... args )
//   -> typename std::common_type<T1,Ts...>::type    // Trailing return type necessary for C++11
{
   return max( a, max( args... ) );
}
*/


// Solution 2: Tail recursion with 'if constexpr' (since C++17)
/*
template< typename T1, typename T2, typename... Ts >
constexpr auto max( T1 const& a, T2 const& b, Ts const&... args )
{
   const auto result = ( a < b ) ? b : a;

   if constexpr( sizeof...(Ts) > 0U ) {
      return max( result, args... );
   }
   else {
      return result;
   }
}
*/


// Solution 3: Fold expressions
/*
template< typename T >
struct MaxHelper { T const& value; };

template< typename T >
MaxHelper(T) -> MaxHelper<T>;

template< typename T1, typename T2 >
constexpr auto operator+( MaxHelper<T1> a, MaxHelper<T2> b )
{
   return MaxHelper{ a.value < b.value ? b.value : a.value };
}

template< typename T1, typename T2, typename... Ts >
constexpr auto max( T1 const& a, T2 const& b, Ts const&... args )
{
   return ( MaxHelper{a} + ( MaxHelper{b} + ... + MaxHelper{args} ) ).value;
}
*/


int main()
{
   int a;
   int b;
   int c;

   std::cin >> a >> b >> c;

   std::cout << max( a, b, c );

   return EXIT_SUCCESS;
}
