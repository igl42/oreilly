/**************************************************************************************************
*
* \file BadRemove.cpp
* \brief C++ Training - Standard Library Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Explain the error in the following program.
*
**************************************************************************************************/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <vector>


int main()
{
   std::vector<int> vec{ 1, -3, 27, 42, 4, -8, 22, 42, 37, 4, 18, 9 };

   vec.erase( std::remove( begin(vec), end(vec)
                         , *std::max_element( begin(vec), end(vec) ) )
            , end(vec) );

   //vec.erase(
   //   std::remove_if( begin(vec), end(vec)
   //                 , [&value=*std::max_element( begin(vec), end(vec) )](int i) {
   //                      return i == value;
   //                   } ),
   //   end(vec) );

   std::cout << "\n"
             << " Expected result: ( 1 -3 27 4 -8 22 37 4 18 9 )\n"
             << " Actual result  : ( ";
   std::copy( vec.begin(), vec.end(), std::ostream_iterator<int>( std::cout, " " ) );
   std::cout << ")\n\n";

   return EXIT_SUCCESS;
}

