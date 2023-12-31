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
* Task: Encapsulate the external 'AnimalConcept' hierarchy in a Type Erasure wrapper and
*       refactor the given solution into a value-based solution.
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

#include <memory>

class Animal
{
 public:
   template< typename AnimalT >
   Animal( AnimalT const& animal )
      : pimpl_{ std::make_unique<Model<AnimalT>>( animal ) }
   {}

 private:
   friend void free_make_sound( Animal const& animal )
   {
      animal.pimpl_->make_sound();
   }

   class Concept
   {
    public:
      virtual ~Concept() = default;
      virtual void make_sound() const = 0;
   };

   template< typename AnimalT >
   class Model final : public Concept
   {
    public:
      explicit Model( AnimalT animal )
         : animal_( animal )
      {}

      void make_sound() const final { free_make_sound( animal_ ); }

    private:
      AnimalT animal_;
   };

   std::unique_ptr<Concept> pimpl_;
};


//---- <Animals.h> --------------------------------------------------------------------------------

//#include <AnimalConcept.h>
#include <memory>
#include <vector>

using Animals = std::vector<Animal>;


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
   Animals animals{};

   animals.emplace_back( Dog{ "Lassie" } );
   animals.emplace_back( Cat{ "Garfield" } );
   animals.emplace_back( Sheep{ "Dolly" } );

   for( auto const& animal : animals ) {
      free_make_sound( animal );
   }

   return EXIT_SUCCESS;
}
