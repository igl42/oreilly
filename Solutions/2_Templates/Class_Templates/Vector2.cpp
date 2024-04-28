/**************************************************************************************************
*
* \file Vector2.cpp
* \brief C++ Training - Class Template Programming Task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Add an 'emplace_back()' function to the 'Vector' class template.
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


template< typename Type, typename Allocator = std::allocator<Type> >
class Vector
{
 public:
   using iterator       = Type*;
   using const_iterator = const Type*;

   Vector() = default;
   Vector( const Vector& sv );
   Vector( Vector&& sv );

   Vector& operator=( const Vector& sv );
   Vector& operator=( Vector&& sv );
   Vector& operator=( std::initializer_list<Type> list );

   ~Vector();

   void push_back( const Type& s );
   void push_back( Type&& s );

   template< typename... Args >
   void emplace_back( Args&&... args );

   size_t size() const;
   size_t capacity() const;

   Type&       operator[]( size_t index );
   const Type& operator[]( size_t index ) const;

   iterator       begin();
   iterator       end();
   const_iterator begin() const;
   const_iterator end()   const;

   void swap( Vector& sv );

 private:
   void reallocate();
   void free();

   Type* begin_{ nullptr };
   Type* end_  { nullptr };
   Type* final_{ nullptr };

   static Allocator alloc;
};

template< typename Type, typename Allocator >
Allocator Vector<Type,Allocator>::alloc;


template< typename Type, typename Allocator >
Vector<Type,Allocator>::Vector( const Vector& sv )
   : begin_( alloc.allocate( sv.size() ) )
   , end_  ( std::uninitialized_copy( sv.begin(), sv.end(), begin_ ) )
   , final_( end_ )
{}


template< typename Type, typename Allocator >
Vector<Type,Allocator>::Vector( Vector&& sv )
   : begin_( sv.begin_ )
   , end_  ( sv.end_   )
   , final_( sv.final_ )
{
   sv.begin_ = nullptr;
   sv.end_   = nullptr;
   sv.final_ = nullptr;
}


template< typename Type, typename Allocator >
Vector<Type,Allocator>& Vector<Type,Allocator>::operator=( const Vector& sv )
{
   Vector tmp( sv );
   swap( tmp );
   return *this;
}


template< typename Type, typename Allocator >
Vector<Type,Allocator>& Vector<Type,Allocator>::operator=( Vector&& sv )
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


template< typename Type, typename Allocator >
Vector<Type,Allocator>& Vector<Type,Allocator>::operator=( std::initializer_list<Type> list )
{
   Vector tmp;
   for( const Type& s : list ) {
      tmp.push_back( s );
   }
   swap( tmp );
   return *this;
}


template< typename Type, typename Allocator >
Vector<Type,Allocator>::~Vector()
{
   free();
}


template< typename Type, typename Allocator >
void Vector<Type,Allocator>::push_back( const Type& v )
{
   if( end_ == final_ ) {
      reallocate();
   }

   ::construct_at( end_, v );  // or since C++20 std::construct_at
   ++end_;
}


template< typename Type, typename Allocator >
void Vector<Type,Allocator>::push_back( Type&& v )
{
   if( end_ == final_ ) {
      reallocate();
   }

   ::construct_at( end_, std::move(v) );  // or since C++20 std::construct_at
   ++end_;
}


template< typename Type, typename Allocator >
template< typename... Args >
void Vector<Type,Allocator>::emplace_back( Args&&... args )
{
   if( end_ == final_ ) {
      reallocate();
   }

   ::construct_at( end_, std::forward<Args>(args)... );  // or since C++20 std::construct_at
   ++end_;
}


template< typename Type, typename Allocator >
size_t Vector<Type,Allocator>::size() const
{
   return end_ - begin_;
}


template< typename Type, typename Allocator >
size_t Vector<Type,Allocator>::capacity() const
{
   return final_ - begin_;
}


template< typename Type, typename Allocator >
Type& Vector<Type,Allocator>::operator[]( size_t index )
{
   return begin_[index];
}


template< typename Type, typename Allocator >
const Type& Vector<Type,Allocator>::operator[]( size_t index ) const
{
   return begin_[index];
}


template< typename Type, typename Allocator >
typename Vector<Type,Allocator>::iterator Vector<Type,Allocator>::begin()
{
   return begin_;
}

template< typename Type, typename Allocator >
typename Vector<Type,Allocator>::iterator Vector<Type,Allocator>::end()
{
   return end_;
}

template< typename Type, typename Allocator >
typename Vector<Type,Allocator>::const_iterator Vector<Type,Allocator>::begin() const
{
   return begin_;
}

template< typename Type, typename Allocator >
typename Vector<Type,Allocator>::const_iterator Vector<Type,Allocator>::end() const
{
   return end_;
}


template< typename Type, typename Allocator >
void Vector<Type,Allocator>::swap( Vector& sv )
{
   using std::swap;

   swap( begin_, sv.begin_ );
   swap( end_  , sv.end_   );
   swap( final_, sv.final_ );
}


template< typename Type, typename Allocator >
void Vector<Type,Allocator>::reallocate()
{
   const size_t n = ( size() ? 2*size() : 1UL );

   auto newbegin( alloc.allocate( n ) );
   auto newend  ( std::uninitialized_copy( begin_, end_, newbegin ) );

   free();

   begin_ = newbegin;
   end_   = newend;
   final_ = begin_ + n;
}


template< typename Type, typename Allocator >
void Vector<Type,Allocator>::free()
{
   ::destroy( begin_, end_ );  // or since C++17 std::destroy
   alloc.deallocate( begin_, capacity() );
}


template< typename Type, typename Allocator >
std::ostream& operator<<( std::ostream& os, const Vector<Type,Allocator>& sv )
{
   os << "(";
   for( const auto& s : sv ) {
      os << " \"" << s << "\"";
   }
   return os << " )";
}


int main()
{
   Vector<std::string> sv;
   sv.push_back( "Bjarne"s );
   sv.push_back( "Herb"s );
   sv.push_back( "Nicolai"s );

   Vector<std::string> sv2( std::move(sv) );

   std::cout << "\n" << sv2 << "\n\n";

   Vector<std::string> sv3;
   sv3.emplace_back( 5, 'a' );
   sv3.emplace_back( 3, 'b' );

   sv2 = std::move(sv3);

   std::cout << "\n" << sv2 << "\n\n";

   return EXIT_SUCCESS;
}
