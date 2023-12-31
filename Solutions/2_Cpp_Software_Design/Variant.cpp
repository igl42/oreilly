/**************************************************************************************************
*
* \file Variant.cpp
* \brief C++ Training - Programming Task for std::variant
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'translate()' and 'area()' operations for the given 'Shape' variant.
*       Hint: the area of a circle is 'radius*radius*M_PI', the area of a square is 'side*side'.
*
**************************************************************************************************/

#define _USE_MATH_DEFINES
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <variant>
#include <vector>


//---- <Vector2D.h> -------------------------------------------------------------------------------

struct Vector2D
{
   double x{};
   double y{};
};

Vector2D operator+( const Vector2D& a, const Vector2D& b )
{
   return Vector2D{ a.x+b.x, a.y+b.y };
}

std::ostream& operator<<( std::ostream& os, const Vector2D& v )
{
   return os << '(' << v.x << ',' << v.y << ')';
}


//---- <Circle.h> ---------------------------------------------------------------------------------

class Circle
{
 public:
   explicit Circle( double radius )
      : radius_( radius )
   {}

   double   radius() const { return radius_; }
   Vector2D center() const { return center_; }

   void center( Vector2D c ) { center_ = c; }

 private:
   double radius_{};
   Vector2D center_;
};


//---- <Square.h> ---------------------------------------------------------------------------------

class Square
{
 public:
   explicit Square( double side )
      : side_( side )
   {}

   double   side  () const { return side_;   }
   Vector2D center() const { return center_; }

   void center( Vector2D c ) { center_ = c; }

 private:
   double side_{};
   Vector2D center_;
};


//---- <Shape.h> ----------------------------------------------------------------------------------

using Shape = std::variant<Circle,Square>;

using Shapes = std::vector<Shape>;


//---- <Draw.h> -----------------------------------------------------------------------------------

struct Draw
{
   void operator()( const Circle& c ) const {
      std::cout << "circle: radius=" << c.radius() << ", center=" << c.center() << std::endl;
   }
   void operator()( const Square& s ) const {
      std::cout << "square: side=" << s.side() << ", center=" << s.center() << std::endl;
   }
};

void draw( const Shape& s )
{
   std::visit( Draw{}, s );
}


//---- <Translate.h> ------------------------------------------------------------------------------

struct Translate
{
   void operator()( Circle& c ) const { c.center( c.center() + offset ); }
   void operator()( Square& s ) const { s.center( s.center() + offset ); }
   Vector2D offset{};
};

void translate( Shape& s, const Vector2D& v )
{
   std::visit( Translate{v}, s );
}


//---- <Area.h> -----------------------------------------------------------------------------------

struct Area
{
   double operator()( const Circle& c ) const { return c.radius() * c.radius() * M_PI; }
   double operator()( const Square& s ) const { return s.side() * s.side(); }
};

double area( const Shape& s )
{
   return std::visit( Area{}, s );
}


//---- <Main.cpp> ---------------------------------------------------------------------------------

int main()
{
   Shapes shapes{};

   shapes.emplace_back( Circle{ 2.3 } );
   shapes.emplace_back( Square{ 1.2 } );
   shapes.emplace_back( Circle{ 4.1 } );

   for( auto& shape : shapes ) {
      translate( shape, Vector2D{1.1,-2.2} );
      draw( shape );
      std::cout << "  area = " << area( shape ) << std::endl;
   }

   return EXIT_SUCCESS;
}
