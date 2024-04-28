/**************************************************************************************************
*
* \file Optional_Cpp20.cpp
* \brief C++ Training - Example for a C++20 implementation of 'std::optional'
*
* Copyright (C) 2015-2020 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the class template 'Optional' based on the C++17 type 'std::optional'.
*
*       The following member functions are required:
*       1.  A default constructor
*       2.  A constructor taking a 'std::nullopt'
*       3.  A copy constructor
*       4.  A move constructor
*       5.  A constructor for lvalues of other type of 'Optional'
*       6.  A constructor for rvalues of other type of 'Optional'
*       7.  A constructor for other types (i.e. 'U')
*       8.  A copy assignment operator
*       9.  A move assignment operator
*       10. An assignment operator for lvalues of other type of 'Optional'
*       11. An assignment operator for rvalues of other type of 'Optional'
*       12. An assignment operator for other types (i.e. 'U')
*       13. A conversion operator to 'bool'
*       13. A dereference operator (i.e. 'operator*()')
*       14. 'value()' member function
*       15. 'reset()' member function
*       16. 'emplace()' member function
*
*       In addition, the following functionality is required:
*       17. An equality operator (i.e. 'operator==()')
*       18. A space-ship operator (i.e. 'operator<=>()')
*       19. A C++20 formatter for 'std::format'
*
**************************************************************************************************/

#include <cassert>
#include <compare>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
#include <type_traits>
#include <utility>

// C++20
//#include <format>


//---- <Optional.h> -------------------------------------------------------------------------------

template< typename T >
class Optional;


namespace detail {

template< typename T >
std::true_type is_optional( const volatile Optional<T>* );

std::false_type is_optional( ... );

} // namespace detail

template< typename T >
struct is_optional
   : public decltype( detail::is_optional( std::declval<T*>() ) )
{};

template< typename T >
struct is_optional<T&>
   : public std::false_type
{};

template< typename T >
constexpr bool is_optional_v = is_optional<T>::value;


template< typename T >
class Optional
{
 private:
   template< typename U >
   static constexpr bool is_constructible_or_convertible_v =
      std::is_constructible_v< T, Optional<U>&        > ||
      std::is_constructible_v< T, const Optional<U>&  > ||
      std::is_constructible_v< T, Optional<U>&&       > ||
      std::is_constructible_v< T, const Optional<U>&& > ||
      std::is_convertible_v< Optional<U>&       , T >   ||
      std::is_convertible_v< const Optional<U>& , T >   ||
      std::is_convertible_v< Optional<U>&&      , T >   ||
      std::is_convertible_v< const Optional<U>&&, T >;

   template< typename U >
   static constexpr bool is_constructible_or_convertible_or_assignable_v =
      is_constructible_or_convertible_v<U>           ||
      std::is_assignable_v< T, Optional<U>& >        ||
      std::is_assignable_v< T, const Optional<U>& >  ||
      std::is_assignable_v< T, Optional<U>&& >       ||
      std::is_assignable_v< T, const Optional<U>&& >;

 public:
   using value_type = T;

   constexpr Optional() noexcept = default;
   constexpr Optional( std::nullopt_t ) noexcept {}

   constexpr Optional( const Optional& ) = default;
   constexpr Optional( const Optional& other )
      requires( !std::is_trivially_copy_constructible_v<T> )
      : used_{ other.used_ }
   {
      if( has_value() ) {
         std::construct_at( &v_.value_, other.value() );
      }
   }

   constexpr Optional( Optional&& ) = default;
   constexpr Optional( Optional&& other )
      requires( !std::is_trivially_move_constructible_v<T> )
      : used_{ other.used_ }
   {
      if( has_value() ) {
         std::construct_at( &v_.value_, std::move(other).value() );
      }
   }

   template< typename U >
   constexpr Optional( const Optional<U>& other )
      requires( std::is_constructible_v< T, const U& > &&
                !is_constructible_or_convertible_v<U> )
      : used_( other.has_value() )
   {
      if( has_value() ) {
         std::construct_at( &v_.value_, other.value() );
      }
   }

   template< typename U >
   constexpr Optional( Optional<U>&& other )
      requires( std::is_constructible_v< T, U&& > &&
                !is_constructible_or_convertible_v<U> )
      : used_( other.has_value() )
   {
      if( has_value() ) {
         std::construct_at( &v_.value_, std::move(other).value() );
      }
   }

   template< typename U = value_type >
   constexpr Optional( U&& value )
      requires( !is_optional_v< std::decay_t<U> > )
      : used_{ true }
   {
      std::construct_at( &v_.value_, std::forward<U>( value ) );
   }

   constexpr ~Optional() = default;

   constexpr ~Optional() requires( !std::is_trivially_destructible_v<T> )
   {
      if( has_value() ) std::destroy_at( &v_.value_ );
   }

   constexpr Optional& operator=( std::nullptr_t ) { reset(); }

   constexpr Optional& operator=( const Optional& ) = default;
   constexpr Optional& operator=( const Optional& other )
      requires( !std::is_trivially_copy_assignable_v<T> )
   {
      if( has_value() && other.has_value() ) {
         value() = other.value();
      }
      else if( other.has_value() ) {
         emplace( other.value() );
      }
      else {
         reset();
      }

      return *this;
   }

   constexpr Optional& operator=( Optional&& ) = default;
   constexpr Optional& operator=( Optional&& other )
      requires( !std::is_trivially_move_assignable_v<T> )
   {
      if( has_value() && other.has_value() ) {
         value() = std::move( other.value() );
      }
      else if( other.has_value() ) {
         emplace( std::move( other.value() ) );
      }
      else {
         reset();
      }

      return *this;
   }

   template< typename U >
   constexpr Optional& operator=( const Optional<U>& other )
      requires( std::is_constructible_v< T, const U& > &&
                std::is_assignable_v< T&, const U& > &&
                !is_constructible_or_convertible_or_assignable_v<U> )
   {
      if( has_value() && other.has_value() ) {
         value() = other.value();
      }
      else if( other.has_value() ) {
         emplace( other.value() );
      }
      else {
         reset();
      }

      return *this;
   }

   template< typename U >
   constexpr Optional& operator=( Optional<U>&& other )
      requires( std::is_constructible_v<T,U> &&
                std::is_assignable_v<T&,U> &&
                !is_constructible_or_convertible_or_assignable_v<U> )
   {
      if( has_value() && other.has_value() ) {
         value() = std::move(other).value();
      }
      else if( other.has_value() ) {
         emplace( std::move(other).value() );
      }
      else {
         reset();
      }

      return *this;
   }

   template< typename U >
   constexpr Optional& operator=( U&& value )
      requires( !is_optional_v< std::decay_t<U> > )
   {
      if( has_value() ) {
         value() = std::forward<U>( value );
      }
      else {
         std::construct_at( &v_.value_, std::forward<U>( value ) );
      }

      return *this;
   }

   constexpr explicit operator bool() const noexcept { return used_; }
   constexpr bool has_value() const noexcept { return used_; }

   constexpr T*       operator->()       &  { return &v_.value_; }
   constexpr const T* operator->() const &  { return &v_.value_; }

   constexpr T&        operator*()       &  { return value(); }
   constexpr const T&  operator*() const &  { return value(); }
   constexpr T&&       operator*()       && { return value(); }
   constexpr const T&& operator*() const && { return value(); }

   constexpr T&        value()       &  { return v_.value_; }
   constexpr const T&  value() const &  { return v_.value_; }
   constexpr T&&       value()       && { return std::move( v_.value_ ); }
   constexpr const T&& value() const && { return std::move( v_.value_ ); }

   constexpr void reset() noexcept
   {
      if( has_value() )
         std::destroy_at( &v_.value_ );
      used_ = false;
   }

   template< typename... Args >
   constexpr T& emplace( Args&&... args )
   {
      reset();
      std::construct_at( &v_.value_, std::forward<Args>( args )... );
      used_ = true;
      return value();
   }

 private:
   union Union {
      Union() = default;
      Union() requires( !std::is_trivially_default_constructible_v<T> ) {}
      ~Union() = default;
      ~Union() requires( !std::is_trivially_destructible_v<T> ) {}
      T value_;
   } v_;
   bool used_{ false };
};


template< typename T, typename U >
constexpr bool operator==( const Optional<T>& lhs, const Optional<U>& rhs )
{
   if( lhs.has_value() && rhs.has_value() )
      return lhs.value() == rhs.value();
   else
      return !lhs.has_value() && !rhs.has_value();
}

template< typename T >
constexpr bool operator==( const Optional<T>& o, std::nullopt_t ) noexcept
{
   return !o.has_value();
}

template< typename T, typename U >
constexpr bool operator==( const Optional<T>& lhs, const U& rhs )
{
   return ( lhs.has_value() ? lhs.value() == rhs : false );
}

template< typename T, std::three_way_comparable_with<T> U >
constexpr std::compare_three_way_result_t<T,U>
   operator<=>( const Optional<T>& lhs, const Optional<U>& rhs ) noexcept
{
   if( !rhs.has_value() )      return std::strong_ordering::less;
   else if( !lhs.has_value() ) return std::strong_ordering::greater;
   else                        return std::compare_three_way{}( *lhs, *rhs );
}

template< typename T >
constexpr std::strong_ordering
   operator<=>( const Optional<T>& o, std::nullopt_t ) noexcept
{
   if( o.has_value() )
      return std::strong_ordering::greater;
   else
      return std::strong_ordering::equal;
}


// The relational operators are no longer needed since C++20. These functions can be
// generated from 'operator==()' and 'operator<=>()'. For reference (and potentially
// backwards compatibility) they are available in the following comment.
/*
template< typename T >
constexpr bool operator==( std::nullopt_t, const Optional<T>& o ) noexcept
{
   return !o.has_value();
}

template< typename T, typename U >
bool operator!=( const Optional<T>& lhs, const Optional<U>& rhs )
{
   return !( lhs == rhs );
}

template< typename T >
bool operator!=( const Optional<T>& o, std::nullopt_t ) noexcept
{
   return o.has_value();
}

template< typename T >
bool operator!=( std::nullopt_t, const Optional<T>& o ) noexcept
{
   return o.has_value();
}

template< typename T, typename U >
bool operator<( const Optional<T>& lhs, const Optional<U>& rhs )
{
   if( !rhs.has_value() ) return false;
   else if( !lhs.has_value() ) return true;
   else return ( *lhs < *rhs );
}

template< typename T >
bool operator<( const Optional<T>& o, std::nullopt_t ) noexcept
{
   return false;
}

template< typename T >
bool operator<( std::nullopt_t, const Optional<T>& o ) noexcept
{
   return o.has_value();
}

template< typename T, typename U >
bool operator<=( const Optional<T>& lhs, const Optional<U>& rhs )
{
   return !( rhs < lhs );
}

template< typename T >
bool operator<=( const Optional<T>& o, std::nullopt_t ) noexcept
{
   return !o.has_value();
}

template< typename T >
bool operator<=( std::nullopt_t, const Optional<T>& o ) noexcept
{
   return true;
}

template< typename T, typename U >
bool operator>( const Optional<T>& lhs, const Optional<U>& rhs )
{
   return rhs < lhs;
}

template< typename T >
bool operator>( const Optional<T>& o, std::nullopt_t ) noexcept
{
   return o.has_value();
}

template< typename T >
bool operator>( std::nullopt_t, const Optional<T>& o ) noexcept
{
   return false;
}

template< typename T, typename U >
bool operator>=( const Optional<T>& lhs, const Optional<U>& rhs )
{
   return !( lhs < rhs );
}

template< typename T >
bool operator>=( const Optional<T>& o, std::nullopt_t ) noexcept
{
   return true;
}

template< typename T >
bool operator>=( std::nullopt_t, const Optional<T>& o ) noexcept
{
   return !o.has_value();
}
*/


// This 'formatter' specialization is needed to make 'Optional' compatible with 'std::format'.
/*
template< typename T >
struct std::formatter< Optional<T> >
   : public std::formatter<T>
{
 public:
   // parse() is inherited from the base class

   template< typename FormatContext >
   auto format(Optional<T> const& o, FormatContext& fc) const
   {
      return std::formatter<T>::format(o.value(), fc);
   }
};
*/


//---- <S.h> --------------------------------------------------------------------------------------

struct S
{
 public:
   S() { std::puts( "S()" ); }
   S( const char* array ) : s_( array ) { std::puts( "S(const char*)" ); }
   S( const std::string& s ) : s_( s ) { std::puts( "S(std::string)" ); }
   S( const S& s ) : s_( s.s_ ) { std::puts( "S(const S&)" ); }
   S( S&& s ) : s_( std::move( s.s_ ) ) { std::puts( "S(S&&)" ); }
   S& operator=( const S& s ) { s_ = s.s_; std::puts( "S& operator=(const S&)" ); return *this; }
   S& operator=( S&& s ) { s_ = std::move(s.s_); std::puts( "S& operator=(S&&)" ); return *this; }
   ~S() { std::puts( "~S()" ); }

   const std::string& get() const { return s_; }

 private:
   std::string s_{};
};

std::ostream& operator<<( std::ostream& os, const S& s )
{
   return os << s.get();
}


//---- <Main.cpp> ---------------------------------------------------------------------------------


int main()
{
   // Trivial types (integral)
   {
      static_assert( std::is_trivially_copy_constructible_v< Optional<int> > );
      static_assert( std::is_trivially_move_constructible_v< Optional<int> > );
      static_assert( std::is_trivially_destructible_v< Optional<int> > );
      static_assert( std::is_trivially_copy_assignable_v< Optional<int> > );
      static_assert( std::is_trivially_move_assignable_v< Optional<int> > );

      Optional<int> o1{};
      Optional<unsigned int> o2{ 1 };

      assert( o1 == std::nullopt );
      assert( std::nullopt == o1 );
      assert( !( o1 < std::nullopt ) );
      assert( !( std::nullopt < o1 ) );
      assert( o1 <= std::nullopt );
      assert( std::nullopt <= o1 );
      assert( !( o1 > std::nullopt ) );
      assert( !( std::nullopt > o1 ) );
      assert( o1 >= std::nullopt );
      assert( std::nullopt >= o1 );

      assert( o2 != std::nullopt );
      assert( std::nullopt != o2 );
      assert( !( o2 < std::nullopt ) );
      assert( std::nullopt < o2 );
      assert( !( o2 <= std::nullopt ) );
      assert( std::nullopt <= o2 );
      assert( o2 > std::nullopt );
      assert( !( std::nullopt > o2 ) );
      assert( o2 >= std::nullopt );
      assert( !( std::nullopt >= o2 ) );

      o1.emplace( 2 );
      o2 = o1;

      Optional<int> o3{ 3 };

      assert( o1 == o2 );
      assert( o1 != o3 );
      assert( o1 <  o3 );
      assert( o1 <= o3 );
      assert( o3 >  o1 );
      assert( o3 >= o1 );

      std::cout << "\n o2 = " << ( o2.has_value() ? std::to_string(*o2) : "<empty>" ) << "\n\n";
   }

   // Trivial types (floating point)
   {
      static_assert( std::is_trivially_copy_constructible_v< Optional<float> > );
      static_assert( std::is_trivially_move_constructible_v< Optional<float> > );
      static_assert( std::is_trivially_destructible_v< Optional<float> > );
      static_assert( std::is_trivially_copy_assignable_v< Optional<float> > );
      static_assert( std::is_trivially_move_assignable_v< Optional<float> > );

      Optional<float> o1{};
      Optional<double> o2{ 1.0 };

      assert( o1 == std::nullopt );
      assert( std::nullopt == o1 );
      assert( !( o1 < std::nullopt ) );
      assert( !( std::nullopt < o1 ) );
      assert( o1 <= std::nullopt );
      assert( std::nullopt <= o1 );
      assert( !( o1 > std::nullopt ) );
      assert( !( std::nullopt > o1 ) );
      assert( o1 >= std::nullopt );
      assert( std::nullopt >= o1 );

      assert( o2 != std::nullopt );
      assert( std::nullopt != o2 );
      assert( !( o2 < std::nullopt ) );
      assert( std::nullopt < o2 );
      assert( !( o2 <= std::nullopt ) );
      assert( std::nullopt <= o2 );
      assert( o2 > std::nullopt );
      assert( !( std::nullopt > o2 ) );
      assert( o2 >= std::nullopt );
      assert( !( std::nullopt >= o2 ) );

      o1.emplace( 2.0F );
      o2 = o1;

      Optional<float> o3{ 3.0F };

      assert( o1 == o2 );
      assert( o1 != o3 );
      assert( o1 <  o3 );
      assert( o1 <= o3 );
      assert( o3 >  o1 );
      assert( o3 >= o1 );

      std::cout << "\n o2 = " << ( o2.has_value() ? std::to_string(*o2) : "<empty>" ) << "\n\n";
   }

   // Non-trivial types
   {
      static_assert( !std::is_trivially_copy_constructible_v< Optional<std::string> > );
      static_assert( !std::is_trivially_move_constructible_v< Optional<std::string> > );
      static_assert( !std::is_trivially_destructible_v< Optional<std::string> > );
      static_assert( !std::is_trivially_copy_assignable_v< Optional<std::string> > );
      static_assert( !std::is_trivially_move_assignable_v< Optional<std::string> > );

      Optional<std::string> o1{};
      Optional<std::string> o2{ "1" };

      assert( o1 == std::nullopt );
      assert( std::nullopt == o1 );
      assert( !( o1 < std::nullopt ) );
      assert( !( std::nullopt < o1 ) );
      assert( o1 <= std::nullopt );
      assert( std::nullopt <= o1 );
      assert( !( o1 > std::nullopt ) );
      assert( !( std::nullopt > o1 ) );
      assert( o1 >= std::nullopt );
      assert( std::nullopt >= o1 );

      assert( o2 != std::nullopt );
      assert( std::nullopt != o2 );
      assert( !( o2 < std::nullopt ) );
      assert( std::nullopt < o2 );
      assert( !( o2 <= std::nullopt ) );
      assert( std::nullopt <= o2 );
      assert( o2 > std::nullopt );
      assert( !( std::nullopt > o2 ) );
      assert( o2 >= std::nullopt );
      assert( !( std::nullopt >= o2 ) );

      o1.emplace( "2" );
      o2 = o1;

      Optional<std::string> o3{ "3" };

      assert( o1 == o2 );
      assert( o1 != o3 );
      assert( o1 <  o3 );
      assert( o1 <= o3 );
      assert( o3 >  o1 );
      assert( o3 >= o1 );

      std::cout << "\n o2 = " << ( o2.has_value() ? *o2 : "<empty>" ) << "\n\n";
   }

   return EXIT_SUCCESS;
}
