/**************************************************************************************************
*
* \file FixedVector.cpp
* \brief C++ Training - Class Design Example
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the class template 'FixedVector'. A fixed vector represents a hybrid between
*       std::vector and std::array, i.e. it holds a maximum number of elements in static memory
*       but can be resized within this bound.
*
*         template< typename Type      // Type of the elements
*                   size_t Capacity >  // Maximum number of elements
*         class FixedVector;
*
*       The following functions are required:
*       1.  A default constructor
*       2.  A constructor taking the initial size
*       3.  A constructor taking the initial size and initial value of all elements
*       4.  A copy constructor
*       5.  A move constructor
*       6.  A function to query the current number of elements
*       7.  A function to query the maximum number of elements
*       8.  A function to access elements
*       9.  Functions for the STL conformant iteration over elements
*       10. A copy assignment operator
*       11. A move assignment operator
*       12. A function to add elements at the end of the vector
*       13. A function to change the number of current elements
*
**************************************************************************************************/

//---- BEGIN OF <FixedVector.h> -------------------------------------------------------------------

#ifndef FIXEDVECTOR_H
#define FIXEDVECTOR_H

#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdlib>
#include <memory>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "Span.h"


template< typename T, typename... Args >
void create_at( T* p, Args&&... value )
{
   ::new (p) T{ std::forward<Args>( value )... };
}


template< typename T >
void destroy_at( T* p )
{
   p->~T();
}


template< typename ForwardIt >
void destroy( ForwardIt first, ForwardIt last )
{
   for( ; first != last; ++first ) {
      destroy_at( std::addressof( *first ) );
   }
}


template< typename Type, size_t Capacity >
class FixedVector final
{
 public:
   using value_type     = Type;
   using iterator       = Type*;
   using const_iterator = Type const*;

 private:
   template< typename U >
   using enable_if_is_convertible =
      std::enable_if_t< std::is_convertible<U,value_type>::value, bool >;

 public:
   FixedVector() = default;

   explicit FixedVector( size_t size, Type const& value = Type{} )
      : size_{ size }
   {
      checkSize( size );
      std::uninitialized_fill( begin(), end(), value );
   }

   template< typename U, enable_if_is_convertible<U> = true >
   FixedVector( std::span<U> s )
      : size_{ s.size() }
   {
      checkSize( s.size() );
      std::uninitialized_copy( s.begin(), s.end(), begin() );
   }

   FixedVector( FixedVector const& other )
      : size_{ other.size_ }
   {
      std::uninitialized_copy( other.begin(), other.end(), begin() );
   }

   template< typename U, size_t M, enable_if_is_convertible<U> = true >
   FixedVector( FixedVector<U,M> const& other )
      : size_{ other.size() }
   {
      checkSize( other.size() );
      std::uninitialized_copy( other.begin(), other.end(), begin() );
   }

   FixedVector( FixedVector&& other ) noexcept
      : size_{ other.size_ }
   {
      //std::uninitialized_copy( other.begin(), other.end(), begin() );  // C++14
      std::uninitialized_move( other.begin(), other.end(), begin() );  // C++17
      destroy( other.begin(), other.end() );
      other.size_ = 0U;
   }

   ~FixedVector()
   {
      destroy( begin(), end() );
   }

   size_t size() const noexcept { return size_; }
   size_t capacity() const noexcept { return Capacity; }

   Type* data() noexcept
   {
      // Solution 1
      return reinterpret_cast<Type*>( raw_ );

      // Solution 2
      //return storage_.v_;
   }

   Type const* data() const noexcept
   {
      // Solution 1
      return reinterpret_cast<Type const*>( raw_ );

      // Solution 2
      //return storage_.v_;
   }

   Type& operator[]( size_t index ) noexcept
   {
      assert( index < size_ );
      return data()[index];
   }

   Type const& operator[]( size_t index ) const noexcept
   {
      assert( index < size_ );
      return data()[index];
   }

   Type& at( size_t index )
   {
      if( index >= size_ ) {
         throw std::invalid_argument( "Out-of-bounds access detected" );
      }
      return (*this)[index];
   }

   Type const& at( size_t index ) const
   {
      if( index >= size_ ) {
         throw std::invalid_argument( "Out-of-bounds access detected" );
      }
      return (*this)[index];
   }

   iterator       begin()        noexcept { return data(); }
   const_iterator begin()  const noexcept { return data(); }
   const_iterator cbegin() const noexcept { return data(); }
   iterator       end()          noexcept { return data() + size_; }
   const_iterator end()    const noexcept { return data() + size_; }
   const_iterator cend()   const noexcept { return data() + size_; }

   FixedVector& operator=( FixedVector const& other )
   {
      resize( other.size() );
      std::copy( other.begin(), other.end(), begin() );
      return *this;
   }

   template< typename U, size_t M, enable_if_is_convertible<U> = true >
   FixedVector& operator=( FixedVector<U,M> const& other )
   {
      if( other.size() > Capacity ) {
         throw std::invalid_argument( "Invalid number of elements" );
      }

      resize( other.size() );
      std::copy( other.begin(), other.end(), begin() );
      return *this;
   }

   FixedVector& operator=( FixedVector&& other ) noexcept
   {
      resize( other.size() );
      std::move( other.begin(), other.end(), begin() );
      destroy( other.begin(), other.end() );
      other.size_ = 0U;
      return *this;
   }

   void push_back( Type const& value )
   {
      //Expects( size_ <= Capacity )    // Design by Contract; see I.6

      if( size_ == Capacity ) {
         throw std::invalid_argument( "Capacity depleted" );
      }

      create_at( end(), value );
      ++size_;

      //Ensures( size_ <= Capacity );   // Design by Contract; see I.8
   }

   void push_back( Type&& value )
   {
      //Expects( size_ <= Capacity )    // Design by Contract; see I.6

      if( size_ == Capacity ) {
         throw std::invalid_argument( "Capacity depleted" );
      }

      create_at( end(), std::move( value ) );
      ++size_;

      //Ensures( size_ <= Capacity );   // Design by Contract; see I.8
   }

   template< typename... Args >
   void emplace_back( Args&&... args )
   {
      //Expects( size_ <= Capacity )    // Design by Contract; see I.6

      if( size_ == Capacity ) {
         throw std::invalid_argument( "Capacity depleted" );
      }

      create_at( end(), std::forward<Args>( args )... );
      ++size_;

      //Ensures( size_ <= Capacity );   // Design by Contract; see I.8
   }

   void resize( size_t size )
   {
      //Expects( size_ <= Capacity )    // Design by Contract; see I.6

      checkSize( size );

      if( size > size_ ) {
         std::uninitialized_fill( data()+size_, data()+size_+size, Type{} );
      }
      else if( size < size_ ) {
         destroy( data()+size, data()+size_ );
      }

      size_ = size;

      //Ensures( size_ <= Capacity );   // Design by Contract; see I.8
   }

 private:
   void checkSize( size_t size )
   {
      if( size > Capacity ) {
         throw std::invalid_argument( "Invalid number of elements" );
      }
   }

   // Solution 1
   alignas(Type) std::byte raw_[Capacity*sizeof(Type)];
   size_t size_{ 0U };

   // Solution 2
   //union Storage {
   //   Storage() {}
   //   ~Storage() {}
   //   std::byte raw_[Capacity*sizeof(Type)];
   //   Type v_[Capacity];
   //} storage_;
   //size_t size_{ 0U };
};

#endif

//---- END OF <FixedVector.h> ---------------------------------------------------------------------


//---- <Main.cpp> ---------------------------------------------------------------------------------

#include <iostream>

template< typename Type, size_t Capacity >
std::ostream& operator<<( std::ostream& os, FixedVector<Type,Capacity> const& v )
{
   os << "(";
   for( auto const& value : v )
      os << " " << value;
   os << " )";
   return os;
}


struct Test
{
   Test() { puts( "Test()" ); }
   Test( int j ) : i( j ) { puts( "Test(int)" ); }
   ~Test() { puts( "~Test()" ); }
   Test( Test const& t ) { i = t.i; puts( "Test(Test const&)" ); }
   Test( Test&& t ) { i = t.i; puts( "Test(Test&&)" ); }
   Test& operator=( Test const& t ) { i = t.i; puts( "Test& operator=(Test const&)" ); return *this; }
   Test& operator=( Test&& t ) { i = t.i; puts( "Test& operator=(Test&&)" ); return *this; }

   int i{ 0 };
};

std::ostream& operator<<( std::ostream& os, Test const& test )
{
   return os << test.i;
}


int main()
{
   // Default constructor
   /*
   {
      FixedVector<int,5> v{};
      std::cout << " Default vector: " << v << "\n";
   }
   */

   // Fixed vector with initial size
   /*
   {
      FixedVector<int,5> v( 4UL );
      std::cout << " Sized vector: " << v << "\n";
   }
   */

   // Fixed vector with initial size and initial value
   /*
   {
      FixedVector<int,5> v( 4UL, 3 );
      std::cout << " Sized vector: " << v << "\n";
   }
   */

   // Copy construction
   /*
   {
      FixedVector<int,5> a( 4UL, 3 );
      FixedVector<int,5> b( a );
      std::cout << " Copied vector: " << b << "\n";
   }
   */

   // Addition of individual elements
   /*
   {
      FixedVector<int,5> v{};
      v.push_back( 1 );
      v.push_back( 2 );
      v.push_back( 3 );
      std::cout << " Individual vector: " << v << "\n";
   }
   */

   // Access to individual elements
   /*
   {
      FixedVector<int,5> v{};
      v.resize( 3 );
      v[0] = 1;
      v[1] = 2;
      v[2] = 3;
      std::cout << " Individual vector: " << v << "\n";
   }
   */

   // Copy assignment
   /*
   {
      FixedVector<int,5> a( 4UL, 3 );
      FixedVector<int,5> b{};
      b = a;
      std::cout << " Copied vector: " << b << "\n";
   }
   */

   return EXIT_SUCCESS;
}

