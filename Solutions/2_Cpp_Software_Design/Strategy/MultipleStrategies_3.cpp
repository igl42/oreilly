/**************************************************************************************************
*
* \file MultipleStrategies_3.cpp
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


//---- <JSONLibrary.h> (external) -----------------------------------------------------------------

#include <iostream>
#include <string>
// ... and many more JSON-related headers

namespace jl {

class JSONWriter
{
 public:
   void start_element( std::string const& element_name ) const
   {
      std::cout << element_name << " {\n";
   }

   template< typename Value >
   void add_key( std::string const& key, Value const& value ) const
   {
      std::cout << "   " << key << ": " << value << "\n";
   }

   void end_element() const
   {
      std::cout << "}\n";
   }
};

} // namespace jl


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

template< typename DrawStrategy, typename PrintStrategy >
class Circle : public Shape
{
 public:
   explicit Circle( double radius, DrawStrategy drawer, PrintStrategy printer )
      : radius_{ radius }
      , center_{}
      , drawer_{ std::move(drawer) }
      , printer_{ std::move(printer) }
   {}

   double radius() const noexcept { return radius_; }
   Point  center() const noexcept { return center_; }

   void draw() const override { drawer_(*this); }
   void print() const override { printer_(*this); }

 private:
   double radius_;
   Point center_{};
   DrawStrategy drawer_;
   PrintStrategy printer_;
};


//---- <Square.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
//#include <Point.h>

template< typename DrawStrategy, typename PrintStrategy >
class Square : public Shape
{
 public:
   explicit Square( double side, DrawStrategy drawer, PrintStrategy printer )
      : side_{ side }
      , center_{}
      , drawer_{ std::move(drawer) }
      , printer_{ std::move(printer) }
   {}

   double side  () const noexcept { return side_; }
   Point  center() const noexcept { return center_; }

   void draw() const override { drawer_(*this); }
   void print() const override { printer_(*this); }

 private:
   double side_;
   Point center_{};
   DrawStrategy drawer_;
   PrintStrategy printer_;
};


//---- <Shapes.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
#include <memory>
#include <vector>

using Shapes = std::vector<std::unique_ptr<Shape>>;


//==== ARCHITECTURAL BOUNDARY =====================================================================


//---- <GLDrawStrategy.h> -------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <GraphicsLibrary.h>
#include <iostream>

class GLDrawStrategy
{
 public:
   explicit GLDrawStrategy( gl::Color color ) : color_{color} {}

   template< typename DrawStrategy, typename PrintStrategy >
   void operator()( Circle<DrawStrategy,PrintStrategy> const& circle ) const
   {
      std::cout << "circle: radius=" << circle.radius()
                << ", color = " << gl::to_string(color_) << '\n';
   }

   template< typename DrawStrategy, typename PrintStrategy >
   void operator()( Square<DrawStrategy,PrintStrategy> const& square ) const
   {
      std::cout << "square: side=" << square.side()
                << ", color = " << gl::to_string(color_) << '\n';
   }

 private:
   gl::Color color_{};
};


//---- <JLPrintStrategy.h> ------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <JSONLibrary.h>

class JLPrintStrategy
{
 public:
   template< typename DrawStrategy, typename PrintStrategy >
   void operator()( Circle<DrawStrategy,PrintStrategy> const& circle ) const
   {
      json_.start_element( "circle" );
      json_.add_key( "radius", circle.radius() );
      json_.end_element();
   }

   template< typename DrawStrategy, typename PrintStrategy >
   void operator()( Square<DrawStrategy,PrintStrategy> const& square ) const
   {
      json_.start_element( "square" );
      json_.add_key( "side", square.side() );
      json_.end_element();
   }

 private:
   jl::JSONWriter json_;
};


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <Shapes.h>
//#include <GLDrawStrategy.h>
//#include <JLPrintStrategy.h>
#include <cstdlib>
#include <memory>

int main()
{
   Shapes shapes{};

   shapes.emplace_back(
      std::make_unique<Circle<GLDrawStrategy,JLPrintStrategy>>(
         2.3, GLDrawStrategy{ gl::Color::red }, JLPrintStrategy{} ) );
   shapes.emplace_back(
      std::make_unique<Square<GLDrawStrategy,JLPrintStrategy>>(
         1.2, GLDrawStrategy{ gl::Color::green }, JLPrintStrategy{} ) );
   shapes.emplace_back(
      std::make_unique<Circle<GLDrawStrategy,JLPrintStrategy>>(
         4.1, GLDrawStrategy{ gl::Color::blue }, JLPrintStrategy{} ) );

   for( auto const& shape : shapes )
   {
      shape->draw();
      shape->print();
   }

   return EXIT_SUCCESS;
}

