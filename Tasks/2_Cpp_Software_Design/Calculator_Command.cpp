/**************************************************************************************************
*
* \file Calculator_Command.cpp
* \brief C++ Training - Example for the Command Design Pattern
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Consider the given 'Calculator' class, which is implemented in terms of the Command
*       design pattern. What would have to be changed to implement it in terms of the Strategy
*       design pattern?
*
**************************************************************************************************/

#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <stack>


//---- <CalculatorCommand.h> ----------------

class CalculatorCommand
{
 public:
   virtual ~CalculatorCommand() = default;

   virtual int execute( int i ) const = 0;
   virtual int undo( int i ) const = 0;
};


//---- <Addition.h> ----------------

//#include <CalculatorCommand.h>

class Addition : public CalculatorCommand
{
 public:
   explicit Addition( int operand ) : operand_(operand) {}

   int execute( int i ) const override
   {
      return i + operand_;
   }
   int undo( int i ) const override
   {
      return i - operand_;
   }

 private:
   int operand_{};
};


//---- <Subtraction.h> ----------------

//#include <CalculatorCommand.h>

class Subtraction : public CalculatorCommand
{
 public:
   explicit Subtraction( int operand ) : operand_(operand) {}

   int execute( int i ) const override
   {
      return i - operand_;
   }
   int undo( int i ) const override
   {
      return i + operand_;
   }

 private:
   int operand_{};
};


//---- <Calculator.h> -----------------------------------------------------------------------------

//#include <CalculatorCommand.h>

class Calculator
{
 public:
   Calculator() = default;

   void compute( std::unique_ptr<CalculatorCommand> command );
   void undoLast();

   int result() const;
   void reset();

 private:
   using CommandStack = std::stack<std::unique_ptr<CalculatorCommand>>;

   int current_{};
   CommandStack stack_;
};


//---- <Calculator.cpp> ---------------------------------------------------------------------------

//#include <Calculator.h>

void Calculator::compute( std::unique_ptr<CalculatorCommand> command )
{
   current_ = command->execute( current_ );
   stack_.push( std::move(command) );
}

void Calculator::undoLast()
{
   if( stack_.empty() ) return;

   auto command = std::move(stack_.top());
   stack_.pop();

   current_ = command->undo(current_);
}

int Calculator::result() const
{
   return current_;
}

void Calculator::reset()
{
   current_ = 0;
   CommandStack{}.swap( stack_ );  // Resetting the stack
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Calculator.h>

int main()
{
   Calculator calculator{};

   auto op1 = std::make_unique<Addition>( 3 );
   auto op2 = std::make_unique<Addition>( 7 );
   auto op3 = std::make_unique<Subtraction>( 4 );
   auto op4 = std::make_unique<Subtraction>( 2 );

   calculator.compute( std::move(op1) );  // Computes 0 + 3, stores and returns 3
   calculator.compute( std::move(op2) );  // Computes 3 + 7, stores and returns 10
   calculator.compute( std::move(op3) );  // Computes 10 - 4, stores and returns 6
   calculator.compute( std::move(op4) );  // Computes 6 - 2, stores and returns 4

   calculator.undoLast();  // Reverts the last operation,
                           // stores and returns 6

   int const res = calculator.result();

   std::cout << "\n res = " << res << " (expected: 6)\n\n";

   return EXIT_SUCCESS;
}
