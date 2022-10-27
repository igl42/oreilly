/**************************************************************************************************
*
* \file VariadicMax.cpp
* \brief C++ Training - Function Template C++ Example
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Extend the 'max()' function template for an arbitrary number of elements.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>


// Definition of the 'max()' function template
template< typename T1, typename T2 >
inline auto max( T1 const& a, T2 const& b )
//   -> std::common_type_t<T1,T2>    // Trailing return type necessary for C++11
{
   return ( a < b ) ? b : a;
}


// 'max()' function template for an arbitrary number of elements
// TODO


int main()
{
   std::cout << "\n"
                " max( 1, 5 )          = " << max( 1, 5 ) << "\n"
                " max( 3, 2 )          = " << max( 3, 2 ) << "\n"
                " max( 1.2, 2.3 )      = " << max( 1.2, 2.3 ) << "\n"
                " max( 1.2, -4 )       = " << max( 1.2, -4 ) << "\n"
                " max( 1, 2.8 )        = " << max( 1, 2.8 ) << "\n"
                //" max( 1, 5, 4 )       = " << max( 1, 5, 4 ) << "\n"
                //" max( 1, -1.3F, 2.3 ) = " << max( 1, -1.3F, 2.3 ) << "\n"
                "\n";

   return EXIT_SUCCESS;
}
