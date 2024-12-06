/**************************************************************************************************
*
* \file Car_Strategy.cpp
* \brief C++ Training - Example for the Strategy Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: The fictional electric car manufacturer 'ElectricHero (EH)' has used the Strategy design
*       for its 'ElectricCar' implementation. What would have to be changed to implement it
*       in terms of the Bridge design pattern?
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>


//---- <ElectricCarImpl.h> ----------------------------------------------------------------------------

class ElectricCarImpl
{
 public:
   virtual ~ElectricCarImpl() = default;

   virtual void start() = 0;
   virtual void stop() = 0;

   virtual void drawPower() = 0;
   virtual void charge() = 0;

   // ... more car-specific functions

 private:
   // ... potentially some car-specific data members (wheels, drivetrain, ...)
};


//---- <ElectricCar.h> ----------------------------------------------------------------------------

//#include <ElectricCarImpl.h>

class ElectricCar
{
 protected:
   explicit ElectricCar( std::unique_ptr<ElectricCarImpl> impl )
      : pimpl_{ std::move(impl) }
   {}

 public:
   virtual ~ElectricCar() = default;
   virtual void drive() = 0;
   // ... more car-specific functions

 protected:
   ElectricCarImpl*       getImpl()       { return pimpl_.get(); }
   ElectricCarImpl const* getImpl() const { return pimpl_.get(); }

 private:
   std::unique_ptr<ElectricCarImpl> pimpl_;  // Pointer-to-implementation (pimpl)
};


//---- <BatteryGen1.h> ----------------------------------------------------------------------------

class BatteryGen1
{
 public:
   BatteryGen1( double charge );

   void drawPower();
   void charge();

 private:
   double charge_{};  // Electrical charge in kWh
   // ...
};


//---- <BatteryGen1.cpp> --------------------------------------------------------------------------

//#include <BatteryGen1.h>
#include <iostream>

BatteryGen1::BatteryGen1( double charge )
   : charge_{charge}
{}

void BatteryGen1::drawPower()
{
   std::cout << "Drawing power from the 'BatteryGen1' (charge=" << charge_ << ")...\n";
}

void BatteryGen1::charge()
{
   std::cout << "Charging the 'BatteryGen1'...\n";
}


//---- <ElectricEngineGen1.h> ---------------------------------------------------------------------

class ElectricEngineGen1
{
 public:
   void start();
   void stop();

 private:
   // ...
};


//---- <ElectricEngineGen1.cpp> -------------------------------------------------------------------

//#include <ElectricEngineGen1.h>
#include <iostream>

void ElectricEngineGen1::start()
{
   std::cout << "Starting the 'ElectricEngineGen1'...\n";
}

void ElectricEngineGen1::stop()
{
   std::cout << "Stopping the 'ElectricEngineGen1'...\n";
}


//---- <ElectricHero.h> ---------------------------------------------------------------------------

//#include <ElectricCar.h>

class ElectricHero : public ElectricCar
{
 public:
   ElectricHero( std::unique_ptr<ElectricCarImpl>&& impl );

   void drive();

   // ... more car or EH-specific functions

 private:
   // ... possibly some EH-specific data members that don't need to be hidden
};


//---- <ElectricHero.cpp> -------------------------------------------------------------------------

//#include <ElectricHero.h>
#include <iostream>

ElectricHero::ElectricHero( std::unique_ptr<ElectricCarImpl>&& impl )
   : ElectricCar{ std::move(impl) }
{}

void ElectricHero::drive()
{
   getImpl()->start();
   getImpl()->drawPower();
   std::cout << "Driving the 'ElectricCar'...\n";
   getImpl()->stop();
}


//==== ARCHITECTURAL BOUNDARY =====================================================================


//---- <ElectricHeroImpl.h> ------------------------------------------------------------------------

//#include <BatteryGen1.h>
//#include <ElectricEngineGen1.h>

class ElectricHeroImpl : public ElectricCarImpl
{
 public:
   explicit ElectricHeroImpl( double charge )
      : battery_{charge}
      , engine_{}
   {}

   void start() override { engine_.start(); }
   void stop() override { engine_.stop(); }

   void drawPower() override { battery_.drawPower(); }
   void charge() override { battery_.charge(); }

   // ... more car or EH-specific functions

 private:
   BatteryGen1 battery_;
   ElectricEngineGen1 engine_;
   // ... more EH-specific data members (wheels, drivetrain, ...)
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <ElectricHero.h>
//#include <ElectricHeroImpl.h>

int main()
{
   ElectricHero ecar{ std::make_unique<ElectricHeroImpl>( 100.0 ) };
   ecar.drive();

   return EXIT_SUCCESS;
}
