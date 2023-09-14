/**************************************************************************************************
*
* \file Function_Ref.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement a simplified std::function_ref to represent a non-owning abstraction for
*       any type of callable.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>
#include <utility>


//---- <Function.h> -------------------------------------------------------------------------------

template< typename Fn >
class Function_Ref;

template< typename R, typename... Args >
class Function_Ref<R(Args...)>
{
 private:
   union Callable {
      void const* functor;
      R(*fptr)(Args...);
   };

 public:
   Function_Ref( R(*fptr)(Args...) )
      : callable_{}
      , invoke_{ []( Callable callable, Args... args ) -> R {
                    return callable.fptr( std::forward<Args>(args)... );
                 } }
   {
      callable_.fptr = fptr;
   }

   template< typename Fn >
   Function_Ref( Fn& callable )  // Type Fn is possibly cv qualified; lvalue
                                 // reference prevents shape references to rvalues
      : callable_{}
      , invoke_{ []( Callable raw, Args... args ) -> R {
                    return (*static_cast<Fn const*>(raw.functor))( std::forward<Args>(args)... );
                 } }
   {
      callable_.functor = std::addressof(callable);
   }

   R operator()( Args... args ) const { return invoke_( callable_, std::forward<Args>(args)... ); }

 private:
   using InvokeOperation = R(Callable, Args...);

   Callable callable_;
   InvokeOperation* invoke_;

   static_assert( sizeof(Callable) == sizeof(void*) );
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

template< typename Fn, typename... Args >
void test( Function_Ref<Fn> const& f, Args&&... args )
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
