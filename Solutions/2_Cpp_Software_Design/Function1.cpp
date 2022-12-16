/**************************************************************************************************
*
* \file Function1.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement a simplified std::function to demonstrate the type erasure design pattern.
*       Use the inheritance-based approach.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>


//---- <Function.h> -------------------------------------------------------------------------------

template< typename Fn >
class Function;

template< typename R, typename... Args >
class Function<R(Args...)>
{
 public:
   template< typename Fn >
   Function( Fn fn )
      : pimpl_( std::make_unique<Model<Fn>>( fn ) )
   {}

   Function( Function const& other )
      : pimpl_( other.pimpl_->clone() )
   {}

   Function& operator=( const Function& other )
   {
      // Copy-and-swap idiom
      Function tmp( other );
      std::swap( pimpl_, tmp.pimpl_ );
      return *this;
   }

   ~Function() = default;
   Function( Function&& ) = default;
   Function& operator=( Function&& ) = default;

   R operator()( Args... args ) const { return pimpl_->invoke( std::forward<Args>( args )... ); }

 private:
   class Concept  // External Polymorphism design pattern
   {
    public:
      virtual ~Concept() = default;
      virtual R invoke( Args... ) const = 0;
      virtual std::unique_ptr<Concept> clone() const = 0;  // Prototype design pattern
   };

   template< typename Fn >
   class Model final : public Concept
   {
    public:
      explicit Model( Fn fn )
         : fn_( fn )
      {}

      R invoke( Args... args ) const final { return fn_( std::forward<Args>( args )... ); }
      std::unique_ptr<Concept> clone() const final { return std::make_unique<Model>( fn_ ); }

    private:
      Fn fn_;
   };

   std::unique_ptr<Concept> pimpl_;  // Bridge design pattern / pimpl idiom
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

template< typename Fn, typename... Args >
void test( const Function<Fn>& f, Args&&... args )
{
   const auto res = f( std::forward<Args>(args)... );
   std::cout << "\n res = " << res << "\n\n";
}


int foo()
{
   return 1;
}

struct Foo {
   double operator()( double d ) const {
      return 2.0*d;
   }
};


int main()
{
   /*
   {
      const auto fp = foo;  // Function pointer
      test<int(void)>( fp );
   }

   {
      const auto fo = Foo{};  // Function object
      test<double(double)>( fo, 1.0 );
   }

   {
      const auto lambda = [](){ return "three"; };  // Lambda
      test<std::string(void)>( lambda );
   }
   */

   return EXIT_SUCCESS;
}
