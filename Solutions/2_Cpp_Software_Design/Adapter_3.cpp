/**************************************************************************************************
*
* \file Adapter_3.cpp
* \brief C++ Training - Example for the Adapter Design Pattern
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Refactor the given 'doSomeWork()' function to avoid the "Pyramid of Doom". For that
*       purpose, implement an adapter to seamlessly connect the three functions 'doSomething()',
*       'doSomethingElse()' and 'doAThirdThing()'.
*
**************************************************************************************************/

#include <cmath>
#include <cstdlib>
#include <iostream>
#include <optional>


//---- <Map.h> ------------------------------------------------------------------------------------

using FP = std::optional<double>(*)(double);

std::optional<double> map( FP fn, std::optional<double> d )
{
   if( d.has_value() ) {
      return fn(d.value());
   }
   else
      return std::nullopt;
}

std::optional<double> operator|( std::optional<double> opt, FP fn )
{
   return map( fn, opt );
}


//---- <DoSomeWork.h> -----------------------------------------------------------------------------

std::optional<double> doSomething( double d )
{
   if( d >= 0.0 ) {
      return std::sqrt( d );
   }
   else {
      return std::nullopt;
   }
}

std::optional<double> doSomethingElse( double d )
{
   if( d > 0.0 && d < 10.0 ) {
      return d * 2.0;
   }
   else {
      return std::nullopt;
   }
}

std::optional<double> doAThirdThing( double d )
{
   if( d > 2.0 ) {
      return d / 4.0;
   }
   else {
      return std::nullopt;
   }
}

std::optional<double> doSomeWork( double d )
{
   return std::make_optional(d)
        | doSomething
        | doSomethingElse
        | doAThirdThing;

   // Alternatively:
   //return
   //   map( doAThirdThing,
   //      map( doSomethingElse,
   //         map( doSomething, std::make_optional(d) ) ) );
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // Success
   {
      auto const result = doSomeWork( 64.0 );

      if( result.has_value() ) {
         std::cout << "\n result = " << result.value() << "\n\n";
      }
      else {
         std::cout << "\n No result!\n\n";
      }
   }

   // Failure
   {
      auto const result = doSomeWork( 1.0 );

      if( result.has_value() ) {
         std::cout << "\n result = " << result.value() << "\n\n";
      }
      else {
         std::cout << "\n No result!\n\n";
      }
   }

   return EXIT_SUCCESS;
}

