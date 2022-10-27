/**************************************************************************************************
*
* \file Sum.cpp
* \brief C++ Training - Variadic Template Programming Task
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Write a generic 'sum()' function that can compute the sum of an arbitrary number of
*       values of any type.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>


int sum( int i1, int i2 )
{
   return i1 + i2;
}

int sum( int i1, int i2, int i3 )
{
   return i1 + i2 + i3;
}

int sum( int i1, int i2, int i3, int i4 )
{
   return i1 + i2 + i3 + i4;
}

double sum( double i1, double i2 )
{
   return i1 + i2;
}

double sum( double i1, double i2, double i3 )
{
   return i1 + i2 + i3;
}

double sum( double i1, double i2, double i3, double i4 )
{
   return i1 + i2 + i3 + i4;
}


int main()
{
   const int    s1 = sum( -1, 2 );
   const int    s2 = sum( 3, -1, -2, 1 );
   const double s3 = sum( 4.2, -1.2 );
   const double s4 = sum( -2.5, 3.7, 2.8 );

   std::cout << "\n"
             << " s1 = " << s1 << "\n"
             << " s2 = " << s2 << "\n"
             << " s3 = " << s3 << "\n"
             << " s4 = " << s4 << "\n"
             << "\n";
}
