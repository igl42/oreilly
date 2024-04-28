/**************************************************************************************************
*
* \file Constraints2.cpp
* \brief C++ Training - Advanced C++20 concepts programming task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task 1: Implement the concept 'IntCompatible' that requires the given type 'T' to be
*         convertible to 'int' and to have a size greater than or equal to the size of 'int'.
*
* Task 2: Implement the concept 'Arithmetic' that requires the given type 'T' to be either
*         an integral or floating point type, but does not accept 'bool'.
*
* Task 3: Implement the concept 'NonConstReference' that requires the given type 'T' to
*         be a reference to a non-const type.
*
* Task 4: Implement the concept 'IntegralAddable' that requires the given type 'T' to be
*         addable. The result of the addition should yield an integral value.
*
* Task 5: Implement the concept 'NoNarrowingConversion' that prevents narrowing conversions
*         between the given types 'From' and 'To'.
*
**************************************************************************************************/

#include <cstdlib>
#include <concepts>
#include <string>
#include <utility>


//---- <Constraints.h> ----------------------------------------------------------------------------

// Task 1: Implement a concept that requires the given type 'T' to be convertible to 'int'
//         and to have a size greater than or equal to the size of 'int'.
// TODO


// Task 2: Implement a concept that requires the given type 'T' to be either an integral or
//         floating point type, but does not accept 'bool'.
// TODO


// Task 3: Implement the concept 'IsNonConstReference' that requires the given type 'T' to
//         be a reference to a non-const type.
// TODO


// Task 4: Implement a concept that requires the given type 'T' to be addable. The result of the
//         addition should yield an integral value.
// TODO


// Task 4: Implement a concept that prevents narrowing conversions between the given types
//         'From' and 'To'.
// TODO


//---- <Main.cpp> ---------------------------------------------------------------------------------

// Task 3
struct Widget {};
int operator+( Widget, Widget );

struct Gadget {};


int main()
{
   // Task 1
   /*
   static_assert(  IntCompatible<int> );
   static_assert(  IntCompatible<unsigned int> );
   static_assert(  IntCompatible<long> );
   static_assert(  IntCompatible<size_t> );
   static_assert(  IntCompatible<float> );
   static_assert(  IntCompatible<double> );
   static_assert( !IntCompatible<char> );
   static_assert( !IntCompatible<unsigned short> );
   static_assert( !IntCompatible<std::string> );
   */

   // Task 2
   /*
   static_assert(  Arithmetic<char> );
   static_assert(  Arithmetic<short> );
   static_assert(  Arithmetic<int> );
   static_assert(  Arithmetic<long> );
   static_assert(  Arithmetic<float> );
   static_assert(  Arithmetic<double> );
   static_assert( !Arithmetic<bool> );
   static_assert( !Arithmetic<std::string> );
   */

   // Task 3
   /*
   static_assert(  NonConstReference<int&> );
   static_assert(  NonConstReference<int&&> );
   static_assert( !NonConstReference<int> );
   static_assert( !NonConstReference<int const&> );
   static_assert( !NonConstReference<int const&&> );
   */

   // Task 4
   /*
   static_assert(  IntegralAddable<int> );
   static_assert(  IntegralAddable<long> );
   static_assert(  IntegralAddable<Widget> );
   static_assert( !IntegralAddable<float> );
   static_assert( !IntegralAddable<std::string> );
   static_assert( !IntegralAddable<Gadget> );
   */

   // Task 5
   /*
   static_assert(  NoNarrowingConversion<int,int> );
   static_assert(  NoNarrowingConversion<int,long> );
   static_assert(  NoNarrowingConversion<float,double> );
   static_assert(  NoNarrowingConversion<double,double> );
   static_assert( !NoNarrowingConversion<int,unsigned int> );
   static_assert( !NoNarrowingConversion<int,short> );
   static_assert( !NoNarrowingConversion<double,float> );
   */

   return EXIT_SUCCESS;
}

