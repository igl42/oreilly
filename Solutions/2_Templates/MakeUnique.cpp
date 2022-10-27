/**************************************************************************************************
*
* \file MakeUnique.cpp
* \brief C++ Training - unique_ptr Example
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement a make_unique() function for the std::unique_ptr class template.
*
**************************************************************************************************/

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <utility>


//---- <Widget.h> ---------------------------------------------------------------------------------

// Auxiliary class for testing purposes
class Widget
{
 public:
   Widget()
   {
      std::cout << " Widget has been created (i=" << i_ << ")\n";
   }

   Widget( int i ) noexcept
      : i_( i )
   {
      std::cout << " Widget has been created (i=" << i_ << ")\n";
   }

   ~Widget() noexcept
   {
      std::cout << " Widget has been destroyed (i=" << i_ << ")\n";
   }

   void set( int i ) noexcept { i_ = i;    }
   int  get() const  noexcept { return i_; }

 private:
   int i_{ 0 };
};




//---- <memory> -----------------------------------------------------------------------------------

// Simplified implementation of the std::unique_ptr class template
template< typename T >
class unique_ptr
{
 public:
   using pointer = T*;

   constexpr unique_ptr();
   explicit  unique_ptr( T* ptr );
             unique_ptr( unique_ptr const& u ) = delete;
             unique_ptr( unique_ptr&& u ) noexcept;

   template< typename U >
   unique_ptr( unique_ptr<U>&& u ) noexcept;

   ~unique_ptr() noexcept;

   unique_ptr& operator=( unique_ptr const& u ) = delete;
   unique_ptr& operator=( unique_ptr&& u ) noexcept;

   template< typename U >
   unique_ptr& operator=( unique_ptr<U>&& u ) noexcept;

   T& operator*()  const { return *ptr_; }
   T* operator->() const { return ptr_;  }

 private:
   T* ptr_;

   template< typename U > friend class unique_ptr;
};


template< typename T >
constexpr unique_ptr<T>::unique_ptr()
   : ptr_( nullptr )
{}


template< typename T >
unique_ptr<T>::unique_ptr( T* ptr )
   : ptr_( ptr )
{}


template< typename T >
unique_ptr<T>::unique_ptr( unique_ptr&& u ) noexcept
   : ptr_( u.ptr_ )
{
   u.ptr_ = nullptr;
}


template< typename T >
template< typename U >
unique_ptr<T>::unique_ptr( unique_ptr<U>&& u ) noexcept
   : ptr_( u.ptr_ )
{
   u.ptr_ = nullptr;
}


template< typename T >
unique_ptr<T>::~unique_ptr() noexcept
{
   delete ptr_;
}


template< typename T >
unique_ptr<T>& unique_ptr<T>::operator=( unique_ptr&& u ) noexcept
{
   delete ptr_;
   ptr_ = u.ptr_;
   u.ptr_ = nullptr;
   return *this;
}


template< typename T >
template< typename U >
unique_ptr<T>& unique_ptr<T>::operator=( unique_ptr<U>&& u ) noexcept
{
   delete ptr_;
   ptr_ = u.ptr_;
   u.ptr_ = nullptr;
   return *this;
}


template< typename T
        , typename... Ts
        , std::enable_if_t< !std::is_array<T>::value >* = nullptr >
unique_ptr<T> make_unique( Ts&&... params )
{
   return unique_ptr<T>( new T( std::forward<Ts>( params )... ) );
}




template< typename T >
class unique_ptr<T[]>
{
 public:
   using pointer = T*;

   constexpr unique_ptr();
   explicit  unique_ptr( T* ptr );
             unique_ptr( unique_ptr const& u ) = delete;
             unique_ptr( unique_ptr&& u ) noexcept;

   ~unique_ptr() noexcept;

   unique_ptr& operator=( unique_ptr const& u ) = delete;
   unique_ptr& operator=( unique_ptr&& u ) noexcept;

   T& operator[]( size_t index ) const { return ptr_[index]; }

 private:
   T* ptr_;
};


template< typename T >
constexpr unique_ptr<T[]>::unique_ptr()
   : ptr_( nullptr )
{}


template< typename T >
unique_ptr<T[]>::unique_ptr( T* ptr )
   : ptr_( ptr )
{}


template< typename T >
unique_ptr<T[]>::unique_ptr( unique_ptr&& u ) noexcept
   : ptr_( u.ptr_ )
{
   u.ptr_ = nullptr;
}


template< typename T >
unique_ptr<T[]>::~unique_ptr() noexcept
{
   delete[] ptr_;
}


template< typename T >
unique_ptr<T[]>& unique_ptr<T[]>::operator=( unique_ptr&& u ) noexcept
{
   delete[] ptr_;
   ptr_ = u.ptr_;
   u.ptr_ = nullptr;
   return *this;
}


template< typename T
        , std::enable_if_t< std::is_array<T>::value >* = nullptr >
unique_ptr<T> make_unique( size_t size )
{
   return unique_ptr<T>( new typename std::remove_extent<T>::type[size]() );
}




//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // unique_ptr for a single Widget
   {
      auto a = make_unique<Widget>( 2 );
      std::cout << " a has been created (a=" << (*a).get() << ")\n\n";

      auto b = make_unique<Widget>( 3 );
      std::cout << " b has been created (b=" << b->get() << ")\n\n";

      //a = b;  // Compilation error!!!

      unique_ptr<const Widget> c( std::move( a ) );
      std::cout << " a has been moved to c (c=" << c->get() << ")\n\n";

      a = std::move( b );
      std::cout << " b has been moved to a (a=" << a->get() << ")\n\n";
   }

   // unique_ptr for an array of Widgets
   {
      auto a = make_unique<Widget[]>( 2 );
      a[0].set( 1 );
      a[1].set( 2 );
      std::cout << " a has been created (a=[" << a[0].get() << "," << a[1].get() << "])\n\n";

      auto b = make_unique<Widget[]>( 3 );
      b[0].set( 3 );
      b[1].set( 4 );
      b[2].set( 5 );
      std::cout << " b has been created (a=[" << b[0].get() << "," << b[1].get() << "," << b[2].get() << "])\n\n";

      //a = b;  // Compilation error!!!

      unique_ptr<Widget[]> c( std::move( a ) );
      std::cout << " a has been moved to c (c=[" << c[0].get() << "," << c[1].get() << "])\n\n";

      a = std::move( b );
      std::cout << " b has been moved to a (a=[" << a[0].get() << "," << a[1].get() << "," << a[2].get() << "])\n\n";
   }

   return EXIT_SUCCESS;
}
