/**************************************************************************************************
*
* \file Sum.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Write a generic 'sum()' function that can compute the sum of an arbitrary number of
*         values of any type.
*
* Step 2: Write a generic 'sum_if()' function that computes the sum of all values that fulfill
*         a given predicate (e.g. 'is_positive()').
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <type_traits>


constexpr int sum( int i1, int i2 )
{
   return i1 + i2;
}

constexpr int sum( int i1, int i2, int i3 )
{
   return i1 + i2 + i3;
}

constexpr int sum( int i1, int i2, int i3, int i4 )
{
   return i1 + i2 + i3 + i4;
}

constexpr double sum( double i1, double i2 )
{
   return i1 + i2;
}

constexpr double sum( double i1, double i2, double i3 )
{
   return i1 + i2 + i3;
}

constexpr double sum( double i1, double i2, double i3, double i4 )
{
   return i1 + i2 + i3 + i4;
}


int main()
{
   // Step 1
   {
      const int    s1 = sum( -1, 2 );
      const int    s2 = sum( 3, -1, -2, 1 );
      const double s3 = sum( 4.2, -1.2 );
      const double s4 = sum( -2.5, 3.7, 2.8 );

      static_assert( sum( -1, 2 ) == 1 );
      static_assert( sum( 3, -1, -2, 1 ) == 1 );
      static_assert( sum( 4.2, -1.2 ) == 3.0 );
      static_assert( sum( -2.5, 3.7, 2.8 ) == 4.0 );

      std::cout << "\n"
                << " s1 = " << s1 << "\n"
                << " s2 = " << s2 << "\n"
                << " s3 = " << s3 << "\n"
                << " s4 = " << s4 << "\n"
                << "\n";
   }

   // Step 2
   /*
   {
      const int    s1 = sum_if( is_positive(), -1, 2 );
      const int    s2 = sum_if( is_positive(), 3, -1, -2, 1 );
      const double s3 = sum_if( is_positive(), 4.2, -1.2 );
      const double s4 = sum_if( is_positive(), -2.5, 3.7, 2.8 );

      static_assert( sum( -1, 2 ) == 2 );
      static_assert( sum( 3, -1, -2, 1 ) == 4 );
      static_assert( sum( 4.2, -1.2 ) == 4.2 );
      static_assert( sum( -2.5, 3.7, 2.8 ) == 6.5 );

      std::cout << "\n"
                << " s1 = " << s1 << "\n"
                << " s2 = " << s2 << "\n"
                << " s3 = " << s3 << "\n"
                << " s4 = " << s4 << "\n"
                << "\n";
   }
   */
}
