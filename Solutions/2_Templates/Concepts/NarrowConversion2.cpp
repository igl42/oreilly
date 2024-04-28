/**************************************************************************************************
*
* \file NarrowConversion2.cpp
* \brief C++ Training - Advanced C++20 concepts programming task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Constraint the 'StrongType' constructor to prevent narrowing conversions by means of
*       C++20 concepts.
*
**************************************************************************************************/

#include <cstdlib>
#include <concepts>
#include <iostream>
#include <utility>


//---- <NoNarrowingConversion.h> ------------------------------------------------------------------

template< typename From, typename To >
concept no_narrowing_conversion_to =
   std::convertible_to<From,To> &&
   requires ( From&& from ) {
      To{ std::forward<From>(from) };
   };


//---- <StrongType.h> -----------------------------------------------------------------------------

template< typename T, typename Tag >
class StrongType
{
 public:
   using value_type = T;

   template< typename U >
      requires no_narrowing_conversion_to<U,T>
   explicit constexpr StrongType( U&& value ) : value_( std::forward<U>(value) ) {}

   constexpr T&       get()       noexcept { return value_; }
   constexpr const T& get() const noexcept { return value_; }

   void swap( StrongType& other ) {
      using std::swap;
      swap( value_, other.value_ );
   }

 private:
   T value_;
};

template< typename T, typename Tag >
std::ostream& operator<<( std::ostream& os, const StrongType<T,Tag>& st )
{
   st.print( os );
   return os;
}

template< typename T, typename Tag >
void swap( StrongType<T,Tag>& a, StrongType<T,Tag>& b )
{
   a.swap( b );
}


//---- <Meter.h> ----------------------------------------------------------------------------------

template< typename T >
using Meter = StrongType<T,struct MeterTag>;

template< typename T >
Meter<T> foo( Meter<T> meter1, Meter<T> meter2 )
{
   return meter1 + meter2;
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // OK: no conversion
   const auto m1 = Meter<long>{ 100L };

   // OK: conversion from 'int' to 'long'
   const auto m2 = Meter<long>{ 100 };

   // Compilation error: narrowing conversion from double to long
   //const auto m3 = Meter<long>{ 100.0 };

   return EXIT_SUCCESS;
}

