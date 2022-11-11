/**************************************************************************************************
*
* \file ResourceOwner.cpp
* \brief C++ Training - Example for Copy and Move Operations
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Implement the copy operations of class 'ResourceOwner'.
*
* Step 2: Implement the move operations of class 'ResourceOwner'.
*
* Step 3: Refactor the 'ResourceOwner' to remove as many of the special member functions as
*         possible without changing the interface or behavior.
*
* Step 4: Assume the invariant that the 'm_resource' pointer must never be a nullptr. What
*         changes to the implementation of the special member functions are necessary?
*
**************************************************************************************************/

#include <cstdlib>
#include <iomanip>  // For the C++14 'std::quoted'
#include <iostream>
#include <string>
#include <utility>


class Resource
{
 public:
   explicit Resource( int i )
      : i_{ i }
   {}

   // Copy constructor (explicit definition as reference for the programming task)
   Resource( Resource const& other )
      : i_{ other.i_ }
   {}

   ~Resource() = default;

   // Copy assignment operator (explicit definition as reference for the programming task)
   Resource& operator=( Resource const& other )
   {
      i_ = other.i_;
      return *this;
   }

   // Move constructor (explicit definition as reference for the programming task)
   Resource( Resource&& other ) noexcept
      : i_{ std::move(other.i_) }
   {}

   // Move assignment operator (explicit definition as reference for the programming task)
   Resource& operator=( Resource&& other ) noexcept
   {
      i_ = std::move(other.i_);
      return *this;
   }

   int get() const { return i_; }
   void set( int i ) { i_ = i; }

 private:
   int i_{};
};


class ResourceOwner
{
 public:
   ResourceOwner( int id, const std::string& name, Resource* resource )
      : m_id      { id }
      , m_name    { name }
      , m_resource{ resource }
   {}

   ~ResourceOwner()
   {
      delete m_resource;
   }

   // Step 1: Implement the copy constructor of class 'ResourceOwner'.
   ResourceOwner( ResourceOwner const& other )
      : m_id  { other.m_id }
      , m_name{ other.m_name }
   {
      if( other.m_resource != nullptr ) {
         m_resource = new Resource( *other.m_resource );
      }
   }

   // Step 1: Implement the copy assignment operator of class 'ResourceOwner'.
   ResourceOwner& operator=( ResourceOwner const& other )
   {
      // Temporary swap idiom
      ResourceOwner tmp( other );
      swap( tmp );
      return *this;
   }

   // Step 2: Implement the move constructor of class 'ResourceOwner'.
   // TODO

   // Step 2: Implement the move assignment operator of class 'ResourceOwner'.
   // TODO

   void swap( ResourceOwner& other ) noexcept
   {
      using std::swap;
      swap( m_id      , other.m_id       );
      swap( m_name    , other.m_name     );
      swap( m_resource, other.m_resource );
   }

   int                id()       const { return m_id;       }
   const std::string& name()     const { return m_name;     }
   Resource*          resource()       { return m_resource; }
   Resource const*    resource() const { return m_resource; }

 private:
   int m_id{ 0 };
   std::string m_name{};
   Resource* m_resource{ nullptr };
};

void swap( ResourceOwner& a, ResourceOwner& b ) noexcept
{
   a.swap( b );
}


int main()
{
   ResourceOwner owner1( 1, "id1", new Resource( 101 ) );
   std::cout << "\n"
             << " owner1: id=" << owner1.id() << ", name=" << std::quoted(owner1.name())
             << ", resource=" << owner1.resource()->get() << ", &resource = " << owner1.resource() << "\n\n";

   ResourceOwner owner2( owner1 );
   std::cout << " owner2: id=" << owner2.id() << ", name=" << std::quoted(owner2.name())
             << ", resource=" << owner2.resource()->get() << ", &resource = " << owner2.resource() << "\n\n";

   owner1.resource()->set( 202 );
   owner2 = owner1;
   std::cout << " owner2: id=" << owner2.id() << ", name=" << std::quoted(owner2.name())
             << ", resource=" << owner2.resource()->get() << ", &resource = " << owner2.resource() << "\n\n";

   //owner1.resource()->set( 303 );
   //ResourceOwner owner3( std::move( owner1 ) );
   //std::cout << " owner3: id=" << owner3.id() << ", name=" << std::quoted(owner3.name())
   //          << ", resource=" << owner3.resource()->get() << ", &resource = " << owner3.resource() << "\n\n";

   //owner2.resource()->set( 404 );
   //owner1 = std::move( owner2 );
   //std::cout << " owner1: id=" << owner1.id() << ", name=" << std::quoted(owner1.name())
   //          << ", resource=" << owner1.resource()->get() << ", &resource = " << owner1.resource() << "\n\n";

   return EXIT_SUCCESS;
}
