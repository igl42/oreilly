/**************************************************************************************************
*
* \file ResourceOwner.cpp
* \brief C++ Training - Example for Copy and Move Operations
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
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

#include <cassert>
#include <cstdlib>
#include <iomanip>  // For the C++14 'std::quoted'
#include <iostream>
#include <memory>
#include <string>
#include <utility>


//---- <Resource.h> (external) --------------------------------------------------------------------

class Resource
{
 private:
   explicit Resource( int i )
      : i_{ i }
   {
      ++number_of_active_instances_;
   }

   // Copy constructor (explicit definition as reference for the programming task)
   Resource( Resource const& other )
      : i_{ other.i_ }
   {
      ++number_of_active_instances_;
   }

   ~Resource()
   {
      --number_of_active_instances_;
   }

   // Copy assignment operator (explicit definition as reference for the programming task)
   Resource& operator=( Resource const& other )
   {
      i_ = other.i_;
      return *this;
   }

   // Move constructor (explicit definition as reference for the programming task)
   Resource( Resource&& other ) noexcept
      : i_{ std::move(other.i_) }
   {
      ++number_of_active_instances_;
   }

   // Move assignment operator (explicit definition as reference for the programming task)
   Resource& operator=( Resource&& other ) noexcept
   {
      i_ = std::move(other.i_);
      return *this;
   }

 public:
   int get() const { return i_; }
   void set( int i ) { i_ = i; }

   static unsigned int number_of_active_instances() { return number_of_active_instances_; }

 private:
   int i_{};

   friend Resource* createResource( int );
   friend Resource* cloneResource( Resource* );
   friend void destroyResource( Resource* );

   static unsigned int number_of_active_instances_;
};

unsigned int Resource::number_of_active_instances_{};

Resource* createResource( int i )
{
   return new Resource{i};
}

Resource* cloneResource( Resource* other )
{
   // Note that this function does not check for nullptrs.
   //   Sigh... External libraries are rarely perfect :-(
   return new Resource{*other};
}

void destroyResource( Resource* resource )
{
   // Note that deleting a nullptr is valid behavior (see http://eel.is/c++draft/expr.delete#2),
   //   but we cannot assume that the library is doing things properly :-(
   delete resource;
}


//---- <ResourceOwner.h> --------------------------------------------------------------------------

class ResourceOwner
{
 public:
   ResourceOwner( int id, std::string const& name, Resource* resource )
      : m_id      { id }
      , m_name    { name }
      , m_resource{ resource }
   {}

   ~ResourceOwner()
   {
      if( m_resource ) {
         destroyResource( m_resource );
      }
   }

   // Step 1: Implement the copy constructor of class 'ResourceOwner'.
   // TODO

   // Step 1: Implement the copy assignment operator of class 'ResourceOwner'.
   // TODO

   // Step 2: Implement the move constructor of class 'ResourceOwner'.
   // TODO

   // Step 2: Implement the move assignment operator of class 'ResourceOwner'.
   // TODO

   int                id()       const { return m_id;       }
   std::string const& name()     const { return m_name;     }
   Resource*          resource()       { return m_resource; }
   Resource const*    resource() const { return m_resource; }

 private:
   int m_id{ 0 };
   std::string m_name{};
   Resource* m_resource{ nullptr };
};


int main()
{
   {
      ResourceOwner owner1( 1, "id1", createResource(101) );
      assert( owner1.id() == 1 );
      assert( owner1.name() == "id1" );
      assert( owner1.resource()->get() == 101 );
      assert( Resource::number_of_active_instances() == 1U );

      ResourceOwner owner2( owner1 );  // Copy constructor
      assert( owner2.id() == 1 );
      assert( owner2.name() == "id1" );
      assert( owner2.resource()->get() == 101 );
      //assert( owner2.resource() != owner1.resource() );
      //assert( Resource::number_of_active_instances() == 2U );

      owner1.resource()->set(202);
      owner2 = owner1;  // Copy assignment operator
      assert( owner2.id() == 1 );
      assert( owner2.name() == "id1" );
      assert( owner2.resource()->get() == 202 );
      //assert( owner2.resource() != owner1.resource() );
      //assert( Resource::number_of_active_instances() == 2U );

      /*
      owner1.resource()->set(303);
      ResourceOwner owner3( std::move(owner1) );  // Move constructor
      assert( owner3.id() == 1 );
      assert( owner3.name() == "id1" );
      assert( owner3.resource()->get() == 303 );
      assert( owner3.resource() != owner1.resource() );
      assert( owner3.resource() != owner2.resource() );
      assert( Resource::number_of_active_instances() == 2U );

      owner2.resource()->set(404);
      owner1 = std::move(owner2);  // Move assignment operator
      assert( owner1.id() == 1 );
      assert( owner1.name() == "id1" );
      assert( owner1.resource()->get() == 404 );
      assert( owner1.resource() != owner2.resource() );
      assert( owner1.resource() != owner3.resource() );
      assert( Resource::number_of_active_instances() == 2U );
      */
   }

   assert( Resource::number_of_active_instances() == 0U );

   return EXIT_SUCCESS;
}
