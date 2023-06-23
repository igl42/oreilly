/**************************************************************************************************
*
* \file ExternalAnimal.cpp
* \brief C++ Training - Programming Task for the External Polymorphism Design Pattern
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Create an external hierarchy for animals that represents the polymorphic behavior
*       of animals.
*
**************************************************************************************************/


//---- <Animal.h> ---------------------------------------------------------------------------------

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

class Cat
{
 public:
   explicit Cat( std::string name ) : name_{ std::move(name) } {}

   std::string const& name() const { return name_; }
   void purr() const { std::cout << name_ << ": purring\n"; }

 private:
   std::string name_;
};

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

class AnimalConcept
{
 public:
   virtual ~AnimalConcept() = default;
   virtual void makeSound() const = 0;
};

template< typename AnimalT >
class AnimalModel final : public AnimalConcept
{
 public:
   explicit AnimalModel( AnimalT animal )
      : animal_( animal )
   {}

   void makeSound() const final { free_makeSound( animal_ ); }

 private:
   AnimalT animal_;
};


//---- <Animals.h> --------------------------------------------------------------------------------

//#include <AnimalConcept.h>
#include <memory>
#include <vector>

using Animals = std::vector< std::unique_ptr<AnimalConcept> >;


//---- <MakeSound.h> ------------------------------------------------------------------------------

//#include <Animals.h>
#include <iostream>

void free_makeSound( Dog const& d ) { std::cout << d.name() << ": bark!\n"; }
void free_makeSound( Cat const& c ) { std::cout << c.name() << ": meow!\n"; }
void free_makeSound( Sheep const& s ) { std::cout << s.name() << ": baa!\n"; }


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Animal.h>
//#include <Animals.h>
//#include <MakeSound.h>
#include <cstdlib>

int main()
{
   Animals animals{};

   animals.emplace_back( std::make_unique<AnimalModel<Dog>>( Dog{ "Lassy" } ) );
   animals.emplace_back( std::make_unique<AnimalModel<Cat>>( Cat{ "Garfield" } ) );
   animals.emplace_back( std::make_unique<AnimalModel<Sheep>>( Sheep{ "Dolly" } ) );

   for( auto const& animal : animals ) {
      animal->makeSound();
   }

   return EXIT_SUCCESS;
}
