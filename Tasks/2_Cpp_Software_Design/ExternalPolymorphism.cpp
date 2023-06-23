/**************************************************************************************************
*
* \file ExternalPolymorphism.cpp
* \brief C++ Training - Programming Task for the External Polymorphism Design Pattern
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Refactor the given Strategy-based solution and extract the polymorphic behavior of
*       all shapes by means of the External Polymorphism design pattern. Note that the general
*       behavior should remain unchanged.
*
**************************************************************************************************/


//---- <GraphicsLibrary.h> (external) -------------------------------------------------------------

#include <string>
// ... and many more graphics-related headers

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


//---- <Point.h> ----------------------------------------------------------------------------------

struct Point
{
   double x;
   double y;
};


//---- <Shape.h> ----------------------------------------------------------------------------------

class Shape
{
 public:
   virtual ~Shape() = default;

   virtual void draw() const = 0;
};


//---- <Circle.h> ---------------------------------------------------------------------------------

//#include <Point.h>
//#include <Shape.h>
#include <functional>
#include <stdexcept>

class Circle : public Shape
{
 public:
   using DrawStrategy = std::function<void(Circle const&)>;

   explicit Circle( double radius, DrawStrategy drawer )
      : radius_( radius )
      , center_()
      , drawer_( std::move(drawer) )
   {
      if( !drawer_ ) {
         throw std::invalid_argument( "Invalid draw strategy" );
      }
   }

   void draw() const override { drawer_(*this); }

   double radius() const { return radius_; }
   Point  center() const { return center_; }

 private:
   double radius_;
   Point center_;
   DrawStrategy drawer_;
};


//---- <Square.h> ---------------------------------------------------------------------------------

//#include <Point.h>
//#include <Shape.h>
#include <functional>
#include <stdexcept>

class Square : public Shape
{
 public:
   using DrawStrategy = std::function<void(Square const&)>;

   explicit Square( double side, DrawStrategy drawer )
      : side_( side )
      , center_()
      , drawer_( std::move(drawer) )
   {
      if( !drawer_ ) {
         throw std::invalid_argument( "Invalid draw strategy" );
      }
   }

   void draw() const override { drawer_(*this); }

   double side() const { return side_; }
   Point center() const { return center_; }

 private:
   double side_;
   Point center_;
   DrawStrategy drawer_;
};


//---- <TestDrawStrategy.h> -----------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <GraphicsLibrary.h>
#include <iostream>

class TestDrawStrategy
{
 public:
   explicit TestDrawStrategy( Color color ) : color_(color) {}

   void operator()( Circle const& circle ) const
   {
      std::cout << "circle: radius=" << circle.radius()
                << ", color = " << to_string(color_) << '\n';
   }

   void operator()( Square const& square ) const
   {
      std::cout << "square: side=" << square.side()
                << ", color = " << to_string(color_) << '\n';
   }

 private:
   Color color_;
};


//---- <ShapeConcept.h> ---------------------------------------------------------------------------

// TODO: Create an external hierarchy for shapes that represents the polymorphic behavior
//       of shapes.

class ShapeConcept
{};


//---- <Shapes.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
#include <memory>
#include <vector>

using Shapes = std::vector< std::unique_ptr<Shape> >;


//---- <DrawAllShapes.h> --------------------------------------------------------------------------

//#include <Shapes.h>

void drawAllShapes( Shapes const& shapes );


//---- <DrawAllShapes.cpp> ------------------------------------------------------------------------

//#include <DrawAllShapes.h>

void drawAllShapes( Shapes const& shapes )
{
   for( auto const& shape : shapes )
   {
      shape->draw();
   }
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <Shapes.h>
//#include <DrawAllShapes.h>
//#include <TestDrawStrategy.h>
#include <cstdlib>

int main()
{
   Shapes shapes{};

   shapes.emplace_back( std::make_unique<Circle>( 2.3, TestDrawStrategy(Color::red) ) );
   shapes.emplace_back( std::make_unique<Square>( 1.2, TestDrawStrategy(Color::green) ) );
   shapes.emplace_back( std::make_unique<Circle>( 4.1, TestDrawStrategy(Color::blue) ) );

   drawAllShapes( shapes );

   return EXIT_SUCCESS;
}

