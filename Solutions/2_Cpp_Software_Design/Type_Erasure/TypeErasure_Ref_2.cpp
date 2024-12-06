/**************************************************************************************************
*
* \file TypeErasure_Ref_2.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'ShapeView' class, representing a reference to a constant shape, by
*       means of Type Erasure. 'ShapeView' may require all types to provide a 'free_draw()'
*       function that draws them to the screen.
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


//---- <DrawSquare.cpp> ---------------------------------------------------------------------------

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

#include <array>
#include <cstddef>
#include <memory>
#include <type_traits>

// Pre-C++20 constraint to formulate the requirement that every shape needs a 'free_draw()' function
/*
template< typename ShapeT, typename = void >
struct is_drawable
   : public std::false_type
{};

template< typename ShapeT >
struct is_drawable< ShapeT, std::void_t< decltype( free_draw( std::declval<ShapeT>() ) ) > >
   : public std::true_type
{};

template< typename ShapeT >
constexpr bool is_drawable_v = is_drawable<ShapeT>::value;

template< typename ShapeT >
using enable_if_is_drawable =
   std::enable_if_t< is_drawable_v<ShapeT>, bool >;
*/

// C++20 concept to formulate the requirement that every shape needs a 'free_draw()' function
/*
template< typename ShapeT >
concept Drawable = requires ( ShapeT shape ) { free_draw( shape ); };
*/

namespace detail {

class Concept
{
 public:
   virtual ~Concept() = default;
   virtual void do_draw() const = 0;
   virtual std::unique_ptr<Concept> clone() const = 0;
   virtual void clone( Concept* memory ) const = 0;
};

template< typename ShapeT >
class NonOwningModel;

template< typename ShapeT >
class OwningModel final : public Concept
{
 public:
   explicit OwningModel( const ShapeT& shape ) : shape_{ shape } {}

   void do_draw() const final { free_draw( shape_ ); }
   std::unique_ptr<Concept> clone() const final { return std::make_unique<OwningModel>(*this); }
   void clone( Concept* memory ) const final { new (memory) NonOwningModel<const ShapeT>( shape_ ); }

 private:
   ShapeT shape_;
};

template< typename ShapeT >
class NonOwningModel final : public Concept
{
 public:
   NonOwningModel( ShapeT& shape ) : shape_{ std::addressof(shape) } {}

   void do_draw() const final { free_draw( *shape_ ); }
   std::unique_ptr<Concept> clone() const final { return std::make_unique<OwningModel<ShapeT>>( *shape_ ); }
   void clone( Concept* memory ) const final { new (memory) NonOwningModel(*this); }

 private:
   ShapeT* shape_{ nullptr };
};

}  // namespace detail


class Shape;


class ShapeView
{
 public:
   template< typename ShapeT >
   ShapeView( ShapeT& shape )  // Type S is possibly cv qualified; lvalue
                               // reference prevents shape references to rvalues
   {
      using Model = detail::NonOwningModel<ShapeT>;
      static_assert( sizeof( Model ) == modelSize, "Invalid model size detected" );
      new (pimpl()) Model( shape );
   }

   ShapeView( ShapeView const& other ) { other.pimpl()->clone( pimpl() ); }
   ShapeView( Shape& other );
   ShapeView( const Shape& other );

   ~ShapeView() { pimpl()->~Concept(); }

   ShapeView& operator=( ShapeView const& other )
   {
      ShapeView copy( other );
      raw_.swap( copy.raw_ );
      return *this;
   }

 private:
   friend void free_draw( ShapeView const& shaperef )
   {
      shaperef.pimpl()->do_draw();
   }

   using Concept = detail::Concept;

   Concept*       pimpl()       { return reinterpret_cast<Concept*>( raw_.data() ); }
   Concept const* pimpl() const { return reinterpret_cast<Concept const*>( raw_.data() ); }

   // Expected size of a model instantiation: sizeof(S*) + sizeof(vptr)
   static constexpr size_t modelSize = 2UL*sizeof(void*);

   alignas(void*) std::array<std::byte,modelSize> raw_;

   friend class Shape;
};


class Shape
{
 public:
   template< typename ShapeT >
   Shape( ShapeT const& shape ) : pimpl_{ std::make_unique<detail::OwningModel<ShapeT>>( shape ) } {}

   Shape( Shape const& other )
      : pimpl_{ other.pimpl_->clone() }
   {}

   Shape( ShapeView const& other )
      : pimpl_{ other.pimpl()->clone() }
   {}

   Shape& operator=( const Shape& other )
   {
      Shape tmp( other );
      std::swap( pimpl_, tmp.pimpl_ );
      return *this;
   }

   ~Shape() = default;
   Shape( Shape&& ) = default;
   Shape& operator=( Shape&& ) = default;

 private:
   friend void free_draw( Shape const& shape )
   {
      shape.pimpl_->do_draw();
   }

   using Concept = detail::Concept;

   std::unique_ptr<Concept> pimpl_;

   friend class ShapeView;
};


ShapeView::ShapeView( Shape& other )
{
   other.pimpl_->clone( pimpl() );
}

ShapeView::ShapeView( const Shape& other )
{
   other.pimpl_->clone( pimpl() );
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <Circle.h>
//#include <Square.h>
//#include <Shapes.h>
//#include <DrawAllShapes.h>
#include <cstdlib>

void performAction( ShapeView shape )
{
   free_draw( shape );
}

int main()
{
   // Create a circle as one representative of a concrete shape type
   Circle circle{ 3.14 };

   // Create a square as a second representative of a concrete shape type
   Square square{ 2.71 };

   // Drawing the two concrete shapes
   free_draw( circle );
   free_draw( square );

   // Drawing the two shapes via abstraction
   performAction( circle );
   performAction( square );

   // Combine the shape and the drawing strategy in a 'Shape' abstraction
   Shape shape1( circle );

   // Draw the shape
   free_draw( shape1 );

   // Create a reference to the shape
   ShapeView shaperef( shape1 );

   // Draw via the shape reference, resulting in the same output
   free_draw( shaperef );

   // Create a copy of the shape via the shape reference
   Shape shape2( shaperef );

   // Drawing the copy will again result in the same output
   free_draw( shape2 );

   return EXIT_SUCCESS;
}

