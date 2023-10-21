/**************************************************************************************************
*
* \file PackIndexing.cpp
* \brief C++ Training - Variadic Template Programming Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'index_pack()' function, which receives a compile time index and a
*       parameter pack, and returns the indexed element of the parameter pack.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <type_traits>


//==== Auxiliary type 'S' ====
struct S
{
   S() { puts( "S()" ); }
   S( const S& ) { puts( "S(const S&)" ); }
   S( S&& ) { puts( "S(S&&)" ); }
   S& operator=( const S& ) { puts( "operator=(const S&)" ); return *this; }
   S& operator=( S&& ) { puts( "operator=(S&&)" ); return *this; };
   ~S() { puts( "~S()" ); }
};

bool operator<( const S& s1, const S& s2 ) noexcept
{
   return true;
}


//==== Implementation of the 'remove_rvalue_reference' type trait ====
template< typename T >
struct remove_rvalue_reference
{
   using type = T;
};

template< typename T >
struct remove_rvalue_reference<T&&>
{
   using type = T;
};

template< typename T >
using remove_rvalue_reference_t = typename remove_rvalue_reference<T>::type;


//==== Implementation of the 'index_pack()' function template ====
template< size_t I, typename T, typename... Ts >
decltype(auto) index_pack( T&& value, Ts&&... values )
{
   static_assert( I <= sizeof...(Ts), "Invalid parameter pack index" );

   if constexpr( I == 0 )
   {
      using result_t = decltype( std::forward<T>(value) );
      using return_t = std::remove_const_t< remove_rvalue_reference_t< result_t > >;
      return static_cast<return_t>( std::forward<T>(value) );
   }
   else
   {
      return index_pack<I-1UL>( std::forward<Ts>(values)... );
   }
}


int main()
{
   //==== Indexing an lvalue ====
   {
      int i = 2;
      decltype(auto) res = index_pack<2>( 0, 1, i, 3, 4 );
      using T = decltype(res);

      std::cout << "\n"
                << " typeid(res) = " << typeid(res).name() << "\n"
                << " std::is_lvalue_reference_v<T> = " << std::is_lvalue_reference_v<T> << "\n"
                << " std::is_rvalue_reference_v<T> = " << std::is_rvalue_reference_v<T> << "\n"
                << "\n";
   }

   //==== Indexing an rvalue ====
   {
      decltype(auto) res = index_pack<2>( 0, 1, 2, 3, 4 );
      using T = decltype(res);

      std::cout << "\n"
                << " typeid(res) = " << typeid(res).name() << "\n"
                << " std::is_lvalue_reference_v<T> = " << std::is_lvalue_reference_v<T> << "\n"
                << " std::is_rvalue_reference_v<T> = " << std::is_rvalue_reference_v<T> << "\n"
                << "\n";
   }

   return EXIT_SUCCESS;
}
