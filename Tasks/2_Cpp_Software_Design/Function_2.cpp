/**************************************************************************************************
*
* \file Function_2.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
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

// TODO: Implement a simplified std::function by means of type erasure.


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
   /*
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
   */

   return EXIT_SUCCESS;
}
