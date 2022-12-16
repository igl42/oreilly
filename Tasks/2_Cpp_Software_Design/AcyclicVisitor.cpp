/**************************************************************************************************
*
* \file AcyclicVisitor.cpp
* \brief C++ Training - Programming Task for the Acyclic Visitor Design Pattern
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Refactor the classic Visitor solution by a value semantics based solution. Note that
*       the general behavior should remain unchanged.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <memory>
#include <vector>


//---- <AbstractVisitor.h> ------------------------------------------------------------------------

class AbstractVisitor
{
 public:
   virtual ~AbstractVisitor() = default;
};


//---- <Shape.h> ----------------------------------------------------------------------------------

class Shape
{
 public:
   virtual ~Shape() = default;

   virtual void accept( const AbstractVisitor& v ) = 0;
};


//---- <Visitor.h> --------------------------------------------------------------------------------

template< typename T >
class Visitor
{
 protected:
   ~Visitor() = default;

 public:
   virtual void visit( const T& ) const = 0;
};


//---- <Circle.h> ---------------------------------------------------------------------------------

class Circle : public Shape
{
 public:
   explicit Circle( double radius )
      : radius_( radius )
   {}

   void accept( const AbstractVisitor& v ) override {
      if( auto cv = dynamic_cast<const Visitor<Circle>*>(&v) ) {
         cv->visit(*this);
      }
   }

   double radius() const { return radius_; }

 private:
   double radius_;
};


//---- <Square.h> ---------------------------------------------------------------------------------

class Square : public Shape
{
 public:
   explicit Square( double side )
      : side_( side )
   {}

   void accept( const AbstractVisitor& v ) override {
      if( auto sv = dynamic_cast<const Visitor<Square>*>(&v) ) {
         sv->visit(*this);
      }
   }

   double side() const { return side_; }

 private:
   double side_;
};


//---- <Draw.h> -----------------------------------------------------------------------------------

class Draw : public AbstractVisitor, public Visitor<Circle>, public Visitor<Square>
{
 public:
   void visit( const Circle& c ) const override { std::cout << "circle: radius=" << c.radius() << "\n"; }
   void visit( const Square& s ) const override { std::cout << "square: side=" << s.side() << "\n"; }
};


//---- <DrawAllShapes.h> --------------------------------------------------------------------------

using Shapes = std::vector< std::unique_ptr<Shape> >;

void drawAllShapes( Shapes const& shapes );


//---- <DrawAllShapes.cpp> ------------------------------------------------------------------------

void drawAllShapes( Shapes const& shapes )
{
   for( auto const& shape : shapes )
   {
      shape->accept( Draw{} );
   }
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   Shapes shapes{};

   shapes.emplace_back( std::make_unique<Circle>( 2.3 ) );
   shapes.emplace_back( std::make_unique<Square>( 1.2 ) );
   shapes.emplace_back( std::make_unique<Circle>( 4.1 ) );

   drawAllShapes( shapes );

   return EXIT_SUCCESS;
}
