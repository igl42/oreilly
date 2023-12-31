/**************************************************************************************************
*
* \file DataOriented.cpp
* \brief C++ Training - Example for a data-oriented approach to draw shapes
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


//---- <Circle.h> ---------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Point.h>

class Circle
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
   : radius_( radius )
   , center_()
{}


//---- <Square.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
//#include <Point.h>

class Square
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
   : side_( side )
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


//---- <Shapes.h> ---------------------------------------------------------------------------------

#include <tuple>
#include <vector>

template< typename... ShapeTypes >
class Shapes
{
 public:
   Shapes() = default;

   template< typename ShapeType >
   void add( ShapeType shape )
   {
      std::get< std::vector<ShapeType> >( shapes_ ).push_back( std::move(shape) );
   }

   template< typename ShapeType >
   std::vector<ShapeType> const& get() const
   {
      return std::get< std::vector<ShapeType> >( shapes_ );
   }

 private:
   std::tuple< std::vector<ShapeTypes>... > shapes_;
};


//---- <DrawAllShapes.h> --------------------------------------------------------------------------

//#include <Shape.h>
#include <memory>
#include <vector>

template< typename ShapeType >
void drawAllShapes( std::vector<ShapeType> const& shapes );

template< typename... ShapeTypes >
void drawAllShapes( Shapes<ShapeTypes...> const& shapes );


//---- <DrawAllShapes.cpp> ------------------------------------------------------------------------

//#include <DrawAllShapes.h>

template< typename ShapeType >
void drawAllShapes( std::vector<ShapeType> const& shapes )
{
   for( auto const& shape : shapes ) {
      draw( shape, gl::Color::red );
   }
}

template< typename... ShapeTypes >
void drawAllShapes( Shapes<ShapeTypes...> const& shapes )
{
   ( drawAllShapes( shapes.template get<ShapeTypes>() ), ... );
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
   // Creating some shapes
   Shapes<Circle,Square> shapes{};
   shapes.add( Circle{ 2.3 } );
   shapes.add( Square{ 1.2 } );
   shapes.add( Circle{ 4.1 } );

   // Drawing all shapes
   drawAllShapes( shapes );

   return EXIT_SUCCESS;
}

