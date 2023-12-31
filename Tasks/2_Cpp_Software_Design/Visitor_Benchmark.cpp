/**************************************************************************************************
*
* \file Visitor_Benchmark.cpp
* \brief C++ Training - Programming Task for the Visitor Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
**************************************************************************************************/

#define BENCHMARK_ENUM_SOLUTION 1
#define BENCHMARK_OO_SOLUTION 1
#define BENCHMARK_CYCLIC_VISITOR_SOLUTION 1
#define BENCHMARK_ACYCLIC_VISITOR_SOLUTION 0
#define BENCHMARK_STD_VARIANT_SOLUTION 1
#define BENCHMARK_MPARK_VARIANT_SOLUTION 1
#define BENCHMARK_BOOST_VARIANT_SOLUTION 0


#define BENCHMARK_WITH_CIRCLE 1
#define BENCHMARK_WITH_ELLIPSE 1
#define BENCHMARK_WITH_SQUARE 1
#define BENCHMARK_WITH_RECTANGLE 1
#define BENCHMARK_WITH_PENTAGON 1
#define BENCHMARK_WITH_HEXAGON 1


#define BENCHMARK_MANUAL_VISIT 0


#include <chrono>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <variant>
#include <vector>
#if BENCHMARK_MPARK_VARIANT_SOLUTION
#  include "mpark/variant.hpp"
#endif
#if BENCHMARK_BOOST_VARIANT_SOLUTION
#  include <boost/variant/variant.hpp>
#endif


struct Vector2D
{
   double x{};
   double y{};
};

Vector2D operator+( Vector2D const& a, Vector2D const& b )
{
   return Vector2D{ a.x+b.x, a.y+b.y };
}


#if BENCHMARK_ENUM_SOLUTION
namespace enum_solution {

   enum ShapeType
   {
#if BENCHMARK_WITH_CIRCLE
      circle,
#endif
#if BENCHMARK_WITH_ELLIPSE
      ellipse,
#endif
#if BENCHMARK_WITH_SQUARE
      square,
#endif
#if BENCHMARK_WITH_RECTANGLE
      rectangle,
#endif
#if BENCHMARK_WITH_PENTAGON
      pentagon,
#endif
#if BENCHMARK_WITH_HEXAGON
      hexagon
#endif
   };

   struct Shape
   {
      explicit Shape( ShapeType t )
         : type{ t }
      {}

      Shape() = default;
      Shape( Shape const& ) = default;
      Shape( Shape&& ) = default;
      virtual ~Shape() = default;
      Shape& operator=( Shape const& ) = default;
      Shape& operator=( Shape&& ) = default;

      ShapeType type{};
   };


#if BENCHMARK_WITH_CIRCLE
   struct Circle : public Shape
   {
      explicit Circle( double r )
         : Shape{ circle }
         , radius{ r }
      {}

      double radius{};
      Vector2D center{};
   };

   void translate( Circle& c, Vector2D const& v )
   {
      c.center = c.center + v;
   }
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse : public Shape
   {
      Ellipse( double r1, double r2 )
         : Shape{ ellipse }
         , radius1{ r1 }
         , radius2{ r2 }
      {}

      double radius1{};
      double radius2{};
      Vector2D center{};
   };

   void translate( Ellipse& e, Vector2D const& v )
   {
      e.center = e.center + v;
   }
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square : public Shape
   {
      explicit Square( double s )
         : Shape{ square }
         , side{ s }
      {}

      double side{};
      Vector2D center{};
   };

   void translate( Square& s, Vector2D const& v )
   {
      s.center = s.center + v;
   }
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle : public Shape
   {
      Rectangle( double w, double h )
         : Shape{ rectangle }
         , width{ w }
         , height{ h }
      {}

      double width{};
      double height{};
      Vector2D center{};
   };

   void translate( Rectangle& r, Vector2D const& v )
   {
      r.center = r.center + v;
   }
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon : public Shape
   {
      explicit Pentagon( double s )
         : Shape{ pentagon }
         , side{ s }
      {}

      double side{};
      Vector2D center{};
   };

   void translate( Pentagon& p, Vector2D const& v )
   {
      p.center = p.center + v;
   }
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon : public Shape
   {
      explicit Hexagon( double s )
         : Shape{ hexagon }
         , side{ s }
      {}

      double side{};
      Vector2D center{};
   };

   void translate( Hexagon& h, Vector2D const& v )
   {
      h.center = h.center + v;
   }
#endif


   using Shapes = std::vector< std::unique_ptr<Shape> >;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto const& s : shapes )
      {
         switch( s->type )
         {
#if BENCHMARK_WITH_CIRCLE
            case circle:
               translate( static_cast<Circle&>( *s.get() ), v );
               break;
#endif
#if BENCHMARK_WITH_ELLIPSE
            case ellipse:
               translate( static_cast<Ellipse&>( *s.get() ), v );
               break;
#endif
#if BENCHMARK_WITH_SQUARE
            case square:
               translate( static_cast<Square&>( *s.get() ), v );
               break;
#endif
#if BENCHMARK_WITH_RECTANGLE
            case rectangle:
               translate( static_cast<Rectangle&>( *s.get() ), v );
               break;
#endif
#if BENCHMARK_WITH_PENTAGON
            case pentagon:
               translate( static_cast<Pentagon&>( *s.get() ), v );
               break;
#endif
#if BENCHMARK_WITH_HEXAGON
            case hexagon:
               translate( static_cast<Hexagon&>( *s.get() ), v );
               break;
#endif
         }
      }
   }

} // namespace enum_solution
#endif


#if BENCHMARK_OO_SOLUTION
namespace object_oriented_solution {

   struct Shape
   {
      virtual ~Shape() {}
      virtual void translate( Vector2D const& v ) = 0;
   };


#if BENCHMARK_WITH_CIRCLE
   struct Circle : public Shape
   {
      explicit Circle( double r )
         : radius{ r }
      {}

      void translate( Vector2D const& v ) override
      {
         center = center + v;
      }

      double radius{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse : public Shape
   {
      Ellipse( double r1, double r2 )
         : radius1{ r1 }
         , radius2{ r2 }
      {}

      void translate( Vector2D const& v ) override
      {
         center = center + v;
      }

      double radius1{};
      double radius2{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square : public Shape
   {
      explicit Square( double s )
         : side{ s }
      {}

      void translate( Vector2D const& v ) override
      {
         center = center + v;
      }

      double side{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle : public Shape
   {
      Rectangle( double w, double h )
         : width{ w }
         , height{ h }
      {}

      void translate( Vector2D const& v ) override
      {
         center = center + v;
      }

      double width{};
      double height{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon : public Shape
   {
      explicit Pentagon( double s )
         : side{ s }
      {}

      void translate( Vector2D const& v ) override
      {
         center = center + v;
      }

      double side{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon : public Shape
   {
      explicit Hexagon( double s )
         : side{ s }
      {}

      void translate( Vector2D const& v ) override
      {
         center = center + v;
      }

      double side{};
      Vector2D center{};
   };
#endif


   using Shapes = std::vector< std::unique_ptr<Shape> >;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto const& s : shapes )
      {
         s->translate( v );
      }
   }

} // namespace object_oriented_solution
#endif


#if BENCHMARK_CYCLIC_VISITOR_SOLUTION
namespace cyclic_visitor_solution {

#if BENCHMARK_WITH_CIRCLE
   struct Circle;
#endif
#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse;
#endif
#if BENCHMARK_WITH_SQUARE
   struct Square;
#endif
#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle;
#endif
#if BENCHMARK_WITH_PENTAGON
   struct Pentagon;
#endif
#if BENCHMARK_WITH_HEXAGON
   struct Hexagon;
#endif


   struct Visitor
   {
      virtual ~Visitor() = default;

#if BENCHMARK_WITH_CIRCLE
      virtual void visit( Circle& ) const = 0;
#endif
#if BENCHMARK_WITH_ELLIPSE
      virtual void visit( Ellipse& ) const = 0;
#endif
#if BENCHMARK_WITH_SQUARE
      virtual void visit( Square& ) const = 0;
#endif
#if BENCHMARK_WITH_RECTANGLE
      virtual void visit( Rectangle& ) const = 0;
#endif
#if BENCHMARK_WITH_PENTAGON
      virtual void visit( Pentagon& ) const = 0;
#endif
#if BENCHMARK_WITH_HEXAGON
      virtual void visit( Hexagon& ) const = 0;
#endif
   };


   struct Shape
   {
      virtual ~Shape() {}
      virtual void accept( Visitor const& v ) = 0;
   };


#if BENCHMARK_WITH_CIRCLE
   struct Circle : public Shape
   {
      explicit Circle( double r )
         : radius{ r }
      {}

      void accept( Visitor const& v ) override { v.visit(*this); }

      double radius{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse : public Shape
   {
      Ellipse( double r1, double r2 )
         : radius1{ r1 }
         , radius2{ r2 }
      {}

      void accept( Visitor const& v ) override { v.visit(*this); }

      double radius1{};
      double radius2{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square : public Shape
   {
      explicit Square( double s )
         : side{ s }
      {}

      void accept( Visitor const& v ) override { v.visit(*this); }

      double side{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle : public Shape
   {
      Rectangle( double w, double h )
         : width{ w }
         , height{ h }
      {}

      void accept( Visitor const& v ) override { v.visit(*this); }

      double width{};
      double height{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon : public Shape
   {
      explicit Pentagon( double s )
         : side{ s }
      {}

      void accept( Visitor const& v ) override { v.visit(*this); }

      double side{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon : public Shape
   {
      explicit Hexagon( double s )
         : side{ s }
      {}

      void accept( Visitor const& v ) override { v.visit(*this); }

      double side{};
      Vector2D center{};
   };
#endif


   struct Translate : public Visitor
   {
      Translate( Vector2D const& vec ) : v{ vec } {}
#if BENCHMARK_WITH_CIRCLE
      void visit( Circle& c ) const override { c.center = c.center + v; }
#endif
#if BENCHMARK_WITH_ELLIPSE
      void visit( Ellipse& e ) const override { e.center = e.center + v; }
#endif
#if BENCHMARK_WITH_SQUARE
      void visit( Square& s ) const override { s.center = s.center + v; }
#endif
#if BENCHMARK_WITH_RECTANGLE
      void visit( Rectangle& r ) const override { r.center = r.center + v; }
#endif
#if BENCHMARK_WITH_PENTAGON
      void visit( Pentagon& p ) const override { p.center = p.center + v; }
#endif
#if BENCHMARK_WITH_HEXAGON
      void visit( Hexagon& h ) const override { h.center = h.center + v; }
#endif
      Vector2D v{};
   };


   using Shapes = std::vector< std::unique_ptr<Shape> >;

   void translate( Shapes const& shapes, Vector2D const& v )
   {
      for( auto const& shape : shapes )
      {
         shape->accept( Translate{ v } );
      }
   }

} // namespace cyclic_visitor_solution
#endif


#if BENCHMARK_ACYCLIC_VISITOR_SOLUTION
namespace acyclic_visitor_solution {

#if BENCHMARK_WITH_CIRCLE
   struct Circle;
#endif
#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse;
#endif
#if BENCHMARK_WITH_SQUARE
   struct Square;
#endif
#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle;
#endif
#if BENCHMARK_WITH_PENTAGON
   struct Pentagon;
#endif
#if BENCHMARK_WITH_HEXAGON
   struct Hexagon;
#endif


   struct AbstractVisitor
   {
      virtual ~AbstractVisitor() = default;
   };


   struct Shape
   {
      virtual ~Shape() {}
      virtual void accept( AbstractVisitor const& v ) = 0;
   };


   template< typename T >
   struct Visitor
   {
      virtual ~Visitor() = default;
      virtual void visit( T& ) const = 0;
   };


#if BENCHMARK_WITH_CIRCLE
   struct Circle : public Shape
   {
      explicit Circle( double r )
         : radius{ r }
      {}

      void accept( AbstractVisitor const& v ) override {
         if( auto cv = dynamic_cast<Visitor<Circle> const*>(&v) ) {
            cv->visit(*this);
         }
      }

      double radius{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse : public Shape
   {
      Ellipse( double r1, double r2 )
         : radius1{ r1 }
         , radius2{ r2 }
      {}

      void accept( AbstractVisitor const& v ) override {
         if( auto ev = dynamic_cast<Visitor<Ellipse> const*>(&v) ) {
            ev->visit(*this);
         }
      }

      double radius1{};
      double radius2{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square : public Shape
   {
      explicit Square( double s )
         : side{ s }
      {}

      void accept( AbstractVisitor const& v ) override {
         if( auto sv = dynamic_cast<Visitor<Square> const*>(&v) ) {
            sv->visit(*this);
         }
      }

      double side{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle : public Shape
   {
      Rectangle( double w, double h )
         : width{ w }
         , height{ h }
      {}

      void accept( AbstractVisitor const& v ) override {
         if( auto rv = dynamic_cast<Visitor<Rectangle> const*>(&v) ) {
            rv->visit(*this);
         }
      }

      double width{};
      double height{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon : public Shape
   {
      explicit Pentagon( double s )
         : side{ s }
      {}

      void accept( AbstractVisitor const& v ) override {
         if( auto sv = dynamic_cast<Visitor<Pentagon> const*>(&v) ) {
            sv->visit(*this);
         }
      }

      double side{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon : public Shape
   {
      explicit Hexagon( double s )
         : side{ s }
      {}

      void accept( AbstractVisitor const& v ) override {
         if( auto sv = dynamic_cast<Visitor<Hexagon> const*>(&v) ) {
            sv->visit(*this);
         }
      }

      double side{};
      Vector2D center{};
   };
#endif


   struct Translate : public AbstractVisitor
#if BENCHMARK_WITH_CIRCLE
                    , public Visitor<Circle>
#endif
#if BENCHMARK_WITH_ELLIPSE
                    , public Visitor<Ellipse>
#endif
#if BENCHMARK_WITH_SQUARE
                    , public Visitor<Square>
#endif
#if BENCHMARK_WITH_RECTANGLE
                    , public Visitor<Rectangle>
#endif
#if BENCHMARK_WITH_PENTAGON
                    , public Visitor<Pentagon>
#endif
#if BENCHMARK_WITH_HEXAGON
                    , public Visitor<Hexagon>
#endif
   {
      Translate( Vector2D const& vec ) : v{ vec } {}
#if BENCHMARK_WITH_CIRCLE
      void visit( Circle& c ) const override { c.center = c.center + v; }
#endif
#if BENCHMARK_WITH_ELLIPSE
      void visit( Ellipse& e ) const override { e.center = e.center + v; }
#endif
#if BENCHMARK_WITH_SQUARE
      void visit( Square& s ) const override { s.center = s.center + v; }
#endif
#if BENCHMARK_WITH_RECTANGLE
      void visit( Rectangle& r ) const override { r.center = r.center + v; }
#endif
#if BENCHMARK_WITH_PENTAGON
      void visit( Pentagon& p ) const override { p.center = p.center + v; }
#endif
#if BENCHMARK_WITH_HEXAGON
      void visit( Hexagon& h ) const override { h.center = h.center + v; }
#endif
      Vector2D v{};
   };


   using Shapes = std::vector< std::unique_ptr<Shape> >;

   void translate( Shapes const& shapes, Vector2D const& v )
   {
      for( auto const& shape : shapes )
      {
         shape->accept( Translate{ v } );
      }
   }

} // namespace acyclic_visitor_solution
#endif


#if BENCHMARK_STD_VARIANT_SOLUTION
namespace std_variant_solution {

#if BENCHMARK_WITH_CIRCLE
   struct Circle
   {
      double radius{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse
   {
      double radius1{};
      double radius2{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square
   {
      double side{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle
   {
      double width{};
      double height{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon
   {
      double side{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon
   {
      double side{};
      Vector2D center{};
   };
#endif


   using Shape = std::variant<
#if BENCHMARK_WITH_CIRCLE
      Circle
#endif
#if BENCHMARK_WITH_CIRCLE && BENCHMARK_WITH_ELLIPSE
      ,Ellipse
#elif BENCHMARK_WITH_ELLIPSE
      Ellipse
#endif
#if ( BENCHMARK_WITH_CIRCLE || BENCHMARK_WITH_ELLIPSE ) && BENCHMARK_WITH_SQUARE
      ,Square
#elif BENCHMARK_WITH_SQUARE
      Square
#endif
#if ( BENCHMARK_WITH_CIRCLE || BENCHMARK_WITH_ELLIPSE || BENCHMARK_WITH_SQUARE ) && BENCHMARK_WITH_RECTANGLE
      ,Rectangle
#elif BENCHMARK_WITH_RECTANGLE
      Rectangle
#endif
#if ( BENCHMARK_WITH_CIRCLE || BENCHMARK_WITH_ELLIPSE || BENCHMARK_WITH_SQUARE || BENCHMARK_WITH_RECTANGLE ) && BENCHMARK_WITH_PENTAGON
      ,Pentagon
#elif BENCHMARK_WITH_PENTAGON
      Pentagon
#endif
#if ( BENCHMARK_WITH_CIRCLE || BENCHMARK_WITH_ELLIPSE || BENCHMARK_WITH_SQUARE || BENCHMARK_WITH_RECTANGLE || BENCHMARK_WITH_PENTAGON ) && BENCHMARK_WITH_HEXAGON
      ,Hexagon
#elif BENCHMARK_WITH_HEXAGON
      Hexagon
#endif
      >;


   struct Translate
   {
#if BENCHMARK_WITH_CIRCLE
      void operator()( Circle& c ) const { c.center = c.center + v; }
#endif
#if BENCHMARK_WITH_ELLIPSE
      void operator()( Ellipse& e ) const { e.center = e.center + v; }
#endif
#if BENCHMARK_WITH_SQUARE
      void operator()( Square& s ) const { s.center = s.center + v; }
#endif
#if BENCHMARK_WITH_RECTANGLE
      void operator()( Rectangle& r ) const { r.center = r.center + v; }
#endif
#if BENCHMARK_WITH_PENTAGON
   void operator()( Pentagon& p ) const { p.center = p.center + v; }
#endif
#if BENCHMARK_WITH_HEXAGON
   void operator()( Hexagon& h ) const { h.center = h.center + v; }
#endif
      Vector2D v{};
   };

   void translate( Shape& s, Vector2D const& v )
   {
#if BENCHMARK_MANUAL_VISIT
#  if BENCHMARK_WITH_CIRCLE
      if( Circle* circle = std::get_if<Circle>(&s) ) {
         circle->center = circle->center + v;
         return;
      }
#  endif
#  if BENCHMARK_WITH_ELLIPSE
      if( Ellipse* ellipse = std::get_if<Ellipse>(&s) ) {
         ellipse->center = ellipse->center + v;
         return;
      }
#  endif
#  if BENCHMARK_WITH_SQUARE
      if( Square* square = std::get_if<Square>(&s) ) {
         square->center = square->center + v;
         return;
      }
#  endif
#  if BENCHMARK_WITH_RECTANGLE
      if( Rectangle* rectangle = std::get_if<Rectangle>(&s) ) {
         rectangle->center = rectangle->center + v;
         return;
      }
#  endif
#  if BENCHMARK_WITH_PENTAGON
      if( Pentagon* pentagon = std::get_if<Pentagon>(&s) ) {
         pentagon->center = pentagon->center + v;
         return;
      }
#  endif
#  if BENCHMARK_WITH_HEXAGON
      if( Hexagon* hexagon = std::get_if<Hexagon>(&s) ) {
         hexagon->center = hexagon->center + v;
         return;
      }
#  endif
#else
      std::visit( Translate{ v }, s );
#endif
   }


   using Shapes = std::vector<Shape>;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto& shape : shapes )
      {
         translate( shape, v );
      }
   }

} // namespace std_variant_solution
#endif


#if BENCHMARK_MPARK_VARIANT_SOLUTION
namespace mpark_variant_solution {

#if BENCHMARK_WITH_CIRCLE
   struct Circle
   {
      double radius{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse
   {
      double radius1{};
      double radius2{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square
   {
      double side{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle
   {
      double width{};
      double height{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon
   {
      double side{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon
   {
      double side{};
      Vector2D center{};
   };
#endif


   using Shape = mpark::variant<
#if BENCHMARK_WITH_CIRCLE
      Circle
#endif
#if BENCHMARK_WITH_CIRCLE && BENCHMARK_WITH_ELLIPSE
      ,Ellipse
#elif BENCHMARK_WITH_ELLIPSE
      Ellipse
#endif
#if ( BENCHMARK_WITH_CIRCLE || BENCHMARK_WITH_ELLIPSE ) && BENCHMARK_WITH_SQUARE
      ,Square
#elif BENCHMARK_WITH_SQUARE
      Square
#endif
#if ( BENCHMARK_WITH_CIRCLE || BENCHMARK_WITH_ELLIPSE || BENCHMARK_WITH_SQUARE ) && BENCHMARK_WITH_RECTANGLE
      ,Rectangle
#elif BENCHMARK_WITH_RECTANGLE
      Rectangle
#endif
#if ( BENCHMARK_WITH_CIRCLE || BENCHMARK_WITH_ELLIPSE || BENCHMARK_WITH_SQUARE || BENCHMARK_WITH_RECTANGLE ) && BENCHMARK_WITH_PENTAGON
      ,Pentagon
#elif BENCHMARK_WITH_PENTAGON
      Pentagon
#endif
#if ( BENCHMARK_WITH_CIRCLE || BENCHMARK_WITH_ELLIPSE || BENCHMARK_WITH_SQUARE || BENCHMARK_WITH_RECTANGLE || BENCHMARK_WITH_PENTAGON ) && BENCHMARK_WITH_HEXAGON
      ,Hexagon
#elif BENCHMARK_WITH_HEXAGON
      Hexagon
#endif
      >;


   struct Translate
   {
#if BENCHMARK_WITH_CIRCLE
      void operator()( Circle& c ) const { c.center = c.center + v; }
#endif
#if BENCHMARK_WITH_ELLIPSE
      void operator()( Ellipse& e ) const { e.center = e.center + v; }
#endif
#if BENCHMARK_WITH_SQUARE
      void operator()( Square& s ) const { s.center = s.center + v; }
#endif
#if BENCHMARK_WITH_RECTANGLE
      void operator()( Rectangle& r ) const { r.center = r.center + v; }
#endif
#if BENCHMARK_WITH_PENTAGON
      void operator()( Pentagon& p ) const { p.center = p.center + v; }
#endif
#if BENCHMARK_WITH_HEXAGON
      void operator()( Hexagon& h ) const { h.center = h.center + v; }
#endif
      Vector2D v{};
   };

   void translate( Shape& s, Vector2D const& v )
   {
#if BENCHMARK_MANUAL_VISIT
#if   BENCHMARK_WITH_CIRCLE
      if( Circle* circle = mpark::get_if<Circle>(&s) ) {
         circle->center = circle->center + v;
         return;
      }
#  endif
#  if BENCHMARK_WITH_ELLIPSE
      if( Ellipse* ellipse = mpark::get_if<Ellipse>(&s) ) {
         ellipse->center = ellipse->center + v;
         return;
      }
#  endif
#  if BENCHMARK_WITH_SQUARE
      if( Square* square = mpark::get_if<Square>(&s) ) {
         square->center = square->center + v;
         return;
      }
#  endif
#  if BENCHMARK_WITH_RECTANGLE
      if( Rectangle* rectangle = mpark::get_if<Rectangle>(&s) ) {
         rectangle->center = rectangle->center + v;
         return;
      }
#  endif
#  if BENCHMARK_WITH_PENTAGON
      if( Pentagon* pentagon = mpark::get_if<Pentagon>(&s) ) {
         pentagon->center = pentagon->center + v;
         return;
      }
#  endif
#  if BENCHMARK_WITH_HEXAGON
      if( Hexagon* hexagon = mpark::get_if<Hexagon>(&s) ) {
         hexagon->center = hexagon->center + v;
         return;
      }
#  endif
#else
      mpark::visit( Translate{ v }, s );
#endif
   }


   using Shapes = std::vector<Shape>;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto& shape : shapes )
      {
         translate( shape, v );
      }
   }

} // namespace mpark_variant_solution
#endif


#if BENCHMARK_BOOST_VARIANT_SOLUTION
namespace boost_variant_solution {

#if BENCHMARK_WITH_CIRCLE
   struct Circle
   {
      double radius{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse
   {
      double radius1{};
      double radius2{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square
   {
      double side{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle
   {
      double width{};
      double height{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon
   {
      double side{};
      Vector2D center{};
   };
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon
   {
      double side{};
      Vector2D center{};
   };
#endif


   using Shape = boost::variant<
#if BENCHMARK_WITH_CIRCLE
      Circle
#endif
#if BENCHMARK_WITH_CIRCLE && BENCHMARK_WITH_ELLIPSE
      ,Ellipse
#elif BENCHMARK_WITH_ELLIPSE
      Ellipse
#endif
#if ( BENCHMARK_WITH_CIRCLE || BENCHMARK_WITH_ELLIPSE ) && BENCHMARK_WITH_SQUARE
      ,Square
#elif BENCHMARK_WITH_SQUARE
      Square
#endif
#if ( BENCHMARK_WITH_CIRCLE || BENCHMARK_WITH_ELLIPSE || BENCHMARK_WITH_SQUARE ) && BENCHMARK_WITH_RECTANGLE
      ,Rectangle
#elif BENCHMARK_WITH_RECTANGLE
      Rectangle
#endif
#if ( BENCHMARK_WITH_CIRCLE || BENCHMARK_WITH_ELLIPSE || BENCHMARK_WITH_SQUARE || BENCHMARK_WITH_RECTANGLE ) && BENCHMARK_WITH_PENTAGON
      ,Pentagon
#elif BENCHMARK_WITH_PENTAGON
      Pentagon
#endif
#if ( BENCHMARK_WITH_CIRCLE || BENCHMARK_WITH_ELLIPSE || BENCHMARK_WITH_SQUARE || BENCHMARK_WITH_RECTANGLE || BENCHMARK_WITH_PENTAGON ) && BENCHMARK_WITH_HEXAGON
      ,Hexagon
#elif BENCHMARK_WITH_HEXAGON
      Hexagon
#endif
      >;


   struct Translate
   {
#if BENCHMARK_WITH_CIRCLE
      void operator()( Circle& c ) const { c.center = c.center + v; }
#endif
#if BENCHMARK_WITH_ELLIPSE
      void operator()( Ellipse& e ) const { e.center = e.center + v; }
#endif
#if BENCHMARK_WITH_SQUARE
      void operator()( Square& s ) const { s.center = s.center + v; }
#endif
#if BENCHMARK_WITH_RECTANGLE
      void operator()( Rectangle& r ) const { r.center = r.center + v; }
#endif
#if BENCHMARK_WITH_PENTAGON
      void operator()( Pentagon& p ) const { p.center = p.center + v; }
#endif
#if BENCHMARK_WITH_HEXAGON
      void operator()( Hexagon& h ) const { h.center = h.center + v; }
#endif
      Vector2D v{};
   };

   void translate( Shape& s, Vector2D const& v )
   {
      boost::apply_visitor( Translate{ v }, s );
   }


   using Shapes = std::vector<Shape>;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto& shape : shapes )
      {
         translate( shape, v );
      }
   }

} // namespace boost_variant_solution
#endif


int main()
{
   constexpr size_t N    ( 10000UL );
   constexpr size_t steps( 25000UL );

   std::random_device rd{};
   unsigned int const seed( rd() );

   std::mt19937 rng{};
   std::uniform_int_distribution<int> int_dist( 1, 6 );
   std::uniform_real_distribution<double> real_dist( 0.0, 1.0 );

   std::cout << std::endl;

#if BENCHMARK_ENUM_SOLUTION
   {
      using namespace enum_solution;

      rng.seed( seed );

      Shapes shapes;

      while( shapes.size() < N )
      {
         int const random_value( int_dist(rng) );

         if( random_value == 1 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( std::make_unique<Circle>( real_dist(rng) ) );
#endif
         }
         else if( random_value == 2 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( std::make_unique<Ellipse>( real_dist(rng), real_dist(rng) ) );
#endif
         }
         else if( random_value == 3 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( std::make_unique<Square>( real_dist(rng) ) );
#endif
         }
         else if( random_value == 4 ) {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( std::make_unique<Rectangle>( real_dist(rng), real_dist(rng) ) );
#endif
         }
         else if( random_value == 5 ) {
#if BENCHMARK_WITH_PENTAGON
            shapes.emplace_back( std::make_unique<Pentagon>( real_dist(rng) ) );
#endif
         }
         else {
#if BENCHMARK_WITH_HEXAGON
            shapes.emplace_back( std::make_unique<Hexagon>( real_dist(rng) ) );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ real_dist(rng), real_dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> const elapsedTime( end - start );
      double const seconds( elapsedTime.count() );

      std::cout << " Enum solution runtime           : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_OO_SOLUTION
   {
      using namespace object_oriented_solution;

      rng.seed( seed );

      Shapes shapes;

      while( shapes.size() < N )
      {
         int const random_value( int_dist(rng) );

         if( random_value == 1 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( std::make_unique<Circle>( real_dist(rng) ) );
#endif
         }
         else if( random_value == 2 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( std::make_unique<Ellipse>( real_dist(rng), real_dist(rng) ) );
#endif
         }
         else if( random_value == 3 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( std::make_unique<Square>( real_dist(rng) ) );
#endif
         }
         else if( random_value == 4 ) {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( std::make_unique<Rectangle>( real_dist(rng), real_dist(rng) ) );
#endif
         }
         else if( random_value == 5 ) {
#if BENCHMARK_WITH_PENTAGON
            shapes.emplace_back( std::make_unique<Pentagon>( real_dist(rng) ) );
#endif
         }
         else {
#if BENCHMARK_WITH_HEXAGON
            shapes.emplace_back( std::make_unique<Hexagon>( real_dist(rng) ) );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ real_dist(rng), real_dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> const elapsedTime( end - start );
      double const seconds( elapsedTime.count() );

      std::cout << " OO solution runtime             : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_CYCLIC_VISITOR_SOLUTION
   {
      using namespace cyclic_visitor_solution;

      rng.seed( seed );

      Shapes shapes;

      while( shapes.size() < N )
      {
         int const random_value( int_dist(rng) );

         if( random_value == 1 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( std::make_unique<Circle>( real_dist(rng) ) );
#endif
         }
         else if( random_value == 2 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( std::make_unique<Ellipse>( real_dist(rng), real_dist(rng) ) );
#endif
         }
         else if( random_value == 3 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( std::make_unique<Square>( real_dist(rng) ) );
#endif
         }
         else if( random_value == 4 ) {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( std::make_unique<Rectangle>( real_dist(rng), real_dist(rng) ) );
#endif
         }
         else if( random_value == 5 ) {
#if BENCHMARK_WITH_PENTAGON
            shapes.emplace_back( std::make_unique<Pentagon>( real_dist(rng) ) );
#endif
         }
         else {
#if BENCHMARK_WITH_HEXAGON
            shapes.emplace_back( std::make_unique<Hexagon>( real_dist(rng) ) );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ real_dist(rng), real_dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> const elapsedTime( end - start );
      double const seconds( elapsedTime.count() );

      std::cout << " Cyclic visitor solution runtime : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_ACYCLIC_VISITOR_SOLUTION
   {
      using namespace acyclic_visitor_solution;

      rng.seed( seed );

      Shapes shapes;

      while( shapes.size() < N )
      {
         int const random_value( int_dist(rng) );

         if( random_value == 1 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( std::make_unique<Circle>( real_dist(rng) ) );
#endif
         }
         else if( random_value == 2 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( std::make_unique<Ellipse>( real_dist(rng), real_dist(rng) ) );
#endif
         }
         else if( random_value == 3 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( std::make_unique<Square>( real_dist(rng) ) );
#endif
         }
         else if( random_value == 4 ) {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( std::make_unique<Rectangle>( real_dist(rng), real_dist(rng) ) );
#endif
         }
         else if( random_value == 5 ) {
#if BENCHMARK_WITH_PENTAGON
            shapes.emplace_back( std::make_unique<Pentagon>( real_dist(rng) ) );
#endif
         }
         else {
#if BENCHMARK_WITH_HEXAGON
            shapes.emplace_back( std::make_unique<Hexagon>( real_dist(rng) ) );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ real_dist(rng), real_dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> const elapsedTime( end - start );
      double const seconds( elapsedTime.count() );

      std::cout << " Acyclic visitor solution runtime: " << seconds << "s\n";
   }
#endif

#if BENCHMARK_STD_VARIANT_SOLUTION
   {
      using namespace std_variant_solution;

      rng.seed( seed );

      Shapes shapes;

      while( shapes.size() < N )
      {
         int const random_value( int_dist(rng) );

         if( random_value == 1 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( Circle{ real_dist(rng) } );
#endif
         }
         else if( random_value == 2 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( Ellipse{ real_dist(rng), real_dist(rng) } );
#endif
         }
         else if( random_value == 3 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( Square{ real_dist(rng) } );
#endif
         }
         else if( random_value == 4 ) {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( Rectangle{ real_dist(rng), real_dist(rng) } );
#endif
         }
         else if( random_value == 5 ) {
#if BENCHMARK_WITH_PENTAGON
            shapes.emplace_back( Pentagon{ real_dist(rng) } );
#endif
         }
         else {
#if BENCHMARK_WITH_HEXAGON
            shapes.emplace_back( Hexagon{ real_dist(rng) } );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ real_dist(rng), real_dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> const elapsedTime( end - start );
      double const seconds( elapsedTime.count() );

      std::cout << " std::variant solution runtime   : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_MPARK_VARIANT_SOLUTION
   {
      using namespace mpark_variant_solution;

      rng.seed( seed );

      Shapes shapes;

      while( shapes.size() < N )
      {
         int const random_value( int_dist(rng) );

         if( random_value == 1 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( Circle{ real_dist(rng) } );
#endif
         }
         else if( random_value == 2 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( Ellipse{ real_dist(rng), real_dist(rng) } );
#endif
         }
         else if( random_value == 3 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( Square{ real_dist(rng) } );
#endif
         }
         else if( random_value == 4 ) {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( Rectangle{ real_dist(rng), real_dist(rng) } );
#endif
         }
         else if( random_value == 5 ) {
#if BENCHMARK_WITH_PENTAGON
            shapes.emplace_back( Pentagon{ real_dist(rng) } );
#endif
         }
         else {
#if BENCHMARK_WITH_HEXAGON
            shapes.emplace_back( Hexagon{ real_dist(rng) } );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ real_dist(rng), real_dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> const elapsedTime( end - start );
      double const seconds( elapsedTime.count() );

      std::cout << " mpark::variant solution runtime : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_BOOST_VARIANT_SOLUTION
   {
      using namespace boost_variant_solution;

      rng.seed( seed );

      Shapes shapes;

      while( shapes.size() < N )
      {
         int const random_value( int_dist(rng) );

         if( random_value == 1 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( Circle{ real_dist(rng) } );
#endif
         }
         else if( random_value == 2 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( Ellipse{ real_dist(rng), real_dist(rng) } );
#endif
         }
         else if( random_value == 3 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( Square{ real_dist(rng) } );
#endif
         }
         else if( random_value == 4 ) {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( Rectangle{ real_dist(rng), real_dist(rng) } );
#endif
         }
         else if( random_value == 5 ) {
#if BENCHMARK_WITH_PENTAGON
            shapes.emplace_back( Pentagon{ real_dist(rng) } );
#endif
         }
         else {
#if BENCHMARK_WITH_HEXAGON
            shapes.emplace_back( Hexagon{ real_dist(rng) } );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ real_dist(rng), real_dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      std::chrono::duration<double> const elapsedTime( end - start );
      double const seconds( elapsedTime.count() );

      std::cout << " boost::variant solution runtime : " << seconds << "s\n";
   }
#endif

   std::cout << std::endl;

   return EXIT_SUCCESS;
}

