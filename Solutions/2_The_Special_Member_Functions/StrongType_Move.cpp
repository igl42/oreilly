/**************************************************************************************************
*
* \file StrongType_Move.cpp
* \brief C++ Training - Advanced programming example for move semantics
*
* Copyright (C) 2015-2021 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: The following 'StrongType' class template represents a strong, distinct type, which acts
*       as a wrapper around another, more basic type (e.g. 'int', 'double', 'std::string', ...).
*       Implement the constructors of the given 'StrongType' class template.
*
* Step 1: Define the necessary compiler-generated constructors (i.e. the special member functions).
*
* Step 2: Define all necessary constructors that enable to create a strong type from different
*         non-strong types (e.g. int -> StrongType<int>, ...).
*
* Step 3: Define all necessary constructors that enable to create a strong type from other
*         strong types (e.g. StrongType<unsigned int> -> StrongType<int>, ...).
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

using namespace std::string_literals;


//---- <StrongType.h> -----------------------------------------------------------------------------

template< typename T, typename Tag >
class StrongType final
{
 private:
   template< typename U >
   using EnableIfNotReference_t =
      std::enable_if_t< !std::is_reference<U>::value, bool >;

   template< typename U >
   using EnableIfIsConvertible_t =
      std::enable_if_t< std::is_convertible<U,T>::value, bool >;

 public:
   using value_type = T;

   //-- Step 1: The compiler-generated constructors (special member functions) --------------------
   StrongType() = default;
   StrongType( const StrongType& ) = default;
   StrongType( StrongType&& ) = default;

   //-- Step 2: Conversion constructors from different non-strong types ---------------------------
   explicit constexpr StrongType( const T& value )
      : value_( value )
   {}

   template< typename U = T, EnableIfNotReference_t<U> = true >
   explicit constexpr StrongType( T&& value )
      : value_( std::move( value ) )
   {}

   template< typename U, EnableIfIsConvertible_t<U> = true >
   explicit constexpr StrongType( U&& value )
      : value_( std::forward<U>(value) )
   {}

   //-- Step 3: Conversion constructors from other strong types -----------------------------------
   template< typename U, EnableIfIsConvertible_t<U> = true >
   explicit constexpr StrongType( const StrongType<U,Tag>& strong )
      : value_( strong.get() )
   {}

   template< typename U, EnableIfIsConvertible_t<U> = true >
   explicit constexpr StrongType( StrongType<U,Tag>&& strong )
      : value_( std::move(strong).get() )
   {}


   //----------------------------------------------------------------------------------------------
   ~StrongType() = default;
   StrongType& operator=( const StrongType& ) & = default;
   StrongType& operator=( StrongType&& ) & = default;

   template< typename U, EnableIfIsConvertible_t<U> = true >
   StrongType& operator=( U&& value )
   {
      value_ = std::forward<U>(value);
      return *this;
   }

   template< typename U, EnableIfIsConvertible_t<U> = true >
   StrongType& operator=( const StrongType<U,Tag>& strong )
   {
      value_ = strong.get();
      return *this;
   }

   template< typename U, EnableIfIsConvertible_t<U> = true >
   StrongType& operator=( StrongType<U,Tag>&& strong )
   {
      value_ = std::move(strong).get();
      return *this;
   }

   constexpr T&        get()       &  noexcept { return value_; }
   constexpr const T&  get() const &  noexcept { return value_; }
   constexpr T&&       get()       && noexcept { return std::move(value_); }
   constexpr const T&& get() const && noexcept { return std::move(value_); }

   void swap( StrongType& other ) {
      using std::swap;
      swap( value_, other.value_ );
   }

 private:
   T value_;
};

template< typename T, typename Tag >
std::ostream& operator<<( std::ostream& os, const StrongType<T,Tag>& st )
{
   os << st.get();
   return os;
}

template< typename T, typename Tag >
void swap( StrongType<T,Tag>& a, StrongType<T,Tag>& b )
{
   a.swap( b );
}


//---- <Email.h> ----------------------------------------------------------------------------------

using Meter  = StrongType<unsigned int,struct MeterTag>;
using LMeter = StrongType<long unsigned int,struct MeterTag>;
using Email  = StrongType<std::string,struct EmailTag>;


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // Step 1: The compiler-generated constructors (special member functions)
   Email email1{};
   std::cout << " email1 = \"" << email1 << "\"\n";

   Email tmp{ "jon.doe@gmail.com" };
   Email email2{ tmp };
   std::cout << " email2 = \"" << email2 << "\"\n";

   Email email3{ std::move(tmp) };
   std::cout << " email3 = \"" << email3 << "\"\n";


   // Step 2: Conversion constructors from different non-strong types
   const std::string s{ "jane.doe@yahoo.com" };
   Email email4{ s };
   std::cout << " email4 = \"" << email4 << "\"\n";

   Email email5{ "info@isocpp.com"s };
   std::cout << " email5 = \"" << email5 << "\"\n";

   Email email6{ "support@cppreference.com" };
   std::cout << " email6 = \"" << email6 << "\"\n";


   // Step 3: Conversion constructors from other strong types
   const LMeter lmeter{ 10UL };
   Meter meter1{ lmeter };
   std::cout << " meter1 = \"" << meter1 << "\"\n";

   Meter meter2{ LMeter{ 20UL } };
   std::cout << " meter2 = \"" << meter2 << "\"\n";


   return EXIT_SUCCESS;
}
