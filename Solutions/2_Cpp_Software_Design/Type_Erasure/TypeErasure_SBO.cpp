/**************************************************************************************************
*
* \file TypeErasure_SBO.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'Shape' class by means of Type Erasure. Use the 'Small Buffer Optimization
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


//---- <Shape.h> ----------------------------------------------------------------------------------

#include <array>
#include <cstddef>
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
   {
      using M = Model<ShapeT>;
      static_assert( sizeof(M) <= buffersize, "Given type is too large" );
      static_assert( alignof(M) <= alignment, "Given type is overaligned" );
      ::new (pimpl()) M( shape );  // Or C++20 'std::construct_at()'
   }

   template< typename ShapeT, typename DrawStrategy >
   Shape( ShapeT const& shape, DrawStrategy const& drawer )
   {
      using M = ExtendedModel<ShapeT,DrawStrategy>;
      static_assert( sizeof(M) <= buffersize, "Given type is too large" );
      static_assert( alignof(M) <= alignment, "Given type is overaligned" );
      ::new (pimpl()) M( shape, drawer );  // Or C++20 'std::construct_at()'
   }

   ~Shape() { pimpl()->~Concept(); }  // Or C++17 'std::destroy_at()'

   Shape( Shape const& other )
   {
      other.pimpl()->clone( pimpl() );
   }

   Shape& operator=( Shape const& other )
   {
      // Copy-and-swap idiom
      Shape copy( other );
      buffer.swap( copy.buffer );
      return *this;
   }

   // Move operations intentionally ignored!

 private:
   friend void free_draw( Shape const& drawable )
   {
      drawable.pimpl()->do_draw();
   }

   struct Concept
   {
      virtual ~Concept() {}
      virtual void do_draw() const = 0;
      virtual void clone( Concept* memory ) const = 0;
   };

   template< typename ShapeT >
   struct Model final : public Concept
   {
      explicit Model( ShapeT const& shape )
         : shape_{ shape }
      {}

      void do_draw() const final { free_draw( shape_ ); }
      void clone( Concept* memory ) const final { ::new (memory) Model(*this); }  // Or C++20 'std::construct_at()'

      ShapeT shape_;
   };

   template< typename ShapeT, typename DrawStrategy >
   struct ExtendedModel final : Concept
   {
      explicit ExtendedModel( ShapeT const& shape, DrawStrategy const& drawer )
         : shape_{ shape }
         , drawer_{ drawer }
      {}

      void do_draw() const final { drawer_( shape_ ); }
      void clone( Concept* memory ) const final { ::new (memory) ExtendedModel(*this); }  // Or C++20 'std::construct_at()'

      ShapeT shape_;
      DrawStrategy drawer_;
   };

   Concept*       pimpl()       noexcept { return reinterpret_cast<Concept*>( buffer.data() ); }
   const Concept* pimpl() const noexcept { return reinterpret_cast<const Concept*>( buffer.data() ); }

   static constexpr size_t buffersize = 128UL;
   static constexpr size_t alignment  =  16UL;

   alignas(alignment) std::array<std::byte,buffersize> buffer;
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

