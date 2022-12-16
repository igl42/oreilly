/**************************************************************************************************
*
* \file Decorator_Item.cpp
* \brief C++ Training - Programming Task for the Decorator Design Pattern
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Introduce a quantity discount and a shopping cart (2 items: 10%, 3 items: 15%,
*         4 items: 20%, more than four items: 25%).
*
* Step 2: Refactor the classic Decorator solution by a value semantics based solution. Note that
*         the general behavior should remain unchanged.
*
**************************************************************************************************/

#include <cmath>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <numeric>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>


//---- <Money.h> --------------------------------------------------------------------------------

struct Money
{
   uint64_t value{};
};

template< typename T, std::enable_if< std::is_arithmetic<T>::value >* = nullptr >
//template< std::arithmetic T >  // C++20 concept
Money operator*( Money money, T factor )
{
   return Money{ static_cast<uint64_t>( money.value * factor ) };
}

constexpr Money operator+( Money lhs, Money rhs ) noexcept
{
   return Money{ lhs.value + rhs.value };
}

std::ostream& operator<<( std::ostream& os, Money money )
{
   return os << money.value;
}


//---- <Item.h> -----------------------------------------------------------------------------------

class Item
{
 public:
   virtual ~Item() = default;
   virtual Money price() const = 0;
};


//---- <DecoratedItem.h> --------------------------------------------------------------------------

class DecoratedItem
   : public Item
{
 public:
   explicit DecoratedItem( std::unique_ptr<Item>&& item )
      : item_( std::move(item) )
   {
      if( !item_ ) {
         throw std::invalid_argument( "Invalid item" );
      }
   }

 protected:
   Item&       item()       { return *item_; }
   const Item& item() const { return *item_; }

 private:
   std::unique_ptr<Item> item_;  // Core Guideline C.133: Avoid protected data
};


//---- <ConferenceTicket.h> --------------------------------------------------------------------------

class ConferenceTicket
   : public Item
{
 public:
   ConferenceTicket( std::string name, Money price )
      : name_{ std::move(name) }
      , price_{ price }
   {}

   const std::string& name() const noexcept {
      return name_;
   }

   Money price() const noexcept override {
      return price_;
   }

 private:
   std::string name_{};
   Money price_{};
};


//---- <CppBook.h> --------------------------------------------------------------------------------

class CppBook
   : public Item
{
 public:
   CppBook( std::string title, Money price )
      : title_{ std::move(title) }
      , price_{ price }
   {}

   const std::string& title() const noexcept {
      return title_;
   }

   Money price() const noexcept override {
      return price_;
   }

 private:
   std::string title_{};
   Money price_{};
};


//---- <Discounted.h> -----------------------------------------------------------------------------

class Discounted
   : public DecoratedItem
{
 public:
   Discounted( std::unique_ptr<Item>&& item, double discount )
      : DecoratedItem( std::move(item) )
      , factor_( 1.0 - discount )
   {
      if( !std::isfinite(discount) || discount < 0.0 || discount > 1.0 ) {
         throw std::invalid_argument( "Invalid discount value" );
      }
   }

   Money price() const override {
      return item().price() * factor_;
   }

 private:
   double factor_;
};


//---- <Taxed.h> ----------------------------------------------------------------------------------

class Taxed
   : public DecoratedItem
{
 public:
   Taxed( std::unique_ptr<Item>&& item, double tax )
      : DecoratedItem( std::move(item) )
      , factor_( 1.0 + tax )
   {
      if( !std::isfinite(tax) || tax < 0.0 ) {
         throw std::invalid_argument( "Invalid tax value" );
      }
   }

   Money price() const override {
      return item().price() * factor_;
   }

 private:
   double factor_;
};


//---- <QuantityDiscounted.h> ---------------------------------------------------------------------

class QuantityDiscounted
{
   // TODO: Introduce a quantity discount for an item that is selected multiple times
   //       (2 items: 10%, 3 items: 15%, 4 items: 20%, more than four items: 25%).
};


//---- <ShoppingCart.h> ---------------------------------------------------------------------------

class ShoppingCart
{
   // TODO: Introduce a discount for different items put into a shopping basket
   //       (2 items: 10%, 3 items: 15%, 4 items: 20%, more than four items: 25%).
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   std::unique_ptr<Item> item1(
      std::make_unique<Taxed>(
         std::make_unique<Discounted>(
            std::make_unique<ConferenceTicket>( "CppCon", Money{999} ),
            0.2 ),
         0.19 ) );

   std::unique_ptr<Item> item2(
      std::make_unique<Taxed>(
         std::make_unique<CppBook>( "Effective C++", Money{19} ),
         0.07 ) );

   std::cout << "\n"
             << " Total price of item1 = " << item1->price() << "\n"
             << " Total price of item2 = " << item2->price() << "\n"
             << "\n";

   return EXIT_SUCCESS;
}

