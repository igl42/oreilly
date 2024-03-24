/**************************************************************************************************
*
* \file CopyControl.cpp
* \brief C++ Training - Copy Control Example
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Assuming that each of the given classes A to F should be copyable and moveable and that
*       all given data members are in private sections, for which of the classes do you have
*       to explicitly define a copy constructor, a move constructor, and a destructor, a copy
*       assignment operator and a move assignment operator? Check the final solution with
*       AddressSanitizer (see https://en.wikipedia.org/wiki/AddressSanitizer).
*
**************************************************************************************************/

#include <algorithm>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <numeric>
#include <string>
#include <utility>
#include <vector>


//---- <Utility.h> --------------------------------------------------------------------------------

template< typename T >
std::ostream& operator<<( std::ostream& os, const std::vector<T>& vec )
{
   os << "(";
   for( const auto& element : vec ) {
      os << " " << element;
   }
   return os << " )";
}

template< typename K, typename V >
std::ostream& operator<<( std::ostream& os, const std::map<K,V>& map )
{
   os << "(";
   for( const auto& pair : map ) {
      os << " (" << pair.first << "," << pair.second << ")";
   }
   return os << " )";
}


//---- <A.h> --------------------------------------------------------------------------------------

class A
{
 public:
   A() = default;

   // Copy constructor
   //A( const A& ) = default;

   // Move constructor
   //A( A&& ) = default;

   // Destructor
   //~A() = default;

   // Copy assignment operator
   //A& operator=( const A& ) = default;

   // Move assignment operator
   //A& operator=( A&& ) = default;

 private:
   int i_{ 42 };
   double d_{ 3.14 };
   std::string s_{ "C++ rocks" };

   friend std::ostream& operator<<( std::ostream& os, const A& a )
   {
      return os << "i=" << a.i_ << ", d=" << a.d_ << ", s=" << std::quoted(a.s_);
   }
};


//---- <B.h> --------------------------------------------------------------------------------------

class B
{
 public:
   explicit B( unsigned int ui ) : ui_{ ui } {}

   // Copy constructor
   //B( const B& ) = default;

   // Move constructor
   //B( B&& ) = default;

   // Destructor
   //~B() = default;

   // Copy assignment operator
   //B& operator=( const B& ) = default;

   // Move assignment operator
   //B& operator=( B&& ) = default;

 private:
   float f_{ 3.14F };
   const unsigned int ui_{};
   std::vector<int> v_{ 1, 2, 3, 4, 5 };

   friend std::ostream& operator<<( std::ostream& os, const B& b )
   {
      return os << "f=" << b.f_ << ", ui=" << b.ui_ << ", v=" << b.v_;
   }
};


//---- <C.h> --------------------------------------------------------------------------------------

class C
{
 public:
   explicit C( unsigned short& us ) : us_{ us } {}

   // Copy constructor
   //C( const C& ) = default;

   // Move constructor
   //C( C&& ) = default;

   // Destructor
   //~C() = default;

   // Copy assignment operator
   //C& operator=( const C& ) = default;

   // Move assignment operator
   //C& operator=( C&& ) = default;

 private:
   long double ld_{ 3.14L };
   unsigned short& us_;
   std::map<int,int> map_{ std::make_pair(1,2), std::make_pair(3,4), std::make_pair(5,6) };

   friend std::ostream& operator<<( std::ostream& os, const C& c )
   {
      return os << "ld=" << c.ld_ << ", us=" << c.us_ << ", map=" << c.map_;
   }
};


//---- <D.h> --------------------------------------------------------------------------------------

class D
{
 public:
   explicit D( std::size_t n )
      : n_{ n }
      , v_{ new double[n_] }
   {
      std::iota( v_, v_+n_, 1.0 );
   }

   // Copy constructor
   //D( const D& ) = default;

   // Move constructor
   //D( D&& ) = default;

   // Destructor
   //~D() = default;

   // Copy assignment operator
   //D& operator=( const D& ) = default;

   // Move assignment operator
   //D& operator=( D&& ) = default;

 private:
   std::size_t n_{ 12UL };
   double* v_;

   friend std::ostream& operator<<( std::ostream& os, const D& d )
   {
      os << "n=" << d.n_ << ", v= (";
      for( std::size_t i=0UL; i<d.n_; ++i ) {
         os << " " << d.v_[i];
      }
      return os << " )";
   }
};


//---- <E.h> --------------------------------------------------------------------------------------

class E
{
 public:
   E() = default;

   // Copy constructor
   //E( const E& ) = default;

   // Move constructor
   //E( E&& ) = default;

   // Destructor
   //~E() = default;

   // Copy assignment operator
   //E& operator=( const E& ) = default;

   // Move assignment operator
   //E& operator=( E&& ) = default;

 private:
   std::size_t a_{ 42UL };
   std::shared_ptr<std::string> s_{ new std::string{ "C++ rocks" } };

   friend std::ostream& operator<<( std::ostream& os, const E& e )
   {
      return os << "a=" << e.a_ << ", s=" << std::quoted(*e.s_);
   }
};


//---- <F.h> --------------------------------------------------------------------------------------

class F
{
 public:
   F() = default;

   // Copy constructor
   //F( const F& ) = default;

   // Move constructor
   //F( F&& ) = default;

   // Destructor
   //~F() = default;

   // Copy assignment operator
   //F& operator=( const F& ) = default;

   // Move assignment operator
   //F& operator=( F&& ) = default;

 private:
   std::size_t a_{ 42UL };
   std::unique_ptr<std::string> u_{ new std::string{ "C++ rocks" } };

   friend std::ostream& operator<<( std::ostream& os, const F& f )
   {
      return os << "a=" << f.a_ << ", u=" << std::quoted(*f.u_);
   }
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   // class A
   /*
   {
      A a1{};

      A a2{ a1 };             // Copy constructor
      A a3{ std::move(a1) };  // Move constructor
      a1 = a2;                // Copy assignment operator
      a2 = std::move(a3);     // Move assignment operator

      std::cout << "\n--A.h------------------\n"
                << a1 << "\n"
                << a2 << "\n"
                << "\n";
   }
   */

   // class B
   /*
   {
      B b1{};

      B b2{ b1 };             // Copy constructor
      B b3{ std::move(b1) };  // Move constructor
      b1 = b2;                // Copy assignment operator
      b2 = std::move(b3);     // Move assignment operator

      std::cout << "\n--B.h------------------\n"
                << b1 << "\n"
                << b2 << "\n"
                << "\n";
   }
   */

   // class C
   /*
   {
      unsigned short us{ 42 };
      C c1{ us };

      C c2{ c1 };             // Copy constructor
      C c3{ std::move(c1) };  // Move constructor
      c1 = c2;                // Copy assignment operator
      c2 = std::move(c3);     // Move assignment operator

      std::cout << "\n--C.h------------------\n"
                << c1 << "\n"
                << c2 << "\n"
                << "\n";
   }
   */

   // class D
   /*
   {
      D d1{ 2UL, 3UL };

      D d2{ d1 };             // Copy constructor
      D d3{ std::move(d1) };  // Move constructor
      d1 = d2;                // Copy assignment operator
      d2 = std::move(d3);     // Move assignment operator

      std::cout << "\n--D.h------------------\n"
                << d1 << "\n"
                << d2 << "\n"
                << "\n";
   }
   */

   // class E
   /*
   {
      E e1{};

      E e2{ e1 };             // Copy constructor
      E e3{ std::move(e1) };  // Move constructor
      e1 = e2;                // Copy assignment operator
      e2 = std::move(e3);     // Move assignment operator

      std::cout << "\n--E.h------------------\n"
                << e1 << "\n"
                << e2 << "\n"
                << "\n";
   }
   */

   // class F
   /*
   {
      F f1{};

      F f2{ f1 };             // Copy constructor
      F f3{ std::move(f1) };  // Move constructor
      f1 = f2;                // Copy assignment operator
      f2 = std::move(f3);     // Move assignment operator

      std::cout << "\n--F.h------------------\n"
                << f1 << "\n"
                << f2 << "\n"
                << "\n";
   }
   */

   return EXIT_SUCCESS;
}
