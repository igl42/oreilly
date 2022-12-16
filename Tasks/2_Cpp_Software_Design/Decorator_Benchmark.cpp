/**************************************************************************************************
*
* \file Decorator_Benchmark.cpp
* \brief C++ Training - Programming Task for the Decorator Design Pattern
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Copy-and-paste the following code into 'quick-bench.com'. Benchmark the time to compute
*       the total price of a given number of items.
*
**************************************************************************************************/

#include <cassert>
#include <chrono>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <random>
#include <string>
#include <type_traits>
#include <vector>


//---- Benchmark configuration --------------------------------------------------------------------

constexpr size_t N( 10000 );  // Number of generated items
constexpr size_t iterations( 5000 );  // Number of benchmark iterations

#define BENCHMARK_CLASSIC_SOLUTION 1
#define BENCHMARK_TYPE_ERASURE_SOLUTION 1
#define BENCHMARK_COMPILE_TIME_SOLUTION 0


//---- Random Number Setup ------------------------------------------------------------------------

std::random_device rd{};
const unsigned int seed( rd() );

std::mt19937 rng{};
std::uniform_real_distribution<double> dist( 0.0, 1.0 );
std::uniform_real_distribution<double> ticket_dist( 500, 1200 );
std::uniform_real_distribution<double> book_dist( 5.0, 35.0 );


//---- Money Implementation ---------------------------------------------------------------------

struct Money
{
   uint64_t value{};
};

Money& operator+=( Money& lhs, Money rhs )
{
   lhs.value += rhs.value;
   return lhs;
}

Money operator+( Money lhs, Money rhs )
{
   return Money{ lhs.value + rhs.value };
}

template< typename T, std::enable_if< std::is_arithmetic<T>::value >* = nullptr >
Money operator*( Money money, T factor )
{
   return Money{ static_cast<uint64_t>( money.value * factor ) };
}

std::ostream& operator<<( std::ostream& os, Money money )
{
   return os << money.value;
}


//---- BENCHMARK_CLASSIC_SOLUTION -----------------------------------------------------------------

#if BENCHMARK_CLASSIC_SOLUTION
namespace classic_solution {

   class Item
   {
    public:
      virtual ~Item() = default;
      virtual Money price() const = 0;
   };


   class ConferenceTicket : public Item
   {
    public:
      ConferenceTicket( std::string name, Money price )
         : name_{ std::move(name) }
         , price_{ price }
      {}

      std::string const& name() const noexcept { return name_; }
      Money price() const noexcept override { return price_; }

    private:
      std::string name_;
      Money price_{};
   };


   class CppBook : public Item
   {
    public:
      CppBook( std::string title, Money price )
         : title_{ std::move(title) }
         , price_{ price }
      {}

      std::string const& title() const noexcept { return title_; }
      Money price() const noexcept override { return price_; }

    private:
      std::string title_;
      Money price_{};
   };


   class Discounted : public Item
   {
    public:
      Discounted( std::unique_ptr<Item>&& item, double discount )
         : item_( std::move(item) )
         , factor_( 1.0 - discount )
      {}

      Money price() const override {
         return item_->price() * factor_;
      }

    private:
      std::unique_ptr<Item> item_;
      double factor_{};
   };


   class Taxed : public Item
   {
    public:
      Taxed( std::unique_ptr<Item>&& item, double tax )
         : item_( std::move(item) )
         , factor_( 1.0 + tax )
      {}

      Money price() const override {
         return item_->price() * factor_;
      }

    private:
      std::unique_ptr<Item> item_;
      double factor_{};
   };

} // namespace classic_solution

static void computeClassicSolution(benchmark::State& state)
{
   using namespace classic_solution;

   rng.seed( seed );

   std::vector<std::unique_ptr<Item>> items;

   for( size_t i=0UL; i<N; ++i ) {
      const double rand = dist( rng );
      if( rand < 0.25 ) {
         items.push_back( std::make_unique<Taxed>(
                             std::make_unique<Discounted>(
                                std::make_unique<ConferenceTicket>( "CppCon", Money{ticket_dist(rng)} ),
                                0.2 ),
                             0.19 ) );
      }
      else if( rand < 0.5 ) {
         items.push_back( std::make_unique<Taxed>(
                             std::make_unique<ConferenceTicket>( "CppCon", Money{ticket_dist(rng)} ),
                             0.19 ) );
      }
      else if( rand < 0.75 ) {
         items.push_back( std::make_unique<Taxed>(
                             std::make_unique<Discounted>(
                                std::make_unique<CppBook>( "Effective C++", Money{book_dist(rng)} ),
                                0.2 ),
                             0.07 ) );
      }
      else {
         items.push_back( std::make_unique<Taxed>(
                             std::make_unique<CppBook>( "Effective C++", Money{book_dist(rng)} ),
                             0.07 ) );
      }
   }

   for( auto _ : state )
   {
      benchmark::DoNotOptimize(
         std::accumulate( items.begin(), items.end(), Money{},
            []( Money accu, const auto& item ) {
               return accu + item->price();
            } )
      );
   }
}
BENCHMARK(computeClassicSolution)->Iterations(iterations);
#endif


//---- BENCHMARK_TYPE_ERASURE_SOLUTION ------------------------------------------------------------

#if BENCHMARK_TYPE_ERASURE_SOLUTION
namespace type_erasure_solution {

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
      Item( T&& item ) : pimpl_( std::make_unique<Model<T>>( std::forward<T>(item) ) ) {}

      Item( const Item& item ) : pimpl_( item.pimpl_->clone() ) {}
      Item( Item&& ) = default;

      ~Item() = default;

      Item& operator=( const Item& item ) { pimpl_ = item.pimpl_->clone(); return *this; }
      Item& operator=( Item&& item ) = default;

      Money price() const { return pimpl_->price(); }

    private:
      struct Concept
      {
         virtual ~Concept() = default;
         virtual Money price() const = 0;
         virtual std::unique_ptr<Concept> clone() const = 0;
      };

      template< typename T >
      struct Model : public Concept
      {
         explicit Model( const T& item ) : item_( item ) {}
         explicit Model( T&& item ) : item_( std::move(item) ) {}
         Money price() const override { return item_.price(); }
         std::unique_ptr<Concept> clone() const override { return std::make_unique<Model<T>>(*this); }
         T item_;
      };

      std::unique_ptr<Concept> pimpl_;
   };


   class ConferenceTicket
   {
    public:
      ConferenceTicket( std::string name, Money price )
         : name_{ std::move(name) }
         , price_{ price }
      {}

      std::string const& name() const noexcept { return name_; }
      Money price() const noexcept { return price_; }

    private:
      std::string name_;
      Money price_{};
   };


   class CppBook
   {
    public:
      CppBook( std::string title, Money price )
         : title_{ std::move(title) }
         , price_{ price }
      {}

      std::string const& title() const noexcept { return title_; }
      Money price() const noexcept { return price_; }

    private:
      std::string title_;
      Money price_{};
   };


   class Discounted
   {
    public:
      Discounted( Item item, double discount )
         : item_( std::move(item) )
         , factor_( 1.0 - discount )
      {}

      Money price() const {
         return item_.price() * factor_;
      }

    private:
      Item item_;
      double factor_;
   };


   class Taxed
   {
    public:
      Taxed( Item item, double tax )
         : item_( std::move(item) )
         , factor_( 1.0 + tax )
      {}

      Money price() const {
         return item_.price() * factor_;
      }

    private:
      Item item_;
      double factor_{};
   };

} // namespace type_erasure_solution

static void computeTypeErasureSolution(benchmark::State& state)
{
   using namespace type_erasure_solution;

   rng.seed( seed );

   std::vector<Item> items;
   Money total{};

   for( size_t i=0UL; i<N; ++i ) {
      const double rand = dist( rng );
      if( rand < 0.25 ) {
         items.push_back( Taxed( Discounted( ConferenceTicket{ "CppCon", Money{ticket_dist(rng)} }, 0.2 ), 0.19 ) );
      }
      else if( rand < 0.5 ) {
         items.push_back( Taxed( ConferenceTicket{ "CppCon", Money{ticket_dist(rng)} }, 0.19 ) );
      }
      else if( rand < 0.75 ) {
         items.push_back( Taxed( Discounted( CppBook{ "Effective C++", Money{book_dist(rng)} }, 0.2 ), 0.07 ) );
      }
      else {
         items.push_back( Taxed( CppBook{ "Effective C++", Money{book_dist(rng)} }, 0.07 ) );
      }
   }

   for( auto _ : state )
   {
      benchmark::DoNotOptimize(
         std::accumulate( items.begin(), items.end(), Money{},
            []( Money accu, const auto& item ) {
               return accu + item.price();
            } )
      );
   }
}
BENCHMARK(computeTypeErasureSolution)->Iterations(iterations);
#endif


//---- BENCHMARK_COMPILE_TIME_SOLUTION ------------------------------------------------------------

#if BENCHMARK_COMPILE_TIME_SOLUTION
namespace compile_time_solution {

   template< typename T >
   concept PricedItem =
      requires ( T item ) {
         { item.price() } -> std::same_as<Money>;
      };


   class ConferenceTicket
   {
    public:
      ConferenceTicket( std::string name, Money total )
         : name_{ std::move(name) }
         , price_{ total }
      {}

      std::string const& name() const noexcept { return name_; }
      Money price() const noexcept { return price_; }

    private:
      std::string name_;
      Money price_;
   };


   class CppBook
   {
    public:
      CppBook( std::string title, Money price )
         : title_{ std::move(title) }
         , price_{ price }
      {}

      std::string const& title() const noexcept { return title_; }
      Money price() const noexcept { return price_; }

    private:
      std::string title_;
      Money price_{};
   };


   template< PricedItem Item, unsigned int discount >
   class Discounted
   {
    public:
      template< typename... Args >
      explicit Discounted( Args&&... args )
         : item_{ std::forward<Args>(args)... }
      {}

      Money price() const {
         return item_.price() * ( 1.0 - (discount/100.0) );
      }

    private:
      Item item_;
   };


   template< PricedItem Item, unsigned int tax >
   class Taxed : private Item
   {
    public:
      template< typename... Args >
      explicit Taxed( Args&&... args )
         : Item{ std::forward<Args>(args)... }
      {}

      Money price() const {
         return Item::price() * ( 1.0 + (tax/100.0) );
      }
   };

} // namespace compile_time_solution

static void computeCompileTimeSolution(benchmark::State& state)
{
   using namespace compile_time_solution;

   rng.seed( seed );

   using TaxedDiscountedConferenceTicket = Taxed<Discounted<ConferenceTicket,20U>,19U>;
   using TaxedConferenceTicket = Taxed<ConferenceTicket,19U>;
   using TaxedDiscountedCppBook = Taxed<Discounted<CppBook,20U>,7U>;
   using TaxedCppBook = Taxed<CppBook,7U>;

   std::vector<TaxedDiscountedConferenceTicket> taxed_discounted_tickets;
   std::vector<TaxedConferenceTicket> taxed_tickets;
   std::vector<TaxedDiscountedCppBook> taxed_discounted_book;
   std::vector<TaxedCppBook> taxed_books;

   for( size_t i=0UL; i<N; ++i ) {
      const double rand = dist( rng );
      if( rand < 0.25 ) {
         taxed_discounted_tickets.push_back( TaxedDiscountedConferenceTicket{ "CppCon", Money{ticket_dist(rng)} } );
      }
      else if( rand < 0.5 ) {
         taxed_tickets.push_back( TaxedConferenceTicket{ "CppCon", Money{ticket_dist(rng)} } );
      }
      else if( rand < 0.75 ) {
         taxed_discounted_book.push_back( TaxedDiscountedCppBook{ "Effective C++", Money{book_dist(rng)} } );
      }
      else {
         taxed_books.push_back( TaxedCppBook{ "Effective C++", Money{book_dist(rng)} } );
      }
   }

   for( auto _ : state )
   {
      benchmark::DoNotOptimize(
         std::accumulate( taxed_discounted_tickets.begin(), taxed_discounted_tickets.end(), Money{},
            []( Money accu, const auto& item ) { return accu + item.price(); } )
      );
      benchmark::DoNotOptimize(
         std::accumulate( taxed_tickets.begin(), taxed_tickets.end(), Money{},
            []( Money accu, const auto& item ) { return accu + item.price(); } )
      );
      benchmark::DoNotOptimize(
         std::accumulate( taxed_discounted_book.begin(), taxed_discounted_book.end(), Money{},
            []( Money accu, const auto& item ) { return accu + item.price(); } )
      );
      benchmark::DoNotOptimize(
         std::accumulate( taxed_books.begin(), taxed_books.end(), Money{},
            []( Money accu, const auto& item ) { return accu + item.price(); } )
      );
   }
}
BENCHMARK(computeCompileTimeSolution)->Iterations(iterations);
#endif

