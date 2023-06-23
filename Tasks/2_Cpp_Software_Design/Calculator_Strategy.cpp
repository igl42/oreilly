/**************************************************************************************************
*
* \file Calculator_Strategy.cpp
* \brief C++ Training - Example for the Strategy Design Pattern
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Consider the given 'Calculator' class, which is implemented in terms of the Strategy
*       design pattern. What would have to be changed to implement it in terms of the Command
*       design pattern?
*
**************************************************************************************************/

#include <cstdlib>
#include <functional>
#include <iostream>


//---- <Calculator.h> -----------------------------------------------------------------------------

class Calculator
{
 public:
   using Strategy = std::function<int(int,int)>;

   Calculator() = default;
   explicit Calculator( Strategy strategy )
      : strategy_{ std::move(strategy) }
   {}

   void set( Strategy strategy );

   int result() const;
   void reset();

   void compute( int );

 private:
   int current_{};
   Strategy strategy_{ std::plus<>{} };
};


//---- <Calculator.cpp> ---------------------------------------------------------------------------

//#include <Calculator.h>

void Calculator::set( Strategy strategy )
{
   strategy_ = std::move(strategy);
}

int Calculator::result() const
{
   return current_;
}

void Calculator::reset()
{
   current_ = 0;
   strategy_ = std::plus<>{};
}

void Calculator::compute( int value )
{
   current_ = strategy_( current_, value );
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Calculator.h>

int main()
{
   Calculator calculator{};

   calculator.compute( 3 );  // Computes 0 + 3, stores and returns 3
   calculator.compute( 7 );  // Computes 3 + 7, stores and returns 10

   calculator.set( std::minus<>{} );

   calculator.compute( 4 );  // Computes 10 - 4, stores and returns 6
   calculator.compute( 2 );  // Computes 6 - 2, stores and returns 4

   calculator.set( std::multiplies<>{} );

   calculator.compute( 5 );  // Computes 4 times 5, stores and returns 20

   int const res = calculator.result();

   std::cout << "\n res = " << res << " (expected: 20)\n\n";

   return EXIT_SUCCESS;
}
