/**************************************************************************************************
*
* \file SimpsonPro.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the empty functions to perform the following operations on the Simpson characters:
*       1. Print all characters to the screen
*       2. Randomize the order of characters ('r')
*       3. Find the youngest character ('y')
*       4. Order them by last name while preserving the order between equal elements ('l')
*       5. Highlight/capitalize the last name of all persons with the given name ('h')
*       6. Put all children first ('c')
*       7. Compute the total length of all last names ('t')
*       8. Check if two adjacent characters have the same age ('s')
*       9. Compute the maximum age difference between two adjacent characters ('d')
*       10. Determine the median age of all characters ('m')
*       11. After ordering all persons by last name, find all the Simpsons ('f')
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
//#include <ranges>


struct Person
{
   std::string firstname;
   std::string lastname;
   int age;
};

bool isChildren( const Person& p )
{
   return p.age < 21;
}

std::ostream& operator<<( std::ostream& os, Person const& person )
{
   return os << std::setw(11) << std::left  << person.firstname
             << std::setw(11) << std::left  << person.lastname
             << std::setw(3)  << std::right << person.age;
}

void toupper( std::string& s )
{
   for( auto& c : s ) {
      c = std::toupper( c );
   }
}




template< typename Table >
void print( const Table& table )
{
   // TODO: Print all characters to the screen

   // Range-based for-loop solution
   for( const Person& p : table ) {
      std::cout << p << '\n';
   }

   // std::for_each solution
   //std::for_each( std::begin(table), std::end(table),
   //               []( const Person& p ) { std::cout << p << "\n"; } );

   // std::copy solution
   //std::copy( std::begin(table)
   //         , std::end(table)
   //         , std::ostream_iterator<Person>( std::cout, "\n" ) );
}

template< typename Table >
void random_order( Table& table )
{
   // TODO: Randomize their order ('r')

   std::random_device rd{};
   std::mt19937 mt{ rd() };

   // Classic algorithm solution
   std::shuffle( std::begin(table), std::end(table), mt );

   // C++20 ranges solution
   /*
   std::ranges::shuffle( table, mt );
   */
}

template< typename Table >
void find_youngest( const Table& table )
{
   // TODO: Find the youngest character ('y')

   // Classic algorithm solution
   const auto pos =
      std::min_element( std::begin(table), std::end(table), []( const Person& lhs, const Person& rhs ) {
         return lhs.age < rhs.age;
      } );

   // C++20 ranges solution
   /*
   const auto pos =
      std::ranges::min_element( table, []( const Person& lhs, const Person& rhs ) {
         return lhs.age < rhs.age;
      } );
   */

   std::cout << "Youngest person = " << pos->firstname << " " << pos->lastname << "\n";
}

template< typename Table >
void order_by_lastname( Table& table )
{
   // TODO: Order them by last name while preserving the order between equal elements ('l')

   // Classic algorithm solution
   std::stable_sort( std::begin(table), std::end(table), []( const Person& lhs, const Person& rhs ) {
      return lhs.lastname < rhs.lastname;
   } );

   // C++20 ranges solution
   /*
   std::ranges::stable_sort( table, []( const Person& lhs, const Person& rhs ) {
      return lhs.lastname < rhs.lastname;
   } );
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
      [lastname=std::move(lastname)]( Person& p ){
         if( p.lastname == lastname ) {
            toupper( p.lastname );
         }
      } );

   // C++20 ranges solution
   /*
   std::ranges::for_each( table, [lastname=std::move(lastname)]( Person& p ){
      if( p.lastname == lastname ) {
         toupper( p.lastname );
      }
   } );
   */
}

template< typename Table >
void children_first( Table& table )
{
   // TODO: Put all children first ('c')
   //       Note that you can use the given 'isChildren()' function.

   // Classic algorithm solution
   std::partition( std::begin(table), std::end(table), []( const Person& p ) {
      return isChildren( p );
   } );

   // C++20 ranges solution
   /*
   std::ranges::partition( table, []( const Person& p ) {
      return isChildren( p );
   } );
   */
}

template< typename Table >
void compute_total_lastname_length( const Table& table )
{
   // TODO: Compute the total length of all last names ('t')

   const size_t length =
      std::transform_reduce( std::begin(table), std::end(table), size_t{}
         , []( size_t accu, size_t length ){ return accu + length; }
         , []( const Person& p ){ return p.lastname.size(); } );
   std::cout << "Total length of all last names = " << length << "\n";
}

template< typename Table >
void same_age( const Table& table )
{
   // TODO: Check if two adjacent characters have the same age ('s')

   // Classic algorithm solution
   const auto pos =
      std::adjacent_find( std::begin(table), std::end(table), []( const Person& lhs, const Person& rhs ) {
         return lhs.age == rhs.age;
      } );

   // C++20 ranges solution
   /*
   const auto pos =
      std::ranges::adjacent_find( table, []( const Person& lhs, const Person& rhs ) {
         return lhs.age == rhs.age;
      } );
   */

   if( pos != std::end(table) ) {
      std::cout << pos->firstname << " and " << (pos+1)->firstname << " have the same age!\n";
   }
   else {
      std::cout << "No consecutive persons with the same age found!\n";
   }
}

template< typename Table >
void maximum_age_difference( const Table& table )
{
   // TODO: Compute the maximum age difference between two adjacent characters ('d')

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
   std::adjacent_find( std::begin(table), std::end(table), [&diff]( const Person& lhs, const Person& rhs ) {
      const auto ageDiff = std::abs( lhs.age - rhs.age );
      diff = std::max( diff, ageDiff );
      return false;
   } );
   */

   // C++20 ranges solution based on 'adjacent_find()'
   /*
   auto diff = 0;
   std::ranges::adjacent_find( table, [&diff]( const Person& lhs, const Person& rhs ) {
      const auto ageDiff = std::abs( lhs.age - rhs.age );
      diff = std::max( diff, ageDiff );
      return false;
   } );
   */

   // Solution based on 'inner_product()'
   const auto diff =
      std::inner_product( std::begin(table), std::prev(std::end(table)),
                          std::next(std::begin(table)),
                          0,
                          []( int accu, int ageDiff ) {
                             return std::max( accu, ageDiff );
                          },
                          []( const Person& a, const Person& b ) {
                             return std::abs( a.age - b.age );
                          } );

   std::cout << " Maximum age different = " << diff << "\n";
}

template< typename Table >
void median_age( Table& table )
{
   // TODO: Determine the median age of all characters ('m')

   // Classic algorithm solution
   std::nth_element( std::begin(table), std::begin(table)+table.size()/2, std::end(table),
      []( const Person& lhs, const Person& rhs ) {
         return rhs.age < lhs.age;
      } );

   // C++20 ranges solution
   /*
   std::ranges::nth_element( table, std::begin(table)+table.size()/2,
      []( const Person& lhs, const Person& rhs ) {
         return rhs.age < lhs.age;
      } );
   */
}

template< typename Table >
void find_simpsons( Table& table )
{
   // TODO: After ordering all persons by last name, find all the Simpsons ('f')

   // Classic algorithm solution
   auto [begin,end] =
      std::equal_range( std::begin(table), std::end(table), Person{"","Simpson",0},
         []( const Person& lhs, const Person& rhs ) {
            return lhs.lastname < rhs.lastname;
         } );

   // C++20 ranges solution
   //auto [begin,end] =
   //   std::ranges::equal_range( table, Person{"","Simpson",0},
   //      []( const Person& lhs, const Person& rhs ) {
   //         return lhs.lastname < rhs.lastname;
   //      } );

   std::cout << "The Simpson:\n";
   for( ; begin!=end; ++begin ) {
      std::cout << *begin << '\n';
   }
   std::cout << '\n';
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

      case 'd':
         maximum_age_difference( table );
         break;

      case 'm':
         median_age( table );
         break;

      case 'f':
         find_simpsons( table );
         break;

      default:
         return EXIT_SUCCESS;
      }

      print( table );
   }

   return EXIT_SUCCESS;
}
