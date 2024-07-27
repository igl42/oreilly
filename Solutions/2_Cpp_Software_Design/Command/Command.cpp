/**************************************************************************************************
*
* \file Command.cpp
* \brief C++ Training - Example for the Command Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Refactor the classic Command solution by means of std::function.
*
**************************************************************************************************/

#include <cstdlib>
#include <functional>
#include <iostream>


//---- <Callback.h> -------------------------------------------------------------------------------

using Callback = std::function<void(int)>;


//---- <Subject.h> --------------------------------------------------------------------------------

class Subject
{
 public:
   explicit Subject( Callback callback );

   void invoke( int i );

 private:
   Callback callback_;
};


//---- <Subject.cpp> ------------------------------------------------------------------------------

Subject::Subject( Callback callback )
   : callback_( std::move( callback ) )
{}

void Subject::invoke( int i )
{
   callback_( i );
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

void foo( int i )
{
   std::cout << "\n foo( " << i << " ) called!\n";
}

struct Foo {
   void operator()( int i )
   {
      std::cout << "\n Foo( " << i << " ) called!\n";
   }
};

int main()
{
   Subject s1( foo );
   Subject s2( Foo{} );

   s1.invoke( 1 );
   s2.invoke( 2 );

   return EXIT_SUCCESS;
}
