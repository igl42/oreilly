/**************************************************************************************************
*
* \file UniquePtr1.cpp
* \brief C++ Training - unique_ptr Example
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement a (simplified) 'std::unique_ptr' class template.
*       Step 1: Implement the 'unique_ptr' base template for single memory resources
*       Step 2: Add a template parameter for a deleter
*       Step 3: Implement a 'unique_ptr' specialization for arrays
*       Step 4: Implement the copy and move operations
*       Step 5: Implement move operations for different pointer types
*       Step 6: Implement the 'reset()' and 'release()' functions
*
**************************************************************************************************/

#include <cstddef>
#include <cstdlib>
#include <iostream>
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

// Simplified implementation of the 'default_delete' policy
template< typename T >
struct default_delete
{
   void operator()( T* ptr ) const { delete ptr; }
};

template< typename T >
struct default_delete<T[]>
{
   template< typename U >
   void operator()( U* ptr ) const { delete[] ptr; }
};




// Simplified implementation of the std::unique_ptr class template
template< typename T, typename D = default_delete<T> >
class unique_ptr
{
 public:
   using pointer = T*;
   using element_type = T;

   constexpr unique_ptr();
   explicit  unique_ptr( T* ptr );
             unique_ptr( unique_ptr const& u ) = delete;
             unique_ptr( unique_ptr&& u ) noexcept;

   template< typename U, typename E >
   unique_ptr( unique_ptr<U,E>&& u ) noexcept;

   ~unique_ptr() noexcept;

   unique_ptr& operator=( unique_ptr const& u ) = delete;
   unique_ptr& operator=( unique_ptr&& u ) noexcept;

   template< typename U, typename E >
   unique_ptr& operator=( unique_ptr<U,E>&& u ) noexcept;

   T& operator*()  const { return *ptr_; }
   T* operator->() const { return ptr_;  }

   void    reset  ( pointer ptr = pointer{} ) noexcept;
   pointer release() noexcept;

 private:
   T* ptr_;

   template< typename U, typename E > friend class unique_ptr;
};


template< typename T, typename D >
constexpr unique_ptr<T,D>::unique_ptr()
   : ptr_( nullptr )
{}


template< typename T, typename D >
unique_ptr<T,D>::unique_ptr( T* ptr )
   : ptr_( ptr )
{}


template< typename T, typename D >
unique_ptr<T,D>::unique_ptr( unique_ptr&& u ) noexcept
   : ptr_( u.ptr_ )
{
   u.ptr_ = nullptr;
}


template< typename T, typename D >
template< typename U, typename E >
unique_ptr<T,D>::unique_ptr( unique_ptr<U,E>&& u ) noexcept
   : ptr_( u.ptr_ )
{
   u.ptr_ = nullptr;
}


template< typename T, typename D >
unique_ptr<T,D>::~unique_ptr() noexcept
{
   D{}( ptr_ );
}


template< typename T, typename D >
unique_ptr<T,D>& unique_ptr<T,D>::operator=( unique_ptr&& u ) noexcept
{
   D{}( ptr_ );
   ptr_ = u.ptr_;
   u.ptr_ = nullptr;
   return *this;
}


template< typename T, typename D >
template< typename U, typename E >
unique_ptr<T,D>& unique_ptr<T,D>::operator=( unique_ptr<U,E>&& u ) noexcept
{
   D{}( ptr_ );
   ptr_ = u.ptr_;
   u.ptr_ = nullptr;
   return *this;
}


template< typename T, typename D >
void unique_ptr<T,D>::reset( pointer ptr ) noexcept
{
   unique_ptr tmp( std::exchange( ptr_, ptr ) );
}


template< typename T, typename D >
auto unique_ptr<T,D>::release() noexcept -> pointer
{
   return std::exchange( ptr_, {} );
}




template< typename T, typename D >
class unique_ptr<T[],D>
{
 public:
   using pointer = T*;
   using element_type = T;

   constexpr unique_ptr();
   explicit  unique_ptr( T* ptr );
             unique_ptr( unique_ptr const& u ) = delete;
             unique_ptr( unique_ptr&& u ) noexcept;

   template< typename U, typename E >
   unique_ptr( unique_ptr<U,E>&& u ) noexcept;

   ~unique_ptr() noexcept;

   unique_ptr& operator=( unique_ptr const& u ) = delete;
   unique_ptr& operator=( unique_ptr&& u ) noexcept;

   template< typename U, typename E >
   unique_ptr& operator=( unique_ptr<U,E>&& u ) noexcept;

   T& operator[]( size_t index ) const { return ptr_[index]; }

   template< typename U >
   void reset( U ptr ) noexcept;

   void    reset( std::nullptr_t ptr = nullptr ) noexcept;
   pointer release() noexcept;

 private:
   T* ptr_;

   template< typename U, typename E > friend class unique_ptr;
};


template< typename T, typename D >
constexpr unique_ptr<T[],D>::unique_ptr()
   : ptr_( nullptr )
{}


template< typename T, typename D >
unique_ptr<T[],D>::unique_ptr( T* ptr )
   : ptr_( ptr )
{}


template< typename T, typename D >
unique_ptr<T[],D>::unique_ptr( unique_ptr&& u ) noexcept
   : ptr_( u.ptr_ )
{
   u.ptr_ = nullptr;
}


template< typename T, typename D >
template< typename U, typename E >
unique_ptr<T[],D>::unique_ptr( unique_ptr<U,E>&& u ) noexcept
   : ptr_( u.ptr_ )
{
   u.ptr_ = nullptr;
}


template< typename T, typename D >
unique_ptr<T[],D>::~unique_ptr() noexcept
{
   D{}( ptr_ );
}


template< typename T, typename D >
unique_ptr<T[],D>& unique_ptr<T[],D>::operator=( unique_ptr&& u ) noexcept
{
   D{}( ptr_ );
   ptr_ = u.ptr_;
   u.ptr_ = nullptr;
   return *this;
}


template< typename T, typename D >
template< typename U, typename E >
unique_ptr<T[],D>& unique_ptr<T[],D>::operator=( unique_ptr<U,E>&& u ) noexcept
{
   D{}( ptr_ );
   ptr_ = u.ptr_;
   u.ptr_ = nullptr;
   return *this;
}


template< typename T, typename D >
template< typename U >
void unique_ptr<T[],D>::reset( U ptr ) noexcept
{
   std::cerr << "\n HERE!!!\n\n";
   unique_ptr tmp( std::exchange( ptr_, ptr ) );
}


template< typename T, typename D >
void unique_ptr<T[],D>::reset( std::nullptr_t ptr ) noexcept
{
   unique_ptr tmp( std::exchange( ptr_, ptr ) );
}


template< typename T, typename D >
auto unique_ptr<T[],D>::release() noexcept -> pointer
{
   return std::exchange( ptr_, {} );
}




//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // unique_ptr for a single Widget
   {
      // Step 1+2
      auto a = unique_ptr<Widget>( new Widget(2) );
      std::cout << " a has been created (a=" << (*a).get() << ")\n\n";

      auto b = unique_ptr<Widget>( new Widget(3) );
      std::cout << " b has been created (b=" << b->get() << ")\n\n";

      // Step 4+5
      //a = b;  // Compilation error!!!

      unique_ptr<const Widget> c( std::move( a ) );
      std::cout << " a has been moved to c (c=" << c->get() << ")\n\n";

      a = std::move( b );
      std::cout << " b has been moved to a (a=" << a->get() << ")\n\n";
   }

   // unique_ptr for an array of Widgets
   {
      // Step 3
      auto a = unique_ptr<Widget[]>( new Widget[2] );
      a[0].set( 1 );
      a[1].set( 2 );
      std::cout << " a has been created (a=[" << a[0].get() << "," << a[1].get() << "])\n\n";

      auto b = unique_ptr<Widget[]>( new Widget[3] );
      b[0].set( 3 );
      b[1].set( 4 );
      b[2].set( 5 );
      std::cout << " b has been created (a=[" << b[0].get() << "," << b[1].get() << "," << b[2].get() << "])\n\n";

      // Step 4+5
      //a = b;  // Compilation error!!!

      unique_ptr<const Widget[]> c( std::move( a ) );
      std::cout << " a has been moved to c (c=[" << c[0].get() << "," << c[1].get() << "])\n\n";

      a = std::move( b );
      std::cout << " b has been moved to a (a=[" << a[0].get() << "," << a[1].get() << "," << a[2].get() << "])\n\n";
   }

   return EXIT_SUCCESS;
}
