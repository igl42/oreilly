/**************************************************************************************************
*
* \file Procedural.cpp
* \brief C++ Training - Example for a procedural approach to draw shapes
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Evaluate the given design with respect to changeability and extensibility.
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


//---- <Shape.h> ----------------------------------------------------------------------------------

enum ShapeType
{
   circle,
   square
};

class Shape
{
 protected:
   explicit Shape( ShapeType type )
      : type_( type )
   {}

 public:
   virtual ~Shape() = default;

   ShapeType getType() const noexcept { return type_; }

 private:
   ShapeType type_;
};


//---- <Circle.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
//#include <Point.h>

class Circle : public Shape
{
 public:
   explicit Circle( double radius );

   double radius() const noexcept { return radius_; }
   Point  center() const noexcept { return center_; }

 private:
   double radius_;
   Point center_{};
};


//---- <Circle.cpp> -------------------------------------------------------------------------------

//#include <Circle.h>

Circle::Circle( double radius )
   : Shape( circle )
   , radius_( radius )
   , center_()
{}


//---- <Square.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
//#include <Point.h>

class Square : public Shape
{
 public:
   explicit Square( double side );

   double side  () const noexcept { return side_; }
   Point  center() const noexcept { return center_; }

 private:
   double side_;
   Point center_{};
};


//---- <Square.cpp> -------------------------------------------------------------------------------

//#include <Square.h>

Square::Square( double side )
   : Shape( square )
   , side_( side )
   , center_()
{}


//---- <Draw.h> -----------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <GraphicsLibrary.h>

void draw( Circle const& circle, gl::Color color );
void draw( Square const& square, gl::Color color );


//---- <Draw.cpp> ---------------------------------------------------------------------------------

//#include <Draw.h>
#include <iostream>

void draw( Circle const& circle, gl::Color color )
{
   std::cout << "circle: radius=" << circle.radius()
             << ", color = " << to_string(color) << '\n';
}

void draw( Square const& square, gl::Color color )
{
   std::cout << "square: side=" << square.side()
             << ", color = " << to_string(color) << '\n';
}


//---- <DrawAllShapes.h> --------------------------------------------------------------------------

//#include <Shape.h>
#include <memory>
#include <vector>

void drawAllShapes( std::vector<std::unique_ptr<Shape>> const& shapes );


//---- <DrawAllShapes.cpp> ------------------------------------------------------------------------

//#include <DrawAllShapes.h>
//#include <Circle.h>
//#include <Square.h>
//#include <Draw.h>

void drawAllShapes( std::vector<std::unique_ptr<Shape>> const& shapes )
{
   for( auto const& shape : shapes )
   {
      switch( shape->getType() )
      {
         case circle:
            draw( *static_cast<Circle const*>( shape.get() ), gl::Color::red );
            break;
         case square:
            draw( *static_cast<Square const*>( shape.get() ), gl::Color::green );
            break;
      }
   }
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <DrawAllShapes.h>
#include <cstdlib>
#include <memory>
#include <vector>

int main()
{
   using Shapes = std::vector<std::unique_ptr<Shape>>;

   // Creating some shapes
   Shapes shapes{};
   shapes.emplace_back( std::make_unique<Circle>( 2.3 ) );
   shapes.emplace_back( std::make_unique<Square>( 1.2 ) );
   shapes.emplace_back( std::make_unique<Circle>( 4.1 ) );

   // Drawing all shapes
   drawAllShapes( shapes );

   return EXIT_SUCCESS;
}

