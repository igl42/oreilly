/**************************************************************************************************
*
* \file Bridge.cpp
* \brief C++ Training - Example for the Bridge Design Pattern
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: In the conceptual header file <X.h>, which #include directives could be immediately
*         removed without ill effect? You may not make any changes other than removing or
*         rewriting #include directives.
*
* Step 2: What further #includes could be removed if we made some suitable changes, and how?
*         This time, you may make changes to 'X' as long as 'X''s base classes and its public
*         interface remain unchanged; and current code that already uses 'X' should not be
*         affected beyond requiring a simple recompilation.
*
* Step 3: What further #includes could be removed if we made further changes to 'X', and how?
*         Now you may make any changes to 'X' as long as they don't change its public interface
*         so that existing code that uses 'X' is unaffected beyond requiring a simple
*         recompilation. Again, note that the comments are important.
*
* Inspired by Herb Sutter's "Exceptional C++", Items 26-29
*
**************************************************************************************************/


//---- <A.h> --------------------------------------------------------------------------------------

#include <iosfwd>

class A
{
 public:
   virtual ~A() = default;

   virtual std::ostream& print( std::ostream& ) const = 0;
};

inline std::ostream& operator<<( std::ostream& os, const A& a )
{
   return a.print( os );
}


//---- <B.h> --------------------------------------------------------------------------------------

#include <string>
#include <utility>

class B
{
 public:
   explicit B( std::string s )
      : s_{ std::move(s) }
   {}

   const std::string& getString() noexcept { return s_; }

 private:
   std::string s_;
};


//---- <C.h> --------------------------------------------------------------------------------------

class C
{
 public:
   virtual ~C() = default;

   int getInt() const noexcept { return i_; }
   double getDouble() const noexcept { return d_; }

 private:
   int i_;
   double d_;
};


//---- <D.h> --------------------------------------------------------------------------------------

//#include <C.h>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

class D : public C
{
 public:
   template< typename... Args >
   explicit D( Args... args )
      : strings_{ std::move(args)... }
   {}

   const std::string& getString( std::size_t index ) noexcept { return strings_[index]; }

 private:
   std::vector<std::string> strings_;
};


//---- <E.h> --------------------------------------------------------------------------------------

#include <string>
#include <utility>

class E
{
 public:
   explicit E( int i, std::string s )
      : i_{ i }
      , s_{ std::move(s) }
   {}

   int getInt() const noexcept { return i_; }
   const std::string& getString() const noexcept { return s_; }

 private:
   int i_;
   std::string s_;
};


//---- <Fwd.h> ------------------------------------------------------------------------------------

class E;


//---- <X.h> --------------------------------------------------------------------------------------

//#include <A.h>
//#include <B.h>
//#include <C.h>
//#include <D.h>
//#include <Fwd.h>

#include <iosfwd>
#include <list>

class X : public A, private B
{
 public:
   X( const C& );

   B  f( int, char* );
   C  f( int, C );
   C& g( B );
   E  h( E );
   std::ostream& print( std::ostream& ) const override;

 private:
   std::list<C> clist_;
   D            d_;
};


//---- <X.cpp> ------------------------------------------------------------------------------------

//#include <X.h>

//#include <E.h>

#include <cassert>
#include <ostream>

X::X( const C& c )
   : A{}
   , B{ "B" }
   , clist_{ c, c, c }
   , d_{ "1", "2", "3" }
{}

B X::f( int, char* )
{
   return B{ "B" };
}

C X::f( int, C )
{
   assert( !clist_.empty() );
   return *begin(clist_);
}

C& X::g( B )
{
   return d_;
}

E X::h( E )
{
   return E{ 42, "E" };
}

std::ostream& X::print( std::ostream& os ) const
{
   return os << "\nPrinting X\n\n";
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <X.h>

#include <cstdlib>
#include <iostream>

int main()
{
   X x{ C{} };

   std::cout << x;

   return EXIT_SUCCESS;
}
