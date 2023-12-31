/**************************************************************************************************
*
* \file Any_2.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement a simplified std::any to demonstrate the type erasure design pattern. Use
*       the void*-based approach.
*
**************************************************************************************************/

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <typeinfo>
#include <vector>


//---- <Any.h> ------------------------------------------------------------------------------------

struct bad_any_cast
   : public std::bad_cast
{};


class Any
{
 public:
   template< typename T >
   Any( T const& t )
      : cast_{ []( void const* raw, std::type_info const& info ) -> void const*
               {
                  if( info != typeid(T) ) {
                     throw bad_any_cast{};
                  }
                  return raw;
               } }
      , clone_{ []( void const* raw ) -> void const*
                {
                   return new T( *static_cast<T const*>(raw) );
                } }
      , pimpl_{ new T( t )
              , []( void const* raw )
                {
                   delete static_cast<T const*>(raw);
                } }
   {}

   Any( Any const& other )
      : cast_ ( other.cast_ )
      , clone_( other.clone_ )
      , pimpl_( clone_( other.pimpl_.get() ), other.pimpl_.get_deleter() )
   {}

   Any& operator=( Any const& other )
   {
      Any tmp( other );
      swap( tmp );
      return *this;
   }

   ~Any() = default;
   Any( Any&& ) = default;
   Any& operator=( Any&& ) = default;

   void swap( Any& a )
   {
      std::swap( cast_, a.cast_ );
      std::swap( clone_, a.clone_ );
      std::swap( pimpl_, a.pimpl_ );
   }

 private:
   using CastOperation = void const*(void const*, std::type_info const&);
   using CloneOperation = void const*(void const*);  // Prototype design pattern
   using DestroyOperation = void(void const*);

   CastOperation* cast_{ nullptr };
   CloneOperation* clone_{ nullptr };
   std::unique_ptr<void const,DestroyOperation*> pimpl_;  // Bridge design pattern / pimpl idiom

   template< typename T >
   friend T any_cast( Any const& any );
};

template< typename T >
T any_cast( Any const& any )
{
   return *static_cast<T const*>( any.cast_( any.pimpl_.get(), typeid(T) ) );
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // unsigned int
   {
      using T = unsigned int;
      Any any( 1U );
      any = 42U;
      T const ui = any_cast<T>( any );
      std::cout << "\n ui  = " << ui << "\n";
   }

   // std::string
   {
      using T = std::string;
      Any any( std::string{ "Demonstration for the any class" } );
      T const s = any_cast<T>( any );
      std::cout << "\n s   = " << std::quoted(s) << "\n";
   }

   // std::vector
   {
      using T = std::vector<int>;
      Any any( T{ 1, 2, 3, 4 } );
      T const vec = any_cast<T>( any );
      std::cout << "\n vec = (" << vec[0] << "," << vec[1] << "," << vec[2] << "," << vec[3] << ")\n";
   }

   // OveralignedArray
   {
      struct OveralignedArray
      {
         alignas(128) int array[3];
      };

      using T = OveralignedArray;
      Any any( T{ 1, 2, 3 } );
      T const oa = any_cast<T>( any );
      std::cout << "\n oa  = (" << oa.array[0] << "," << oa.array[1] << "," << oa.array[2] << ")\n";
   }

   // unsigned int -> std::string
   {
      using T = std::string;
      Any any( 1U );
      any = std::string{ "Replacement for the unsigned int 1U" };
      T const s = any_cast<T>( any );
      std::cout << "\n s   = " << std::quoted(s) << "\n\n";
   }

   return EXIT_SUCCESS;
}
