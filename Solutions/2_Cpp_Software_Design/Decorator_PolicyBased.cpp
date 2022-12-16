/**************************************************************************************************
*
* \file Decorator_PolicyBased.cpp
* \brief C++ Training - Programming Task for the Decorator Design Pattern
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Refactor the classic Decorator solution by a value semantics based solution. Note that
*       the general behavior should remain unchanged.
*
**************************************************************************************************/

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <type_traits>


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
   return os << std::fixed << std::setprecision(2) << money.value;
}


//---- <StoragePolicies.h> ------------------------------------------------------------------------

struct DynamicStorage
{
   template< typename T, typename... Args >
   T* create( Args&&... args ) const
   {
      return new T( std::forward<Args>( args )... );
   }

   template< typename T >
   void destroy( T* ptr ) const noexcept
   {
      delete ptr;
   }
};

template< size_t Capacity, size_t Alignment >
struct StaticStorage
{
   template< typename T, typename... Args >
   T* create( Args&&... args ) const
   {
      static_assert( sizeof(T) <= Capacity, "The given type is too large" );
      static_assert( alignof(T) <= Alignment, "The alignment requirements of the given type are not satisfied" );
      return new (static_cast<void*>(buffer_)) T( std::forward<Args>( args )... );
   }

   template< typename T >
   void destroy( T* ptr ) const noexcept
   {
      ptr->~T();
   }

   alignas(Alignment) std::byte buffer_[Capacity];
};



//---- <NoUniqueAddress.h> ------------------------------------------------------------------------

#if ( defined(__GNUC__) && __GNUC__ >= 9 ) || ( defined(__clang__) && !defined(__apple_build_version__) && __clang_major__ >= 9 )
#  define NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#  define NO_UNIQUE_ADDRESS
#endif


//---- <Item.h> -----------------------------------------------------------------------------------

template< typename StoragePolicy >
class Item;


template< typename StoragePolicy >
std::true_type isItem( const volatile Item<StoragePolicy>* );

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


template< typename StoragePolicy >
class Item
{
 public:
   template< typename T >
   using enable_if_not_is_item = std::enable_if_t< !IsItem_v<T>, bool >;

   template< typename T, enable_if_not_is_item<T> = true >
   Item( T&& item ) : pimpl_( policy_.template create<Model<T>>( std::forward<T>(item) ) ) {}

   Item( const Item& item ) : pimpl_( item.pimpl_->clone( policy_ ) ) {}
   Item( Item&& item ) : pimpl_( item.pimpl_->move( policy_ ) ) {}

   ~Item() { policy_.destroy( pimpl_ ); }

   Item& operator=( const Item& item )
   {
      policy_.destroy( pimpl_ );
      pimpl_ = item.pimpl_->clone( policy_ );
      return *this;
   }

   Item& operator=( Item&& item )
   {
      policy_.destroy( pimpl_ );
      pimpl_ = item.pimpl_->move( policy_ );
      return *this;
   }

   Money price() const { return pimpl_->price(); }

 private:
   struct Concept
   {
      virtual ~Concept() = default;
      virtual Money price() const = 0;
      virtual Concept* clone( const StoragePolicy& ) const = 0;
      virtual Concept* move( const StoragePolicy& ) const = 0;
   };

   template< typename T >
   struct Model final : public Concept
   {
      explicit Model( const T& item ) : item_( item ) {}
      explicit Model( T&& item ) : item_( std::move(item) ) {}
      Money price() const final { return item_.price(); }
      Concept* clone( const StoragePolicy& policy ) const final { return policy.template create<Model>(*this); }
      Concept* move( const StoragePolicy& policy ) const final { return policy.template create<Model>( std::move(*this) ); }
      T item_;
   };

   NO_UNIQUE_ADDRESS StoragePolicy policy_{};
   Concept* pimpl_{};
};

using DynamicItem = Item<DynamicStorage>;
using StaticItem  = Item<StaticStorage<40UL,8UL>>;


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
   Discounted( DynamicItem item, double discount )
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
   DynamicItem item_;
   double factor_;
};


//---- <Taxed.h> ----------------------------------------------------------------------------------

class Taxed
{
 public:
   Taxed( DynamicItem item, double tax )
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
   DynamicItem item_;
   double factor_;
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   DynamicItem item1( Taxed( Discounted( ConferenceTicket{ "CppCon", Money{999} }, 0.2 ), 0.19 ) );
   DynamicItem item2( Taxed( CppBook{ "Effective C++", Money{19} }, 0.07 ) );

   std::cout << "\n"
             << " Total price of item1 = " << item1.price() << "\n"
             << " Total price of item2 = " << item2.price() << "\n"
             << "\n";

   return EXIT_SUCCESS;
}

