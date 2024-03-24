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

#include <cstdlib>
#include <iomanip>  // For the C++14 'std::quoted'
#include <iostream>
#include <string>
#include <utility>


//---- <Resource.h> (external) --------------------------------------------------------------------

class Resource
{
 private:
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

 public:
   int get() const { return i_; }
   void set( int i ) { i_ = i; }

 private:
   int i_{};

   friend Resource* createResource( int );
   friend Resource* cloneResource( Resource* );
   friend void destroyResource( Resource* );
};

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
   ResourceOwner( ResourceOwner const& other )
      : m_id  { other.m_id }    // Copy of the integer
      , m_name{ other.m_name }  // Copy construction of the string
   {
      if( other.m_resource != nullptr ) {
         m_resource = cloneResource( other.m_resource );  // Copy construction of the resource
      }
   }

   // Step 1: Implement the copy assignment operator of class 'ResourceOwner'.
   ResourceOwner& operator=( ResourceOwner const& other )
   {
      // Solution 1: Manual solution
      if( this != &other )
      {
         m_id   = other.m_id;    // Copy of the integer
         m_name = other.m_name;  // Copy assignment of the string

         if( m_resource ) {
            destroyResource( m_resource );
            m_resource = nullptr;
         }

         if( other.m_resource != nullptr ) {
            m_resource = cloneResource( other.m_resource );  // Copy construction of the resource
         }
      }
      return *this;

      // Solution 2: Copy-and-swap idiom
      /*
      ResourceOwner tmp{ other };  // Copy constructor call
      swap( tmp );
      return *this;
      */
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
   std::string const& name()     const { return m_name;     }
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
   ResourceOwner owner1( 1, "id1", createResource(101) );
   std::cout << "\n"
             << " owner1: id=" << owner1.id() << ", name=" << std::quoted(owner1.name())
             << ", resource=" << owner1.resource()->get() << ", &resource = " << owner1.resource() << "\n\n";

   ResourceOwner owner2( owner1 );  // Copy constructor
   std::cout << " owner2: id=" << owner2.id() << ", name=" << std::quoted(owner2.name())
             << ", resource=" << owner2.resource()->get() << ", &resource = " << owner2.resource() << "\n\n";

   owner1.resource()->set(202);
   owner2 = owner1;  // Copy assignment operator
   std::cout << " owner2: id=" << owner2.id() << ", name=" << std::quoted(owner2.name())
             << ", resource=" << owner2.resource()->get() << ", &resource = " << owner2.resource() << "\n\n";

   //owner1.resource()->set(303);
   //ResourceOwner owner3( std::move(owner1) );  // Move constructor
   //std::cout << " owner3: id=" << owner3.id() << ", name=" << std::quoted(owner3.name())
   //          << ", resource=" << owner3.resource()->get() << ", &resource = " << owner3.resource() << "\n\n";

   //owner2.resource()->set(404);
   //owner1 = std::move(owner2);  // Move assignment operator
   //std::cout << " owner1: id=" << owner1.id() << ", name=" << std::quoted(owner1.name())
   //          << ", resource=" << owner1.resource()->get() << ", &resource = " << owner1.resource() << "\n\n";

   return EXIT_SUCCESS;
}
