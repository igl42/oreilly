/**************************************************************************************************
*
* \file Vector1.cpp
* \brief C++ Training - Class Template Programming Task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Rework the 'StringVector' class to a class template named 'Vector'.
*
**************************************************************************************************/

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>

using std::size_t;
using namespace std::string_literals;


template< typename T, typename... Args >
constexpr T* construct_at( T* p, Args&&... args )
{
   void* address = const_cast<void*>(static_cast<const volatile void*>(p));
   return ::new (address) T( std::forward<Args>(args)... );
}


template< typename T >
constexpr void destroy_at( T* p )
{
   p->~T();
}


template< typename ForwardIt >
constexpr void destroy( ForwardIt first, ForwardIt last )
{
   for( ; first!=last; ++first ) {
      ::destroy_at( std::addressof(*first) );  // or since C++17 std::destroy_at
   }
}


class StringVector
{
 public:
   using iterator       = std::string*;
   using const_iterator = const std::string*;

   StringVector() = default;
   StringVector( const StringVector& sv );
   StringVector( StringVector&& sv );

   StringVector& operator=( const StringVector& sv );
   StringVector& operator=( StringVector&& sv );

   ~StringVector();

   void   push_back( const std::string& s );
   void   push_back( std::string&& s );
   size_t size() const;
   size_t capacity() const;

   iterator       begin();
   iterator       end();
   const_iterator begin() const;
   const_iterator end()   const;

   void swap( StringVector& sv );

 private:
   void reallocate();
   void free();

   std::string* begin_{ nullptr };
   std::string* end_  { nullptr };
   std::string* final_{ nullptr };

   static std::allocator<std::string> alloc;
};

std::allocator<std::string> StringVector::alloc;


StringVector::StringVector( const StringVector& sv )
   : begin_( alloc.allocate( sv.size() ) )
   , end_  ( std::uninitialized_copy( sv.begin(), sv.end(), begin_ ) )
   , final_( end_ )
{}


StringVector::StringVector( StringVector&& sv )
   : begin_( sv.begin_ )
   , end_  ( sv.end_   )
   , final_( sv.final_ )
{
   sv.begin_ = nullptr;
   sv.end_   = nullptr;
   sv.final_ = nullptr;
}


StringVector& StringVector::operator=( const StringVector& sv )
{
   StringVector tmp( sv );
   swap( tmp );
   return *this;
}


StringVector& StringVector::operator=( StringVector&& sv )
{
   free();

   begin_ = sv.begin_;
   end_   = sv.end_;
   final_ = sv.final_;

   sv.begin_ = nullptr;
   sv.end_   = nullptr;
   sv.final_ = nullptr;

   return *this;
}


StringVector::~StringVector()
{
   free();
}


void StringVector::push_back( const std::string& s )
{
   if( end_ == final_ ) {
      reallocate();
   }

   ::construct_at( end_, s );  // or since C++20 std::construct_at
   ++end_;
}


void StringVector::push_back( std::string&& s )
{
   if( end_ == final_ ) {
      reallocate();
   }

   ::construct_at( end_, std::move(s) );  // or since C++20 std::construct_at
   ++end_;
}


size_t StringVector::size() const
{
   return end_ - begin_;
}


size_t StringVector::capacity() const
{
   return final_ - begin_;
}


StringVector::iterator StringVector::begin()
{
   return begin_;
}

StringVector::iterator StringVector::end()
{
   return end_;
}

StringVector::const_iterator StringVector::begin() const
{
   return begin_;
}

StringVector::const_iterator StringVector::end() const
{
   return end_;
}


void StringVector::swap( StringVector& sv )
{
   using std::swap;

   swap( begin_, sv.begin_ );
   swap( end_  , sv.end_   );
   swap( final_, sv.final_ );
}


void StringVector::reallocate()
{
   const size_t n = ( size() ? 2*size() : 1UL );

   auto newbegin( alloc.allocate( n ) );
   auto newend  ( std::uninitialized_copy( begin_, end_, newbegin ) );

   free();

   begin_ = newbegin;
   end_   = newend;
   final_ = begin_ + n;
}


void StringVector::free()
{
   ::destroy( begin_, end_ );  // or since C++17 std::destroy()
   alloc.deallocate( begin_, capacity() );
}


std::ostream& operator<<( std::ostream& os, const StringVector& sv )
{
   os << "(";
   for( const auto& s : sv ) {
      os << " \"" << s << "\"";
   }
   return os << " )";
}


int main()
{
   /*
   Vector<std::string> sv;
   sv.push_back( "Bjarne"s );
   sv.push_back( "Herb"s );
   sv.push_back( "Nicolai"s );

   Vector<std::string> sv2( std::move(sv) );

   std::cout << "\n" << sv2 << "\n\n";

   Vector<std::string> sv3;
   sv3.push_back( "Alexander" );
   sv3.push_back( "Andrei" );

   sv2 = std::move(sv3);

   std::cout << "\n" << sv2 << "\n\n";
   */

   return EXIT_SUCCESS;
}
