/**************************************************************************************************
*
* \file Function_2.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement a simplified std::function to demonstrate the type erasure design pattern.
*       Use the void*-based approach.
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
      : invoke_( []( void* c, Args... args ) -> R {
                    auto* const fn( static_cast<Fn*>(c) );
                    return (*fn)( std::forward<Args>(args)... );
                 } )
      , clone_( []( void* c ) -> void* {
                   auto* const fn( static_cast<Fn*>(c) );
                   return new Fn( *fn );
                } )
      , pimpl_( new Fn( std::move(fn) )
              , []( void* c ){
                   auto* const fn( static_cast<Fn*>(c) );
                   delete fn;
                } )
   {}

   Function( Function const& other )
      : invoke_( other.invoke_ )
      , clone_ ( other.clone_ )
      , pimpl_ ( clone_( other.pimpl_.get() ), other.pimpl_.get_deleter() )
   {}

   Function& operator=( Function const& other )
   {
      Function tmp( other );
      swap( tmp );
      return *this;
   }

   ~Function() = default;
   Function( Function&& ) = default;
   Function& operator=( Function&& ) = default;

   void swap( Function& fn )
   {
      std::swap( invoke_, fn.invoke_ );
      std::swap( clone_, fn.clone_ );
      std::swap( pimpl_, fn.pimpl_ );
   }

   R operator()( Args... args ) const
   {
      return invoke_( pimpl_.get(), std::forward<Args>(args)... );
   }

 private:
   using InvokeOperation  = R(void*, Args...);
   using CloneOperation   = void*(void*);
   using DestroyOperation = void(void*);

   InvokeOperation* invoke_{ nullptr };
   CloneOperation*  clone_ { nullptr };
   std::unique_ptr<void,DestroyOperation*> pimpl_;  // Bridge design pattern / pimpl idiom
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

template< typename Fn, typename... Args >
void test( Function<Fn> const& f, Args&&... args )
{
   auto const res = f( std::forward<Args>(args)... );
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
   {
      auto const fp = foo;  // Function pointer
      test<int(void)>( fp );
   }

   {
      auto const fo = Foo{};  // Function object
      test<double(double)>( fo, 1.0 );
   }

   {
      auto const lambda = [](){ return "three"; };  // Lambda
      test<std::string(void)>( lambda );
   }

   return EXIT_SUCCESS;
}
