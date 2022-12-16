/**************************************************************************************************
*
* \file RefactorSingleton_1.cpp
* \brief C++ Training - Programming Task for the Singleton Design Pattern
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Refactor the given 'Database' Singleton by means of an abstraction according to the
*       Strategy design pattern. Prove the improved changeability and testability by means
*       of a 'CustomPersistance' implementation.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>


//---- <PersistenceInterface.h> -------------------------------------------------------------------

namespace persistence {

class PersistenceInterface
{
 public:
   virtual ~PersistenceInterface() = default;

   bool write( /* some arguments */ )
   {
      return do_write( /*...*/ );
   }
   bool read( /* some arguments */ ) const
   {
      return do_read( /*...*/ );
   }

   // ... More database specific functionality

 private:
   virtual bool do_write( /* some arguments */ ) = 0;
   virtual bool do_read( /* some arguments */ ) const = 0;
};


namespace detail {

extern PersistenceInterface* instance;

} // namespace detail


PersistenceInterface* get_persistence_interface();
void set_persistence_interface( PersistenceInterface* persistence );

} // namespace persistence


//---- <Database.h> -------------------------------------------------------------------------------

namespace persistence {

class Database : public PersistenceInterface
{
 public:
   Database()
   {
      std::cout << "**** Database created ****\n";
   }

   bool do_write( /* some arguments */ ) override
   {
      std::cout << "Database::write(): Writing to the database...\n";
      return true;
   }

   bool do_read( /* some arguments */ ) const override
   {
      std::cout << "Database::read(): Reading from the database...\n";
      return true;
   }

   // ... More database specific functionality
};

} // namespace persistence


//---- <PersistenceInterface.cpp> -----------------------------------------------------------------

//#include <Database.h>

namespace persistence {

namespace detail {

PersistenceInterface* instance = nullptr;

} // namespace detail


PersistenceInterface* get_persistence_interface()
{
   // Local object, initialized by an "Immediately Invoked Lambda Expression (IILE)"
   static bool init = [](){
      if( !detail::instance ) {
         static Database db;
         detail::instance = &db;
      }
      return true;
   }();

   return detail::instance;
}

void set_persistence_interface( PersistenceInterface* persistence )
{
   detail::instance = persistence;
}

} // namespace persistence


//---- <Widget.h> ---------------------------------------------------------------------------------

class Widget
{
 public:
   void doSomething()
   {
      // ...
      persistence::get_persistence_interface()->read( /* some arguments */ );
      // ...
   }
};


//---- <Gadget.h> ---------------------------------------------------------------------------------

class Gadget
{
 public:
   void doSomething()
   {
      // ...
      persistence::get_persistence_interface()->write( /* some arguments */ );
      // ...
   }
};


//---- <CustomPersistence.h> ----------------------------------------------------------------------

class CustomPersistence : public persistence::PersistenceInterface
{
 public:
   CustomPersistence() = default;
   CustomPersistence( CustomPersistence const& db ) = default;

   bool do_write( /* some arguments */ ) override
   {
      std::cout << "CustomPersistence::write(): Writing to the custom persistence...\n";
      return true;
   }

   bool do_read( /* some arguments */ ) const override
   {
      std::cout << "CustomPersistence::read(): Reading from the custom persistence...\n";
      return true;
   }

   // ... More database specific functionality

 private:
   // ... Potential implementation details and data members
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   Widget w{};
   Gadget g{};

   //CustomPersistence persistence;
   //persistence::set_persistence_interface( &persistence );

   w.doSomething();
   g.doSomething();s

   return EXIT_SUCCESS;
}
