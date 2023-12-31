/**************************************************************************************************
*
* \file Strategy.cpp
* \brief C++ Training - Programming Task for the Strategy Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Refactor the classic Strategy solution by a value semantics based solution. Note that
*         the general behavior should remain unchanged.
*
* Step 2: Switch from one to another graphics library. Discuss the feasibility of the change:
*         how easy is the change? How many pieces of code on which level of the architecture
*         have to be touched?
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


//---- <GraphicsFramework.h> (external) -----------------------------------------------------------

#include <string>
// ... and many more graphics-related headers

namespace gf {

enum class Color
{
   yellow  = 0xFFFF00,
   cyan    = 0x00FFFF,
   magenta = 0xFF00FF
};

std::string to_string( Color color )
{
   switch( color ) {
      case Color::yellow:
         return "yellow (0xFFFF00)";
      case Color::cyan:
         return "cyan (0x00FFFF)";
      case Color::magenta:
         return "magenta (0xFF00FF)";
      default:
         return "unknown";
   }
}

} // namespace gf


//---- <Point.h> ----------------------------------------------------------------------------------

struct Point
{
   double x;
   double y;
};


//---- <DrawStrategy.h> ---------------------------------------------------------------------------

class Circle;
class Square;

class DrawStrategy
{
 public:
   virtual ~DrawStrategy() = default;

   virtual void draw( Circle const& circle ) const = 0;
   virtual void draw( Square const& square ) const = 0;
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
//#include <DrawStrategy.h>
#include <memory>
#include <stdexcept>

class Circle : public Shape
{
 public:
   Circle( double radius, std::unique_ptr<DrawStrategy>&& drawer )
      : radius_( radius )
      , center_()
      , drawer_( std::move(drawer) )
   {
      if( !drawer_ ) {
         throw std::invalid_argument( "Invalid draw strategy" );
      }
   }

   void draw() const override { drawer_->draw(*this); }

   double radius() const { return radius_; }
   Point  center() const { return center_; }

 private:
   double radius_;
   Point center_;
   std::unique_ptr<DrawStrategy> drawer_;
};


//---- <Square.h> ---------------------------------------------------------------------------------

//#include <Point.h>
//#include <Shape.h>
//#include <DrawStrategy.h>
#include <memory>
#include <stdexcept>

class Square : public Shape
{
 public:
   Square( double side, std::unique_ptr<DrawStrategy>&& drawer )
      : side_( side )
      , center_()
      , drawer_( std::move(drawer) )
   {
      if( !drawer_ ) {
         throw std::invalid_argument( "Invalid draw strategy" );
      }
   }

   void draw() const override { drawer_->draw(*this); }

   double side() const { return side_; }
   Point  center() const { return center_; }

 private:
   double side_;
   Point center_;
   std::unique_ptr<DrawStrategy> drawer_;
};


//---- <GLDrawStrategy.h> -------------------------------------------------------------------------

//#include <DrawStrategy.h>
//#include <Circle.h>
//#include <Square.h>
//#include <GraphicsLibrary.h>
#include <iostream>

class GLDrawStrategy : public DrawStrategy
{
 public:
   explicit GLDrawStrategy( gl::Color color ) : color_(color) {}

   void draw( Circle const& circle ) const override
   {
      std::cout << "circle: radius=" << circle.radius()
                << ", color = " << to_string(color_) << '\n';
   }

   void draw( Square const& square ) const override
   {
      std::cout << "square: side=" << square.side()
                << ", color = " << to_string(color_) << '\n';
   }

 private:
   gl::Color color_;
};


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
//#include <GLDrawStrategy.h>
#include <cstdlib>

int main()
{
   Shapes shapes{};

   shapes.emplace_back(
      std::make_unique<Circle>( 2.3, std::make_unique<GLDrawStrategy>(gl::Color::red) ) );
   shapes.emplace_back(
      std::make_unique<Square>( 1.2, std::make_unique<GLDrawStrategy>(gl::Color::green) ) );
   shapes.emplace_back(
      std::make_unique<Circle>( 4.1, std::make_unique<GLDrawStrategy>(gl::Color::blue) ) );

   drawAllShapes( shapes );

   return EXIT_SUCCESS;
}

