/**************************************************************************************************
*
* \file AcyclicVisitor.cpp
* \brief C++ Training - Programming Task for the Acyclic Visitor Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Refactor the classic Visitor solution by a value semantics based solution. Note that
*       the general behavior should remain unchanged.
*
**************************************************************************************************/


//---- <GraphicsLibrary.h> (external) -------------------------------------------------------------

#include <string>
// ... and many more graphics-related headers

namespace gl {

enum class Color
{
   red   = 0xFF0000,
   green = 0x00FF00,
   blue  = 0x0000FF
};

std::string to_string( Color color )
{
   switch( color ) {
      case Color::red:
         return "red (0xFF0000)";
      case Color::green:
         return "green (0x00FF00)";
      case Color::blue:
         return "blue (0x0000FF)";
      default:
         return "unknown";
   }
}

} // namespace gl


//---- <Point.h> ----------------------------------------------------------------------------------

struct Point
{
   double x;
   double y;
};


//---- <AbstractVisitor.h> ------------------------------------------------------------------------

class AbstractVisitor
{
 public:
   virtual ~AbstractVisitor() = default;
};


//---- <Shape.h> ----------------------------------------------------------------------------------

//#include <AbstractVisitor.h>

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

//#include <Point.h>
//#include <Shape.h>

class Circle : public Shape
{
 public:
   explicit Circle( double radius )
      : radius_{ radius }
      , center_{}
   {}

   void accept( const AbstractVisitor& v ) override {
      if( auto cv = dynamic_cast<const Visitor<Circle>*>(&v) ) {
         cv->visit(*this);
      }
   }

   double radius() const { return radius_; }
   Point  center() const { return center_; }

 private:
   double radius_;
   Point center_;
};


//---- <Square.h> ---------------------------------------------------------------------------------

//#include <Point.h>
//#include <Shape.h>

class Square : public Shape
{
 public:
   explicit Square( double side )
      : side_{ side }
      , center_{}
   {}

   void accept( const AbstractVisitor& v ) override {
      if( auto sv = dynamic_cast<const Visitor<Square>*>(&v) ) {
         sv->visit(*this);
      }
   }

   double side() const { return side_; }
   Point center() const { return center_; }

 private:
   double side_;
   Point center_;
};


//---- <GLDrawVisitor.h> --------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <Visitor.h>
//#include <GraphicsLibrary.h>
#include <iostream>

class GLDrawVisitor : public AbstractVisitor
                    , public Visitor<Circle>
                    , public Visitor<Square>
{
 public:
   explicit GLDrawVisitor( gl::Color color ) : color_{color} {}

   void visit( Circle const& circle ) const override
   {
      std::cout << "circle: radius=" << circle.radius()
                << ", color = " << gl::to_string(color_) << '\n';
   }

   void visit( Square const& square ) const override
   {
      std::cout << "square: side=" << square.side()
                << ", color = " << gl::to_string(color_) << '\n';
   }

 private:
   gl::Color color_{};
};


//---- <Shapes.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
#include <memory>
#include <vector>

using Shapes = std::vector<std::unique_ptr<Shape>>;


//---- <DrawAllShapes.h> --------------------------------------------------------------------------

//#include <Shapes.h>

void drawAllShapes( Shapes const& shapes );


//---- <DrawAllShapes.cpp> ------------------------------------------------------------------------

//#include <DrawAllShapes.h>
//#include <GLDrawVisitor.h>

void drawAllShapes( Shapes const& shapes )
{
   for( auto const& shape : shapes )
   {
      shape->accept( GLDrawVisitor{gl::Color::red} );
   }
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <Shapes.h>
//#include <DrawAllShapes.h>
#include <cstdlib>

int main()
{
   Shapes shapes{};

   shapes.emplace_back( std::make_unique<Circle>( 2.3 ) );
   shapes.emplace_back( std::make_unique<Square>( 1.2 ) );
   shapes.emplace_back( std::make_unique<Circle>( 4.1 ) );

   drawAllShapes( shapes );

   return EXIT_SUCCESS;
}
