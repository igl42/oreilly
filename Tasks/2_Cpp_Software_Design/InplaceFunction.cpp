/**************************************************************************************************
*
* \file InplaceFunction.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
**************************************************************************************************/

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <string>


//---- <Function.h> -------------------------------------------------------------------------------

template< typename Fn, size_t Capacity, size_t Alignment = 8UL >
class Function;

template< typename R, typename... Args, size_t Capacity, size_t Alignment >
class Function<R(Args...),Capacity,Alignment>
{
 public:
   template< typename Fn >
   Function( Fn fn )
   {
      static_assert( sizeof(Fn) <= Capacity, "Given type is too large" );
      new (pimpl()) Model<Fn>( fn );
   }

   Function( Function const& f )
   {
      f.pimpl()->clone( pimpl() );
   }

   Function& operator=( Function f )
   {
      pimpl()->~Concept();
      f.pimpl()->clone( pimpl() );
      return *this;
   }

   ~Function() { pimpl()->~Concept(); }

   R operator()( Args... args ) { return (*pimpl())( std::forward<Args>( args )... ); }

 private:
   class Concept
   {
    public:
      virtual ~Concept() = default;
      virtual R operator()( Args... ) const = 0;
      virtual void clone( Concept* memory ) const = 0;
   };

   template< typename Fn >
   class Model final : public Concept
   {
    public:
      explicit Model( Fn fn )
         : fn_( fn )
      {}

      R operator()( Args... args ) const final { return fn_( std::forward<Args>( args )... ); }
      void clone( Concept* memory ) const final { new (memory) Model(*this); }

    private:
      Fn fn_;
   };

   Concept*       pimpl()       { return reinterpret_cast<Concept*>( buffer ); }
   const Concept* pimpl() const { return reinterpret_cast<const Concept*>( buffer ); }

   alignas(Alignment) std::byte buffer[Capacity+sizeof(void*)];
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

template< typename Fn, size_t Capacity, typename... Args >
void test( const Function<Fn,Capacity>& f, Args&&... args )
{
   const auto res = f( std::forward<Args>(args)... );
   std::cout << "\n res = " << res << "\n\n";
}


int foo()
{
   return 1;
}

struct Foo {
   double operator()( double d ) const {
      return 2.0*d;
   }
};


int main()
{
   /*
   {
      const auto fp = foo;  // Function pointer
      test<int(void),8UL>( fp );
   }

   {
      const auto fo = Foo{};  // Function object
      test<double(double),8UL>( fo, 1.0 );
   }

   {
      const auto lambda = [](){ return "three"; };  // Lambda
      test<std::string(void),8UL>( lambda );
   }
   */

   return EXIT_SUCCESS;
}
