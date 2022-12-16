/**************************************************************************************************
*
* \file TypeErasure_Ref.cpp
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

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <type_traits>
#include <vector>


//---- <Shape.h> ----------------------------------------------------------------------------------

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

class ShapeConstRef
{
   // TODO: Define 'ShapeConstRef' as an abstraction for constant, drawable shape types
};


//---- <Circle.h> ---------------------------------------------------------------------------------

class Circle
{
 public:
   explicit Circle( double radius )
      : radius_( radius )
   {}

   double radius() const { return radius_; }

 private:
   double radius_;
};


//---- <DrawCircle.h> -----------------------------------------------------------------------------

void draw( Circle const& circle );


//---- <DrawCircle.cpp> ---------------------------------------------------------------------------

void draw( Circle const& circle )
{
   std::cout << "circle: radius=" << circle.radius() << std::endl;
}


//---- <Square.h> ---------------------------------------------------------------------------------

class Square
{
 public:
   explicit Square( double side )
      : side_( side )
   {}

   double side() const { return side_; }

 private:
   double side_;
};


//---- <DrawSquare.h> -----------------------------------------------------------------------------

void draw( Square const& square );


//---- <DrawSquare.cpp> ---------------------------------------------------------------------------

void draw( Square const& square )
{
   std::cout << "square: side=" << square.side() << std::endl;
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

void performAction( ShapeConstRef shape )
{
   // TODO: Implement the drawing via the 'ShapeConstRef' abstraction
   //draw( shape );
}

int main()
{
   /*
   // Create a circle as one representative of a concrete shape type
   Circle circle{ 3.14 };

   // Create a square as a second representative of a concrete shape type
   Square square{ 2.71 };

   // Drawing the two concrete shapes
   draw( circle );
   draw( square );

   // Drawing the two shapes via abstraction
   performAction( circle );
   performAction( square );
   */

   return EXIT_SUCCESS;
}

