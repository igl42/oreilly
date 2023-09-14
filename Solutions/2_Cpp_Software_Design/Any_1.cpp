/**************************************************************************************************
*
* \file Any_1.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement a simplified std::any to demonstrate the type erasure design pattern. Use
*       the inheritance-based approach.
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
   Any( T const& t ) : pimpl_( std::make_unique<Model<T>>( t ) ) {}

   Any( Any const& any ) : pimpl_( any.pimpl_->clone() ) {}
   Any& operator=( Any const& any ) { Any tmp( any ); std::swap( pimpl_, tmp.pimpl_ ); return *this; }

   Any( Any&& ) = default;
   Any& operator=( Any&& ) = default;

   ~Any() = default;

 private:
   class Concept  // External Polymorphism design pattern
   {
    public:
      virtual ~Concept() = default;
      virtual void const* get( std::type_info const& info ) const = 0;
      virtual std::unique_ptr<Concept> clone() const = 0;  // Prototype design pattern
   };

   template< typename T >
   class Model : public Concept
   {
    public:
      explicit Model( T const& t )
         : t_( t )
      {}

      void const* get( std::type_info const& info ) const override
      {
         if( info != typeid(T) ) {
            throw bad_any_cast{};
         }
         return std::addressof(t_);   // Alternatively: static_cast<void const*>( &t_ );
      }

      std::unique_ptr<Concept> clone() const override { return std::make_unique<Model>( t_ ); }

    private:
      T t_;
   };

   std::unique_ptr<Concept> pimpl_;  // Bridge design pattern / pimpl idiom

   template< typename T >
   friend T any_cast( Any const& any );
};

template< typename T >
T any_cast( Any const& any )
{
   return *static_cast<T const*>( any.pimpl_->get( typeid(T) ) );
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
      using T1 = unsigned int;
      using T2 = std::string;
      Any any( 1U );
      any = std::string{ "Replacement for the unsigned int 1U" };
      T2 const s = any_cast<T2>( any );
      std::cout << "\n s   = " << std::quoted(s) << "\n\n";
   }

   return EXIT_SUCCESS;
}
