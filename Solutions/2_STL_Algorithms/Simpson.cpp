/**************************************************************************************************
*
* \file Simpson.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the empty functions to perform the following operations on the Simpson characters:
*       1. Print all characters to the screen
*       2. Randomize their order ('r')
*       3. Find the youngest person ('y')
*       4. Order them by first name ('f')
*       5. Order them by last name while preserving the order between equal elements ('l')
*       6. Order them by age while preserving the order between equal elements ('a')
*       7. Put all Simpsons first without affecting the general order of characters ('s')
*       8. Compute the total age of all characters ('t')
*       9. Determine the third oldest character as quickly as possible ('3')
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


struct Person
{
   std::string firstname;
   std::string lastname;
   int age;
};

std::ostream& operator<<( std::ostream& os, Person const& person )
{
   return os << std::setw(11) << std::left  << person.firstname
             << std::setw(10) << std::left  << person.lastname
             << std::setw(3)  << std::right << person.age;
}





bool sortByFirstName( const Person& lhs, const Person& rhs )
{
   return lhs.firstname < rhs.firstname;
}

struct SortByLastName
{
   bool operator()( const Person& lhs, const Person& rhs )
   {
      return lhs.lastname < rhs.lastname;
   }
};




template< typename Table >
void print( const Table& table )
{
   // Range-based for-loop solution
   for( const Person& p : table ) {
      std::cout << p << "\n";
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
void find_youngest( const Table& table )
{
   const auto pos = std::min_element( std::begin(table), std::end(table),
                                      []( const Person& lhs, const Person& rhs ) {
                                         return lhs.age < rhs.age;
                                      } );
   std::cout << "Youngest person = " << pos->firstname << " " << pos->lastname << "\n";
}

template< typename Table >
void random_order( Table& table )
{
   std::random_device rd{};
   std::mt19937 mt{ rd() };
   std::shuffle( std::begin(table), std::end(table), mt );
}

template< typename Table >
void order_by_firstname( Table& table )
{
   std::sort( std::begin(table), std::end(table), sortByFirstName );
}

template< typename Table >
void order_by_lastname( Table& table )
{
   std::stable_sort( std::begin(table), std::end(table), SortByLastName{} );
}

template< typename Table >
void order_by_age( Table& table )
{
   std::stable_sort( std::begin(table), std::end(table),
                     []( const Person& lhs, const Person& rhs ){
                        return lhs.age < rhs.age;
                     } );
}

template< typename Table >
void simpsons_first( Table& table )
{
   std::stable_partition( std::begin(table), std::end(table),
                          []( const Person& person ){
                             return person.lastname == "Simpson";
                          } );
}

template< typename Table >
void compute_total_age( const Table& table )
{
   const auto age = std::accumulate( std::begin(table), std::end(table), 0,
                                     []( int age, const Person& p ){
                                        return age + p.age;
                                     } );
   std::cout << "Total age = " << age << "\n";
}

template< typename Table >
void third_oldest( Table& table )
{
   std::nth_element( std::begin(table), std::begin(table)+2, std::end(table),
                     []( const Person& lhs, const Person& rhs ) {
                        return rhs.age < lhs.age;
                     } );
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

      case 's':
         simpsons_first( table );
         break;

      case 't':
         compute_total_age( table );
         break;

      case '3':
         third_oldest( table );
         break;

      default:
         return EXIT_SUCCESS;
      }

      print( table );
   }
}
