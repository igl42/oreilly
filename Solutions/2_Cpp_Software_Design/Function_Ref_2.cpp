/**************************************************************************************************
*
* \file Function_Ref_2.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement a simplified std::function_ref to represent a non-owning abstraction for
*       any type of callable.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <string>
#include <memory>
#include <utility>


//---- <Function.h> -------------------------------------------------------------------------------

namespace detail {

template< typename R, typename... Args >
class Concept
{
 public:
   virtual ~Concept() = default;
   virtual R invoke( Args... ) const = 0;
   virtual std::unique_ptr<Concept> clone() const = 0;  // Prototype design pattern
   virtual void clone( Concept* memory ) const = 0;
};

template< typename Fn, typename R, typename... Args >
class NonOwningModel;

template< typename Fn, typename R, typename... Args >
class OwningModel final : public Concept<R,Args...>
{
 public:
   using Concept_t = Concept<R,Args...>;

   explicit OwningModel( Fn fn ) : fn_{ fn } {}

   R invoke( Args... args ) const final { return fn_( std::forward<Args>( args )... ); }
   std::unique_ptr<Concept_t> clone() const final { return std::make_unique<OwningModel>(*this); }
   void clone( Concept_t* memory ) const final { new (memory) NonOwningModel<Fn const,R,Args...>( fn_ ); }

 private:
   Fn fn_;
};

template< typename Fn, typename R, typename... Args >
class NonOwningModel final : public Concept<R,Args...>
{
 public:
   using Concept_t = Concept<R,Args...>;

   NonOwningModel( Fn& fn ) : fn_{ std::addressof(fn) } {}

   R invoke( Args... args ) const final { return (*fn_)( std::forward<Args>( args )... ); }
   std::unique_ptr<Concept_t> clone() const final { return std::make_unique<OwningModel<Fn,R,Args...>>( *fn_ ); }
   void clone( Concept_t* memory ) const final { new (memory) NonOwningModel(*this); }

 private:
   Fn* fn_{ nullptr };
};

}  // namespace detail


template< typename Fn >
class Function;

template< typename Fn >
class FunctionRef;


template< typename R, typename... Args >
class Function<R(Args...)>
{
 public:
   template< typename Fn >
   Function( Fn fn ) : pimpl_( std::make_unique<detail::OwningModel<Fn,R,Args...>>( fn ) ) {}

   Function( Function const& other ) : pimpl_( other.pimpl_->clone() ) {}
   Function& operator=( Function const& other ) { std::swap( pimpl_, other.pimpl_ ); return *this; }

   Function( Function&& ) = default;
   Function& operator=( Function&& ) = default;

   ~Function() = default;

   R operator()( Args... args ) const { return pimpl_->invoke( std::forward<Args>( args )... ); }

 private:
   using Concept = detail::Concept<R,Args...>;

   std::unique_ptr<Concept> pimpl_;

   template< typename F > friend class FunctionRef;
};


template< typename R, typename... Args >
class FunctionRef<R(Args...)>
{
 public:
   // Expected size of a model instantiation: sizeof(Fn*) + sizeof(vptr)
   static constexpr size_t modelSize = 16UL;

   template< typename Fn >
   FunctionRef( Fn& fn )  // Type Fn is possibly cv qualified;
                          // lvalue reference prevents fn references to rvalues
   {
      using Model = detail::NonOwningModel<Fn,R,Args...>;
      static_assert( sizeof( Model ) == modelSize, "Invalid model size detected" );
      new (raw_) Model( fn );
   }

   FunctionRef( FunctionRef const& other )    { other.pimpl()->clone( pimpl() ); }
   FunctionRef( Function<R(Args...)>& other ) { other.pimpl_->clone( pimpl() ); }

   ~FunctionRef() { pimpl()->~Concept(); }

   FunctionRef& operator=( FunctionRef const& other )
   {
      pimpl()->~Concept();
      other.pimpl()->clone( pimpl() );
      return *this;
   }

   R operator()( Args... args ) const { return pimpl()->invoke( std::forward<Args>( args )... ); }

 private:
   using Concept = detail::Concept<R,Args...>;

   Concept*       pimpl()       { return reinterpret_cast<Concept*>( raw_ ); }
   Concept const* pimpl() const { return reinterpret_cast<Concept const*>( raw_ ); }

   alignas(void*) char raw_[modelSize];
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

template< typename Fn, typename... Args >
void test( FunctionRef<Fn> const& f, Args&&... args )
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
      test<int(void)>( fp );
   }

   {
      auto const fo = Foo{};  // Function object
      test<double(double)>( fo, 1.0 );
   }

   {
      auto const lambda = [](){ return "three"; };  // Lambda
      test<std::string(void)>( lambda );
   }

   {
      auto const fn = Function<int(void)>( [](){ return 4; } );  // Function instance
      test<int(void)>( fn );
   }

   return EXIT_SUCCESS;
}
