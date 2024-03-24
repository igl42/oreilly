/**************************************************************************************************
*
* \file RVO3.cpp
* \brief C++ Training - Example for copy elision (aka Return Value Optimization; RVO)
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Evaluate the given code examples. Will the functions apply copy elision (aka RVO)?
*
**************************************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <string>
#include <utility>


struct S
{
   S() { std::puts( "S()" ); }
   S( char const* s ) : value( s ) { std::puts( "S(char const*)" ); }
   S( S const& ) { std::puts( "S(S const&)" ); }
   S( S&& ) { std::puts( "S(S&&)" ); }
   ~S() { std::puts( "~S()" ); }
   S& operator=( S const& ) { std::puts( "S& operator=(S const&)" ); return *this; }
   S& operator=( S&& ) { std::puts( "S& operator=(S&&)" ); return *this; }

   std::string value;
};


//*************************************************************************************************
// RVO Example 1: Return of unnamed stack variable
S f()  // Also with 'S const' return type
{
   return S{};
}

int main()
{
   S s{ f() };
}
//*************************************************************************************************


//*************************************************************************************************
// RVO Example 2: Return of named stack variable
/*
S f()
{
   S s{ "1" };
   s = S{ "2" };
   return s;
}

int main()
{
   S s{ f() };
}
*/
//*************************************************************************************************


//*************************************************************************************************
// RVO Example 3: Return stack variable by means of move
/*
S f()
{
   S s{};
   return std::move(s);
}

int main()
{
   S s{ f() };
}
*/
//*************************************************************************************************


//*************************************************************************************************
// RVO Example 4: Return of function argument
/*
S f( S s )
{
   return s;
}

int main()
{
   S s1{};
   S s2{ f( s1 ) };
}
*/
//*************************************************************************************************


//*************************************************************************************************
// RVO Example 5: Conditional return of function argument
/*
S f( bool b, S s )
{
   if( b )
      s = S{};
   return s;
}

int main()
{
   S s1{};
   S s2{ f( rand() > (RAND_MAX/2), s1 ) };
}
*/
//*************************************************************************************************


//*************************************************************************************************
// RVO Example 6: Conditional return of lvalues
/*
S f( bool b )
{
   S s1{};
   S s2{};

   if( b )
      return s1;
   else
      return s2;
}

int main()
{
   S s{ f( rand() > (RAND_MAX/2) ) };
}
*/
//*************************************************************************************************


//*************************************************************************************************
// RVO Example 7: Conditional return of rvalues (1)
/*
S f( bool b )
{
   if( b )
      return S{};
   else
      return S{};
}

int main()
{
   S s{ f( rand() > (RAND_MAX/2) ) };
}
*/
//*************************************************************************************************


//*************************************************************************************************
// RVO Example 8: Conditional return of rvalues (2)
/*
S getS() { return S{ "First option" }; }

S f( bool b )
{
   if( b )
      return getS();
   return S{ "Second option" };
}

int main()
{
   S s{ f( rand() > (RAND_MAX/2) ) };
}
*/
//*************************************************************************************************


//*************************************************************************************************
// RVO Example 9: Conditional return of lvalue vs. rvalue (1)
/*
S f( bool b )
{
   if( b )
   {
      S s{};
      return s;
   }
   return S{};
}

int main()
{
   S s{ f( rand() > (RAND_MAX/2) ) };
}
*/
//*************************************************************************************************


//*************************************************************************************************
// RVO Example 10: Conditional return of lvalue vs. rvalue (2)
/*
S f( bool b )
{
   S s{};
   if( b )
      return s;
   return S{};
}

int main()
{
   S s{ f( false ) };
}
*/
//*************************************************************************************************


//*************************************************************************************************
// RVO Example 11: Return from conditional operator (1)
/*
S f( bool b )
{
   S s{};
   return b ? s : S{};
}

int main()
{
   S s{ f( true ) };
}
*/
//*************************************************************************************************


//*************************************************************************************************
// RVO Example 12: Return from conditional operator (2)
/*
S getS() { return S{}; }

S f( bool b )
{
   return b ? getS() : S{};
}

int main()
{
   S s{ f( false ) };
}
*/
//*************************************************************************************************

