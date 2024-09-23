/**************************************************************************************************
*
* \file CopyOperations.cpp
* \brief C++ Training - Example for Compiler Generated Functions
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Consider the given vector class. Assume that the shown constructors, destructors,
*       and assignment operators are properly implemented. However, the following code
*       has several memory issues. Explain the reason for this behavior.
*
**************************************************************************************************/

#include <cstdlib>


template< typename Type >
class Vector
{
 public:
   explicit Vector( size_t size )
      : size_( size )
      , v_   ( new Type[size] )
   {}

   ~Vector() { delete[] v_; }

   template< typename Other >
   Vector( const Vector<Other>& v )
   {
      /* Initialize the vector as copy of v */
   }

   template< typename Other >
   const Vector& operator=( const Vector<Other>& v )
   {
      /* Copy the contents of v into this vector */
   }

   // ...

 private:
   size_t size_;  // Current size of the vector
   Type* v_;      // Dynamically allocated vector elements
   // ...
};


int main()
{
   Vector<double> a( 5 );
   Vector<double> b( a );  // Potential memory corruption!
   Vector<double> c( 5 );
   c = a;  // Potential memory corruption!

   return EXIT_SUCCESS;
}
