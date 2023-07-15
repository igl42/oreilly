/**************************************************************************************************
*
* \file STLpro.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Solve the following tasks on a vector of integers by means of STL algorithms:
*       - Compute the product of all elements in the vector
*       - Extract all numbers <= 5 from the vector
*       - Compute the (numerical) length of the vector
*       - Compute the ratios v[i+1]/v[i] for all elements v[i] in v
*       - Move the range [v[3],v[5]] to the beginning of the vector
*
**************************************************************************************************/

#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <vector>


using Ints    = std::vector<int>;
using Doubles = std::vector<double>;


template< typename T >
void printVector( std::vector<T> const& numbers )
{
   // TODO: Print all numbers to the screen

   std::cout << "(";
   std::for_each( std::begin(numbers), std::end(numbers), []( T value ){ std::cout << " " << value; } );
   std::cout << " )";
}


int computeProduct( Ints const& ints )
{
   // TODO: Compute the product of all elements in the vector

   int const product = std::accumulate( std::begin(ints), std::end(ints), 0,
      []( int init, int value ) {
         return init * value;
      } );

   return product;
}


Ints extractInts( Ints const& ints )
{
   // TODO: Extract all numbers <= 5 from the vector

   Ints lessThan5( ints.size(), 0 );
   lessThan5.erase( std::copy_if( std::begin(ints), std::end(ints), std::begin(lessThan5),
                                  []( int i ){ return i <= 5; } ),
                    std::end(lessThan5) );
   return lessThan5;
}


double computeLength( Ints const& ints )
{
   // TODO: Compute the (numerical) length of the vector

   return std::sqrt( std::inner_product( std::begin(ints), std::end(ints), std::begin(ints), double{} ) );
}


Doubles computeRatios( Ints const& ints )
{
   // TODO: Compute the ratios v[i+1]/v[i] for all elements v[i] in v
   Doubles ratios( ints.size() - 1U, 0.0 );
   std::transform( std::begin(ints)+1U, std::end(ints), std::begin(ints), std::begin(ratios),
      []( double divident, double divisor )
      {
         return divident/divisor;
      } );
   return ratios;

   // Alternative solution; Note that an umodified copy of the first element
   // of 'ints' is written to the beginning of 'ratios'
   /*
   Doubles ratios( ints.size() );
   std::adjacent_difference( std::begin(ints), std::end(ints), std::begin(ratios),
      []( double divident, double divisor )
      {
         return divident/divisor;
      } );
   */
   return ratios;
}


Ints moveRange( Ints const& ints )
{
   // TODO: Move the range [v[3],v[5]] to the beginning of the vector

   Ints moved( ints );
   std::rotate( std::begin(moved), std::begin(moved)+3U, std::end(moved) );
   return moved;
}


int main()
{
   Ints ints{ 1, 5, 2, 8, 7, 10, 4 };

   // Compute the product of all elements in v
   {
      std::cout << " Product of all elements: expected = 22400, actual = ";
      int const product = computeProduct( ints );
      std::cout << product << "\n";
   }

   // Extract all numbers <= 5 from the vector
   {
      std::cout << " All values <= 5: expected = ( 1 5 2 4 ), actual = ";
      printVector( extractInts( ints ) );
      std::cout << "\n";
   }

   // Compute the numerical length of the vector
   {
      std::cout << " Numerical length of the vector: expected = 16.0935, actual = ";
      double const length = computeLength( ints );
      std::cout << length << "\n";
   }

   // Compute the ratios v[i+1]/v[i] for all elements v[i] in v
   {
      std::cout << " Ratios: expected = ( 5 0.4 4 0.875 1.42857 0.4 ), actual = ";
      printVector( computeRatios( ints ) );
      std::cout << "\n";
   }

   // Move the range [v[3],v[5]] to the beginning of the vector
   {
      std::cout << " Moved range: expected = ( 8 7 10 4 1 5 2 ), actual = ";
      printVector( moveRange( ints ) );
      std::cout << "\n";
   }
}
