/**************************************************************************************************
*
* \file FixedVector.cpp
* \brief C++ Training - Class Design Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the class template 'FixedVector'. A fixed vector represents a hybrid between
*       std::vector and std::array, i.e. it holds a maximum number of elements in static memory
*       but can be resized within this bound.
*
*         template< typename Type      // Type of the elements
*                   size_t Capacity >  // Maximum number of elements
*         class FixedVector;
*
*       The following functions are required:
*       1.  A default constructor
*       2.  A constructor taking the initial size
*       3.  A constructor taking the initial size and initial value of all elements
*       4.  A copy constructor
*       5.  A move constructor
*       6.  A function to query the current number of elements
*       7.  A function to query the maximum number of elements
*       8.  A function to access elements
*       9.  Functions for the STL conformant iteration over elements
*       10. A copy assignment operator
*       11. A move assignment operator
*       12. A function to add elements at the end of the vector
*       13. A function to change the number of current elements
*
**************************************************************************************************/

//---- BEGIN OF <FixedVector.h> -------------------------------------------------------------------

#ifndef FIXEDVECTOR_H
#define FIXEDVECTOR_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>


template< typename Type, size_t Capacity >
class FixedVector
{
 public:
   // TODO:
   //  - Default constructor
   //  - Constructor taking the initial size
   //  - Constructor taking the initial size and initial value of all elements
   //  - Copy constructor
   //  - Move constructor
   //  - Function to query the current number of elements
   //  - Function to query the maximum number of elements
   //  - Function to access elements
   //  - Functions for the STL conformant iteration over elements
   //  - Copy assignment operator
   //  - Move assignment operator
   //  - Function to add elements at the end of the vector
   //  - Function to change the number of current elements

 private:
   // TODO:
   //  - Data members
};

#endif

//---- END OF <FixedVector.h> ---------------------------------------------------------------------


//---- <Main.cpp> ---------------------------------------------------------------------------------

#include <iostream>

template< typename Type, size_t Capacity >
std::ostream& operator<<( std::ostream& os, FixedVector<Type,Capacity>& v )
{
   os << "(";
   for( auto const& value : v )
      os << " " << value;
   os << " )";
   return os;
}


struct Test
{
   Test() { puts( "Test()" ); }
   Test( int j ) : i( j ) { puts( "Test(int)" ); }
   ~Test() { puts( "~Test()" ); }
   Test( Test const& t ) { i = t.i; puts( "Test(Test const&)" ); }
   Test( Test&& t ) { i = t.i; puts( "Test(Test&&)" ); }
   Test& operator=( Test const& t ) { i = t.i; puts( "Test& operator=(Test const&)" ); return *this; }
   Test& operator=( Test&& t ) { i = t.i; puts( "Test& operator=(Test&&)" ); return *this; }

   int i{ 0 };
};

std::ostream& operator<<( std::ostream& os, Test const& test )
{
   return os << test.i;
}


int main()
{
   // Default constructor
   /*
   {
      FixedVector<int,5> v{};
      std::cout << " Default vector: " << v << "\n";
   }
   */

   // Fixed vector with initial size
   /*
   {
      FixedVector<int,5> v( 4UL );
      std::cout << " Sized vector: " << v << "\n";
   }
   */

   // Fixed vector with initial size and initial value
   /*
   {
      FixedVector<int,5> v( 4UL, 3 );
      std::cout << " Sized vector: " << v << "\n";
   }
   */

   // Copy construction
   /*
   {
      FixedVector<int,5> a( 4UL, 3 );
      FixedVector<int,5> b( a );
      std::cout << " Copied vector: " << b << "\n";
   }
   */

   // Addition of individual elements
   /*
   {
      FixedVector<int,5> v{};
      v.push_back( 1 );
      v.push_back( 2 );
      v.push_back( 3 );
      std::cout << " Individual vector: " << v << "\n";
   }
   */

   // Access to individual elements
   /*
   {
      FixedVector<int,5> v{};
      v.resize( 3 );
      v[0] = 1;
      v[1] = 2;
      v[2] = 3;
      std::cout << " Individual vector: " << v << "\n";
   }
   */

   // Copy assignment
   /*
   {
      FixedVector<int,5> a( 4UL, 3 );
      FixedVector<int,5> b{};
      b = a;
      std::cout << " Copied vector: " << b << "\n";
   }
   */

   return EXIT_SUCCESS;
}

