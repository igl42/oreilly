/**************************************************************************************************
*
* \file SimpsonPro.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the empty functions to perform the following operations on the Simpson characters:
*       1. Print all persons to the screen
*       2. Randomize the order of persons ('r')
*       3. Find the youngest person ('y')
*       4. Order them by last name while preserving the order between equal elements ('l')
*       5. Highlight/capitalize the last name of all persons with the given name ('h')
*       6. Put all children of age 6 to 17 first ('c')
*       7. Compute the total length of all last names ('t')
*       8. Check if two adjacent persons have the same age ('s')
*       9. Determine the median age of all persons ('m')
*       10. After ordering all persons by last name, find all the Simpsons ('f')
*       11. Compute the maximum age difference between two adjacent persons ('d')
*       12. Print a string containing the first names of all children ('p')
*
**************************************************************************************************/

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <iomanip>
#include <numeric>
#include <random>
#include <string>
#include <vector>

// C++20
//#include <format>
//#include <ranges>

using namespace std::string_literals;


struct Person
{
   std::string firstname;
   std::string lastname;
   int age;
};

std::ostream& operator<<( std::ostream& os, Person const& person )
{
   return os << std::setw(11) << std::left  << person.firstname
             << std::setw(11) << std::left  << person.lastname
             << std::setw(3)  << std::right << person.age;

   // C++20 format solution
   /*
   os << std::format( "{:<11}{:<11}{:>3}", person.firstname, person.lastname, person.age );
   return os;
   */

   // C++23 'println()' solution
   /*
   std::println( "{:<11}{:<11}{:>3}", person.firstname, person.lastname, person.age );
   */
}

bool is_child( Person const& p )
{
   return p.age < 18;
}

void toupper( std::string& s )
{
   for( auto& c : s ) {
      c = std::toupper( c );
   }
}

auto youngest()
{
   return []( Person const& lhs, Person const& rhs )
   {
      return lhs.age < rhs.age;
   };
}

auto by_lastname()
{
   return []( Person const& lhs, Person const& rhs )
   {
      return lhs.lastname < rhs.lastname;
   };
}

auto has_lastname( std::string_view lastname )
{
   return [lastname]( Person const& person )
   {
      return person.lastname == lastname;
   };
}

auto have_same_age()
{
   return []( Person const& lhs, Person const& rhs )
   {
      return lhs.age == rhs.age;
   };
}

auto younger_than( int age )
{
   return [age]( Person const& person ) { return person.age < age; };
}

auto older_than( int age )
{
   return [age]( Person const& person ) { return person.age > age; };
}

template< typename... Functions >
auto when_all( Functions... functions )
{
   return [functions...]<typename... Ts>( Ts const&... values )
   {
      return ( functions(values...) && ... );
   };
}




template< typename Table >
void print( Table const& table )
{
   // TODO: Print all persons to the screen

   // Range-based for-loop solution
   for( Person const& p : table ) {
      std::cout << p << '\n';
   }

   // std::for_each solution
   /*
   std::for_each( std::begin(table), std::end(table),
      []( Person const& p )
      {
         std::cout << p << '\n';
      } );
   */

   // std::copy solution
   /*
   std::copy( std::begin(table), std::end(table),
      std::ostream_iterator<Person>( std::cout, "\n" ) );
   */
}

template< typename Table >
void random_order( Table& table )
{
   // TODO: Randomize their order ('r')

   // Classic algorithm solution
   std::shuffle( std::begin(table), std::end(table), std::random_device{} );

   // C++20 ranges solution
   /*
   std::ranges::shuffle( table, std::random_device{} );
   */
}

template< typename Table >
void find_youngest( Table const& table )
{
   // TODO: Find the youngest person ('y')

   // Classic algorithm solution
   auto const pos =
      std::min_element( std::begin(table), std::end(table), youngest() );

   // C++20 ranges solution
   /*
   auto const pos = std::ranges::min_element( table, {}, &Person::age );
   */

   if( pos != std::end(table) ) {
      std::cout << "Youngest person = " << pos->firstname << " " << pos->lastname << '\n';
   }
}

template< typename Table >
void order_by_lastname( Table& table )
{
   // TODO: Order them by last name while preserving the order between equal elements ('l')

   // Classic algorithm solution
   std::stable_sort( std::begin(table), std::end(table), by_lastname() );

   // C++20 ranges solution
   /*
   std::ranges::stable_sort( table, {}, &Person::lastname );
   */
}

template< typename Table >
void highlight_lastname( Table& table )
{
   std::string lastname{};

   std::cout << "Enter last name: ";
   std::cin >> lastname;

   // TODO: Highlight/capitalize the last name of all persons with the given name ('h')
   //       Note that you can use the given 'toupper()' function to capitalize a string.

   // Classic algorithm solution
   std::for_each( std::begin(table), std::end(table),
      [lastname=std::move(lastname)]( Person& p )
      {
         if( p.lastname == lastname ) {
            toupper( p.lastname );
         }
      } );

   // C++20 ranges solution
   /*
   std::ranges::for_each( table | std::views::filter( has_lastname("Simpson") ),
      []( Person& person )
      {
         toupper(person.lastname);
      } );
   */
}

template< typename Table >
void children_first( Table& table )
{
   // TODO: Put all children of age 6 to 17 first ('c')

   // Classic algorithm solution
   std::partition( std::begin(table), std::end(table),
      []( Person const& person )
      {
         return person.age > 5 && person.age < 18;
      } );

   // C++20 ranges solution
   /*
   std::ranges::partition( table,
      when_all( older_than(5), younger_than(18) ) );
   */
}

template< typename Table >
void compute_total_lastname_length( Table const& table )
{
   // TODO: Compute the total length of all last names ('t')

   auto const total_length =
      std::transform_reduce( std::begin(table), std::end(table), size_t{}
         , []( size_t accu, size_t length ){ return accu + length; }
         , []( Person const& p ){ return p.lastname.size(); } );
   std::cout << "Total length of all last names = " << total_length << '\n';
}

template< typename Table >
void same_age( Table const& table )
{
   // TODO: Check if two adjacent persons have the same age ('s')

   // Classic algorithm solution
   auto const pos =
      std::adjacent_find( std::begin(table), std::end(table), have_same_age() );

   // C++20 ranges solution
   /*
   auto const pos =
      std::ranges::adjacent_find( table, {}, &Person::age );
   */

   if( pos != std::end(table) ) {
      std::cout << pos->firstname << " and " << (pos+1)->firstname << " have the same age!\n";
   }
   else {
      std::cout << "No consecutive persons with the same age found!\n";
   }
}

template< typename Table >
void median_age( Table& table )
{
   // TODO: Determine the median age of all persons ('m')

   // Classic algorithm solution
   std::nth_element( std::begin(table), std::begin(table)+table.size()/2, std::end(table), youngest() );

   // C++20 ranges solution
   /*
   std::ranges::nth_element( table, std::begin(table)+table.size()/2, {}, &Person::age );
   */
}

template< typename Table >
void find_simpsons( Table& table )
{
   // TODO: After ordering all persons by last name, find all the Simpsons ('f')

   // Classic algorithm solution
   auto [begin,end] =
      std::equal_range( std::begin(table), std::end(table), Person{"","Simpson",0}, by_lastname() );

   // C++20 ranges solution
   /*
   auto [begin,end] =
      std::ranges::equal_range( table, "Simpson"s, {}, &Person::lastname );
   */

   std::cout << "The Simpson:\n";
   for( ; begin!=end; ++begin ) {
      std::cout << *begin << '\n';
   }
   std::cout << '\n';
}

template< typename Table >
void maximum_age_difference( Table const& table )
{
   // TODO: Compute the maximum age difference between two adjacent persons ('d')

   // Traditional for loop solution
   /*
   int max = std::numeric_limits<int>::lowest();
   for( auto l=std::begin(table), r=std::next(std::begin(table)); r!=std::end(table); ++l, ++r ) {
      max = std::max( max, std::abs( l->age, r->age ) );
   }
   */

   // Classic algorithm solution based on 'adjacent_find()'
   /*
   auto diff = 0;
   std::adjacent_find( std::begin(table), std::end(table),
      [&diff]( Person const& lhs, Person const& rhs )
      {
         auto const ageDiff = std::abs( lhs.age - rhs.age );
         diff = std::max( diff, ageDiff );
         return false;
      } );
   */

   // C++20 ranges solution based on 'adjacent_find()'
   /*
   auto diff = 0;
   std::ranges::adjacent_find( table,
      [&diff]( Person const& lhs, Person const& rhs )
      {
         auto const ageDiff = std::abs( lhs.age - rhs.age );
         diff = std::max( diff, ageDiff );
         return false;
      } );
   */

   // Solution based on 'inner_product()'
   auto const diff =
      std::inner_product( std::begin(table), std::prev(std::end(table)),
                          std::next(std::begin(table)),
                          0,
                          []( int accu, int ageDiff )
                          {
                             return std::max( accu, ageDiff );
                          },
                          []( Person const& a, Person const& b )
                          {
                             return std::abs( a.age - b.age );
                          } );

   std::cout << " Maximum age different = " << diff << '\n';
}

template< typename Table >
void print_children( Table const& table )
{
   // TODO: Print a string containing the first names of all children ('p')

   // Classic algorithm solution
   std::string const names =
      std::accumulate( std::begin(table), std::end(table), std::string{},
         []( std::string accu, Person const& person )
         {
            if( is_child(person) ) {
               if( !accu.empty() ) {
                  accu += ' ';
               }
               accu += person.firstname;
            }
            return std::move(accu);
         } );

   // C++17 solution based on 'transform_reduce()'
   /*
   std::string const names =
      std::transform_reduce( std::begin(table), std::end(table), std::string{},
         []( std::string accu, std::string const& name )
         {
            if( !name.empty() ) {
               if( !accu.empty() )
                  accu += ' ';
               accu += name;
            }
            return std::move(accu);
         },
         []( Person const& person )
         {
            if( is_child(person) )
               return person.firstname;
            else
               return std::string{};
         } );
   */

   // C++23 ranges solution
   /*
   std::string const names =
      std::ranges::fold_left( table | std::views::filter( younger_than(18) ), std::string{},
         []( std::string accu, Person const& person )
            {
               if( !accu.empty() ) {
                  accu += ' ';
               }
               accu += person.firstname;

               return std::move(accu);
            } );
   */

   std::cout << "Children names = " << names << '\n';
}




int main()
{
   std::vector<Person> table =
      { Person{ "Homer",      "Simpson",    38 }
      , Person{ "Marge",      "Simpson",    34 }
      , Person{ "Bart",       "Simpson",    10 }
      , Person{ "Lisa",       "Simpson",     8 }
      , Person{ "Maggie",     "Simpson",     1 }
      , Person{ "Hans",       "Moleman",    33 }
      , Person{ "Ralph",      "Wiggum",      8 }
      , Person{ "Milhouse",   "Van Houten", 10 }
      , Person{ "Ned",        "Flanders",   60 }
      , Person{ "Jeff",       "Albertson",  45 }
      , Person{ "Montgomery", "Burns",     104 } };

   char command;

   while( std::cout << "Enter command: " && std::cin >> command )
   {
      switch( command )
      {
      case 'r':
         random_order( table );
         break;

      case 'y':
         find_youngest( table );
         break;

      case 'l':
         order_by_lastname( table );
         break;

      case 'h':
         highlight_lastname( table );
         break;

      case 'c':
         children_first( table );
         break;

      case 't':
         compute_total_lastname_length( table );
         break;

      case 's':
         same_age( table );
         break;

      case 'm':
         median_age( table );
         break;

      case 'f':
         find_simpsons( table );
         break;

      case 'd':
         maximum_age_difference( table );
         break;

      case 'p':
         print_children( table );
         break;

      default:
         return EXIT_SUCCESS;
      }

      print( table );
   }

   return EXIT_SUCCESS;  // or std::unreachable() in C++23
}
