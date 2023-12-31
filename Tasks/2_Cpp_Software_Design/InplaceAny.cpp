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
   Any( const T& t )
   {
      static_assert( sizeof(T) <= Capacity, "The given type is too large" );
      static_assert( alignof(T) <= Alignment, "The alignment requirements of the given type are not satisfied" );
      new (pimpl()) Model<T>( t );
   }

   Any( Any const& any )
   {
      any.pimpl()->clone( pimpl() );
   }

   Any& operator=( const Any& any )
   {
      pimpl()->~Concept();
      any.pimpl()->clone( pimpl() );
      return *this;
   }

   template< typename T >
   Any& operator=( const T& t )
   {
      pimpl()->~Concept();
      new (pimpl()) Model<T>( t );
      return *this;
   }

   ~Any() { pimpl()->~Concept(); }

 private:
   class Concept
   {
    public:
      virtual ~Concept() = default;
      virtual const void* get( const std::type_info& info ) const = 0;
      virtual void clone( Concept* memory ) const = 0;
   };

   template< typename T >
   class Model final : public Concept
   {
    public:
      explicit Model( const T& t )
         : t_( t )
      {}

      const void* get( const std::type_info& info ) const final
      {
         if( info != typeid(T) ) {
            throw bad_any_cast{};
         }
         return static_cast<const void*>( &t_ );
      }

      void clone( Concept* memory ) const final { new (memory) Model( t_ ); }

    private:
      T t_;
   };

   Concept*       pimpl()       { return reinterpret_cast<Concept*>( buffer ); }
   const Concept* pimpl() const { return reinterpret_cast<const Concept*>( buffer ); }

   alignas(Alignment) char buffer[Capacity+sizeof(void*)];

   template< typename T, size_t C, size_t A >
   friend T any_cast( const Any<C,A>& any );
};

template< typename T, size_t Capacity, size_t Alignment >
T any_cast( const Any<Capacity,Alignment>& any )
{
   return *static_cast<const T*>( any.pimpl()->get( typeid(T) ) );
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // unsigned int
   {
      using T = unsigned int;
      Any<sizeof(T),alignof(T)> any( 1U );
      any = 42U;
      const T ui = any_cast<T>( any );
      std::cout << "\n ui  = " << ui << "\n";
   }

   // std::string
   {
      using T = std::string;
      Any<sizeof(T),alignof(T)> any( std::string{ "Demonstration for an inplace any" } );
      const T s = any_cast<T>( any );
      std::cout << "\n s   = " << std::quoted(s) << "\n";
   }

   // std::vector
   {
      using T = std::vector<int>;
      Any<sizeof(T),alignof(T)> any( T{ 1, 2, 3, 4 } );
      const T vec = any_cast<T>( any );
      std::cout << "\n vec = (" << vec[0] << "," << vec[1] << "," << vec[2] << "," << vec[3] << ")\n";
   }

   // OveralignedArray
   {
      struct OveralignedArray
      {
         alignas(128) int array[3];
      };

      using T = OveralignedArray;
      Any<sizeof(T),alignof(T)> any( T{ 1, 2, 3 } );
      const T oa = any_cast<T>( any );
      std::cout << "\n oa  = (" << oa.array[0] << "," << oa.array[1] << "," << oa.array[2] << ")\n";
   }

   // unsigned int -> std::string
   {
      using T = std::string;
      Any<sizeof(T),alignof(T)> any( 1U );
      any = std::string{ "Replacement for the unsigned int 1U" };
      const T s = any_cast<T>( any );
      std::cout << "\n s   = " << std::quoted(s) << "\n\n";
   }

   return EXIT_SUCCESS;
}
