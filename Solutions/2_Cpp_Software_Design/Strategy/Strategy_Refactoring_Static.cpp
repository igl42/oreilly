/**************************************************************************************************
*
* \file Strategy_Refactoring_Static.cpp
* \brief C++ Training - Programming Task for the Strategy Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Refactor the classic runtime polymorphic Strategy solution by a compile-time
*         polymorphic solution based on templates. Note that the general behavior should
*         remain unchanged.
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

#include <sstream>
#include <string>
// ... and many more graphics-related headers

namespace gf {

enum class Color : int
{
   yellow  = 0xFFFF00,
   cyan    = 0x00FFFF,
   magenta = 0xFF00FF
};

using Brightness = unsigned int;

std::string print_string( Color color, Brightness brightness )
{
   std::ostringstream oss;

   switch( color ) {
      case Color::yellow:
         oss << "yellow (0xFFFF00)";
         break;
      case Color::cyan:
         oss << "cyan (0x00FFFF)";
         break;
      case Color::magenta:
         oss << "magenta (0xFF00FF)";
         break;
      default:
         oss << "unknown";
         break;
   }

   oss << ", brightness=" << brightness;

   return oss.str();
}

} // namespace gf


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
#include <memory>
#include <stdexcept>

template< typename DrawStrategy >
class Circle : public Shape
{
 public:
   Circle( double radius, DrawStrategy drawer )
      : radius_{ radius }
      , center_{}
      , drawer_{ std::move(drawer) }
   {}

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
#include <memory>
#include <stdexcept>

template< typename DrawStrategy >
class Square : public Shape
{
 public:
   Square( double side, DrawStrategy drawer )
      : side_{ side }
      , center_{}
      , drawer_{ std::move(drawer) }
   {}

   void draw() const override { drawer_(*this); }

   double side() const { return side_; }
   Point  center() const { return center_; }

 private:
   double side_;
   Point center_;
   DrawStrategy drawer_;
};


//---- <GLDrawStrategy.h> -------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <GraphicsLibrary.h>
#include <iostream>

class GLDrawStrategy
{
 public:
   explicit GLDrawStrategy( gl::Color color ) : color_{color} {}

   void operator()( Circle<GLDrawStrategy> const& circle ) const
   {
      std::cout << "circle: radius=" << circle.radius()
                << ", color = " << gl::to_string(color_) << '\n';
   }

   void operator()( Square<GLDrawStrategy> const& square ) const
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
      std::make_unique<Circle<GLDrawStrategy>>( 2.3, GLDrawStrategy(gl::Color::red) ) );
   shapes.emplace_back(
      std::make_unique<Square<GLDrawStrategy>>( 1.2, GLDrawStrategy(gl::Color::green) ) );
   shapes.emplace_back(
      std::make_unique<Circle<GLDrawStrategy>>( 4.1, GLDrawStrategy(gl::Color::blue) ) );

   drawAllShapes( shapes );

   return EXIT_SUCCESS;
}

