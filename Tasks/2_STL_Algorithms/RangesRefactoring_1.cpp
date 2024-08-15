/**************************************************************************************************
*
* \file RangesRefactoring_1.cpp
* \brief C++ Training - Refactoring Task from Imperative to Declarative Code
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Understand the inner workings of the 'select_birthday_children()' function: what does
*         the function return?
*
* Step 2: Refactor the function from an imperative to a declarative stype by means of C++20
*         ranges.
*
* Step 3: Compare the runtime performance of both versions (imperative and declarative).
*
**************************************************************************************************/


//---- <ranges> -----------------------------------------------------------------------------------

#include <concepts>
#include <ranges>
#include <type_traits>

// Simplified implementation of C++23 'std::ranges::to<>()'
template< template<typename...> class C >
struct to_range
{};

template< template<typename...> class C, std::ranges::input_range R >
constexpr auto to( R&& range )
{
   using T = std::ranges::range_value_t<R>;
   static_assert( !std::is_reference_v<T> );
   return C<T>( std::ranges::begin(range), std::ranges::end(range) );
}

template< template<typename...> class C >
constexpr auto to()
{
   return to_range<C>{};
}

template< std::ranges::input_range R, template<typename...> class C >
auto operator|( R&& range, to_range<C> )
{
   return to<C>(range);
}


//---- <Date.h> -----------------------------------------------------------------------------------

#include <compare>
#include <ostream>

struct Year
{
   int value;

   std::strong_ordering operator<=>( Year const& ) const = default;

   friend std::ostream& operator<<( std::ostream& os, Year year )
   {
      return os << year.value;
   }
};


struct Month
{
   int value;

   std::strong_ordering operator<=>( Month const& ) const = default;

   friend std::ostream& operator<<( std::ostream& os, Month month )
   {
      return os << month.value;
   }
};


struct Day
{
   int value;

   std::strong_ordering operator<=>( Day const& ) const = default;

   friend std::ostream& operator<<( std::ostream& os, Day day )
   {
      return os << day.value;
   }
};


struct Date
{
   Year year;
   Month month;
   Day day;

   std::strong_ordering operator<=>( Date const& ) const = default;

   friend std::ostream& operator<<( std::ostream& os, Date const& date )
   {
      return os << date.day << '.' << date.month << '.' << date.year;
   }
};


//---- <Person.h> ---------------------------------------------------------------------------------

//#include <Date.h>
#include <iomanip>
#include <ostream>
#include <string>

struct Person
{
   std::string firstname;
   std::string lastname;
   Date birthday;

   friend std::ostream& operator<<( std::ostream& os, Person const& person )
   {
      os << std::setw(11) << std::left << person.firstname
         << std::setw(11) << std::left << person.lastname
         << person.birthday;
      return os;
   }
};


//---- <Random.h> ---------------------------------------------------------------------------------

//#include <Person.h>
#include <random>
#include <vector>
using std::size_t;

std::vector<Person> createPersons( size_t N, std::mt19937 rng )
{
   std::uniform_int_distribution<int> years{ 1940, 2020 };
   std::uniform_int_distribution<int> months{ 1, 12 };
   std::uniform_int_distribution<int> days{ 1, 31 };

   std::vector<Person> persons{};

   for( size_t i=0; i<N; ++i )
   {
      persons.push_back(
         Person{ "John", "Doe", { Year{ years(rng) }, Month{ months(rng) }, Day{ days(rng) } } }
      );
   }

   return persons;
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Person.h>
#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <map>
#include <vector>
using namespace std::string_literals;

using Contacts = std::map<std::string,std::vector<Person>>;

std::vector<Person> select_birthday_children( Contacts const& contacts )
{
   // Manual solution (imperative style)
   std::vector<Person> birthday_children{};

   for( auto const& contact_group : contacts )
   {
      for( Person const& person : contact_group.second )
      {
         if( person.birthday.year == Year{1955} &&
             ( person.birthday.month == Month{10} || person.birthday.month == Month{11} ) )
         {
            auto begin = birthday_children.begin();
            auto end   = birthday_children.end();
            while( begin!=end && begin->birthday < person.birthday ) {
               ++begin;
            }
            birthday_children.insert( begin, person );
         }
      }
   }

   return birthday_children;
}


int main()
{
   {
      Contacts const contacts
         { std::make_pair( "Friends"s, std::vector
            { Person{ "Klaus", "Iglberger", { Year{1980}, Month{1}, Day{30} } }
            , Person{ "Bjarne", "Stroustrup", { Year{1950}, Month{12}, Day{30} } }
            , Person{ "Scott", "Meyers", { Year{1959}, Month{4}, Day{9} } } } )
         , std::make_pair( "Business"s, std::vector
            // Musicians
            { Person{ "Billy", "Idol", { Year{1955}, Month{11}, Day{30} } }
            , Person{ "Tuomas", "Holopainen", { Year{1976}, Month{12}, Day{25} } }
            , Person{ "Sharon", "den Adel", { Year{1974}, Month{7}, Day{12} } }
            , Person{ "Lang", "Lang", { Year{1982}, Month{6}, Day{14} } }
            // Actors/actresses
            , Person{ "Sean", "Connery", { Year{1930}, Month{8}, Day{25} } }
            , Person{ "Whoopi", "Goldberg", { Year{1955}, Month{11}, Day{13} } }
            , Person{ "Rowan", "Atkinson", { Year{1955}, Month{1}, Day{5} } }
            , Person{ "Bruce", "Willis", { Year{1955}, Month{3}, Day{19} } }
            // CEOs in Tech
            , Person{ "Steve", "Jobs", { Year{1955}, Month{2}, Day{24} } }
            , Person{ "Tim", "Cook", { Year{1960}, Month{11}, Day{1} } }
            , Person{ "Bill", "Gates", { Year{1955}, Month{10}, Day{28} } } } ) };

      // Selecting all birthday children from October and November 1955
      auto const birthday_children{ select_birthday_children( contacts ) };

      for( auto const& birthday_child : birthday_children ) {
         std::cout << birthday_child << '\n';
      }
   }

   /*
   {
      constexpr size_t N = 5000000;

      std::random_device rd{};
      std::mt19937 mt{ rd() };

      Contacts const contacts
         { std::make_pair( "Friends"s, createPersons(N,mt) )
         , std::make_pair( "Business"s, createPersons(N,mt) ) };

      std::chrono::time_point<std::chrono::high_resolution_clock> start_time, end_time;
      start_time = std::chrono::high_resolution_clock::now();

      auto const birthday_children{ select_birthday_children( contacts ) };

      end_time = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> const elapsedTime = end_time - start_time;

      double const seconds( elapsedTime.count() );

      std::cout << "Runtime: " << seconds << "\n";
   }
   */

   return EXIT_SUCCESS;
}
