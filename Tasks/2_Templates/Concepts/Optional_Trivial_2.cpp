/**************************************************************************************************
*
* \file Optional_Trivial_2.cpp
* \brief C++ Training - std::optional Performance Analysis
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Copy-and-paste the following code into 'godbolt.org'. Compare the generated assembly
*       code for the two 'f()' functions. Which of the two 'Optional' implementations is faster?
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <type_traits>


//---- <TrivialOptional.h> ------------------------------------------------------------------------

template< typename T >
class TrivialOptional
{
 public:
   constexpr TrivialOptional() = default;
   constexpr TrivialOptional( T const& value )
      : used_{ true }
   {
      std::construct_at( &value_, value );
   }

   ~TrivialOptional() = default;

   constexpr const T& value() const { return value_; }

   // ... many more member functions

 private:
   union { T value_; };
   bool used_{ false };
};

void f( TrivialOptional<int> o )
{
   std::cout << o.value();
}


//---- <NonTrivialOptional.h> ---------------------------------------------------------------------

template< typename T >
class NonTrivialOptional
{
 public:
   constexpr NonTrivialOptional() = default;
   constexpr NonTrivialOptional( T const& value )
      : used_{ true }
   {
      std::construct_at( &value_, value );
   }

   ~NonTrivialOptional()
   {
      if( used_ ) std::destroy_at( &value_ );
   }

   constexpr const T& value() const { return value_; }

   // ... many more member functions

 private:
   union { T value_; };
   bool used_{ false };
};

void f( NonTrivialOptional<int> o )
{
   std::cout << o.value();
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   static_assert(  std::is_trivially_destructible_v< TrivialOptional<int> > );
   static_assert( !std::is_trivially_destructible_v< NonTrivialOptional<int> > );

   f( TrivialOptional<int>{ 42 } );
   f( NonTrivialOptional<int>{ 42 } );

   return EXIT_SUCCESS;
}

