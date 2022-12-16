/**************************************************************************************************
*
* \file TypeErasure_Ref_1.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'ShapeConstRef' class, representing a reference to a constant shape, by
*       means of Type Erasure. 'ShapeConstRef' may require all types to provide a free 'draw()'
*       function that draws them to the screen.
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

#include <cstddef>
#include <memory>
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
                  draw( *model );
               } )
      , clone_( []( void const* c ) -> void* {
                   auto const* model = static_cast<ShapeT const*>(c);
                   return new ShapeT( *model );
                } )
      , pimpl_( new ShapeT( shape )
              , []( void* c ){
                   auto* model = static_cast<ShapeT*>(c);
                   delete model;
                } )
   {}

   Shape( Shape const& other )
      : draw_ ( other.draw_ )
      , clone_( other.clone_ )
      , pimpl_( clone_( other.pimpl_.get() ), other.pimpl_.get_deleter() )
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
   friend class ShapeConstRef;

   friend void draw( Shape const& shape )
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


class ShapeConstRef
{
 public:
   template< typename ShapeT >
   ShapeConstRef( ShapeT& shape )  // Type ShapeT is possibly cv qualified; lvalue
                                   // reference prevents shape references to rvalues
      : shape_{ std::addressof(shape) }
      , draw_{ []( void const* shape ){
                  draw( *static_cast<ShapeT const*>(shape) );
               } }
   {}

   ShapeConstRef( Shape& shape )  // lvalue reference prevents shape references to rvalues
      : shape_{ shape.pimpl_.get() }
      , draw_{ shape.draw_ }
   {}

 private:
   friend void draw( ShapeConstRef const& shape )
   {
      shape.draw_( shape.shape_ );
   }

   using DrawOperation = void(void const*);

   void const* shape_{ nullptr };
   DrawOperation* draw_{ nullptr };
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


//---- <Draw.h> -----------------------------------------------------------------------------------

class Circle;
class Square;

void draw( Circle const& circle );
void draw( Square const& square );


//---- <Draw.cpp> ---------------------------------------------------------------------------------

//#include <Draw.h>
//#include <Circle.h>
//#include <Square.h>
#include <iostream>

void draw( Circle const& circle )
{
   std::cout << "circle: radius=" << circle.radius() << std::endl;
}

void draw( Square const& square )
{
   std::cout << "square: side=" << square.side() << std::endl;
}


//---- <Shapes.h> ---------------------------------------------------------------------------------

#include <vector>

using ShapeConstRefs = std::vector<ShapeConstRef>;


//---- <DrawAllShapes.h> --------------------------------------------------------------------------

//#include <Shapes.h>

void drawAllShapes( ShapeConstRefs const& shapes );


//---- <DrawAllShapes.cpp> ------------------------------------------------------------------------

//#include <DrawAllShapes.h>
//#include <Draw.h>

void drawAllShapes( ShapeConstRefs const& shapes )
{
   for( auto const& shape : shapes )
   {
      draw( shape );
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
   // Create a circle as one representative of a concrete shape type
   Circle circle{ 3.14 };

   // Combine the shape and the drawing strategy in a 'Shape' abstraction
   Shape shape1( circle );

   // Draw the shape
   draw( shape1 );

   // Create a reference to the shape
   ShapeConstRef shaperef( shape1 );

   // Draw via the shape reference, resulting in the same output
   draw( shaperef );

   // Put a shape reference into a shape
   // This will create a copy of the ShapeConstRef instance, thus
   // the 'Shape' instance will act as a reference, too.
   Shape shape2( shaperef );

   // Drawing the copy will again result in the same output
   draw( shape2 );

   return EXIT_SUCCESS;
}

