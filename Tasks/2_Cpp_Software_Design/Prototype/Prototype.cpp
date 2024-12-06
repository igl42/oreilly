/**************************************************************************************************
*
* \file Prototype.cpp
* \brief C++ Training - Example for the Prototype Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Discuss the advantages and disadvantages of the given implementation of the classic
*       Prototype design pattern.
*
**************************************************************************************************/

#include <memory>
#include <cstdlib>
#include <iostream>


//---- <Animal.h> ---------------------------------------------------------------------------------

class Animal
{
 public:
   virtual ~Animal() = default;
   virtual void make_sound() const = 0;
   virtual std::unique_ptr<Animal> clone() const = 0;
};


//---- <Sheep.h> ----------------------------------------------------------------------------------

class Sheep : public Animal
{
 public:
   void make_sound() const override;
   std::unique_ptr<Animal> clone() const override;
};


//---- <Sheep.cpp> --------------------------------------------------------------------------------

void Sheep::make_sound() const
{
   std::cout << " Sheep::make_sound():  bark!\n";
}

std::unique_ptr<Animal> Sheep::clone() const
{
   std::cout << " Sheep::clone()\n";
   return std::make_unique<Sheep>(*this);
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   std::unique_ptr<Animal> sheep( std::make_unique<Sheep>() );
   sheep->make_sound();

   std::unique_ptr<Animal> cloned_sheep( sheep->clone() );
   cloned_sheep->make_sound();

   return EXIT_SUCCESS;
}
