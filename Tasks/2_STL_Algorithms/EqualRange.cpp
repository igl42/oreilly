/**************************************************************************************************
*
* \file EqualRange.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: You have a large collection of players, sorted by score, and need to get all players
*       with a score between 10000 and 20000.
*
**************************************************************************************************/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>


struct Player
{
   std::string name{};
   int score{};
   // Potentially many more data members
};

// Hard-coded range of scores (10000-20000)
struct ScoreRange
{
   int min{};
   int max{};
};

// Implementation of the compare function for the 'equal_range()' algorithm
struct Comparator
{
   bool operator()( Player p, ScoreRange r ) const { return p.score < r.min; }  // Used by std::lower_bound
   bool operator()( ScoreRange r, Player p ) const { return r.max < p.score; }  // Used by std::upper_bound
};


int main()
{
   // The sorted range of players
   const std::vector<Player> players {
      Player{ "Denise" ,  5134 },
      Player{ "Stuart" ,  6034 },
      Player{ "Penny"  ,  8355 },
      Player{ "Berni"  ,  9111 },
      Player{ "Amy"    , 10234 },
      Player{ "Howard" , 11770 },
      Player{ "Raj"    , 14713 },
      Player{ "Leonard", 18064 },
      Player{ "Sheldon", 19112 },
      Player{ "Wil"    , 20112 },
      Player{ "Champ"  , 22063 }
   };

   // Finding all players with a score between 10000 and 20000 (using C++17 structured bindings)
   auto [low,upp] = std::equal_range( begin(players), end(players)
                                    , ScoreRange{ 10000, 20000 }, Comparator{} );

   // Printing the range of 5 players with a score between 10000 and 20000
   for( ; low!=upp; ++low ) {
      std::cout << " Player: " << low->name << ", score: " << low->score << "\n";
   }

   return EXIT_SUCCESS;
}

