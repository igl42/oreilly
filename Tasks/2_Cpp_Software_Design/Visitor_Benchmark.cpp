/**************************************************************************************************
*
* \file Visitor_Benchmark.cpp
* \brief C++ Training - Programming Task for the Visitor Design Pattern
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
**************************************************************************************************/

#define BENCHMARK_ENUM_SOLUTION 1
#define BENCHMARK_OO_SOLUTION 1
#define BENCHMARK_CYCLIC_VISITOR_SOLUTION 1
#define BENCHMARK_ACYCLIC_VISITOR_SOLUTION 1
#define BENCHMARK_STD_VARIANT_SOLUTION 1
#define BENCHMARK_MPARK_VARIANT_SOLUTION 1
#define BENCHMARK_BOOST_VARIANT_SOLUTION 0


#define BENCHMARK_WITH_CIRCLE 1
#define BENCHMARK_WITH_ELLIPSE 1
#define BENCHMARK_WITH_SQUARE 1
#define BENCHMARK_WITH_RECTANGLE 1


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

Vector2D operator+( const Vector2D& a, const Vector2D& b )
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
      rectangle
#endif
   };

   struct Shape
   {
      explicit Shape( ShapeType t )
         : type{ t }
      {}

      Shape() = default;
      Shape( const Shape& ) = default;
      Shape( Shape&& ) = default;
      virtual ~Shape() = default;
      Shape& operator=( const Shape& ) = default;
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

   void translate( Circle& c, const Vector2D& v )
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

   void translate( Ellipse& e, const Vector2D& v )
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

   void translate( Square& s, const Vector2D& v )
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

   void translate( Rectangle& r, const Vector2D& v )
   {
      r.center = r.center + v;
   }
#endif


   using Shapes = std::vector< std::unique_ptr<Shape> >;

   void translate( Shapes& shapes, const Vector2D& v )
   {
      for( const auto& s : shapes )
      {
         switch ( s->type )
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
         }
      }
   }

} // namespace enum_solution
#endif


#if BENCHMARK_OO_SOLUTION
namespace object_oriented_solution {

   struct Shape
   {
      Shape() = default;
      Shape( const Shape& ) = default;
      Shape( Shape&& ) = default;
      virtual ~Shape() {}
      Shape& operator=( const Shape& ) = default;
      Shape& operator=( Shape&& ) = default;

      virtual void translate( const Vector2D& v ) = 0;
   };


#if BENCHMARK_WITH_CIRCLE
   struct Circle : public Shape
   {
      explicit Circle( double r )
         : radius{ r }
      {}

      void translate( const Vector2D& v ) override
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

      void translate( const Vector2D& v ) override
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

      void translate( const Vector2D& v ) override
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

      void translate( const Vector2D& v ) override
      {
         center = center + v;
      }

      double width{};
      double height{};
      Vector2D center{};
   };
#endif


   using Shapes = std::vector< std::unique_ptr<Shape> >;

   void translate( Shapes& shapes, const Vector2D& v )
   {
      for( const auto& s : shapes )
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


   struct Visitor
   {
      Visitor() = default;
      Visitor( const Visitor& ) = default;
      Visitor( Visitor&& ) = default;
      virtual ~Visitor() = default;
      Visitor& operator=( const Visitor& ) = default;
      Visitor& operator=( Visitor&& ) = default;

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
   };


   struct Shape
   {
      Shape() = default;
      Shape( const Shape& ) = default;
      Shape( Shape&& ) = default;
      virtual ~Shape() {}
      Shape& operator=( const Shape& ) = default;
      Shape& operator=( Shape&& ) = default;

      virtual void accept( const Visitor& v ) = 0;
   };


#if BENCHMARK_WITH_CIRCLE
   struct Circle : public Shape
   {
      explicit Circle( double r )
         : radius{ r }
      {}

      void accept( const Visitor& v ) override { v.visit(*this); }

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

      void accept( const Visitor& v ) override { v.visit(*this); }

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

      void accept( const Visitor& v ) override { v.visit(*this); }

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

      void accept( const Visitor& v ) override { v.visit(*this); }

      double width{};
      double height{};
      Vector2D center{};
   };
#endif


   struct Translate : public Visitor
   {
      Translate( const Vector2D& vec ) : v{ vec } {}
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
      Vector2D v{};
   };


   using Shapes = std::vector< std::unique_ptr<Shape> >;

   void translate( Shapes const& shapes, const Vector2D& v )
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


   struct AbstractVisitor
   {
      AbstractVisitor() = default;
      AbstractVisitor( const AbstractVisitor& ) = default;
      AbstractVisitor( AbstractVisitor&& ) = default;
      virtual ~AbstractVisitor() = default;
      AbstractVisitor& operator=( const AbstractVisitor& ) = default;
      AbstractVisitor& operator=( AbstractVisitor&& ) = default;
   };


   struct Shape
   {
      Shape() = default;
      Shape( const Shape& ) = default;
      Shape( Shape&& ) = default;
      virtual ~Shape() {}
      Shape& operator=( const Shape& ) = default;
      Shape& operator=( Shape&& ) = default;

      virtual void accept( const AbstractVisitor& v ) = 0;
   };


   template< typename T >
   struct Visitor
   {
      Visitor() = default;
      Visitor( const Visitor& ) = default;
      Visitor( Visitor&& ) = default;
      virtual ~Visitor() = default;
      Visitor& operator=( const Visitor& ) = default;
      Visitor& operator=( Visitor&& ) = default;

      virtual void visit( T& ) const = 0;
   };


#if BENCHMARK_WITH_CIRCLE
   struct Circle : public Shape
   {
      explicit Circle( double r )
         : radius{ r }
      {}

      void accept( const AbstractVisitor& v ) override {
         if( auto cv = dynamic_cast<const Visitor<Circle>*>(&v) ) {
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

      void accept( const AbstractVisitor& v ) override {
         if( auto ev = dynamic_cast<const Visitor<Ellipse>*>(&v) ) {
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

      void accept( const AbstractVisitor& v ) override {
         if( auto sv = dynamic_cast<const Visitor<Square>*>(&v) ) {
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

      void accept( const AbstractVisitor& v ) override {
         if( auto rv = dynamic_cast<const Visitor<Rectangle>*>(&v) ) {
            rv->visit(*this);
         }
      }

      double width{};
      double height{};
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
   {
      Translate( const Vector2D& vec ) : v{ vec } {}
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
      Vector2D v{};
   };


   using Shapes = std::vector< std::unique_ptr<Shape> >;

   void translate( Shapes const& shapes, const Vector2D& v )
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
      Vector2D v{};
   };

   void translate( Shape& s, const Vector2D& v )
   {
      /*
#if BENCHMARK_WITH_CIRCLE
      if( Circle* circle = std::get_if<Circle>(&s) ) {
         circle->center = circle->center + v;
         return;
      }
#endif
#if BENCHMARK_WITH_ELLIPSE
      if( Ellipse* ellipse = std::get_if<Ellipse>(&s) ) {
         ellipse->center = ellipse->center + v;
         return;
      }
#endif
#if BENCHMARK_WITH_SQUARE
      if( Square* square = std::get_if<Square>(&s) ) {
         square->center = square->center + v;
         return;
      }
#endif
#if BENCHMARK_WITH_RECTANGLE
      if( Rectangle* rectangle = std::get_if<Rectangle>(&s) ) {
         rectangle->center = rectangle->center + v;
         return;
      }
#endif
      */

      std::visit( Translate{ v }, s );
   }


   using Shapes = std::vector<Shape>;

   void translate( Shapes& shapes, const Vector2D& v )
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
      Vector2D v{};
   };

   void translate( Shape& s, const Vector2D& v )
   {
      mpark::visit( Translate{ v }, s );
   }


   using Shapes = std::vector<Shape>;

   void translate( Shapes& shapes, const Vector2D& v )
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
      Vector2D v{};
   };

   void translate( Shape& s, const Vector2D& v )
   {
      boost::apply_visitor( Translate{ v }, s );
   }


   using Shapes = std::vector<Shape>;

   void translate( Shapes& shapes, const Vector2D& v )
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
   const unsigned int seed( rd() );

   std::mt19937 rng{};
   std::uniform_real_distribution<double> dist( 0.0, 1.0 );

   std::cout << std::endl;

#if BENCHMARK_ENUM_SOLUTION
   {
      using namespace enum_solution;

      rng.seed( seed );

      Shapes shapes;

      while( shapes.size() < N )
      {
         const double r( dist(rng) );

         if( r < 0.25 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( std::make_unique<Circle>( dist(rng) ) );
#endif
         }
         else if( r < 0.5 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( std::make_unique<Ellipse>( dist(rng), dist(rng) ) );
#endif
         }
         else if( r < 0.75 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( std::make_unique<Square>( dist(rng) ) );
#endif
         }
         else {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( std::make_unique<Rectangle>( dist(rng), dist(rng) ) );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

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
         const double r( dist(rng) );

         if( r < 0.25 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( std::make_unique<Circle>( dist(rng) ) );
#endif
         }
         else if( r < 0.5 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( std::make_unique<Ellipse>( dist(rng), dist(rng) ) );
#endif
         }
         else if( r < 0.75 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( std::make_unique<Square>( dist(rng) ) );
#endif
         }
         else {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( std::make_unique<Rectangle>( dist(rng), dist(rng) ) );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

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
         const double r( dist(rng) );

         if( r < 0.25 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( std::make_unique<Circle>( dist(rng) ) );
#endif
         }
         else if( r < 0.5 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( std::make_unique<Ellipse>( dist(rng), dist(rng) ) );
#endif
         }
         else if( r < 0.75 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( std::make_unique<Square>( dist(rng) ) );
#endif
         }
         else {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( std::make_unique<Rectangle>( dist(rng), dist(rng) ) );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

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
         const double r( dist(rng) );

         if( r < 0.25 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( std::make_unique<Circle>( dist(rng) ) );
#endif
         }
         else if( r < 0.5 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( std::make_unique<Ellipse>( dist(rng), dist(rng) ) );
#endif
         }
         else if( r < 0.75 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( std::make_unique<Square>( dist(rng) ) );
#endif
         }
         else {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( std::make_unique<Rectangle>( dist(rng), dist(rng) ) );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

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
         const double r( dist(rng) );

         if( r < 0.25 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( Circle{ dist(rng) } );
#endif
         }
         else if( r < 0.25 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( Ellipse{ dist(rng), dist(rng) } );
#endif
         }
         else if( r < 0.75 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( Square{ dist(rng) } );
#endif
         }
         else {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( Rectangle{ dist(rng), dist(rng) } );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

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
         const double r( dist(rng) );

         if( r < 0.25 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( Circle{ dist(rng) } );
#endif
         }
         else if( r < 0.25 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( Ellipse{ dist(rng), dist(rng) } );
#endif
         }
         else if( r < 0.75 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( Square{ dist(rng) } );
#endif
         }
         else {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( Rectangle{ dist(rng), dist(rng) } );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

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
         const double r( dist(rng) );

         if( r < 0.25 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( Circle{ dist(rng) } );
#endif
         }
         else if( r < 0.25 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( Ellipse{ dist(rng), dist(rng) } );
#endif
         }
         else if( r < 0.75 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( Square{ dist(rng) } );
#endif
         }
         else {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( Rectangle{ dist(rng), dist(rng) } );
#endif
         }
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

      std::cout << " boost::variant solution runtime : " << seconds << "s\n";
   }
#endif

   std::cout << std::endl;

   return EXIT_SUCCESS;
}

