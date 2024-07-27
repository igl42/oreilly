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


//---- <Command.h> --------------------------------------------------------------------------------

class Command
{
 public:
   explicit Command() = default;
   virtual ~Command() = default;

   void execute( int i );

 private:
   virtual void doExecute( int i ) = 0;
};


//---- <Command.cpp> ------------------------------------------------------------------------------

void Command::execute( int i )
{
   std::cout << " Executing command with argument " << i << "...\n";
   doExecute( i );
}


//---- <Subject.h> --------------------------------------------------------------------------------

class Subject
{
 public:
   explicit Subject( Command* command );

   void invoke( int i );

 private:
   Command* command_;
};


//---- <Subject.cpp> ------------------------------------------------------------------------------

Subject::Subject( Command* command )
   : command_( command )
{}

void Subject::invoke( int i )
{
   command_->execute( i );
}


//---- <ConcreteCommand.h> ------------------------------------------------------------------------

class ConcreteCommand : public Command
{
 public:
   explicit ConcreteCommand() = default;

 private:
   void doExecute( int i ) override;
};

//---- <ConcreteCommand.cpp> ----------------------------------------------------------------------

void ConcreteCommand::doExecute( int i )
{
   std::cout << " Executing concrete command with argument " << i << "...\n";
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   ConcreteCommand command;

   Subject subject( &command );

   subject.invoke( 1 );

   return EXIT_SUCCESS;
}
