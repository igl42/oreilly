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
#include <memory>
#include <string>


//---- <Function.h> -------------------------------------------------------------------------------

template< typename Fn, size_t Capacity, size_t Alignment = 8UL >
class Function;

template< typename R, typename... Args, size_t Capacity, size_t Alignment >
class Function<R(Args...),Capacity,Alignment>
{
 public:
   template< typename Callable >
   Function( Callable callable )
   {
      using M = Model<Callable>;
      static_assert( sizeof(M) <= Capacity, "Given type is too large" );
      static_assert( alignof(M) <= Alignment, "Given type is not properly aligned" );
      ::new (pimpl()) M( callable );  // Alternatively 'std::construct_at()' (C++20)
   }

   Function( Function const& f )
   {
      f.pimpl()->clone( pimpl() );
   }

   Function& operator=( Function const& f )
   {
      pimpl()->~Concept();
      f.pimpl()->clone( pimpl() );
      return *this;
   }

   ~Function()
   {
      pimpl()->~Concept();  // Alternatively 'std::destroy_at()' (C++17)
   }

   R operator()( Args... args ) const { return (*pimpl())( std::forward<Args>( args )... ); }

 private:
   class Concept
   {
    public:
      virtual ~Concept() = default;
      virtual R operator()( Args... ) const = 0;
      virtual void clone( Concept* memory ) const = 0;
   };

   template< typename Callable >
   class Model final : public Concept
   {
    public:
      explicit Model( Callable callable )
         : callable_( callable )
      {}

      R operator()( Args... args ) const final { return callable_( std::forward<Args>( args )... ); }
      void clone( Concept* memory ) const final { new (memory) Model(*this); }

    private:
      Callable callable_;
   };

   Concept*       pimpl()       { return reinterpret_cast<Concept*>( buffer ); }
   Concept const* pimpl() const { return reinterpret_cast<Concept const*>( buffer ); }

   alignas(Alignment) std::byte buffer[Capacity];
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

template< typename Fn, size_t Capacity, typename... Args >
void test( Function<Fn,Capacity> const& f, Args&&... args )
{
   auto const res = f( std::forward<Args>(args)... );
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

   {
      auto const fp = foo;  // Function pointer
      test<int(void),16UL>( fp );
   }

   {
      auto const fo = Foo{};  // Function object
      test<double(double),16UL>( fo, 1.0 );
   }

   {
      auto const lambda = [](){ return "three"; };  // Lambda
      test<std::string(void),16UL>( lambda );
   }


   return EXIT_SUCCESS;
}
