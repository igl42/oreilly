/**************************************************************************************************
*
* \file PolymorphicAllocator.cpp
* \brief C++ Training - Example for the application of Type Erasure
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'PolymorphicAllocator' class by means of Type Erasure. 'PolymorphicAllocator'
*       may require all types to provide an 'allocate()' and a 'deallocate()' member function.
*
**************************************************************************************************/

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <numeric>
#include <string>


template< typename T >
class PolymorphicAllocator
{
   // TODO: Implement the 'PolymorphicAllocator' class by means of Type Erasure.
};


template< typename T >
class Allocator
{
 public:
   using value_type    = T;         //!< Type of the allocated values.
   using pointer       = T*;        //!< Type of a pointer to the allocated values.
   using const_pointer = const T*;  //!< Type of a pointer-to-const to the allocated values.

   template< typename T2 >
   struct rebind
   {
      using other = Allocator<T2>;
   };

   /*[[nodiscard]]*/ pointer allocate( std::size_t n )
   {
      return reinterpret_cast<pointer>( ::operator new[]( n*sizeof(T) ) );
   }

   void deallocate( pointer ptr, std::size_t /*n*/ ) noexcept
   {
      ::operator delete[]( ptr );
   }

   template< typename T1, typename T2 >
   friend bool operator==( const Allocator<T1>& lhs, const Allocator<T2>& rhs ) noexcept
   {
      return true;
   }

   template< typename T1, typename T2 >
   friend bool operator!=( const Allocator<T1>& lhs, const Allocator<T2>& rhs ) noexcept
   {
      return false;
   }
};


int main()
{
   /*
   {
      PolymorphicAllocator<int> pa1{ std::allocator<int>{} };
      int* array = pa1.allocate( 5UL );
      std::iota( array, array+5UL, 1UL );
      for( size_t i=0UL; i<5UL; ++i ) {
         std::cout << " " << array[i];
      }
      std::cout << "\n";
      pa1.deallocate( array, 5UL );
   }

   {
      PolymorphicAllocator<std::string> pa1{ Allocator<std::string>{} };
      std::string* array = pa1.allocate( 5UL );
      std::uninitialized_fill( array, array+5UL, "Example" );
      for( size_t i=0UL; i<5UL; ++i ) {
         std::cout << " " << array[i];
      }
      std::cout << "\n";
      pa1.deallocate( array, 5UL );
   }
   */

   return EXIT_SUCCESS;
}

