/**************************************************************************************************
*
* \file STLMax.cpp
* \brief C++ Training - An improved implementation of the STL max() function
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement an improved max() algorithm that is able to efficiently deal with lvalues and
*       rvalues.
*
**************************************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <type_traits>


struct S
{
   S() { puts( "S()" ); }
   S( const S& ) { puts( "S(const S&)" ); }
   S( S&& ) { puts( "S(S&&)" ); }
   S& operator=( const S& ) { puts( "operator=(const S&)" ); return *this; }
   S& operator=( S&& ) { puts( "operator=(S&&)" ); return *this; };
   ~S() { puts( "~S()" ); }
};

bool operator<( const S& s1, const S& s2 ) noexcept
{
   return true;
}


template< typename T >
const T& max( const T& a, const T& b )
{
   return a < b ? b : a;
}


int main()
{
   S s1{};
   S s2{};

   //==== lvalue/lvalue ====
   {
      std::cout << "\n ==== lvalue/lvalue ====\n";
      decltype(auto) result = max( s1, s2 );
      using Result = decltype(result);
      std::cout << " typeid(result) = " << typeid(result).name() << "\n"
                << "   is_lvalue_reference = " << std::is_lvalue_reference<Result>::value << "\n"
                << "   is_rvalue_reference = " << std::is_rvalue_reference<Result>::value << "\n"
                << "\n";
   }

   //==== lvalue/rvalue ====
   {
      std::cout << "\n ==== lvalue/rvalue ====\n";
      decltype(auto) result = max( s1, S{} );
      using Result = decltype(result);
      std::cout << " typeid(result) = " << typeid(result).name() << "\n"
                << "   is_lvalue_reference = " << std::is_lvalue_reference<Result>::value << "\n"
                << "   is_rvalue_reference = " << std::is_rvalue_reference<Result>::value << "\n"
                << "\n";
   }

   //==== rvalue/lvalue ====
   {
      std::cout << "\n ==== rvalue/lvalue ====\n";
      decltype(auto) result = max( S{}, s2 );
      using Result = decltype(result);
      std::cout << " typeid(result) = " << typeid(result).name() << "\n"
                << "   is_lvalue_reference = " << std::is_lvalue_reference<Result>::value << "\n"
                << "   is_rvalue_reference = " << std::is_rvalue_reference<Result>::value << "\n"
                << "\n";
   }

   //==== rvalue/rvalue ====
   {
      std::cout << "\n ==== rvalue/rvalue ====\n";
      decltype(auto) result = max( S{}, S{} );
      using Result = decltype(result);
      std::cout << " typeid(result) = " << typeid(result).name() << "\n"
                << "   is_lvalue_reference = " << std::is_lvalue_reference<Result>::value << "\n"
                << "   is_rvalue_reference = " << std::is_rvalue_reference<Result>::value << "\n"
                << "\n";
   }

   return EXIT_SUCCESS;
}
