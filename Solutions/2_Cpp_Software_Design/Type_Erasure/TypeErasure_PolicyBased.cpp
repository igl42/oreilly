/**************************************************************************************************
*
* \file TypeErasure_PolicyBased.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'Shape' class by means of Type Erasure. Use Policy-based Design to let
*       users decide about the memory allocation scheme. 'Shape' may require all types to
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


//---- <DrawSquare.h> -----------------------------------------------------------------------------

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


//---- <StoragePolicies.h> ------------------------------------------------------------------------

#include <array>
#include <cstddef>
#include <utility>

struct DynamicStorage
{
   template< typename T, typename... Args >
   T* create( Args&&... args ) const
   {
      return new T( std::forward<Args>( args )... );
   }

   template< typename T >
   void destroy( T* ptr ) const noexcept
   {
      delete ptr;
   }
};

template< size_t Capacity, size_t Alignment >
struct StaticStorage
{
   template< typename T, typename... Args >
   T* create( Args&&... args ) const
   {
      static_assert( sizeof(T) <= Capacity, "The given type is too large" );
      static_assert( alignof(T) <= Alignment, "The alignment requirements of the given type are not satisfied" );
      return ::new (static_cast<void*>(buffer_.data())) T( std::forward<Args>( args )... );  // Or C++20 'std::construct_at()'
   }

   template< typename T >
   void destroy( T* ptr ) const noexcept
   {
      ptr->~T();
   }

   alignas(Alignment) std::array<std::byte,Capacity> buffer_;
};

/*
template< size_t Capacity, size_t Alignment >
struct SmallStorage
{
   template< typename T, typename... Args >
   T* create( Args&&... args ) const
   {
      if( sizeof(T) <= Capacity )
         return ::new ((void*)buffer_) T( std::forward<Args>( args )... );  // Or C++20 'std::construct_at()'
      else
         return new T( std::forward<Args>( args )... );
   }

   template< typename T >
   void destroy( T* ptr ) const noexcept
   {
      if( sizeof(T) <= Capacity )
         ptr->~T();
      else
         delete ptr;
   }

   alignas(Alignment) std::byte buffer_[Capacity];
};
*/


//---- <NoUniqueAddress.h> ------------------------------------------------------------------------

#if ( defined(__GNUC__) && __GNUC__ >= 9 ) || ( defined(__clang__) && !defined(__apple_build_version__) && __clang_major__ >= 9 )
#  define NO_UNIQUE_ADDRESS [[no_unique_address]]
#else
#  define NO_UNIQUE_ADDRESS
#endif


//---- <Shape.h> ----------------------------------------------------------------------------------

//#include <StoragePolicies.h>
#include <cstddef>
#include <type_traits>

// Pre-C++20 constraint to formulate the requirement that every shape needs a 'free_draw()' function
/*
template< typename ShapeT, typename DrawStrategy, typename = void >
struct is_drawable
   : public std::false_type
{};

template< typename ShapeT, typename DrawStrategy >
struct is_drawable< ShapeT, DrawStrategy
                  , std::void_t< decltype( std::declval<DrawStrategy>()( std::declval<ShapeT>() ) ) > >
   : public std::true_type
{};

template< typename ShapeT, typename DrawStrategy >
constexpr bool is_drawable_v = is_drawable<ShapeT,DrawStrategy>::value;

template< typename ShapeT, typename DrawStrategy >
using enable_if_is_drawable =
   std::enable_if_t< is_drawable_v<ShapeT,DrawStrategy>, bool >;
*/

// C++20 concept to formulate the requirement that every shape needs a 'free_draw()' function
/*
template< typename ShapeT, typename DrawStrategy >
concept Drawable =
   requires ( ShapeT shape, DrawStrategy drawer )
   {
      drawer( shape );
   };
*/

template< typename StoragePolicy >
class Shape
{
 public:
   template< typename ShapeT, typename DrawStrategy = FreeDraw >
   Shape( ShapeT const& shape, DrawStrategy const& drawer = {} )
      : pimpl_{ policy_.template create<Model<ShapeT,DrawStrategy>>( shape, drawer ) }
   {}

   Shape( Shape const& other ) : pimpl_{ other.pimpl_->clone( policy_ ) } {}
   Shape( Shape&& other ) : pimpl_{ other.pimpl_->move( policy_ ) } {}

   ~Shape() { policy_.destroy( pimpl_ ); }

   Shape& operator=( Shape const& other )
   {
      Shape copy( other );
      policy_.destroy( pimpl_ );
      pimpl_ = other.pimpl_->clone( policy_ );
      return *this;
   }

   Shape& operator=( Shape&& other )
   {
      policy_.destroy( pimpl_ );
      pimpl_ = other.pimpl_->move( policy_ );
      return *this;
   }

 private:
   friend void free_draw( Shape const& other )
   {
      other.pimpl_->do_draw();
   }

   struct Concept
   {
      virtual ~Concept() = default;
      virtual void do_draw() const = 0;
      virtual Concept* clone( StoragePolicy const& ) const = 0;
      virtual Concept* move( StoragePolicy const& ) = 0;
   };

   template< typename ShapeT, typename DrawStrategy >
   struct Model final : public Concept
   {
      Model( ShapeT const& shape, DrawStrategy const& drawer )
         : shape_{ shape }
         , drawer_{ drawer }
      {}

      void do_draw() const override { drawer_( shape_ ); }

      Concept* clone( StoragePolicy const& policy ) const override
      {
         return policy.template create<Model>(*this);
      }

      Concept* move( StoragePolicy const& policy ) override
      {
         return policy.template create<Model>( std::move(*this) );
      }

      ShapeT shape_;
      DrawStrategy drawer_;
   };

   NO_UNIQUE_ADDRESS StoragePolicy policy_{};
   Concept* pimpl_{};
};

using DynamicShape = Shape<DynamicStorage>;
using StaticShape  = Shape<StaticStorage<40UL,8UL>>;
//using SmallShape   = Shape<SmallStorage<40UL,8UL>>;


//---- <Shapes.h> ---------------------------------------------------------------------------------

//#include <Shapes.h>
#include <vector>

using Shapes = std::vector<DynamicShape>;


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

