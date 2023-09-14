/**************************************************************************************************
*
* \file TypeErasure_SBO_MVF.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'Shape' class by means of Type Erasure. Use the 'Small Buffer Optimization
*       (SBO)' technique to avoid any dynamic allocation. Also avoid the use of virtual functions,
*       but implement them manually by means of class-internal function pointers. 'Shape' may
*       require all types to provide a 'free_draw()' function that draws them to the screen.
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
         return "blue (0xFF00FF)";
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


//---- <Shape.h> ----------------------------------------------------------------------------------

#include <array>
#include <memory>
#include <utility>
#include <type_traits>

// Pre-C++20 constraint to formulate the requirement that every shape needs a 'draw()' function
/*
template< typename T, typename = void >
struct is_drawable
   : public std::false_type
{};

template< typename T >
struct is_drawable< T, std::void_t< decltype( draw( std::declval<T>() ) ) > >
   : public std::true_type
{};

template< typename T >
constexpr bool is_drawable_v = is_drawable<T>::value;

template< typename T >
using enable_if_is_drawable =
   std::enable_if_t< is_drawable_v<T>, bool >;
*/

// C++20 concept to formulate the requirement that every shape needs a 'draw()' function
/*
template<typename T>
concept Drawable = requires ( T shape ) { draw( shape ); };
*/


class Shape
{
 public:
   template< typename ShapeT >
   Shape( ShapeT const& shape )
      : draw_( []( void const* c ){
                  auto const* model = static_cast<ShapeT const*>(c);
                  free_draw( *model );
               } )
      , clone_( []( void const* c, std::byte* raw ) {
                   auto const* model = static_cast<ShapeT const*>(c);
                   ::new (raw) ShapeT( *model );
                } )
      , destroy_( []( void* c ){
                     auto* model = static_cast<ShapeT*>(c);
                     model->~ShapeT();
                  } )
   {
      static_assert( sizeof(ShapeT) <= buffersize, "Given type is too large" );
      static_assert( alignof(ShapeT) <= alignment, "Given type is overaligned" );
      ::new (buffer_.data()) ShapeT( shape );
   }

   Shape( Shape const& other )
      : draw_   ( other.draw_ )
      , clone_  ( other.clone_ )
      , destroy_( other.destroy_ )
   {
      clone_( other.buffer_.data(), buffer_.data() );
   }

   Shape& operator=( const Shape& other )
   {
      Shape tmp( other );
      swap( tmp );
      return *this;
   }

   // Move operations intentionally ignored!

   ~Shape() { destroy_( buffer_.data() ); }

   void swap( Shape& s )
   {
      std::swap( draw_, s.draw_ );
      std::swap( clone_, s.clone_ );
      std::swap( destroy_, s.destroy_ );
      std::swap( buffer_, s.buffer_ );
   }

 private:
   friend void free_draw( Shape const& shape )
   {
      shape.draw_( shape.buffer_.data() );
   }

   using DrawOperation    = void(void const*);
   using CloneOperation   = void(void const*,std::byte*);
   using DestroyOperation = void(void*);

   DrawOperation*    draw_   { nullptr };
   CloneOperation*   clone_  { nullptr };
   DestroyOperation* destroy_{ nullptr };

   static constexpr size_t buffersize = 128UL;
   static constexpr size_t alignment  =  16UL;

   alignas(alignment) std::array<std::byte,buffersize> buffer_;
};

void swap( Shape& lhs, Shape& rhs )
{
   lhs.swap( rhs );
}


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


//---- <Draw.h> -----------------------------------------------------------------------------------

class Circle;
class Square;

void free_draw( Circle const& circle );
void free_draw( Square const& square );


//---- <Draw.cpp> ---------------------------------------------------------------------------------

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

