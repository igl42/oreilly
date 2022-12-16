/**************************************************************************************************
*
* \file Prototype.cpp
* \brief C++ Training - Example for the Prototype Design Pattern
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Discuss the advantages and disadvantages of the given implementation of the classic
*       Adapter design pattern.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <list>
#include <memory>
#include <vector>


//---- <Container.h> ------------------------------------------------------------------------------

template< typename T >
class Container
{
 public:
   virtual ~Container() = default;

   virtual void push_back( const T& ) = 0;
   virtual void pop_back() = 0;
   virtual void print( std::ostream& ) const = 0;
};


//---- <Vector.h> ---------------------------------------------------------------------------------

template< typename T >
class Vector : public Container<T>
{
 public:
   // Note: No explicit declaration of any special member function!

   void push_back( const T& value ) override { vector_.push_back( value ); }
   void pop_back() override { vector_.pop_back(); }
   void print( std::ostream& os ) const override;

 private:
   std::vector<T> vector_;
};

template< typename T >
void Vector<T>::print( std::ostream& os ) const
{
   os << "(";
   for( const auto& value : vector_ ) {
      os << " " << value;
   }
   os << " )";
}


//---- <List.cpp> ---------------------------------------------------------------------------------

template< typename T >
class List : public Container<T>
{
 public:
   // Note: No explicit declaration of any special member function!

   void push_back( const T& value ) override { list_.push_back( value ); }
   void pop_back() override { list_.pop_back(); }
   void print( std::ostream& os ) const override;

 private:
   std::list<T> list_;
};

template< typename T >
void List<T>::print( std::ostream& os ) const
{
   os << "(";
   for( const auto& value : list_ ) {
      os << " " << value;
   }
   os << " )";
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   std::unique_ptr<Container<int>> c1( std::make_unique<Vector<int>>() );
   std::unique_ptr<Container<int>> c2( std::make_unique<List<int>>() );

   c1->push_back( 1 );
   c1->push_back( 2 );
   c1->push_back( 3 );
   c1->push_back( 5 );
   c1->pop_back();
   c1->push_back( 4 );
   c1->print( std::cout );
   std::cout << '\n';

   c2->push_back( 5 );
   c2->pop_back();
   c2->push_back( 4 );
   c2->push_back( 3 );
   c2->push_back( 2 );
   c2->push_back( 1 );
   c2->print( std::cout );
   std::cout << '\n';

   return EXIT_SUCCESS;
}
