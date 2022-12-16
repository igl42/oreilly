/**************************************************************************************************
*
* \file Any.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
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
   Any( const T& t ) : pimpl_( std::make_unique<Model<T>>( t ) ) {}

   Any( Any const& any ) : pimpl_( any.pimpl_->clone() ) {}
   Any& operator=( const Any& any ) { Any tmp( any ); std::swap( pimpl_, tmp.pimpl_ ); return *this; }

   Any( Any&& ) = default;
   Any& operator=( Any&& ) = default;

   ~Any() = default;

 private:
   class Concept
   {
    public:
      virtual ~Concept() = default;
      virtual const void* get( const std::type_info& info ) const = 0;
      virtual std::unique_ptr<Concept> clone() const = 0;
   };

   template< typename T >
   class Model : public Concept
   {
    public:
      explicit Model( const T& t )
         : t_( t )
      {}

      const void* get( const std::type_info& info ) const override
      {
         if( info != typeid(T) ) {
            throw bad_any_cast{};
         }
         return static_cast<const void*>( &t_ );
      }

      std::unique_ptr<Concept> clone() const override { return std::make_unique<Model>( t_ ); }

    private:
      T t_;
   };

   std::unique_ptr<Concept> pimpl_;

   template< typename T >
   friend T any_cast( const Any& any );
};

template< typename T >
T any_cast( const Any& any )
{
   return *static_cast<const T*>( any.pimpl_->get( typeid(T) ) );
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // unsigned int
   {
      using T = unsigned int;
      Any any( 1U );
      any = 42U;
      const T ui = any_cast<T>( any );
      std::cout << "\n ui  = " << ui << "\n";
   }

   // std::string
   {
      using T = std::string;
      Any any( std::string{ "Demonstration for an inplace any" } );
      const T s = any_cast<T>( any );
      std::cout << "\n s   = " << std::quoted(s) << "\n";
   }

   // std::vector
   {
      using T = std::vector<int>;
      Any any( T{ 1, 2, 3, 4 } );
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
      Any any( T{ 1, 2, 3 } );
      const T oa = any_cast<T>( any );
      std::cout << "\n oa  = (" << oa.array[0] << "," << oa.array[1] << "," << oa.array[2] << ")\n";
   }

   // unsigned int -> std::string
   {
      using T1 = unsigned int;
      using T2 = std::string;
      Any any( 1U );
      any = std::string{ "Replacement for the unsigned int 1U" };
      const T2 s = any_cast<T2>( any );
      std::cout << "\n s   = " << std::quoted(s) << "\n\n";
   }

   return EXIT_SUCCESS;
}
