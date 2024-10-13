/**************************************************************************************************
*
* \file PrintTuple.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Write an output operator for a tuple of variadic size and content.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>
#include <tuple>

using namespace std::string_literals;


//---- <PrintTuple.h> -----------------------------------------------------------------------------

template< typename... Args >
std::ostream& operator<<( std::ostream& os, std::tuple<Args...> const& tuple )
{
   // TODO
   return os;
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // std::tuple<int,int,int>
   {
      std::tuple t = std::make_tuple( 1, 2, 3 );
      std::cout << t << '\n';
   }

   // std::tuple<int,double,std::string>
   {
      std::tuple t = std::make_tuple( 42, 3.14, "C++Training"s );
      std::cout << t << '\n';
   }

   return EXIT_SUCCESS;
}
