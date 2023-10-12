/**************************************************************************************************
*
* \file STLIntro.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Solve the following tasks on a vector of integers by means of STL algorithms:
*       - Print the contents of the vector to the screen
*       - Reverse the order of elements in the vector
*       - Find the first element with the value 5
*       - Count the elements with the value 5
*       - Replace all 5s by 2s
*       - Sort the vector
*       - Determine the range of 2s
*
**************************************************************************************************/

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>


using Ints = std::vector<int>;


void printToScreen( Ints const& ints )
{
   std::copy( std::begin(ints), std::end(ints), std::ostream_iterator<int>( std::cout, " " ) );
   std::cout << "\n";
}


void reverseOrder( Ints& ints )
{
   std::reverse( std::begin(ints), std::end(ints) );

   printToScreen( ints );
}


void findFirstFive( Ints const& ints )
{
   auto pos = std::find( std::begin(ints), std::end(ints), 5 );

   if( pos != std::end(ints) ) {
      std::cout << "Found element " << *pos << "\n";
   }
}


void countNumberOfFives( Ints const& ints )
{
   size_t const num = std::count( std::begin(ints), std::end(ints), 5 );

   std::cout << "Number of 5s in the vector: " << num << "\n";
}


void replaceAllFivesWithTwos( Ints& ints )
{
   std::replace( std::begin(ints), std::end(ints), 5, 2 );

   printToScreen( ints );
}


void sortInts( Ints& ints )
{
   std::sort( std::begin(ints), std::end(ints) );

   printToScreen( ints );
}


void findAllTwos( Ints const& ints )
{
   auto pos1 = std::lower_bound( std::begin(ints), std::end(ints), 2 );
   auto pos2 = std::upper_bound( std::begin(ints), std::end(ints), 2 );

   std::cout << "Number of 2s in the vector: " << distance( pos1, pos2 ) << "\n";
}





int main()
{
   Ints ints{ 3, 6, 27, 5, 1, 8, 5, 4 };

   printToScreen( ints );
   reverseOrder( ints );
   findFirstFive( ints );
   countNumberOfFives( ints );
   replaceAllFivesWithTwos( ints );
   sortInts( ints );
   findAllTwos( ints );
}

