/**************************************************************************************************
*
* \file Max_Assembly.cpp
* \brief C++ Training - Function Template C++ Example
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Copy-and-paste the following code into Compiler Explorer (i.e. 'godbolt.org').
*       Analyse the resulting assembly code of the given 'max()' implementations with
*       different compilers and a high optimization level (e.g. -O3 or /O2).
*
**************************************************************************************************/

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>
#include <type_traits>


//== Explicit max() implementation for integers and strings =======================================

constexpr int max( int a, int b )
{
   return ( a < b ? b : a );
}

inline std::string max( std::string const& a, std::string const& b )
{
   return ( a < b ? b : a );
}


//== Generic max() implementation =================================================================
/*
template< typename T1, typename T2 >
inline auto max( T1 const& a, T2 const& b )
{
   return ( a < b ) ? b : a;
}
*/


int main()
{
   {
      int a;
      int b;

      std::cin >> a >> b;

      std::cout << max( a, b );
   }

   /*
   {
      std::string a;
      std::string b;

      std::cin >> a >> b;

      std::cout << max( a, b );
   }
   */

   return EXIT_SUCCESS;
}
