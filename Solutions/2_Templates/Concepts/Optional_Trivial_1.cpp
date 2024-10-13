/**************************************************************************************************
*
* \file Optional_Trivial_1.cpp
* \brief C++ Training - Advanced C++20 concept programming task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Use C++20 concepts to guarantee that a specialization of 'Optional' has the same
*       destruction characteristics as its contained type. For trivial types, the destructor
*       of 'Optional' should be trivial, for non-trivial types it should be non-trivial and
*       properly destroy the contained value.
*
**************************************************************************************************/

#include <cstdlib>
#include <memory>
#include <string>
#include <type_traits>


template< typename T >
class Optional
{
 public:
   constexpr Optional() = default;
   constexpr Optional( T const& value )
      : used_{ true }
   {
      std::construct_at( &value_, value );
   }

   // For trivial types (e.g. 'int', 'double', 'float*', ...) the destructor of 'Optional'
   // should also be trivial.
   ~Optional() = default;

   // For non-trivial types (e.g. 'std::string', ...) the following destructor should be
   // used, which makes 'Optional' non-trivial.
   ~Optional() requires( !std::is_trivially_destructible_v<T> )
   {
      if( used_ ) std::destroy_at( &value_ );
   }

 private:
   union { T value_; };
   bool used_{ false };
};


int main()
{
   static_assert(  std::is_trivially_destructible_v< Optional<int> > );
   static_assert( !std::is_trivially_destructible_v< Optional<std::string> > );

   return EXIT_SUCCESS;
}

