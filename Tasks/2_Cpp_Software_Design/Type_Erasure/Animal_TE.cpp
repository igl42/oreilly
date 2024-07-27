/**************************************************************************************************
*
* \file Animal_TE.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Encapsulate the external 'AnimalConcept' hierarchy in an owning Type Erasure wrapper
*         and refactor the given solution into a value-based solution.
*
* Step 2: Provide a non-owning Type Erasure wrapper that does not allocate dynamically and that
*         does not create a copy of the given animal.
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
   void wag_tail() const { std::cout << name_ << ": wagging its tail\n"; }

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


//---- <Animal.h> ---------------------------------------------------------------------------------

// Step 1: Encapsulate the external 'AnimalConcept' hierarchy in an owning Type Erasure wrapper
//         and refactor the given solution into a value-based solution.

class AnimalConcept
{
 public:
   virtual ~AnimalConcept() = default;
   virtual void make_sound() const = 0;
};

template< typename AnimalT >
class AnimalModel final : public AnimalConcept
{
 public:
   explicit AnimalModel( AnimalT animal )
      : animal_( animal )
   {}

   void make_sound() const final { free_make_sound( animal_ ); }

 private:
   AnimalT animal_;
};


// Step 2: Provide a non-owning Type Erasure wrapper that does not allocate dynamically and that
//         does not create a copy of the given animal.

class AnimalView
{
 public:
   // Step 2: TODO
};


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

// For a list of animal sounds, see https://en.wikipedia.org/wiki/List_of_animal_sounds

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

void let_animal_make_sound( AnimalView animal )
{
   // Step 2: TODO
}

int main()
{
   // Step 1: Encapsulate the external 'AnimalConcept' hierarchy in an owning Type Erasure
   //         wrapper and refactor the given solution into a value-based solution.
   {
      Animals animals{};

      animals.emplace_back( std::make_unique<AnimalModel<Dog>>( Dog{ "Lassie" } ) );
      animals.emplace_back( std::make_unique<AnimalModel<Cat>>( Cat{ "Garfield" } ) );
      animals.emplace_back( std::make_unique<AnimalModel<Sheep>>( Sheep{ "Dolly" } ) );

      for( auto const& animal : animals ) {
         animal->make_sound();
      }
   }

   // Step 2: Provide a non-owning Type Erasure wrapper that does not allocate dynamically
   //         and that does not create a copy of the given animal.
   /*
   {
      Dog dog{ "Lassie" };
      Cat cat{ "Garfield" };
      Sheep sheep{ "Dolly" };

      let_animal_make_sound( dog );
      let_animal_make_sound( cat );
      let_animal_make_sound( sheep );
   }
   */

   return EXIT_SUCCESS;
}
