/**************************************************************************************************
*
* \file TypeErasure_MVF.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'Shape' class by means of Type Erasure. Avoid the use of virtual functions,
*       but implement them by manually means of class-internal function pointers. 'Shape' may
*       require all types to provide a 'free_draw()' function that draws them to the screen.
*
**************************************************************************************************/

#include <cstdlib>
#include <iostream>
#include <memory>
#include <utility>
#include <type_traits>
#include <vector>


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


//---- <Draw.cpp> ---------------------------------------------------------------------------------

//#include <Draw.h>
//#include <Circle.h>
//#include <Square.h>
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

// Pre-C++20 constraint to formulate the requirement that every shape needs a 'free_draw()' function
/*
template< typename T, typename = void >
struct is_drawable
   : public std::false_type
{};

template< typename T >
struct is_drawable< T, std::void_t< decltype( free_draw( std::declval<T>() ) ) > >
   : public std::true_type
{};

template< typename T >
constexpr bool is_drawable_v = is_drawable<T>::value;

template< typename T >
using enable_if_is_drawable =
   std::enable_if_t< is_drawable_v<T>, bool >;
*/

// C++20 concept to formulate the requirement that every shape needs a 'free_draw()' function
/*
template<typename T>
concept Drawable = requires ( T shape ) { free_draw( shape ); };
*/


class Shape
{
 public:
   template< typename ShapeT >
   Shape( ShapeT const& shape )
      : draw_{ []( void const* c ){
                  auto const* model = static_cast<ShapeT const*>(c);
                  free_draw( *model );
               } }
      , clone_{ []( void const* c ) -> void* {
                   auto const* model = static_cast<ShapeT const*>(c);
                   return new ShapeT( *model );
                } }
      , pimpl_{ new ShapeT( shape )
              , []( void* c ){
                   auto* model = static_cast<ShapeT*>(c);
                   delete model;
                } }
   {}

   Shape( Shape const& other )
      : draw_ { other.draw_ }
      , clone_{ other.clone_ }
      , pimpl_{ clone_( other.pimpl_.get() ), other.pimpl_.get_deleter() }
   {}

   Shape& operator=( const Shape& other )
   {
      Shape tmp( other );
      swap( tmp );
      return *this;
   }

   ~Shape() = default;
   Shape( Shape&& ) = default;
   Shape& operator=( Shape&& ) = default;

   void swap( Shape& s )
   {
      std::swap( draw_, s.draw_ );
      std::swap( clone_, s.clone_ );
      std::swap( pimpl_, s.pimpl_ );
   }

 private:
   friend void free_draw( Shape const& shape )
   {
      shape.draw_( shape.pimpl_.get() );
   }

   using DrawOperation    = void(void const*);
   using CloneOperation   = void*(void const*);
   using DestroyOperation = void(void*);

   DrawOperation*  draw_ { nullptr };
   CloneOperation* clone_{ nullptr };
   std::unique_ptr<void,DestroyOperation*> pimpl_;
};

void swap( Shape& lhs, Shape& rhs )
{
   lhs.swap( rhs );
}


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

