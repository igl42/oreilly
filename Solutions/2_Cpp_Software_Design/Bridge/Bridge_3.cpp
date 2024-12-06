/**************************************************************************************************
*
* \file Bridge.cpp
* \brief C++ Training - Example for the Bridge Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
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

   std::string const& getString() noexcept { return s_; }

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

   std::string const& getString( std::size_t index ) noexcept { return strings_[index]; }

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
   std::string const& getString() const noexcept { return s_; }

 private:
   int i_;
   std::string s_;
};


//---- <Fwd.h> ------------------------------------------------------------------------------------

class B;
class C;
class E;


//---- <X.h> --------------------------------------------------------------------------------------

//#include <A.h>

#include <iosfwd>
#include <memory>

class X : public A
{
 public:
   X( C const& );

   ~X();

   X( X const& other );
   X& operator=( X const& other );

   X( X&& );  // Not defaulted and not noexcept!
   X& operator=( X&& ) noexcept;

   B  f( int, char* );
   C  f( int, C );
   C& g( B );
   E  h( E );
   std::ostream& print( std::ostream& ) const override;

 private:
   struct Impl;
   std::unique_ptr<Impl> pimpl_;
};


//---- <X.cpp> ------------------------------------------------------------------------------------

//#include <X.h>

//#include <B.h>
//#include <C.h>
//#include <D.h>
//#include <E.h>

#include <cassert>
#include <list>
#include <ostream>

struct X::Impl
{
   Impl( C const& c )
      : b_{ "B" }
      , clist_{ c, c, c }
      , d_{ "1", "2", "3" }
   {}

   B            b_;
   std::list<C> clist_;
   D            d_;
};

X::X( C const& c )
   : A{}
   , pimpl_{ new Impl{ c } }
{}

X::~X() = default;

X::X( X const& other )
   : A{ other }
   , pimpl_{ std::make_unique<Impl>( *other.pimpl_ ) }
{}

X& X::operator=( X const& other )
{
   // Solution 1
   A::operator=( other );
   *pimpl_ = std::move(*other.pimpl_);

   // Solution 2 (Copy-and-swap idiom)
   //X tmp( other );
   //*this = std::move(tmp);

   return *this;
}

X::X( X&& other )  // Not noexcept, because of std::make_unique!
   : A{ std::move(other) }
   , pimpl_{ std::make_unique<Impl>( std::move(*other.pimpl_) ) }
{}

X& X::operator=( X&& other ) noexcept
{
   A::operator=( std::move(other) );
   *pimpl_ = std::move(*other.pimpl_);
   return *this;
}

B X::f( int, char* )
{
   return B{ "B" };
}

C X::f( int, C )
{
   assert( !pimpl_->clist_.empty() );
   return *begin(pimpl_->clist_);
}

C& X::g( B )
{
   return pimpl_->d_;
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
