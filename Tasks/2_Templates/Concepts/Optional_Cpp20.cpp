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
class Optional
{
 public:
   // TODO:
   //  - Default constructor
   //  - Constructor taking a 'std::nullopt'
   //  - Copy constructor
   //  - Move constructor
   //  - Constructor for lvalues of other type of 'Optional'
   //  - Constructor for rvalues of other type of 'Optional'
   //  - Constructor for other types (i.e. 'U')
   //  - Copy assignment operator
   //  - Move assignment operator
   //  - Assignment operator for lvalues of other type of 'Optional'
   //  - Assignment operator for rvalues of other type of 'Optional'
   //  - Assignment operator for other types (i.e. 'U')
   //  - Conversion operator to 'bool'
   //  - Dereference operator (i.e. 'operator*()')
   //  - 'value()' member function
   //  - 'reset()' member function
   //  - 'emplace()' member function

 private:
   // TODO:
   //  - Data members
};


// TODO:
//  - Equality operator (i.e. 'operator==()')
//  - Space-ship operator (i.e. 'operator<=>()')
//  - C++20 formatter for 'std::format'


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
   /*
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
   */

   // Trivial types (floating point)
   /*
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
   */

   // Non-trivial types
   /*
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
   */

   return EXIT_SUCCESS;
}
