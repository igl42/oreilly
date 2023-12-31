/**************************************************************************************************
*
* \file TypeErasure_dyno.cpp
* \brief C++ Training - Programming Task for Type Erasure
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Implement the 'Shape' class by means of the 'dyno' library (https://github.com/ldionne/dyno).
*       'Shape' may require all types to provide a free 'draw()' function that draws them to the
*       screen.
*
* Note: You will need the 'dyno' library (https://github.com/ldionne/dyno) to make this example
*       compile!
*
**************************************************************************************************/

/*
#include <cstdlib>
#include <iostream>
#include <vector>
#include <dyno.hpp>
using namespace dyno::literals;


struct ShapeConcept : decltype( dyno::requires_(
   dyno::CopyConstructible{},
   dyno::MoveConstructible{},
   dyno::Destructible{},
   "draw"_s = dyno::function<void (const dyno::T&)>
)) { };

template <typename T>
auto const dyno::default_concept_map<ShapeConcept, T> = dyno::make_concept_map(
   "draw"_s = []( const T& self ) { free_draw( self ); }
);

class Shape
{
 public:
   template <typename T>
   Shape( T x ) : poly_{x} { }

   void draw() const
   { poly_.virtual_( "draw"_s )( poly_ ); }

 private:
   dyno::poly<ShapeConcept> poly_;
};

void free_draw( const Shape& shape )
{
   shape.draw();
}


using Shapes = std::vector<Shape>;

void drawAllShapes( const Shapes& shapes )
{
   for( const auto& shape : shapes )
   {
      free_draw( shape );
   }
}


struct Circle
{
   double radius;
};

void free_draw( const Circle& circle )
{
   std::cout << "circle: radius=" << circle.radius << '\n';
}


struct Square
{
   double side;
};

void free_draw( const Square& square )
{
   std::cout << "square: side=" << square.side << '\n';
}


int main()
{
   Shapes shapes{};

   shapes.emplace_back( Circle{ 2.3 } );
   shapes.emplace_back( Square{ 1.2 } );
   shapes.emplace_back( Circle{ 4.1 } );

   drawAllShapes( shapes );

   return EXIT_SUCCESS;
}
*/

