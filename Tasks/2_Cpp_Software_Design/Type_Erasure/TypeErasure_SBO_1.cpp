/**************************************************************************************************
*
* \file TypeErasure_SBO_1.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Upgrade the given Type Erasure implementation by means of the 'Small Buffer Optimization
*       (SBO)' technique to avoid any dynamic allocation. 'Shape' may require all types to
*       provide a 'free_draw()' function that draws them to the screen.
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


//---- <Circle.h> ---------------------------------------------------------------------------------

//#include <Point.h>

class Circle
{
 public:
   explicit Circle( double radius )
      : radius_{ radius }
      , center_{}
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
      : side_{ side }
      , center_{}
   {}

   double side() const { return side_; }
   Point center() const { return center_; }

 private:
   double side_;
   Point center_;
};


//==== ARCHITECTURAL BOUNDARY =====================================================================


//---- <Draw.h> -----------------------------------------------------------------------------------

class Circle;
class Square;

void free_draw( Circle const& circle );
void free_draw( Square const& square );

struct FreeDraw
{
   template< typename T >
   void operator()( T const& shape ) const
   {
      free_draw(shape);
   }
};


//---- <Draw.cpp> ---------------------------------------------------------------------------------

//#include <Draw.h>
//#include <Circle.h>
//#include <Square.h>
//#include <GraphicsLibrary.h>
#include <iostream>

void free_draw( Circle const& circle )
{
   std::cout << "circle: radius=" << circle.radius() << std::endl;
}

void free_draw( Square const& square )
{
   std::cout << "square: side=" << square.side() << std::endl;
}


//---- <Shape.h> ----------------------------------------------------------------------------------

#include <memory>
#include <type_traits>
#include <utility>

class Shape
{
 public:
   template< typename ShapeT, typename DrawStrategy = FreeDraw >  // Strategy design pattern
   Shape( ShapeT const& shape, DrawStrategy const& drawer = {} )
      : pimpl_{ std::make_unique<Model<ShapeT,DrawStrategy>>( shape, drawer ) }
   {}

 private:
   friend void free_draw( Shape const& shape )
   {
      shape.pimpl_->do_draw();
   }

   struct Concept  // External Polymorphism design pattern
   {
      virtual ~Concept() = default;
      virtual void do_draw() const = 0;
   };

   template< typename ShapeT, typename DrawStrategy >
   struct Model final : public Concept
   {
      explicit Model( ShapeT const& shape, DrawStrategy const& drawer )
         : shape_{ shape }
         , drawer_{ drawer }
      {}

      void do_draw() const final { drawer_( shape_ ); }

      ShapeT shape_;
      DrawStrategy drawer_;
   };

   std::unique_ptr<Concept> pimpl_;  // Bridge design pattern (pimpl idiom)
};


//---- <Shapes.h> ---------------------------------------------------------------------------------

//#include <Shape.h>
#include <vector>

using Shapes = std::vector<Shape>;


//---- <DrawAllShapes.h> --------------------------------------------------------------------------

//#include <Shapes.h>

void drawAllShapes( Shapes const& shapes );


//---- <DrawAllShapes.cpp> ------------------------------------------------------------------------

//#include <DrawAllShapes.h>
//#include <Draw.h>

void drawAllShapes( Shapes const& shapes )
{
   for( auto const& shape : shapes )
   {
      free_draw( shape );
   }
}


//---- <GLDrawStrategy.h> -------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <GraphicsLibrary.h>
#include <iostream>

class GLDrawStrategy
{
 public:
   explicit GLDrawStrategy( gl::Color color ) : color_{color} {}

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
   gl::Color color_{};
};


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
   shapes.emplace_back( Square{ 1.2 }, GLDrawStrategy{gl::Color::green} );
   shapes.emplace_back( Circle{ 4.1 }, [color = gl::Color::red]( Circle const& circle ){
      std::cout << "circle: radius=" << circle.radius()
                << ", color = " << gl::to_string(color) << std::endl;
   } );

   drawAllShapes( shapes );

   return EXIT_SUCCESS;
}

