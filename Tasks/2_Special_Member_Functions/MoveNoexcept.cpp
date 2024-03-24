/**************************************************************************************************
*
* \file MoveNoexcept.cpp
* \brief C++ Training - Example for Move Semantics
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Examine the influence of declaring the move operations 'noexcept' by means of creating
*       a 'std::vector' of strings.
*
**************************************************************************************************/

#include <algorithm>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


struct String
{
 public:
   String() = default;

   String( const char* s )
      : s_{ s }
   {}

   String( std::string s )
      : s_{ std::move(s) }
   {}

   ~String() = default;
   String( const String& ) = default;
   String& operator=( const String& ) = default;
   String( String&& ) noexcept(true) = default;
   String& operator=( String&& ) noexcept(true) = default;

 private:
   std::string s_;
};


int main()
{
   constexpr size_t N( 5000000 );

   std::vector<String> v;

   std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
   start = std::chrono::high_resolution_clock::now();

   for( size_t i=0UL; i<N; ++i ) {
      v.emplace_back( "A long string of 30 characters" );
   }

   end = std::chrono::high_resolution_clock::now();
   const std::chrono::duration<double> elapsedTime( end - start );
   const double seconds( elapsedTime.count() );

   std::cout << " Runtime: " << seconds << "s\n\n";

   return EXIT_SUCCESS;
}

