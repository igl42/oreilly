/**************************************************************************************************
*
* \file FastPimpl.cpp
* \brief C++ Training - Example for the Bridge Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Refactor the given 'ElectricCar' class by means of the "Fast Pimpl Idiom":
*        - Evaluate the required size and alignment of the 'Impl' class
*        - Replace the 'ElectricEngineGen1' and 'BatteryGen1' data members with an 'Impl' class
*        - Refactor the special member functions of the 'ElectricCar' class
*
**************************************************************************************************/


//---- <ElectricEngineGen1.h> ---------------------------------------------------------------------

//#include <Engine.h>

class ElectricEngineGen1
{
 public:
   ElectricEngineGen1( int power );
   ~ElectricEngineGen1();

   ElectricEngineGen1( ElectricEngineGen1 const& other );
   ElectricEngineGen1& operator=( ElectricEngineGen1 const& other );

   ElectricEngineGen1( ElectricEngineGen1&& other );
   ElectricEngineGen1& operator=( ElectricEngineGen1&& other );

   void start();
   void stop();

 private:
   int power_{};  // Power in kW
};


//---- <ElectricEngineGen1.cpp> -------------------------------------------------------------------

//#include <ElectricEngineGen1.h>
#include <iostream>

ElectricEngineGen1::ElectricEngineGen1( int power )
   : power_{power}
{
   std::cout << "Creating the 'ElectricEngineGen1' (power=" << power_ << ")...\n";
}

ElectricEngineGen1::~ElectricEngineGen1()
{
   std::cout << "Destroying the 'ElectricEngineGen1'...\n";
}

ElectricEngineGen1::ElectricEngineGen1( ElectricEngineGen1 const& other )
   : power_{other.power_}
{
   std::cout << "Copy-constructing an 'ElectricEngineGen1' (power=" << power_ << ")...\n";
}

ElectricEngineGen1& ElectricEngineGen1::operator=( ElectricEngineGen1 const& other )
{
   std::cout << "Copy-assigning an 'ElectricEngineGen1' (power=" << power_ << ")...\n";
   power_ = other.power_;
   return *this;
}

ElectricEngineGen1::ElectricEngineGen1( ElectricEngineGen1&& other )
   : power_{other.power_}
{
   std::cout << "Move-constructing an 'ElectricEngineGen1' (power=" << power_ << ")...\n";
}

ElectricEngineGen1& ElectricEngineGen1::operator=( ElectricEngineGen1&& other )
{
   std::cout << "Move-assigning an 'ElectricEngineGen1' (power=" << power_ << ")...\n";
   power_ = other.power_;
   return *this;
}

void ElectricEngineGen1::start()
{
   std::cout << "Starting the 'ElectricEngineGen1' (power=" << power_ << ")...\n";
}

void ElectricEngineGen1::stop()
{
   std::cout << "Stopping the 'ElectricEngineGen1'...\n";
}


//---- <BatteryGen1.h> ----------------------------------------------------------------------------

//#include <Battery.h>

class BatteryGen1
{
 public:
   BatteryGen1( double charge );
   ~BatteryGen1();

   BatteryGen1( BatteryGen1 const& );
   BatteryGen1& operator=( BatteryGen1 const& );

   BatteryGen1( BatteryGen1&& );
   BatteryGen1& operator=( BatteryGen1&& );

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
{
   std::cout << "Creating the 'BatteryGen1' (charge=" << charge_ << ")...\n";
}

BatteryGen1::~BatteryGen1()
{
   std::cout << "Destroying the 'BatteryGen1'...\n";
}

BatteryGen1::BatteryGen1( BatteryGen1 const& other )
   : charge_{other.charge_}
{
   std::cout << "Copy constructing a 'BatteryGen1' (charge=" << charge_ << ")...\n";
}

BatteryGen1& BatteryGen1::operator=( BatteryGen1 const& other )
{
   std::cout << "Copy assigning a 'BatteryGen1' (charge=" << charge_ << ")...\n";
   charge_ = other.charge_;
   return *this;
}

BatteryGen1::BatteryGen1( BatteryGen1&& other )
   : charge_{other.charge_}
{
   std::cout << "Move constructing a 'BatteryGen1' (charge=" << charge_ << ")...\n";
}

BatteryGen1& BatteryGen1::operator=( BatteryGen1&& other )
{
   std::cout << "Move assigning a 'BatteryGen1' (charge=" << charge_ << ")...\n";
   charge_ = other.charge_;
   return *this;
}

void BatteryGen1::drawPower()
{
   std::cout << "Drawing power from the 'BatteryGen1' (charge=" << charge_ << ")...\n";
}

void BatteryGen1::charge()
{
   std::cout << "Charging the 'BatteryGen1'...\n";
}


//---- <ElectricCar.h> ----------------------------------------------------------------------------

//#include <BatteryGen1.h>
//#include <ElectricEngineGen1.h>

class ElectricCar
{
 public:
   ElectricCar();

   void drive();
   // ... more car-specific functions

 private:
   ElectricEngineGen1 engine_;
   BatteryGen1        battery_;
};


//---- <ElectricCar.cpp> --------------------------------------------------------------------------

//#include <ElectricCar.h>
#include <iostream>

ElectricCar::ElectricCar()
   : engine_{ 100 }
   , battery_{ 80.0 }
{}

void ElectricCar::drive()
{
   engine_.start();
   battery_.drawPower();
   std::cout << "Driving the 'ElectricCar'...\n";
   engine_.stop();
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <ElectricCar.h>
#include <cstdlib>

int main()
{
   std::cout << "\n----Default constructor----\n";
   ElectricCar ecar1{};
   ecar1.drive();

   std::cout << "\n----Copy constructor----\n";
   ElectricCar ecar2{ ecar1 };
   ecar2.drive();

   std::cout << "\n----Copy assignment----\n";
   ecar2 = ecar1;
   ecar2.drive();

   std::cout << "\n----Move constructor----\n";
   ElectricCar ecar3{ std::move(ecar1) };
   ecar3.drive();

   std::cout << "\n----Move assignment----\n";
   ecar3 = std::move(ecar2);
   ecar3.drive();

   std::cout << "\n----Destructors----\n";

   return EXIT_SUCCESS;
}

