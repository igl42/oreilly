/**************************************************************************************************
*
* \file IsPunct.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Write a program to strip the punctuation from a std::string. The input to the
*       program should be a string of characters including punctuation. The output should
*       be a std::string in which the punctuation is removed.
*
**************************************************************************************************/

#include <algorithm>
#include <cctype>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <random>
#include <string>


std::string generateString( std::size_t size )
{
   constexpr double percentage( 0.2 );  // Percentage of punctation characters [0..1]

   std::string s( size, 'a' );

   const size_t num( size * percentage );
   std::fill( s.begin(), s.begin() + num, '!' );

   std::random_device rd{};
   std::mt19937 mt{ rd() };
   std::shuffle( begin(s), end(s), mt );

   return s;
}


int main()
{
   std::string s{};

   // Manual entry
   std::cout << "\n Enter a string: ";
   std::cin >> s;

   // Automatic generation
   //s = generateString( 1000UL );

   std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
   start = std::chrono::high_resolution_clock::now();


   s.erase( std::remove_if( s.begin(), s.end(), ispunct ), s.end() );


   end = std::chrono::high_resolution_clock::now();
   const std::chrono::duration<double> elapsedTime( end - start );
   const double seconds( elapsedTime.count() );

   std::cout << " The string without punctuation: '" << s << "' (length=" << s.size() << ")\n";
   std::cout << " Runtime: " << seconds << "s\n\n";

   return EXIT_SUCCESS;
}

