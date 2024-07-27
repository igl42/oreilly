/**************************************************************************************************
*
* \file FixedVector_Strategy.cpp
* \brief C++ Training - Programming Task for the Strategy Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Replace the hard-coded logging mechanism by means of a template-based Strategy
*         implementation. Demonstrate how this helps to invert the dependencies.
*
* Step 2: Replace the hard-coded error handling mechanism (i.e. 'assert()') by means of
*         a template-based Strategy implementation.
*
**************************************************************************************************/


// Command line parameters to enable logging
//#define ENABLE_LOGGING


//---- <Logging.h> (external) ---------------------------------------------------------------------

#include <iostream>
#include <string_view>

enum class LogLevel
{
   error   = 0,
   warning = 1,
   debug   = 2
};

template< LogLevel level >
inline void log( std::string_view message )
{
#ifdef ENABLE_LOGGING
   if constexpr( level >= LogLevel::error ) {
      std::cerr << message << '\n';
   }
#endif
}

inline void log_error( std::string_view message )
{
   log<LogLevel::error>( message );
}

inline void log_warning( std::string_view message )
{
   log<LogLevel::warning>( message );
}

inline void log_debug( std::string_view message )
{
   log<LogLevel::debug>( message );
}


//---- <FixedVector.h> ----------------------------------------------------------------------------

#include <algorithm>
#include <cstddef>
#include <cstdlib>
#include <initializer_list>
#include <memory>
#include <string_view>


// Step 1: Replace the hard-coded logging mechanism by means of a template-based Strategy
//         implementation.
/*
struct NullLogger
{
   void log_error  ( [[maybe_unused]] std::string_view message ) const {}
   void log_warning( [[maybe_unused]] std::string_view message ) const {}
   void log_debug  ( [[maybe_unused]] std::string_view message ) const {}
};
*/


// Step 2: Replace the hard-coded error handling mechanism (i.e. 'assert()') by means of
//         a template-based Strategy implementation.
/*
struct Abort
{
   void operator()( [[maybe_unused]] std::string_view message ) const
   {
      abort();
   }
};
*/


template< typename Type, size_t Capacity >
class FixedVector final
{
 public:
   using value_type     = Type;
   using iterator       = Type*;
   using const_iterator = Type const*;

   FixedVector() = default;

   explicit FixedVector( size_t size, Type const& value = Type{} )
      : size_{ size }
   {
      checkSize( size );
      std::uninitialized_fill( begin(), end(), value );
   }

   FixedVector( std::initializer_list<Type> init )
      : size_{ init.size() }
   {
      checkSize( init.size() );
      std::uninitialized_copy( init.begin(), init.end(), begin() );
   }

   FixedVector( FixedVector const& other )
      : size_{ other.size_ }
   {
      std::uninitialized_copy( other.begin(), other.end(), begin() );
   }

   FixedVector( FixedVector&& other ) noexcept
      : size_{ other.size_ }
   {
      std::uninitialized_move( other.begin(), other.end(), begin() );
      std::destroy( other.begin(), other.end() );
      other.size_ = 0U;
   }

   ~FixedVector()
   {
      std::destroy( begin(), end() );
   }

   FixedVector& operator=( FixedVector const& other )
   {
      resize( other.size() );
      std::copy( other.begin(), other.end(), begin() );
      return *this;
   }

   FixedVector& operator=( FixedVector&& other ) noexcept
   {
      resize( other.size() );
      std::move( other.begin(), other.end(), begin() );
      std::destroy( other.begin(), other.end() );
      other.size_ = 0U;
      return *this;
   }

   size_t size() const { return size_; }
   size_t capacity() const { return Capacity; }

   Type*       data()       { return reinterpret_cast<Type*>( raw_ ); }
   Type const* data() const { return reinterpret_cast<Type const*>( raw_ ); }

   iterator       begin()       { return data(); }
   const_iterator begin() const { return data(); }
   iterator       end()         { return data() + size_; }
   const_iterator end()   const { return data() + size_; }

   Type& operator[]( size_t index )
   {
      if( index >= size_ ) {
         auto message = "Out-of-bounds access in FixedVector::operator[](size_t)";
         log_error( message );
         abort();
      }
      return data()[index];
   }

   Type const& operator[]( size_t index ) const
   {
      if( index >= size_ ) {
         auto message = "Out-of-bounds access in FixedVector::operator[](size_t)";
         log_error( message );
         abort();
      }
      return data()[index];
   }

 private:
   void checkSize( size_t size ) const
   {
      if( size > Capacity ) {
         throw std::invalid_argument( "Invalid number of elements" );
      }
   }

   alignas(Type) std::byte raw_[Capacity*sizeof(Type)];  // Intentionally left uninitialized!
   size_t size_{ 0U };

   static_assert( sizeof(std::byte) == 1U );
   static_assert( Capacity > 0U, "Capacity must be a non-zero value" );
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <FixedVector.h>
//#include <Logging.h>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>
#include <string_view>


// Step 1: Implement a logging Strategy that writes all log messages to the console.
// TODO


// Step 2: Implement an error Strategy that throws an exception.
// TODO


int main()
{
   FixedVector<int,20> v{ 1, 2, 3, 4, 5 };

   try {
      std::cout << '\n'
                << " v[1] = " << v[1] << '\n'
                << " v[3] = " << v[3] << '\n'
                << " v[5] = " << v[5] << '\n'
                << '\n';
   }
   catch( std::exception const& ex ) {
      std::cerr << "Exception caught: " << ex.what() << "\n";
   }

   return EXIT_SUCCESS;
}

