/**************************************************************************************************
*
* \file Decorator_Creature.cpp
* \brief C++ Training - Programming Task for the Decorator Design Pattern
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Help the knight 'Roland' to win against the dragon 'Darksmoke' by conjuring helpful
*         magical equipment (e.g. 'IceSword', 'ShoesOfAgility', 'StrengthEnchantment', or
*         'MagicShackles').
*
* Step 2: Refactor the classic Decorator solution by a value semantics based solution. Note that
*         the general behavior should remain unchanged.
*
* Step 3: Discuss the interface segregation of the 'Creature' class: what would be the benefits
*         and drawbacks of separating the 'attack()', 'defense()', and 'speed()' functions?
*
**************************************************************************************************/


//---- <Stats.h> ----------------------------------------------------------------------------------

#include <ostream>

struct Attack
{
   int value;

   operator int() const { return value; }

   friend std::ostream& operator<<( std::ostream& os, Attack attack )
   {
      return os << attack.value;
   }
};

struct Defense
{
   int value;

   operator int() const { return value; }

   friend std::ostream& operator<<( std::ostream& os, Defense defense )
   {
      return os << defense.value;
   }
};

struct Speed
{
   int value;

   operator int() const { return value; }

   friend std::ostream& operator<<( std::ostream& os, Speed speed )
   {
      return os << speed.value;
   }
};


//---- <Creature.h> -------------------------------------------------------------------------------

#include <ostream>
#include <string_view>

class Creature
{
 public:
   virtual ~Creature() = default;

   virtual std::string_view name() const = 0;

   virtual Attack  attack() const = 0;
   virtual Defense defense() const = 0;
   virtual Speed   speed() const = 0;
};

std::ostream& operator<<( std::ostream& os, Creature const& creature );


//---- <Creature.cpp> -----------------------------------------------------------------------------

//#include <Creature.h>

std::ostream& operator<<( std::ostream& os, Creature const& creature )
{
   return os << creature.name()
             << " (attack: " << creature.attack()
             << ", defense: " << creature.defense()
             << ", speed: " << creature.speed()
             << ')';
}


//---- <WhiteKnight.h> ----------------------------------------------------------------------------

//#include <Creature.h>
#include <string>

class WhiteKnight
   : public Creature
{
 public:
   explicit WhiteKnight( std::string name )
      : name_{ std::move(name) }
   {}

   std::string_view name() const override { return name_; }

   Attack  attack () const override { return Attack{2}; }
   Defense defense() const override { return Defense{2}; }
   Speed   speed  () const override { return Speed{2}; }

 private:
   std::string name_;
};


//---- <Goblin.h> ---------------------------------------------------------------------------------

//#include <Creature.h>
#include <string>

class Goblin
   : public Creature
{
 public:
   explicit Goblin( std::string name )
      : name_{ std::move(name) }
   {}

   std::string_view name() const override { return name_; }

   Attack  attack () const override { return Attack{1}; }
   Defense defense() const override { return Defense{1}; }
   Speed   speed  () const override { return Speed{1}; }

 private:
   std::string name_;
};


//---- <Dragon.h> ---------------------------------------------------------------------------------

//#include <Creature.h>
#include <string>

class Dragon
   : public Creature
{
 public:
   explicit Dragon( std::string name )
      : name_{ std::move(name) }
   {}

   std::string_view name() const override { return name_; }

   Attack  attack () const override { return Attack{6}; }
   Defense defense() const override { return Defense{4}; }
   Speed   speed  () const override { return Speed{3}; }

 private:
   std::string name_;
};


//---- <ModifiedCreature.h> -----------------------------------------------------------------------

//#include <Creature.h>
#include <memory>
#include <stdexcept>
#include <utility>

class ModifiedCreature
   : public Creature
{
 public:
   explicit ModifiedCreature( std::unique_ptr<Creature>&& creature )
      : creature_{ std::move(creature) }
   {
      if( !creature_ ) {
         throw std::invalid_argument( "Invalid creature" );
      }
   }

   std::string_view name() const override { return creature_->name(); }

   Attack  attack () const override { return creature_->attack(); }
   Defense defense() const override { return creature_->defense(); }
   Speed   speed  () const override { return creature_->speed(); }

 protected:
   Creature&       creature()       { return *creature_; }
   const Creature& creature() const { return *creature_; }

 private:
   std::unique_ptr<Creature> creature_;
};


//---- <IceSword.h> -------------------------------------------------------------------------------

//#include <ModifiedCreature.h>

class IceSword
   : public ModifiedCreature
{
 public:
   using ModifiedCreature::ModifiedCreature;

   Attack attack() const override
   {
      // TODO: Make the ice sword a stronger weapon
      return Attack{ 2 };
   }
};


//---- <ShoesOfAgility.h> -------------------------------------------------------------------------

//#include <ModifiedCreature.h>

// TODO


//---- <StrengthEnchantment.h> --------------------------------------------------------------------

//#include <ModifiedCreature.h>

// TODO


//---- <MagicShackles.h> --------------------------------------------------------------------------

//#include <ModifiedCreature.h>

// TODO


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Dragon.h>
//#include <Goblin.h>
//#include <IceSword.h>
//#include <MagicShackles.h>
//#include <ShoesOfAgility.h>
//#include <StrengthEnchantment.h>
//#include <WhiteKnight.h>
#include <iostream>

void attacks( Creature const& creature1, Creature const& creature2 )
{
   // Attack rules:
   // - creature1 attacks first;
   // - If the attack value of creature1 is higher than the defense of creature2, creature1 wins;
   // - creature2 attacks second;
   // - If the attack value of creature2 is higher than the defense of creature1, creature2 wins;

   if( creature1.attack() > creature2.defense() ) {
      std::cout << creature1.name() << " wins against " << creature2.name() << '\n';
   }
   else if( creature2.attack() > creature1.defense() ) {
      std::cout << creature2.name() << " wins against " << creature1.name() << '\n';
   }
   else {
      std::cout << "No winner in " << creature1.name() << " against " << creature2.name() << '\n';
   }
}

void fight( Creature const& creature1, Creature const& creature2 )
{
   // Fighting rules:
   // - The creature with the higher speed attacks first;
   // - If both creates have the same speed, the creature with the higher attack value attacks first;

   if( creature1.speed() > creature2.speed() )
   {
      attacks( creature1, creature2 );
   }
   else if( creature2.speed() > creature1.speed() )
   {
      attacks( creature2, creature1 );
   }
   else if( creature1.attack() > creature2.attack() )
   {
      attacks( creature1, creature2 );
   }
   else if( creature2.attack() > creature1.attack() )
   {
      attacks( creature2, creature1 );
   }
   else {
      std::cout << "No winner in " << creature1.name() << " against " << creature2.name() << '\n';
   }
}

int main()
{
   std::unique_ptr<Creature> knight =
      std::make_unique<WhiteKnight>( "Roland" );

   std::unique_ptr<Creature> goblin =
      std::make_unique<Goblin>( "Zoz" );

   std::unique_ptr<Creature> dragon =
      std::make_unique<Dragon>( "Darksmoke" );

   std::cout << '\n'
             << *knight << '\n'
             << *goblin << '\n'
             << *dragon << '\n'
             << '\n';

   fight( *knight, *goblin );
   fight( *knight, *dragon );

   return EXIT_SUCCESS;
}

