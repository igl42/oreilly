/**************************************************************************************************
*
* \file PackIndexing.cpp
* \brief C++ Training - Variadic Template Programming Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'index_pack()' function, which receives a compile time index and a
*       parameter pack, and returns the indexed element of the parameter pack.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <typeinfo>
#include <type_traits>


// TODO: Implement the 'index_pack()' function, which receives a compile time index and a
//       parameter pack, and returns the indexed element of the parameter pack.
//template< size_t I, typename T, typename... Ts >
//??? index_pack( T&& value, Ts&&... values );


int main()
{
   //==== Indexing an lvalue ====
   /*
   {
      int i = 2;
      decltype(auto) res = index_pack<2>( 0, 1, i, 3, 4 );
      using T = decltype(res);

      std::cout << "\n"
                << " typeid(res) = " << typeid(res).name() << "\n"
                << " std::is_lvalue_reference_v<T> = " << std::is_lvalue_reference_v<T> << "\n"
                << " std::is_rvalue_reference_v<T> = " << std::is_rvalue_reference_v<T> << "\n"
                << "\n";
   }
   */

   //==== Indexing an rvalue ====
   /*
   {
      decltype(auto) res = index_pack<2>( 0, 1, 2, 3, 4 );
      using T = decltype(res);

      std::cout << "\n"
                << " typeid(res) = " << typeid(res).name() << "\n"
                << " std::is_lvalue_reference_v<T> = " << std::is_lvalue_reference_v<T> << "\n"
                << " std::is_rvalue_reference_v<T> = " << std::is_rvalue_reference_v<T> << "\n"
                << "\n";
   }
   */

   return EXIT_SUCCESS;
}
