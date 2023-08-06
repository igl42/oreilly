/**************************************************************************************************
*
* \file VariadicMax.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Extend the 'max()' function template for an arbitrary number of elements.
*
* Step 2: Use the 'max()' function template to determine the size of the largest type given to
*         the 'Variant' class template.
*
**************************************************************************************************/

#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <type_traits>


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
template< typename T, typename... Ts >
constexpr auto max( T const& a, Ts const&... args )
//   -> typename std::common_type<T,Ts...>::type    // Trailing return type necessary for C++11
{
   if constexpr( sizeof...(Ts) == 0U ) {
      return a;
   }
   else {
      auto const b = max( args... );
      return ( a < b ? b : a );
   }
}


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


// Application of the 'max()' function template to determine the largest given type
template< typename T, typename... Ts >
struct Variant
{
 public:
   // ...

   static constexpr size_t capacity  = max( sizeof(T), sizeof(Ts)... );
   static constexpr size_t alignment = max( alignof(T), alignof(Ts)... );

 private:
   alignas(alignment) std::array<std::byte,capacity> buffer_;
};


int main()
{
   std::cout << "\n"
                " max( 1, 5 )          = " << max( 1, 5 ) << "\n"
                " max( 3, 2 )          = " << max( 3, 2 ) << "\n"
                " max( 1.2, 2.3 )      = " << max( 1.2, 2.3 ) << "\n"
                " max( 1.2, -4 )       = " << max( 1.2, -4 ) << "\n"
                " max( 1, 2.8 )        = " << max( 1, 2.8 ) << "\n"
                " max( 1, 5, 4 )       = " << max( 1, 5, 4 ) << "\n"
                " max( 1, -1.3F, 2.3 ) = " << max( 1, -1.3F, 2.3 ) << "\n"
                "\n";


   Variant<int,double,std::string> v{};

   std::cout << "\n"
                " v.capacity  = " << v.capacity << "\n"
                " v.alignment = " << v.alignment << "\n"
                "\n";

   return EXIT_SUCCESS;
}
