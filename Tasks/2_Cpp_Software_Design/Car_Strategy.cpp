/**************************************************************************************************
*
* \file Car_Strategy.cpp
* \brief C++ Training - Example for the Strategy Design Pattern
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Consider the given 'Car' example, which demonstrates the Strategy design pattern. What
*       would have to be changed to implement it in terms of the Bridge design pattern?
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
   Car( std::unique_ptr<Engine> engine )
      : engine_{ std::move(engine) }
   {}

 public:
   virtual ~Car() = default;
   virtual void drive() = 0;
   // ... more car-specific functions

 protected:
   Engine* getEngine() { return engine_.get(); }

 private:
   std::unique_ptr<Engine> engine_;  // Pointer-to-implementation (pimpl)
};


//---- <ElectricCar.h> ----------------------------------------------------------------------------

//#include <Car.h>

class ElectricCar : public Car
{
 public:
   ElectricCar( std::unique_ptr<Engine> engine );

   void drive();
   // ...

 private:
   // ...
};


//---- <ElectricCar.cpp> --------------------------------------------------------------------------

//#include <ElectricCar.h>

ElectricCar::ElectricCar( std::unique_ptr<Engine> engine )
   : Car{ std::move(engine) }
{}

void ElectricCar::drive()
{
   getEngine()->start();
   std::cout << "Driving the 'ElectricCar'...\n";
   getEngine()->stop();
}


//---- <ElectricEngine.h> -------------------------------------------------------------------------

//#include <Engine.h>

class ElectricEngine : public Engine
{
 public:
   void start() override;
   void stop() override;

 private:
   // ...
};


//---- <ElectricEngine.cpp> -----------------------------------------------------------------------

//#include <ElectricEngine.h>

void ElectricEngine::start()
{
   std::cout << "Starting the 'ElectricEngine'...\n";
}

void ElectricEngine::stop()
{
   std::cout << "Stopping the 'ElectricEngine'...\n";
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <ElectricEngine.h>
//#include <ElectricCar.h>

int main()
{
   ElectricCar ecar{ std::make_unique<ElectricEngine>() };
   ecar.drive();

   return EXIT_SUCCESS;
}
