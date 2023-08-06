/**************************************************************************************************
*
* \file VariadicMinMax.cpp
* \brief C++ Training - Function Template C++ Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Extend the 'minmax()' function template for an arbitrary number of elements.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <utility>


// Definition of the 'minmax()' function template
template< typename T1, typename T2 >
inline auto minmax( T1 const& a, T2 const& b )
   -> std::pair< std::common_type_t<T1,T2>, std::common_type_t<T1,T2> >
{
   if( a < b )
      return std::make_pair( a, b );
   else
      return std::make_pair( b, a );
}


// 'minmax()' function template for an arbitrary number of elements
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
                " minmax( 1, 5 )          = " << minmax( 1, 5 ) << "\n"
                " minmax( 3, 2 )          = " << minmax( 3, 2 ) << "\n"
                " minmax( 1.2, 2.3 )      = " << minmax( 1.2, 2.3 ) << "\n"
                " minmax( 1.2, -4 )       = " << minmax( 1.2, -4 ) << "\n"
                " minmax( 1, 2.8 )        = " << minmax( 1, 2.8 ) << "\n"
                //" minmax( 1, 5, 4 )       = " << minmax( 1, 5, 4 ) << "\n"
                //" minmax( 1, -1.3F, 2.3 ) = " << minmax( 1, -1.3F, 2.3 ) << "\n"
                "\n";

   return EXIT_SUCCESS;
}
