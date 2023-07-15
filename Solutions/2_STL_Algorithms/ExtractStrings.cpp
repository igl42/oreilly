/**************************************************************************************************
*
* \file ExtractStrings.cpp
* \brief C++ Training - Algorithm Programming Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'extract_strings()' algorithm. The algorithm should extract all strings
*       from a long string of space-separated words.
*
*       Example:
*          "Hello World" -> "Hello" & "World"
*
**************************************************************************************************/

#include <algorithm>
#include <cctype>
#include <iterator>
#include <iostream>
#include <string>
#include <vector>


template< typename OutputIterator >
void extract_strings( std::string s, OutputIterator out )
{
   auto pos = begin(s);

   while( pos != end(s) )
   {
      const auto beginWord = std::find_if_not( pos, end(s), isspace );
      const auto endWord   = std::find_if( beginWord, end(s), isspace );

      if( beginWord != endWord ) {
         *out = std::string( beginWord, endWord );
         ++out;
      }

      pos = endWord;
   }
}


int main()
{
   std::string s( "Long string with many words separated by spaces inside" );
   std::vector<std::string> words{};

   extract_strings( s, std::back_inserter<std::vector<std::string>>( words ) );

   std::cout << " Extracted strings:\n";
   for( const std::string& s : words ) {
      std::cout << "   " << s << '\n';
   }
}
