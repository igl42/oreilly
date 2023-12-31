/**************************************************************************************************
*
* \file UniquePtr_TypeErasure.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
**************************************************************************************************/

#include <array>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>


//---- <UniquePtr.cpp> ----------------------------------------------------------------------------

template< typename T >
class UniquePtr
{
 public:
   template< typename Deleter = std::default_delete<T> >
   explicit UniquePtr( T* ptr, Deleter d = std::default_delete<T>{} )
      : ptr_{ptr}
   {
      using M = Model<Deleter>;
      static_assert( sizeof(M) <= buffersize, "Given type is too large" );
      static_assert( alignof(M) <= alignment, "Given type is overaligned" );
      ::new (pimpl()) M( std::move(d) );
   }

   ~UniquePtr()
   {
      pimpl()->destroy(ptr_);
      pimpl()->~Concept();
   }

   UniquePtr( UniquePtr const& ) = delete;
   UniquePtr& operator=( UniquePtr const& ) = delete;

   UniquePtr( UniquePtr&& other )
      : ptr_{ std::exchange(other.ptr_,nullptr) }
   {
      other.pimpl()->clone( pimpl() );
   }

   UniquePtr& operator=( UniquePtr&& other )
   {
      pimpl()->destroy(ptr_);
      pimpl()->~Concept();
      ptr_ = std::exchange( other.ptr_, nullptr );
      other.pimpl()->clone( pimpl() );
      return *this;
   }

 private:
   struct Concept
   {
      virtual ~Concept() = default;
      virtual void destroy( T* ptr ) const = 0;
      virtual void clone( Concept* memory ) const = 0;
   };

   template< typename Deleter >
   struct Model final : public Concept
   {
      Model( Deleter d ) : d_{std::move(d)} {}
      virtual void destroy( T* ptr ) const override { d_(ptr); }
      void clone( Concept* memory ) const override { ::new (memory) Model(*this); }
      Deleter d_;
   };

   Concept*       pimpl()       noexcept { return reinterpret_cast<Concept*>( buffer.data() ); }
   Concept const* pimpl() const noexcept { return reinterpret_cast<Concept const*>( buffer.data() ); }

   static constexpr size_t buffersize = 16UL;
   static constexpr size_t alignment  =  8UL;

   T* ptr_;
   alignas(alignment) std::array<std::byte,buffersize> buffer;
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

struct S
{
   S() { puts( "S()" ); }
   S( const S& ) { puts( "S(const S&)" ); }
   S( S&& ) { puts( "S(S&&)" ); }
   S& operator=( const S& ) { puts( "operator=(const S&)" ); return *this; }
   S& operator=( S&& ) { puts( "operator=(S&&)" ); return *this; };
   ~S() { puts( "~S()" ); }
};


struct ChattyDeleter
{
   template< typename T >
   void operator()( T* ptr ) const
   {
      std::cerr << "Destroying ptr " << ptr << "\n";
      delete ptr;
   }

   ChattyDeleter() = default;
   ChattyDeleter( ChattyDeleter const& ) { std::puts( "ChattyDeleter(const ChattyDeleter&)" ); }
   ChattyDeleter( ChattyDeleter&& ) { std::puts( "ChattyDeleter(ChattyDeleter&&)" ); }
   ChattyDeleter& operator=( ChattyDeleter const& ) { std::puts( "ChattyDeleter& operator=(const ChattyDeleter&)" ); return *this; }
   ChattyDeleter& operator=( ChattyDeleter&& ) { std::puts( "ChattyDeleter& operator=(ChattyDeleter&&)" ); return *this; }
};


int main()
{
   UniquePtr<S> uptr1( new S{}, ChattyDeleter{} );

   auto uptr2 = std::move(uptr1);

   return EXIT_SUCCESS;
}

