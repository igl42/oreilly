/**************************************************************************************************
*
* \file FoldExpressions.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
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

#include <cstdlib>
#include <iostream>
#include <type_traits>


struct S
{
   int i;
};

std::ostream& operator<<( std::ostream& os, S s )
{
   return os << s.i;
}

S operator+( S lhs, S rhs )
{
   std::cout << " Adding " << lhs << " and " << rhs << "\n";
   return S{ lhs.i + rhs.i };
}

S operator+( int lhs, S rhs )
{
   std::cout << " Adding " << lhs << " and " << rhs << "\n";
   return S{ lhs + rhs.i };
}

S operator+( S lhs, int rhs )
{
   std::cout << " Adding " << lhs << " and " << rhs << "\n";
   return S{ lhs.i + rhs };
}


/*
// The following 32 operators are foldable:
//  ==   !=   <    >    <=   >=   &&   ||   ,    .*  ->*  =
//  +    -    *    /    %    ^    &    |    <<   >>
//  +=   -=   *=   /=   %=   ^=   &=   |=   <<=  >>=

// The following 3 operators are not foldable:
//  .    ->    []
*/


template< typename... Ts >
auto sum( Ts const&... values )
{
   // Unary left fold:   ( ( ( v0 + v1 ) + v2 ) + ... )
   return ( ... + values );

   // Unary right fold:  ( v0 + ( ... + ( vY + vZ ) ) )
   //return ( values + ... );

   // Binary left fold:  ( ( ( ( 0 + v0 ) + v1 ) + v2 ) + ... )
   //return ( 0 + ... + values );

   // Binary right fold: ( v0 + ( ... + ( vY + ( vZ + 0 ) ) ) )
   //return ( values + ... + 0 );
}


/*
template< typename Fn, typename... Ts >
auto apply( Fn fn, Ts const&... values )
{
   static_assert( std::conjunction_v< std::is_invocable<Fn,Ts>... > );

   // Unary left fold:   ( ( ( fn(v0), fn(v1) ), ... ), fn(vZ) )
   return ( ..., fn(values) );

   // Unary right fold:  ( fn(v0), ( fn(v1), ( ..., fn(vZ) ) ) )
   //return ( fn(values), ... );
}

int square( int i ) { return i*i; }
*/


int main()
{
   auto const result = sum( S{1}, S{2}, S{3}, S{4} );
   std::cout << " Result = " << result << "\n";

   /*
   auto const result = apply( square, 1, 2, 3, 4 );
   std::cout << " Result = " << result << "\n";
   */

   return EXIT_SUCCESS;
}

