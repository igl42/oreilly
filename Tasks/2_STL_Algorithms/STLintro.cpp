/**************************************************************************************************
*
* \file STLintro.cpp
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
   // TODO
}


void reverseOrder( Ints& ints )
{
   // TODO
}


void findFirstFive( Ints const& ints )
{
   // TODO
}


void countNumberOfFives( Ints const& ints )
{
   // TODO
}


void replaceAllFivesWithTwos( Ints& ints )
{
   // TODO
}


void sortInts( Ints& ints )
{
   // TODO
}


void findAllTwos( Ints const& ints )
{
   // TODO
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

