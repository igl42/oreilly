/**************************************************************************************************
*
* \file MultipleStrategies.cpp
* \brief C++ Training - Programming Task for the Strategy Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Consider the following shape classes with 'draw()' and 'print()' functions. How would
*         you externalize the implementation details for both functions? Think about solutions
*         for both dynamic and static polymorphism and discuss pros and cons.
*
* Step 2: Think about adding a new types (e.g. 'Rectangle', different implementations of either
*         the 'draw()' or 'print()' functions). How much effort would this be? How many places
*         would have to be touched and how would this relate to the OCP?
*
* Step 3: Think about adding a new operation (e.g. serialize(), ...). How much effort would
*         this be? How many places would have to be touched and how would this relate to the OCP?
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

class Shape
{
 public:
   virtual ~Shape() = default;

   virtual void draw() const = 0;   // To draw the shape on the screen
   virtual void print() const = 0;  // To print the shape in different formats (JSON, XML, ...)
};


//---- <Circle.h> ---------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Point.h>
//#include <GraphicsLibrary.h>

class Circle : public Shape
{
 public:
   explicit Circle( double radius, gl::Color color );

   double radius() const noexcept { return radius_; }
   Point  center() const noexcept { return center_; }

   void draw() const override;
   void print() const override;

 private:
   double radius_;
   Point center_{};
   gl::Color color_{};
};


//---- <Circle.cpp> -------------------------------------------------------------------------------

//#include <Circle.h>
#include <iostream>

Circle::Circle( double radius, gl::Color color )
   : radius_{ radius }
   , center_{}
   , color_{ color }
{}

void Circle::draw() const
{
   std::cout << "circle: radius=" << radius_
             << ", color = " << gl::to_string(color_) << '\n';
}

void Circle::print() const
{
   std::cout << "circle {\n"
                "   radius: " << radius_ << "\n"
                "}\n";
}


//---- <Square.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
//#include <Point.h>
//#include <GraphicsLibrary.h>

class Square : public Shape
{
 public:
   explicit Square( double side, gl::Color color );

   double side  () const noexcept { return side_; }
   Point  center() const noexcept { return center_; }

   void draw() const override;
   void print() const override;

 private:
   double side_;
   Point center_{};
   gl::Color color_{};
};


//---- <Square.cpp> -------------------------------------------------------------------------------

//#include <Square.h>
#include <iostream>

Square::Square( double side, gl::Color color )
   : side_{ side }
   , center_{}
   , color_{ color }
{}

void Square::draw() const
{
   std::cout << "square: side=" << side_
             << ", color = " << gl::to_string(color_) << '\n';
}

void Square::print() const
{
   std::cout << "square {\n"
                "   side: " << side_ << "\n"
                "}\n";
}


//---- <Shapes.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
#include <memory>
#include <vector>

using Shapes = std::vector<std::unique_ptr<Shape>>;


//==== ARCHITECTURAL BOUNDARY =====================================================================


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <Shapes.h>
//#include <DrawAllShapes.h>
#include <cstdlib>
#include <memory>

int main()
{
   Shapes shapes{};

   shapes.emplace_back( std::make_unique<Circle>( 2.3, gl::Color::red ) );
   shapes.emplace_back( std::make_unique<Square>( 1.2, gl::Color::green ) );
   shapes.emplace_back( std::make_unique<Circle>( 4.1, gl::Color::blue ) );

   for( auto const& shape : shapes )
   {
      shape->draw();
      shape->print();
   }

   return EXIT_SUCCESS;
}

