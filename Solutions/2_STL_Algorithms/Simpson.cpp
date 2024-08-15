/**************************************************************************************************
*
* \file Simpson.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the empty functions to perform the following operations on the Simpson characters:
*       1. Print all persons to the screen
*       2. Randomize their order ('r')
*       3. Find the youngest person ('y')
*       4. Order them by first name ('f')
*       5. Order them by last name while preserving the order between equal elements ('l')
*       6. Order them by age while preserving the order between equal elements ('a')
*       7. Count the number of children ('c')
*       8. Put all Simpsons first without affecting the general order of persons ('s')
*       9. Compute the total age of all persons ('t')
*       10. Put the last person first, moving all others by one position ('0')
*       11. Determine the fourth oldest person as quickly as possible ('4')
*
**************************************************************************************************/

#include <algorithm>
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

bool is_younger( Person const& person, int age )
{
   return person.age < age;
}

bool is_older( Person const& person, int age )
{
   return person.age > age;
}




struct IsYounger
{
   [[nodiscard]] constexpr bool operator()( Person const& lhs, Person const& rhs ) const noexcept
   {
      return lhs.age < rhs.age;
   }
};

auto younger_than( int age )
{
   return [age]( Person const& person ) { return is_younger(person,age); };
}

auto older_than( int age )
{
   return [age]( Person const& person ) { return is_older(person,age); };
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
   for( auto const& p : table ) {
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
   std::ranges::shuffle( table, mt );
   */
}

template< typename Table >
void find_youngest( Table const& table )
{
   // TODO: Find the youngest person ('y')

   // Classic algorithm solution
   auto const pos =
      std::min_element( std::begin(table), std::end(table),
         []( Person const& lhs, Person const& rhs )
         {
            return lhs.age < rhs.age;
         } );

   // C++20 ranges solution
   /*
   auto const pos = std::ranges::min_element( table, {}, &Person::age );
   */

   if( pos != std::end(table) ) {
      std::cout << "Youngest person = " << pos->firstname << " " << pos->lastname << '\n';
   }
}

template< typename Table >
void order_by_firstname( Table& table )
{
   // TODO: Order them by first name ('f')

   // Classic algorithm solution
   std::sort( std::begin(table), std::end(table),
      []( Person const& lhs, Person const& rhs )
      {
         return lhs.firstname < rhs.firstname;
      } );

   // C++20 ranges solution
   /*
   std::ranges::sort( table, {}, &Person::firstname );
   */
}

template< typename Table >
void order_by_lastname( Table& table )
{
   // TODO: Order them by last name while preserving the order between equal elements ('l')

   // Classic algorithm solution
   std::stable_sort( std::begin(table), std::end(table),
      []( Person const& lhs, Person const& rhs )
      {
         return lhs.lastname < rhs.lastname;
      } );

   // C++20 ranges solution
   /*
   std::ranges::stable_sort( table, {}, &Person::lastname );
   */
}

template< typename Table >
void order_by_age( Table& table )
{
   // TODO: Order them by age while preserving the order between equal elements ('a')

   // Classic algorithm solution
   std::stable_sort( std::begin(table), std::end(table), IsYounger{} );

   // C++20 ranges solution
   /*
   std::ranges::stable_sort( table, IsYounger{} );
   */
}

template< typename Table >
void count_children( Table const& table )
{
   // TODO: Count the number of children ('c')
   //       Hint: Assume that children are older than 6 and younger than 18 years

   // Classic algorithm solution
   size_t const count =
      std::count_if( std::begin(table), std::end(table),
         when_all( older_than(6), younger_than(18) ) );

   // C++20 ranges solution
   /*
   size_t const count =
      std::ranges::count_if( table, younger_than(18) );
   */

   std::cout << "The table contains " << count << " children\n";
}

template< typename Table >
void simpsons_first( Table& table )
{
   // TODO: Put all Simpsons first without affecting the general order of persons ('s')
   //       Hint: Don't use any 'sort()' algorithm

   // Classic algorithm solution
   std::stable_partition( std::begin(table), std::end(table),
      []( Person const& person )
      {
         return person.lastname == "Simpson";
      } );

   // C++20 ranges solution
   /*
   std::ranges::stable_partition( table,
      []( Person const& person )
      {
         return person.lastname == "Simpson";
      } );
   */
}

template< typename Table >
void compute_total_age( Table const& table )
{
   // TODO: Compute the total age of all persons ('t')

   auto const age =
      std::accumulate( std::begin(table), std::end(table), int{},
         []( int age, Person const& p )
         {
            return age + p.age;
         } );
   std::cout << "Total age = " << age << '\n';
}

template< typename Table >
void last_to_first( Table& table )
{
   // TODO: Put the last person first, moving all others by one position ('0')
   //       Hint: Don't use the 'shift_left()', 'shift_right()', or 'move()' algorithms

   // Classic algorithm solution
   std::rotate( std::begin(table), std::end(table)-1, std::end(table) );

   // C++20 ranges solution
   /*
   std::ranges::rotate( table, std::end(table)-1 );
   */
}

template< typename Table >
void fourth_oldest( Table& table )
{
   // TODO: Determine the fourth oldest person as quickly as possible ('4')
   //       Note that you are allowed to change the order of persons.

   // Classic algorithm solution
   std::nth_element( std::begin(table), std::begin(table)+3, std::end(table),
      []( Person const& lhs, Person const& rhs )
      {
         return rhs.age < lhs.age;
      } );

   // C++20 ranges solution
   /*
   std::ranges::nth_element( table, std::begin(table)+3, std::greater<>{}, &Person::age );
   */
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

      case 'f':
         order_by_firstname( table );
         break;

      case 'l':
         order_by_lastname( table );
         break;

      case 'a':
         order_by_age( table );
         break;

      case 'c':
         count_children( table );
         break;

      case 's':
         simpsons_first( table );
         break;

      case 't':
         compute_total_age( table );
         break;

      case '0':
         last_to_first( table );
         break;

      case '4':
         fourth_oldest( table );
         break;

      default:
         return EXIT_SUCCESS;
      }

      print( table );
   }

   return EXIT_SUCCESS;  // or std::unreachable() in C++23
}
