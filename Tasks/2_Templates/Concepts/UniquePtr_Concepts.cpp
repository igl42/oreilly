/**************************************************************************************************
*
* \file UniquePtr_Concepts.cpp
* \brief C++ Training - unique_ptr Example
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Constrain the move operations for different pointer types of the given 'unique_ptr'
*       implementation to convertible pointer types by means of C++20 concepts. Note that in
*       this example you don't have to constrain the deleter!
*
**************************************************************************************************/

#include <concepts>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <utility>


//---- <Widget.h> ---------------------------------------------------------------------------------

// Auxiliary class for testing purposes
class WidgetBase
{
 public:
   explicit WidgetBase( int i )
      : i_{i}
   {}

   virtual ~WidgetBase() = default;
   int getInt() const { return i_; }

 private:
   int i_{ 42 };
};

class Widget : public WidgetBase
{
 public:
   Widget( int i, double d )
      : WidgetBase{i}
      , d_{d}
   {
      std::cout << " Widget has been created (i=" << getInt() << ", d=" << getDouble() << ")\n";
   }

   ~Widget()
   {
      std::cout << " Widget has been destroyed (i=" << getInt() << ", d=" << getDouble() << ")\n";
   }

   double getDouble() const { return d_; }

 private:
   double d_{ 3.14 };
};

std::ostream& operator<<( std::ostream& os, Widget const& w )
{
   return os << '(' << w.getInt() << ',' << w.getDouble() << ')';
}




//---- <memory> -----------------------------------------------------------------------------------

//==== Simplified implementation of the 'default_delete' policy ====
template< typename T >
struct default_delete
{
   void operator()( T* ptr ) const { delete ptr; }
};

template< typename T >
struct default_delete<T[]>
{
   template< typename U >  // No constraint for 'U'
   void operator()( U* ptr ) const { delete[] ptr; }
};




//==== Simplified implementation of the std::unique_ptr class template ====
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

   // TODO: Constrain the move constructor for different pointer types by means of a concept.
   //       The following constraints need to be fulfilled:
   //          a) unique_ptr<U, E>::pointer is implicitly convertible to pointer
   //          b) U is not an array type
   template< typename U, typename E >
   unique_ptr( unique_ptr<U,E>&& u ) noexcept;

   ~unique_ptr() noexcept;

   unique_ptr& operator=( unique_ptr const& u ) = delete;
   unique_ptr& operator=( unique_ptr&& u ) noexcept;

   // TODO: Constrain the move assignment operator for different pointer types by means of a concept
   //       The following constraints need to be fulfilled:
   //          a) unique_ptr<U, E>::pointer is implicitly convertible to pointer
   //          b) U is not an array type
   template< typename U, typename E >
   unique_ptr& operator=( unique_ptr<U,E>&& u ) noexcept;

   T& operator*()  const { return *ptr_; }
   T* operator->() const { return ptr_;  }

   void    reset  ( pointer ptr = pointer{} ) noexcept;
   pointer release() noexcept;

   void swap( unique_ptr& other ) noexcept;

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


// TODO: Constrain the move constructor for different pointer types by means of a concept.
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


// TODO: Constrain the move assignment operator for different pointer types by means of a concept.
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
void unique_ptr<T,D>::swap( unique_ptr& other ) noexcept
{
   std::swap( ptr_, other.ptr_ );
}




//==== Simplified implementation of the std::unique_ptr specialization for arrays ====
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

   // TODO: Constrain the move constructor for different pointer types by means of a concept.
   //       The following constraints need to be fulfilled:
   //          a) U is an array type
   //          b) pointer is the same type as element_type*
   //          c) unique_ptr<U,E>::pointer is the same type as unique_ptr<U,E>::element_type*
   //          d) unique_ptr<U,E>::element_type(*)[] is convertible to element_type(*)[]
   template< typename U, typename E >
   unique_ptr( unique_ptr<U,E>&& u ) noexcept;

   ~unique_ptr() noexcept;

   unique_ptr& operator=( unique_ptr const& u ) = delete;
   unique_ptr& operator=( unique_ptr&& u ) noexcept;

   // TODO: Constrain the move assignment operator for different pointer types by means of a concept.
   //       The following constraints need to be fulfilled:
   //          a) U is an array type
   //          b) pointer is the same type as element_type*
   //          c) unique_ptr<U,E>::pointer is the same type as unique_ptr<U,E>::element_type*
   //          d) unique_ptr<U,E>::element_type(*)[] is convertible to element_type(*)[]
   template< typename U, typename E >
   unique_ptr& operator=( unique_ptr<U,E>&& u ) noexcept;

   T& operator[]( size_t index ) const { return ptr_[index]; }

   void    reset( std::nullptr_t ptr = nullptr ) noexcept;
   pointer release() noexcept;

   void swap( unique_ptr& other ) noexcept;

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


// TODO: Constrain the move constructor for different pointer types by means of a concept.
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


// TODO: Constrain the move assignment operator for different pointer types by means of a concept.
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
void unique_ptr<T[],D>::reset( std::nullptr_t ptr ) noexcept
{
   unique_ptr tmp( std::exchange( ptr_, ptr ) );
}


template< typename T, typename D >
auto unique_ptr<T[],D>::release() noexcept -> pointer
{
   return std::exchange( ptr_, {} );
}


template< typename T, typename D >
void unique_ptr<T[],D>::swap( unique_ptr& other ) noexcept
{
   std::swap( ptr_, other.ptr_ );
}




//==== Free unique_ptr functions ====
template< typename T, typename D >
void swap( unique_ptr<T,D>& a, unique_ptr<T,D>& b ) noexcept
{
   a.swap( b );
}

template< typename T, typename... Args >
unique_ptr<T> make_unique( Args&&... args )
{
   return unique_ptr<T>( new T( std::forward<Args>(args)... ) );
}




//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // unique_ptr for a single Widget
   {
      std::cout << "\n==== unique_ptr for a single Widget ====\n";

      auto a = make_unique<Widget>(1,1.1);
      std::cout << " a has been created (a=" << (*a).getInt() << ")\n";

      auto b = make_unique<Widget const>(2,2.2);
      std::cout << " b has been created (b=" << b->getInt() << ")\n";

      //a = b;  // Compilation error!!!

      unique_ptr<WidgetBase const> c{ std::move( a ) };
      std::cout << " a has been moved to c (c=" << c->getInt() << ")\n";

      c = std::move( b );
      std::cout << " b has been moved to c (c=" << c->getInt() << ")\n";

      //---- Error cases for 'const T' to 'T' conversions ----
      /*
      unique_ptr<Widget> d1{ std::move(b) };  // Compilation error!!

      unique_ptr<Widget> d2{};
      d2 = std::move(b);  // Compilation error!!!
      */

      //---- Error cases for 'WidgetBase' to 'Widget' conversions ----
      /*
      unique_ptr<Widget> e1{ std::move(c) };  // Compilation error!!

      unique_ptr<Widget> e2{};
      e2 = std::move(c);  // Compilation error!!
      */

      //---- Error cases for 'Widget[]' to 'Widget' conversions ----
      /*
      unique_ptr<Widget[]> array{};

      unique_ptr<Widget> f1{ std::move(array) };  // Compilation error!!

      unique_ptr<Widget> f2{};
      f2 = std::move(array);  // Compilation error!!
      */
   }

   // unique_ptr for an array of Widgets
   {
      std::cout << "\n==== unique_ptr for an array of Widgets ====\n";

      auto a = unique_ptr<Widget[]>( new Widget[2]{ {1,1.1}, {2,2.2} } );
      std::cout << " a has been created (a=[" << a[0] << "," << a[1] << "])\n";

      auto b = unique_ptr<Widget const[]>( new Widget[3]{ {3,3.3}, {4,4.4}, {5,5.5} } );
      std::cout << " b has been created (a=[" << b[0] << "," << b[1] << "," << b[2] << "])\n";

      //a = b;  // Compilation error!!!

      unique_ptr<Widget const[]> c( std::move( a ) );
      std::cout << " a has been moved to c (c=[" << c[0] << "," << c[1] << "])\n";

      c = std::move( b );
      std::cout << " b has been moved to c (c=[" << c[0] << "," << c[1] << "," << c[2] << "])\n";

      //---- Error cases for 'const T' to 'T' conversions ----
      /*
      unique_ptr<Widget[]> d1{ std::move(b) };  // Compilation error!!

      unique_ptr<Widget[]> d2{};
      d2 = std::move(b);  // Compilation error!!!
      */

      //---- Error cases for 'WidgetBase[]' to 'Widget[]' conversions ----
      /*
      unique_ptr<WidgetBase[]> array{};

      unique_ptr<Widget> e1{ std::move(array) };  // Compilation error!!

      unique_ptr<Widget> e2{};
      e2 = std::move(array);  // Compilation error!!
      */

      //---- Error cases for 'Widget[]' to 'WidgetBase[]' conversions ----
      /*
      unique_ptr<WidgetBase[]> f1( std::move( a ) );  // Compilation error!!!

      unique_ptr<WidgetBase[]> f2{};
      f2 = std::move( a );  // Compilation error!!!
      */
   }

   return EXIT_SUCCESS;
}
