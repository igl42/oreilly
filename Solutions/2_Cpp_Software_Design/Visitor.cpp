/**************************************************************************************************
*
* \file Visitor.cpp
* \brief C++ Training - Programming Task for the Visitor Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Implement the 'area()' operations as a classic visitor. Hint: the area of a circle
*         is 'radius*radius*M_PI', the area of a square is 'side*side'.
*
* Step 2: Refactor the classic Visitor solution by a value semantics based solution. Note that
*         the general behavior should remain unchanged.
*
* Step 3: Switch from one to another graphics library. Discuss the feasibility of the change:
*         how easy is the change? How many pieces of code on which level of the architecture
*         have to be touched?
*
* Step 4: Discuss the advantages of the value semantics based solution in comparison to the
*         classic solution.
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


//---- <Circle.h> ---------------------------------------------------------------------------------

//#include <Point.h>

class Circle
{
 public:
   explicit Circle( double radius )
      : radius_( radius )
      , center_()
   {}

   double radius() const { return radius_; }
   Point  center() const { return center_; }

 private:
   double radius_;
   Point center_;
};


//---- <Square.h> ---------------------------------------------------------------------------------

//#include <Point.h>

class Square
{
 public:
   explicit Square( double side )
      : side_( side )
      , center_()
   {}

   double side() const { return side_; }
   Point center() const { return center_; }

 private:
   double side_;
   Point center_;
};


//---- <GLDraw.h> ---------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <GraphicsLibrary.h>
#include <iostream>

class GLDraw
{
 public:
   explicit GLDraw( gl::Color color ) : color_(color) {}

   void operator()( Circle const& circle ) const
   {
      std::cout << "circle: radius=" << circle.radius()
                << ", color = " << gl::to_string(color_) << '\n';
   }

   void operator()( Square const& square ) const
   {
      std::cout << "square: side=" << square.side()
                << ", color = " << gl::to_string(color_) << '\n';
   }

 private:
   gl::Color color_;
};


//---- <Area.h> -----------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
#define _USE_MATH_DEFINES
#include <cmath>

class Area
{
 public:
   double operator()( Circle const& circle ) const
   {
      return circle.radius() * circle.radius() * M_PI;
   }

   double operator()( Square const& square ) const
   {
      return square.side() * square.side();
   }
};


//---- <Shape.h> ----------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
#include <variant>

using Shape = std::variant<Circle,Square>;


//---- <Shapes.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
#include <vector>

using Shapes = std::vector<Shape>;


//---- <DrawAllShapes.h> --------------------------------------------------------------------------

//#include <Shapes.h>

void drawAllShapes( Shapes const& shapes );


//---- <DrawAllShapes.cpp> ------------------------------------------------------------------------

//#include <DrawAllShapes.h>
//#include <GLDraw.h>

void drawAllShapes( Shapes const& shapes )
{
   for( auto const& shape : shapes )
   {
      std::visit( GLDraw{gl::Color::red}, shape );
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

   shapes.emplace_back( Circle{ 2.3 } );
   shapes.emplace_back( Square{ 1.2 } );
   shapes.emplace_back( Circle{ 4.1 } );

   drawAllShapes( shapes );

   return EXIT_SUCCESS;
}

