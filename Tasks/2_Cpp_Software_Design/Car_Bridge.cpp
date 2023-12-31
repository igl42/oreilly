/**************************************************************************************************
*
* \file Car_Bridge.cpp
* \brief C++ Training - Example for the Bridge Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Consider the given 'Car' example, which demonstrates the Bridge design pattern. What
*       would have to be changed to implement it in terms of the Strategy design pattern?
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>


//---- <Engine.h> ---------------------------------------------------------------------------------

class Engine
{
 public:
   virtual ~Engine() = default;
   virtual void start() = 0;
   virtual void stop() = 0;
   // ... more engine-specific functions

 private:
   // ...
};


//---- <Car.h> ------------------------------------------------------------------------------------

//#include <Engine.h>

class Car
{
 protected:
   explicit Car( std::unique_ptr<Engine> engine )
      : engine_{ std::move(engine) }
   {}

 public:
   virtual ~Car() = default;
   virtual void drive() = 0;
   // ... more car-specific functions

 protected:
   Engine*       getEngine()       { return engine_.get(); }
   Engine const* getEngine() const { return engine_.get(); }

 private:
   std::unique_ptr<Engine> engine_;  // Pointer-to-implementation (pimpl)

   // ... more car-specific data members (wheels, drivetrain, ...)
};


//---- <ElectricEngineGen1.h> ---------------------------------------------------------------------

//#include <Engine.h>

class ElectricEngineGen1 : public Engine
{
 public:
   void start() override;
   void stop() override;

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


//---- <ElectricCar.h> ----------------------------------------------------------------------------

//#include <Car.h>

class ElectricCar : public Car
{
 public:
   ElectricCar();

   void drive();
   // ...

 private:
   // ...

   // ... more electric car-specific data members (battery, ...)
};


//---- <ElectricCar.cpp> --------------------------------------------------------------------------

//#include <ElectricCar.h>
//#include <ElectricEngineGen1.h>
#include <iostream>

ElectricCar::ElectricCar()
   : Car{ std::make_unique<ElectricEngineGen1>() }
{}

void ElectricCar::drive()
{
   getEngine()->start();
   std::cout << "Driving the 'ElectricCar'...\n";
   getEngine()->stop();
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <ElectricCar.h>

int main()
{
   ElectricCar ecar{};
   ecar.drive();

   return EXIT_SUCCESS;
}
