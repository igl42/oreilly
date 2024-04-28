/**************************************************************************************************
*
* \file PrintTuple.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Write an output operator for a tuple of variadic size and content.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>

using namespace std::string_literals;


//---- <PrintTuple.h> -----------------------------------------------------------------------------

// C++11 solution based on tail recursion
/*
template< typename... Args, size_t N >
void print_tuple( std::ostream& os, std::tuple<Args...> const& tuple
                , std::integral_constant<size_t,N>, std::integral_constant<size_t,N> )
{}

template< typename... Args, size_t I, size_t N >
void print_tuple( std::ostream& os, std::tuple<Args...> const& tuple
                , std::integral_constant<size_t,I>, std::integral_constant<size_t,N> )
{
   static_assert( I < N );

   if( I > 0U ) os << ',';

   os << std::get<I>(tuple);

   print_tuple( os, tuple
              , std::integral_constant<size_t,I+1U>{}
              , std::integral_constant<size_t,N>{} );
}

template< typename... Args >
std::ostream& operator<<( std::ostream& os, std::tuple<Args...> const& tuple )
{
   os << '(';
   print_tuple( os, tuple
              , std::integral_constant<size_t,0U>{}
              , std::integral_constant<size_t,sizeof...(Args)>{} );
   os << ')';
   return os;
}
*/


// C++17 solution based on if constexpr
template< typename... Args, size_t I, size_t N >
void print_tuple( std::ostream& os, std::tuple<Args...> const& tuple
                , std::integral_constant<size_t,I>, std::integral_constant<size_t,N> )
{
   static_assert( I <= N );

   if constexpr( I < N )
   {
      if( I > 0U ) os << ',';

      os << std::get<I>(tuple);

      print_tuple( os, tuple
                 , std::integral_constant<size_t,I+1U>{}
                 , std::integral_constant<size_t,N>{} );
   }
}

template< typename... Args >
std::ostream& operator<<( std::ostream& os, std::tuple<Args...> const& tuple )
{
   os << '(';
   print_tuple( os, tuple
              , std::integral_constant<size_t,0U>{}
              , std::integral_constant<size_t,sizeof...(Args)>{} );
   os << ')';
   return os;
}


// C++17 solution using a fold expression based on the comma operator
/*
template< class Tuple, std::size_t... Is >
void print_tuple( std::ostream& os, const Tuple& t, std::index_sequence<Is...> )
{
   os << '(';

   // C++17 fold expression based on the comma operator
   ( ( os << ( Is == 0 ?  "" : "," ) << std::get<Is>(t) ), ... );

   os << ')';
}

template< typename... Args >
std::ostream& operator<<( std::ostream& os, std::tuple<Args...> const& tuple )
{
   print_tuple( os, tuple, std::make_index_sequence<sizeof...(Args)>{} );
   return os;
}
*/


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // std::tuple<int,int,int>
   {
      std::tuple t = std::make_tuple( 1, 2, 3 );
      std::cout << t << '\n';
   }

   // std::tuple<int,double,std::string>
   {
      std::tuple t = std::make_tuple( 42, 3.14, "C++Training"s );
      std::cout << t << '\n';
   }

   return EXIT_SUCCESS;
}
