/**************************************************************************************************
*
* \file Decorator_Item_2.cpp
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

class Item;


std::true_type isItem( const volatile Item* );

std::false_type isItem( ... );

template< typename T >
struct IsItem
   : public decltype( isItem( std::declval<T*>() ) )
{};

template< typename T >
struct IsItem<T&>
   : public std::false_type
{};

template< typename T >
constexpr bool IsItem_v = IsItem<T>::value;


class Item
{
 public:
   template< typename T >
   using enable_if_not_is_item = std::enable_if_t< !IsItem_v<T>, bool >;

   template< typename T, enable_if_not_is_item<T> = true >
   Item( T&& item )
      : pimpl_( std::make_unique<Model<std::remove_reference_t<T>>>( std::forward<T>(item) ) )
   {}

   Item( const Item& item ) : pimpl_( item.pimpl_->clone() ) {}
   Item( Item&& ) = default;

   ~Item() = default;

   Item& operator=( const Item& item ) { pimpl_ = item.pimpl_->clone(); return *this; }
   Item& operator=( Item&& ) = default;

   Money price() const { return pimpl_->price(); }

 private:
   struct Concept
   {
      virtual ~Concept() = default;
      virtual Money price() const = 0;
      virtual std::unique_ptr<Concept> clone() const = 0;
   };

   template< typename T >
   struct Model final : public Concept
   {
      explicit Model( const T& item ) : item_( item ) {}
      explicit Model( T&& item ) : item_( std::move(item) ) {}
      Money price() const final { return item_.price(); }
      std::unique_ptr<Concept> clone() const final { return std::make_unique<Model<T>>(*this); }
      T item_;
   };

   std::unique_ptr<Concept> pimpl_;
};


//---- <ConferenceTicket.h> --------------------------------------------------------------------------

class ConferenceTicket
{
 public:
   ConferenceTicket( std::string name, Money price )
      : name_{ std::move(name) }
      , price_{ price }
   {}

   const std::string& name() const noexcept {
      return name_;
   }

   Money price() const noexcept {
      return price_;
   }

 private:
   std::string name_{};
   Money price_{};
};


//---- <CppBook.h> --------------------------------------------------------------------------------

class CppBook
{
 public:
   CppBook( std::string title, Money price )
      : title_{ std::move(title) }
      , price_{ price }
   {}

   const std::string& title() const noexcept {
      return title_;
   }

   Money price() const noexcept {
      return price_;
   }

 private:
   std::string title_{};
   Money price_{};
};


//---- <Discounted.h> -----------------------------------------------------------------------------

class Discounted
{
 public:
   Discounted( Item item, double discount )
      : item_( std::move(item) )
      , factor_( 1.0 - discount )
   {
      if( !std::isfinite(discount) || discount < 0.0 || discount > 1.0 ) {
         throw std::invalid_argument( "Invalid discount value" );
      }
   }

   Money price() const {
      return item_.price() * factor_;
   }

 private:
   Item item_;
   double factor_;
};


//---- <Taxed.h> ----------------------------------------------------------------------------------

class Taxed
{
 public:
   Taxed( Item item, double tax )
      : item_( std::move(item) )
      , factor_( 1.0 + tax )
   {
      if( !std::isfinite(tax) || tax < 0.0 ) {
         throw std::invalid_argument( "Invalid tax value" );
      }
   }

   Money price() const {
      return item_.price() * factor_;
   }

 private:
   Item item_;
   double factor_;
};


//---- <QuantityDiscounted.h> ---------------------------------------------------------------------

class QuantityDiscounted
{
 public:
   QuantityDiscounted( Item item, size_t count )
      : item_{ item }
      , count_{ count }
   {}

   Money price() const {
      return item_.price() * count_ * ( 1.0-discount() );
   }

 private:
   double discount() const
   {
      if     ( count_ >  4U ) return 0.25;
      else if( count_ == 4U ) return 0.2;
      else if( count_ == 3U ) return 0.15;
      else if( count_ == 2U ) return 0.1;
      else                    return 0.0;
   }

   Item item_;
   size_t count_{};
};


//---- <ShoppingCart.h> ---------------------------------------------------------------------------

class ShoppingCart
{
 public:
   template< typename... Items >
   ShoppingCart( Items&&... items )
      : items_{}
   {
      ( items_.push_back( std::forward<Items>(items) ), ... );
   }

   Money price() const {
      const Money sum =
         std::accumulate( begin(items_), end(items_), Money{}
                        , []( Money accu, const auto& item ){ return accu + item.price(); } );
      return sum * ( 1.0-discount() );
   }

 private:
   double discount() const
   {
      if     ( items_.size() >  4U ) return 0.25;
      else if( items_.size() == 4U ) return 0.2;
      else if( items_.size() == 3U ) return 0.15;
      else if( items_.size() == 2U ) return 0.1;
      else                           return 0.0;
   }

   std::vector<Item> items_;
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   Item item1( Taxed( Discounted( ConferenceTicket{ "CppCon", Money{999} }, 0.2 ), 0.19 ) );
   Item item2( Taxed( QuantityDiscounted( CppBook{ "Effective C++", Money{19} }, 5 ), 0.07 ) );

   Item item3( ShoppingCart( item1, item2 ) );

   std::cout << "\n"
             << " Total price of item1 = " << item1.price() << "\n"
             << " Total price of item2 = " << item2.price() << "\n"
             << " Total price of item3 = " << item3.price() << "\n"
             << "\n";

   return EXIT_SUCCESS;
}

