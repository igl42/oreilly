/**************************************************************************************************
*
* \file UniquePtr_Strategy.cpp
* \brief C++ Training - Programming Task for the Strategy Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Replace the hard-coded call to 'delete()' with a template-based Strategy implementation.
*
**************************************************************************************************/


//---- <Widget.h> ---------------------------------------------------------------------------------

#include <iostream>

// Auxiliary class for testing purposes
class Widget
{
 public:
   Widget()
   {
      std::cout << " Widget has been created (i=" << i_ << ")\n";
   }

   explicit Widget( int i ) noexcept
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

#include <utility>

template< typename T >
class unique_ptr
{
 public:
   using pointer = T*;
   using element_type = T;

   unique_ptr() = default;

   explicit unique_ptr( T* ptr )
      : ptr_{ptr}
   {}

   unique_ptr( unique_ptr const& ) = delete;
   unique_ptr& operator=( unique_ptr const& ) = delete;

   unique_ptr( unique_ptr&& other )
      : ptr_{ other.ptr_ }
   {
      other.ptr_ = nullptr;
   }

   unique_ptr& operator=( unique_ptr&& other )
   {
      ptr_ = std::exchange( other.ptr_, nullptr );
      return *this;
   }

   ~unique_ptr()
   {
      // TODO: Replace the hard-coded call to 'delete()' with a
      //       template-based Strategy implementation
      delete ptr_;
   }

   void reset( pointer ptr = pointer{} ) noexcept
   {
      unique_ptr tmp( std::exchange( ptr_, ptr ) );
   }

   pointer release() noexcept
   {
      return std::exchange( ptr_, {} );
   }

   T& operator*()  const { return *ptr_; }
   T* operator->() const { return ptr_;  }

 private:
   T* ptr_{};
};


template< typename T, typename... Ts >
unique_ptr<T> make_unique( Ts&&... params )
{
   return unique_ptr<T>( new T( std::forward<Ts>( params )... ) );
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <memory>
#include <cstdlib>
#include <iostream>


int main()
{
   auto a = make_unique<Widget>( 2 );
   std::cout << " a has been created (a=" << (*a).get() << ")\n\n";

   auto b = make_unique<Widget const>( 3 );
   std::cout << " b has been created (b=" << b->get() << ")\n\n";

   return EXIT_SUCCESS;
}

