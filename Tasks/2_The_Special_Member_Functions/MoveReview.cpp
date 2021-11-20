/**************************************************************************************************
*
* \file MoveReview.cpp
* \brief C++ Training - Programming Example for Move Operations and RVO
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Review the implementation of the wordFrequency() function and analyze it with respect
*       to rvalues and unnecessary, expensive copy operations.
*
**************************************************************************************************/

#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <numeric>
#include <type_traits>
#include <vector>


// Possible implementation of std::inner_product
/*
template<class InputIt1, class InputIt2,
         class T,
         class BinaryOperation1, class BinaryOperation2>
T inner_product(InputIt1 first1, InputIt1 last1,
                InputIt2 first2, T init,
                BinaryOperation1 op1
                BinaryOperation2 op2)
{
    while (first1 != last1) {
         init = op1(init, op2(*first1, *first2));
         ++first1;
         ++first2;
    }
    return init;
}
*/


// Analyse the word_frequency() function with respect to rvalues and unnecessary, expensive
// copy operations.
auto word_frequency( const std::vector<std::string>& words )
{
   using dictionary = std::map<std::string,long>;

   const std::vector<long> values( words.size(), 1L );

   return std::inner_product(
      std::begin(words), std::end(words),
      std::begin(values),
      dictionary{},
      []( dictionary& lhs, const dictionary& rhs ) -> dictionary {
         for( const auto& pair : rhs ) { lhs[pair.first] += pair.second; }
         return lhs;
      },
      []( const std::string& s, long value ) -> dictionary {
         return dictionary{ std::make_pair(s,value) };
      } );
}


int main()
{
   std::vector<std::string> v{ "A", "C", "G", "A", "D", "C", "E", "A", "D", "G", "F", "B" };

   // Create a dictionary with the given vector of strings
   const auto dict( word_frequency( v ) );

   std::cout << "\n";
   for( const auto& pair : dict )
      std::cout << " word = " << std::quoted(pair.first) << ", count = " << pair.second << "\n";
   std::cout << "\n\n";

   return EXIT_SUCCESS;
}
