/**************************************************************************************************
*
* \file ObjectOriented.cpp
* \brief C++ Training - Example for an object-oriented approach to draw shapes
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
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

//#include <Circle.h>
//#include <Point.h>
//#include <GraphicsLibrary.h>

class Circle : public Shape
{
 public:
   explicit Circle( double radius, Color color );

   double radius() const noexcept { return radius_; }
   Point  center() const noexcept { return center_; }

   void draw() const override;

 private:
   double radius_;
   Point center_{};
   Color color_;
};


//---- <Circle.cpp> -------------------------------------------------------------------------------

//#include <Circle.h>
#include <iostream>

Circle::Circle( double radius, Color color )
   : radius_( radius )
   , center_()
   , color_( color )
{}

void Circle::draw() const
{
   std::cout << "circle: radius=" << radius_
             << ", color = " << to_string(color_) << '\n';
}


//---- <Square.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
//#include <Point.h>
//#include <GraphicsLibrary.h>

class Square : public Shape
{
 public:
   explicit Square( double side, Color color );

   double side  () const noexcept { return side_; }
   Point  center() const noexcept { return center_; }

   void draw() const override;

 private:
   double side_;
   Point center_{};
   Color color_;
};


//---- <Square.cpp> -------------------------------------------------------------------------------

//#include <Square.h>
#include <iostream>

Square::Square( double side, Color color )
   : side_( side )
   , center_()
   , color_( color )
{}

void Square::draw() const
{
   std::cout << "square: side=" << side_
             << ", color = " << to_string(color_) << '\n';
}


//---- <DrawAllShapes.h> --------------------------------------------------------------------------

//#include <Shape.h>
#include <memory>
#include <vector>

void drawAllShapes( const std::vector<std::unique_ptr<Shape>>& shapes );


//---- <DrawAllShapes.cpp> ------------------------------------------------------------------------

//#include <DrawAllShapes.h>

void drawAllShapes( const std::vector<std::unique_ptr<Shape>>& shapes )
{
   for ( const auto& shape : shapes )
   {
      shape->draw();
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
   shapes.emplace_back( std::make_unique<Circle>( 2.3, Color::red ) );
   shapes.emplace_back( std::make_unique<Square>( 1.2, Color::green ) );
   shapes.emplace_back( std::make_unique<Circle>( 4.1, Color::blue ) );

   // Drawing all shapes
   drawAllShapes( shapes );

   return EXIT_SUCCESS;
}

