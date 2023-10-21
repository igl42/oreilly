/**************************************************************************************************
*
* \file MinMax.cpp
* \brief C++ Training - Function Template C++ Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Write a 'minmax()' function template that takes a single template parameter for its
*         two function parameters.
*
* Step 2: Write a 'minmax()' function template that takes two template parameters instead of
*         one (one for each function parameter).
*
* Step 3: Overload the 'minmax()' function template for integers.
*
* Step 4: Specialize the 'minmax()' function template(s) for integers.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <utility>


// Step 1: Definition of the 'minmax()' function template with a single template argument
// TODO


// Step 2: Definition of the 'minmax()' function template with a two template arguments
// TODO


// Step 3: Overload of the 'minmax()' function
// TODO


// Step 4: Specialization of the 'minmax()' function template with a single template argument
// TODO


// Step 4: Specialization of the 'minmax()' function template with two template arguments
// TODO


// Auxiliary helper function to print 'std::pair'
template< typename T1, typename T2 >
std::ostream& operator<<( std::ostream& os, std::pair<T1,T2> const& p )
{
   return os << "(" << p.first << "," << p.second << ")";
}


int main()
{
   std::cout << "\n"
                //" minmax( 1, 5 )    = " << minmax( 1, 5 ) << "\n"
                //" minmax( 3, 2 )    = " << minmax( 3, 2 ) << "\n"
                //" minmax( 1.2, -4 ) = " << minmax( 1.2, -4 ) << "\n"
                //" minmax( 1, 2.8 )  = " << minmax( 1, 2.8 ) << "\n"
                "\n";

   return EXIT_SUCCESS;
}
