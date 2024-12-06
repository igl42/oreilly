/**************************************************************************************************
*
* \file InplaceAny.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
**************************************************************************************************/

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <typeinfo>
#include <vector>


//---- <Any.h> ------------------------------------------------------------------------------------

struct bad_any_cast
   : public std::bad_cast
{};


template< size_t Capacity, size_t Alignment >
class Any
{
 public:
   template< typename T >
   Any( T const& t )
   {
      using M = Model<T>;
      static_assert( sizeof(M) <= Capacity, "The given type is too large" );
      static_assert( alignof(M) <= Alignment, "The alignment requirements of the given type are not satisfied" );
      ::new (pimpl()) M( t );  // Alternatively 'std::construct_at()' (C++20)
   }

   Any( Any const& any )
   {
      any.pimpl()->clone( pimpl() );
   }

   Any& operator=( Any const& any )
   {
      pimpl()->~Concept();
      any.pimpl()->clone( pimpl() );
      return *this;
   }

   template< typename T >
   Any& operator=( T const& t )
   {
      pimpl()->~Concept();
      new (pimpl()) Model<T>( t );
      return *this;
   }

   ~Any()
   {
      pimpl()->~Concept();  // Alternatively 'std::destroy_at()' (C++17)
   }

 private:
   class Concept
   {
    public:
      virtual ~Concept() = default;
      virtual void const* get( std::type_info const& info ) const = 0;
      virtual void clone( Concept* memory ) const = 0;
   };

   template< typename T >
   class Model final : public Concept
   {
    public:
      explicit Model( T const& t )
         : t_( t )
      {}

      void const* get( std::type_info const& info ) const final
      {
         if( info != typeid(T) ) {
            throw bad_any_cast{};
         }
         return static_cast<void const*>( &t_ );
      }

      void clone( Concept* memory ) const final { new (memory) Model( t_ ); }

    private:
      T t_;
   };

   Concept*       pimpl()       { return reinterpret_cast<Concept*>( buffer ); }
   Concept const* pimpl() const { return reinterpret_cast<Concept const*>( buffer ); }

   alignas(Alignment) char buffer[Capacity+sizeof(void*)];

   template< typename T, size_t C, size_t A >
   friend T any_cast( Any<C,A> const& any );
};

template< typename T, size_t Capacity, size_t Alignment >
T any_cast( Any<Capacity,Alignment> const& any )
{
   return *static_cast<T const*>( any.pimpl()->get( typeid(T) ) );
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // unsigned int
   {
      using T = unsigned int;
      Any<16U,8U> any( 1U );
      any = 42U;
      T const ui = any_cast<T>( any );
      std::cout << "\n ui  = " << ui << "\n";
   }

   // std::string
   {
      using T = std::string;
      Any<48U,8U> any( std::string{ "Demonstration for an inplace any" } );
      T const s = any_cast<T>( any );
      std::cout << "\n s   = " << std::quoted(s) << "\n";
   }

   // std::vector
   {
      using T = std::vector<int>;
      Any<48U,8U> any( T{ 1, 2, 3, 4 } );
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
      Any<256U,128U> any( T{ 1, 2, 3 } );
      T const oa = any_cast<T>( any );
      std::cout << "\n oa  = (" << oa.array[0] << "," << oa.array[1] << "," << oa.array[2] << ")\n";
   }

   // unsigned int -> std::string
   {
      using T = std::string;
      Any<48U,8U> any( 1U );
      any = std::string{ "Replacement for the unsigned int 1U" };
      T const s = any_cast<T>( any );
      std::cout << "\n s   = " << std::quoted(s) << "\n\n";
   }

   return EXIT_SUCCESS;
}
