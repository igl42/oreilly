/**************************************************************************************************
*
* \file Bridge_Static.cpp
* \brief C++ Training - Example for the Bridge Design Pattern
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
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

class B;
class C;
class E;


//---- <X.h> --------------------------------------------------------------------------------------

#include <cstddef>
#include <iosfwd>
#include <memory>
#include <type_traits>

#if _MSC_VER && !__INTEL_COMPILER
#  define _ENABLE_EXTENDED_ALIGNED_STORAGE
#endif

//#include <A.h>
//#include <Fwd.h>

class X : public A
{
 public:
   X( const C& );
   ~X();

   B  f( int, char* );
   C  f( int, C );
   C& g( B );
   E  h( E );
   std::ostream& print( std::ostream& ) const override;

 private:
   struct XImpl;

   XImpl& pimpl() { return *reinterpret_cast<XImpl*>(&buffer_); }

   static constexpr size_t buffersize  = 100;
   static constexpr size_t bufferalign =  16;

   using Buffer = std::aligned_storage<buffersize,bufferalign>::type;
   Buffer buffer_;
};


inline std::ostream& operator<<( std::ostream& os, const X& x )
{
   return x.print( os );
}


//---- <X.cpp> ------------------------------------------------------------------------------------

//#include <X.h>
//#include <B.h>
//#include <C.h>
//#include <D.h>
//#include <E.h>

#include <cassert>
#include <list>
#include <ostream>

struct X::XImpl
{
   XImpl( const C& c )
      : b_{ "B" }
      , clist_{ c, c, c }
      , d_{ "1", "2", "3" }
   {}

   B            b_;
   std::list<C> clist_;
   D            d_;
};

X::X( const C& c )
   : A{}
{
   static_assert( sizeof(XImpl) <= sizeof(buffer_) );
   static_assert( alignof(XImpl) <= alignof(Buffer) );

   new (&buffer_) XImpl{ c };
}

X::~X() = default;

B X::f( int, char* )
{
   return B{ "B" };
}

C X::f( int, C )
{
   assert( !pimpl().clist_.empty() );
   return *begin(pimpl().clist_);
}

C& X::g( B )
{
   return pimpl().d_;
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

#include <iostream>

//#include <X.h>

int main()
{
   X x{ C{} };

   x.print( std::cout );
}
