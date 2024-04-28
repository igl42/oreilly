/**************************************************************************************************
*
* \file StringViewAdd.cpp
* \brief C++ Training - Example for a std::string_view Problem with Generic Addition
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: The following code example contains a serious bug. Explain the bug and discuss a solution.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>


std::string operator+( std::string_view lhs, std::string_view rhs )
{
   return std::string( lhs ) + std::string( rhs );
}


template< typename T >
T add( const T& lhs, const T& rhs )
{
   return lhs + rhs;
}


int main()
{
   std::string s1{ "Hello," };
   std::string s2{ " World" };

   std::string_view sv1{ s1 };
   std::string_view sv2{ s2 };

   const auto result = add( sv1, sv2 );

   std::cout << "\n result = " << result << "\n\n";

   return EXIT_SUCCESS;
}
