/**************************************************************************************************
*
* \file Animal_EP.cpp
* \brief C++ Training - Programming Task for the External Polymorphism Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Create an external hierarchy for animals that represents the polymorphic behavior
*       of animals.
*
**************************************************************************************************/


//---- <Dog.h> ------------------------------------------------------------------------------------

#include <iostream>
#include <string>

class Dog
{
 public:
   explicit Dog( std::string name ) : name_{ std::move(name) } {}

   std::string const& name() const { return name_; }
   void wagTail() const { std::cout << name_ << ": wagging its tail\n"; }

 private:
   std::string name_;
};


//---- <Cat.h> ------------------------------------------------------------------------------------

#include <iostream>
#include <string>

class Cat
{
 public:
   explicit Cat( std::string name ) : name_{ std::move(name) } {}

   std::string const& name() const { return name_; }
   void purr() const { std::cout << name_ << ": purring\n"; }

 private:
   std::string name_;
};


//---- <Sheep.h> ----------------------------------------------------------------------------------

#include <iostream>
#include <string>

class Sheep
{
 public:
   explicit Sheep( std::string name ) : name_{ std::move(name) } {}

   std::string const& name() const { return name_; }
   void shear() const { std::cout << name_ << " is shorn\n"; }

 private:
   std::string name_;
};


//---- <AnimalConcept.h> --------------------------------------------------------------------------

// TODO: Create an external hierarchy for animals that represents the polymorphic behavior
//       of animals.

class AnimalConcept
{};


//---- <Animals.h> --------------------------------------------------------------------------------

//#include <AnimalConcept.h>
#include <memory>
#include <vector>

using Animals = std::vector< std::unique_ptr<AnimalConcept> >;


//---- <MakeSound.h> ------------------------------------------------------------------------------

//#include <Dog.h>
//#include <Cat.h>
//#include <Sheep.h>
#include <iostream>

void free_make_sound( Dog const& d ) { std::cout << d.name() << ": bark!\n"; }
void free_make_sound( Cat const& c ) { std::cout << c.name() << ": meow!\n"; }
void free_make_sound( Sheep const& s ) { std::cout << s.name() << ": baa!\n"; }


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Dog.h>
//#include <Cat.h>
//#include <Sheep.h>
//#include <Animals.h>
//#include <MakeSound.h>
#include <cstdlib>

int main()
{
   /*
   Animals animals{};

   animals.emplace_back( std::make_unique<AnimalModel<Dog>>( Dog{ "Lassie" } ) );
   animals.emplace_back( std::make_unique<AnimalModel<Cat>>( Cat{ "Garfield" } ) );
   animals.emplace_back( std::make_unique<AnimalModel<Sheep>>( Sheep{ "Dolly" } ) );

   for( auto const& animal : animals ) {
      animal->make_sound();
   }
   */

   return EXIT_SUCCESS;
}
