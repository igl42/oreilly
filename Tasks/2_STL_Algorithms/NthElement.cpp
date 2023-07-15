/**************************************************************************************************
*
* \file NthElement.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: You have a vector of points on a plane and need to find the K closest points to the
*       origin (0,0) in any order.
*
**************************************************************************************************/

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <random>


struct Point
{
   double x;
   double y;
};

double distance_to_origin( Point p )
{
   return std::sqrt( p.x*p.x + p.y*p.y );
}

double square_distance_to_origin( Point p )
{
   return p.x*p.x + p.y*p.y;
}

std::ostream& operator<<( std::ostream& os, Point p )
{
   return os << '(' << p.x << ',' << p.y << ')';
}


int main()
{
   // The range of points
   std::array<Point,12U> points {
      Point{  1.1, -2.3 },
      Point{ -0.2,  3.7 },
      Point{  2.3,  0.9 },
      Point{ -0.8, -0.4 },
      Point{  3.0, -1.9 },
      Point{ -0.5,  2.2 },
      Point{  1.7,  3.1 },
      Point{ -0.6, -1.3 },
      Point{  1.3, -0.2 },
      Point{ -2.9,  0.1 },
      Point{  0.1,  2.1 },
      Point{ -1.6, -1.3 }
   };

   // Shuffling the points
   std::random_device rd{};
   std::shuffle( begin(points), end(points), rd );

   // Select the number of required points
   constexpr size_t K( 3U );
   static_assert( K > 0U && K < 12U );

   // Determining the K closest points to the origin
   std::nth_element( begin(points), begin(points)+K-1U, end(points),
      []( Point p1, Point p2 ){
         return square_distance_to_origin(p1) < square_distance_to_origin(p2);
      } );

   // Printing the final order of points
   for( Point point : points ) {
      std::cout << point << " (distance = " << distance_to_origin(point) << ")\n";
   }

   return EXIT_SUCCESS;
}

