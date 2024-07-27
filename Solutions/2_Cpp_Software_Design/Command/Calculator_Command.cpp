/**************************************************************************************************
*
* \file Calculator_Command.cpp
* \brief C++ Training - Example for the Command Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
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


//---- <Command.h> ----------------

class Command
{
 public:
   template< typename Cmd >
   Command( Cmd cmd )
      : pimpl_{ new Cmd{cmd}
              , []( void* c ){
                   auto* data = static_cast<Cmd*>(c);
                   delete data;
                } }
      , execute_{ []( void* c, int i ) -> int {
                     auto* const data = static_cast<Cmd*>(c);
                     return data->execute(i);
                  } }
      , undo_{ []( void* c, int i ) -> int {
                  auto* const data = static_cast<Cmd*>(c);
                  return data->undo(i);
               } }
      , clone_{ []( void* c ) -> void* {
                   auto* const data = static_cast<Cmd*>(c);
                   return new Cmd(*data);
                } }
   {}

   int execute( int i ) const { return execute_( pimpl_.get(), i ); }
   int undo( int i ) const { return undo_( pimpl_.get(), i ); }

   ~Command() = default;
   Command( Command&& ) = default;
   Command& operator=( Command&& ) = default;

   Command( Command const& other )
      : pimpl_{ other.clone_( other.pimpl_.get() ), other.pimpl_.get_deleter() }
      , execute_{ other.execute_ }
      , undo_{ other.undo_ }
      , clone_{ other.clone_ }
   {}

   Command& operator=( Command const& other )
   {
      Command copy( other );
      swap( copy );
      return *this;
   }

   void swap( Command& other )
   {
      std::swap( pimpl_, other.pimpl_ );
      std::swap( execute_, other.execute_ );
      std::swap( undo_, other.undo_ );
   }

 private:
   using Delete  = void(void*);
   using Execute = int(void*, int);
   using Undo    = int(void*, int);
   using Clone   = void*(void*);

   std::unique_ptr<void,Delete*> pimpl_;
   Execute* execute_;
   Undo* undo_;
   Clone* clone_;
};



//---- <Addition.h> ----------------

class Addition
{
 public:
   explicit Addition( int operand ) : operand_(operand) {}

   int execute( int i ) const
   {
      return i + operand_;
   }
   int undo( int i ) const
   {
      return i - operand_;
   }

 private:
   int operand_{};
};


//---- <Subtraction.h> ----------------

class Subtraction
{
 public:
   explicit Subtraction( int operand ) : operand_(operand) {}

   int execute( int i ) const
   {
      return i - operand_;
   }
   int undo( int i ) const
   {
      return i + operand_;
   }

 private:
   int operand_{};
};


//---- <Calculator.h> -----------------------------------------------------------------------------

//#include <Command.h>

class Calculator
{
 public:
   Calculator() = default;

   void compute( Command command );
   void undoLast();

   int result() const;
   void reset();

 private:
   using CommandStack = std::stack<Command>;

   int current_{};
   CommandStack stack_;
};


//---- <Calculator.cpp> ---------------------------------------------------------------------------

//#include <Calculator.h>

void Calculator::compute( Command command )
{
   current_ = command.execute( current_ );
   stack_.push( std::move(command) );
}

void Calculator::undoLast()
{
   if( stack_.empty() ) return;

   auto command = std::move(stack_.top());
   stack_.pop();

   current_ = command.undo(current_);
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

   calculator.compute( Addition( 3 ) );     // Computes 0 + 3, stores and returns 3
   calculator.compute( Addition( 7 ) );     // Computes 3 + 7, stores and returns 10
   calculator.compute( Subtraction( 4 ) );  // Computes 10 - 4, stores and returns 6
   calculator.compute( Subtraction( 2 ) );  // Computes 6 - 2, stores and returns 4

   calculator.undoLast();  // Reverts the last operation,
                           // stores and returns 6

   int const res = calculator.result();

   std::cout << "\n res = " << res << " (expected: 6)\n\n";

   return EXIT_SUCCESS;
}
