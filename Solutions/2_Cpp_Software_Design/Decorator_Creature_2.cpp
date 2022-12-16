/**************************************************************************************************
*
* \file Decorator_Creature_2.cpp
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

//#include <Stats.h>
#include <memory>
#include <ostream>
#include <string_view>

class Creature
{
 public:
   template< typename CreatureT >
   Creature( CreatureT creature )
      : pimpl_( std::make_unique<Model<CreatureT>>( std::move(creature) ) )
   {}

   Creature( const Creature& other ) : pimpl_( other.pimpl_->clone() ) {}
   Creature( Creature&& ) = default;

   ~Creature() = default;

   Creature& operator=( const Creature& other ) { pimpl_ = other.pimpl_->clone(); return *this; }
   Creature& operator=( Creature&& ) = default;

   std::string_view name() const { return pimpl_->name(); }
   Attack attack() const { return pimpl_->attack(); }
   Defense defense() const { return pimpl_->defense(); }
   Speed speed() const { return pimpl_->speed(); }

 private:
   struct Concept
   {
      virtual ~Concept() = default;
      virtual std::string_view name() const = 0;
      virtual Attack attack() const = 0;
      virtual Defense defense() const = 0;
      virtual Speed speed() const = 0;
      virtual std::unique_ptr<Concept> clone() const = 0;
   };

   template< typename CreatureT >
   struct Model final : public Concept
   {
      explicit Model( CreatureT creature ) : creature_( std::move(creature) ) {}
      std::string_view name() const final { return creature_.name(); }
      Attack attack() const final { return creature_.attack(); }
      Defense defense() const final { return creature_.defense(); }
      Speed speed() const final { return creature_.speed(); }
      std::unique_ptr<Concept> clone() const final { return std::make_unique<Model<CreatureT>>(*this); }
      CreatureT creature_;
   };

   std::unique_ptr<Concept> pimpl_;
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

//#include <Stats.h>
#include <string>
#include <string_view>

class WhiteKnight
{
 public:
   explicit WhiteKnight( std::string name )
      : name_{ std::move(name) }
   {}

   std::string_view name() const { return name_; }

   Attack  attack () const { return Attack{2}; }
   Defense defense() const { return Defense{2}; }
   Speed   speed  () const { return Speed{2}; }

 private:
   std::string name_;
};


//---- <Goblin.h> ---------------------------------------------------------------------------------

//#include <Stats.h>
#include <string>
#include <string_view>

class Goblin
{
 public:
   explicit Goblin( std::string name )
      : name_{ std::move(name) }
   {}

   std::string_view name() const { return name_; }

   Attack  attack () const { return Attack{1}; }
   Defense defense() const { return Defense{1}; }
   Speed   speed  () const { return Speed{1}; }

 private:
   std::string name_;
};


//---- <Dragon.h> ---------------------------------------------------------------------------------

//#include <Stats.h>
#include <string>
#include <string_view>

class Dragon
{
 public:
   explicit Dragon( std::string name )
      : name_{ std::move(name) }
   {}

   std::string_view name() const { return name_; }

   Attack  attack () const { return Attack{6}; }
   Defense defense() const { return Defense{4}; }
   Speed   speed  () const { return Speed{3}; }

 private:
   std::string name_;
};


//---- <IceSword.h> -------------------------------------------------------------------------------

//#include <Creature.h>

class IceSword
{
 public:
   explicit IceSword( Creature creature )
      : creature_( std::move(creature) )
   {}

   std::string_view name() const { return creature_.name(); }
   Attack attack() const
   {
      if( creature_.attack() > 1 ) {
         return Attack{creature_.attack() + 1};
      }
      else {
         return creature_.attack();
      }
   }
   Defense defense() const { return creature_.defense(); }
   Speed speed() const { return creature_.speed(); }

 private:
   Creature creature_;
};


//---- <ShoesOfAgility.h> -------------------------------------------------------------------------

//#include <Creature.h>

class ShoesOfAgility
{
 public:
   explicit ShoesOfAgility( Creature creature )
      : creature_( std::move(creature) )
   {}

   std::string_view name() const { return creature_.name(); }
   Attack attack() const { return creature_.attack(); }
   Defense defense() const { return creature_.defense(); }
   Speed speed() const
   {
      return Speed{ creature_.speed()+2 };
   }

 private:
   Creature creature_;
};


//---- <StrengthEnchantment.h> --------------------------------------------------------------------

//#include <Creature.h>

class StrengthEnchantment
{
 public:
   explicit StrengthEnchantment( Creature creature )
      : creature_( std::move(creature) )
   {}

   std::string_view name() const { return creature_.name(); }
   Attack attack() const
   {
      return Attack{ creature_.attack()+2 };
   }
   Defense defense() const { return creature_.defense(); }
   Speed speed() const { return creature_.speed(); }

 private:
   Creature creature_;
};


//---- <MagicShackles.h> --------------------------------------------------------------------------

//#include <Creature.h>

class MagicShackles
{
 public:
   explicit MagicShackles( Creature creature )
      : creature_( std::move(creature) )
   {}

   std::string_view name() const { return creature_.name(); }
   Attack attack() const { return creature_.attack(); }
   Defense defense() const { return creature_.defense(); }
   Speed speed() const
   {
      return Speed{0};
   }

 private:
   Creature creature_;
};


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
   Creature knight =
      StrengthEnchantment(
         ShoesOfAgility(
            IceSword(
               WhiteKnight( "Roland" )
            )
         )
      );

   Creature goblin =
      Goblin( "Zoz" );

   Creature dragon =
      MagicShackles(
         Dragon( "Darksmoke" )
      );

   std::cout << '\n'
             << knight << '\n'
             << goblin << '\n'
             << dragon << '\n'
             << '\n';

   fight( knight, goblin );
   fight( knight, dragon );

   return EXIT_SUCCESS;
}

