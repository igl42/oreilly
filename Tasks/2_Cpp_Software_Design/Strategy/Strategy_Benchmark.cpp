/**************************************************************************************************
*
* \file Strategy_Benchmark.cpp
* \brief C++ Training - Programming Task for the Strategy Design Pattern
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
**************************************************************************************************/

#define BENCHMARK_OO_SOLUTION 1
#define BENCHMARK_STRATEGY_SOLUTION 1
#define BENCHMARK_STD_FUNCTION_SOLUTION 1
#define BENCHMARK_BOOST_FUNCTION_SOLUTION 0
#define BENCHMARK_MANUAL_FUNCTION_SOLUTION 1
#define BENCHMARK_TYPE_ERASURE_SOLUTION 1
#define BENCHMARK_TYPE_ERASURE_SBO_SOLUTION 0
#define BENCHMARK_TYPE_ERASURE_MANUAL_SOLUTION 0
#define BENCHMARK_TYPE_ERASURE_DYNO_SOLUTION 0


#define BENCHMARK_WITH_CIRCLE 1
#define BENCHMARK_WITH_ELLIPSE 1
#define BENCHMARK_WITH_SQUARE 1
#define BENCHMARK_WITH_RECTANGLE 1
#define BENCHMARK_WITH_PENTAGON 1
#define BENCHMARK_WITH_HEXAGON 1


#include <array>
#include <chrono>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <random>
#include <type_traits>
#include <utility>
#include <vector>
#if BENCHMARK_BOOST_FUNCTION_SOLUTION
#  include <boost/function.hpp>
#endif
#if BENCHMARK_TYPE_ERASURE_DYNO_SOLUTION
#  include <dyno.hpp>
using namespace dyno::literals;
#endif

#if _MSC_VER && !__INTEL_COMPILER
#  define _ENABLE_EXTENDED_ALIGNED_STORAGE
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


#if BENCHMARK_OO_SOLUTION
namespace object_oriented_solution {

   struct Shape
   {
      virtual ~Shape() = default;
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


   using Shapes = std::vector<std::unique_ptr<Shape>>;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto const& shape : shapes )
      {
         shape->translate( v );
      }
   }

} // namespace object_oriented_solution
#endif


#if BENCHMARK_STRATEGY_SOLUTION
namespace strategy_solution {

   template< typename ShapeT >
   struct TranslateStrategy
   {
      virtual ~TranslateStrategy() = default;
      virtual void translate( ShapeT& shape, Vector2D const& v ) const = 0;
   };


   struct Shape
   {
      virtual ~Shape() = default;
      virtual void translate( Vector2D const& v ) = 0;
   };


#if BENCHMARK_WITH_CIRCLE
   struct Circle : public Shape
   {
      Circle( double r, std::unique_ptr<TranslateStrategy<Circle>>&& ts )
         : radius{ r }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy->translate( *this, v ); }

      double radius{};
      Vector2D center{};
      std::unique_ptr<TranslateStrategy<Circle>> strategy{};
   };
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse : public Shape
   {
      Ellipse( double r1, double r2, std::unique_ptr<TranslateStrategy<Ellipse>>&& ts )
         : radius1{ r1 }
         , radius2{ r2 }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy->translate( *this, v ); }

      double radius1{};
      double radius2{};
      Vector2D center{};
      std::unique_ptr<TranslateStrategy<Ellipse>> strategy{};
   };
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square : public Shape
   {
      Square( double s, std::unique_ptr<TranslateStrategy<Square>>&& ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy->translate( *this, v ); }

      double side{};
      Vector2D center{};
      std::unique_ptr<TranslateStrategy<Square>> strategy{};
   };
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle : public Shape
   {
      Rectangle( double w, double h, std::unique_ptr<TranslateStrategy<Rectangle>>&& ts )
         : width{ w }
         , height{ h }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy->translate( *this, v ); }

      double width{};
      double height{};
      Vector2D center{};
      std::unique_ptr<TranslateStrategy<Rectangle>> strategy{};
   };
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon : public Shape
   {
      Pentagon( double s, std::unique_ptr<TranslateStrategy<Pentagon>>&& ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy->translate( *this, v ); }

      double side{};
      Vector2D center{};
      std::unique_ptr<TranslateStrategy<Pentagon>> strategy{};
   };
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon : public Shape
   {
      Hexagon( double s, std::unique_ptr<TranslateStrategy<Hexagon>>&& ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy->translate( *this, v ); }

      double side{};
      Vector2D center{};
      std::unique_ptr<TranslateStrategy<Hexagon>> strategy{};
   };
#endif


   template< typename ShapeT >
   struct ConcreteTranslateStrategy : public TranslateStrategy<ShapeT>
   {
      void translate( ShapeT& shape, Vector2D const& v ) const override
      {
         shape.center = shape.center + v;
      }
   };


   using Shapes = std::vector<std::unique_ptr<Shape>>;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto& shape : shapes )
      {
         shape->translate( v );
      }
   }

} // namespace strategy_solution
#endif


#if BENCHMARK_STD_FUNCTION_SOLUTION
namespace std_function_solution {

   struct Shape
   {
      virtual ~Shape() = default;
      virtual void translate( Vector2D const& v ) = 0;
   };


#if BENCHMARK_WITH_CIRCLE
   struct Circle : public Shape
   {
      using TranslateStrategy = std::function<void(Circle&, Vector2D const&)>;

      Circle( double r, TranslateStrategy ts )
         : radius{ r }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double radius{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Circle& circle, Vector2D const& v )
   {
      circle.center = circle.center + v;
   }
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse : public Shape
   {
      using TranslateStrategy = std::function<void(Ellipse&, Vector2D const&)>;

      Ellipse( double r1, double r2, TranslateStrategy ts )
         : radius1{ r1 }
         , radius2{ r2 }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double radius1{};
      double radius2{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Ellipse& ellipse, Vector2D const& v )
   {
      ellipse.center = ellipse.center + v;
   }
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square : public Shape
   {
      using TranslateStrategy = std::function<void(Square&, Vector2D const&)>;

      Square( double s, TranslateStrategy ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double side{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Square& square, Vector2D const& v )
   {
      square.center = square.center + v;
   }
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle : public Shape
   {
      using TranslateStrategy = std::function<void(Rectangle&, Vector2D const&)>;

      Rectangle( double w, double h, TranslateStrategy ts )
         : width{ w }
         , height{ h }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double width{};
      double height{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Rectangle& rectangle, Vector2D const& v )
   {
      rectangle.center = rectangle.center + v;
   }
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon : public Shape
   {
      using TranslateStrategy = std::function<void(Pentagon&, Vector2D const&)>;

      Pentagon( double s, TranslateStrategy ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double side{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Pentagon& pentagon, Vector2D const& v )
   {
      pentagon.center = pentagon.center + v;
   }
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon : public Shape
   {
      using TranslateStrategy = std::function<void(Hexagon&, Vector2D const&)>;

      Hexagon( double s, TranslateStrategy ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double side{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Hexagon& hexagon, Vector2D const& v )
   {
      hexagon.center = hexagon.center + v;
   }
#endif


   struct Translate {
      template< typename T >
      void operator()( T& t, Vector2D const& v )
      {
         translate( t, v );
      }
   };


   using Shapes = std::vector<std::unique_ptr<Shape>>;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto& shape : shapes )
      {
         shape->translate( v );
      }
   }

} // namespace std_function_solution
#endif


#if BENCHMARK_BOOST_FUNCTION_SOLUTION
namespace boost_function_solution {

   struct Shape
   {
      virtual ~Shape() = default;
      virtual void translate( Vector2D const& v ) = 0;
   };


#if BENCHMARK_WITH_CIRCLE
   struct Circle : public Shape
   {
      using TranslateStrategy = boost::function<void(Circle&, Vector2D const&)>;

      Circle( double r, TranslateStrategy ts )
         : radius{ r }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double radius{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Circle& circle, Vector2D const& v )
   {
      circle.center = circle.center + v;
   }
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse : public Shape
   {
      using TranslateStrategy = boost::function<void(Ellipse&, Vector2D const&)>;

      Ellipse( double r1, double r2, TranslateStrategy ts )
         : radius1{ r1 }
         , radius2{ r2 }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double radius1{};
      double radius2{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Ellipse& ellipse, Vector2D const& v )
   {
      ellipse.center = ellipse.center + v;
   }
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square : public Shape
   {
      using TranslateStrategy = boost::function<void(Square&, Vector2D const&)>;

      Square( double s, TranslateStrategy ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double side{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Square& square, Vector2D const& v )
   {
      square.center = square.center + v;
   }
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle : public Shape
   {
      using TranslateStrategy = boost::function<void(Rectangle&, Vector2D const&)>;

      Rectangle( double w, double h, TranslateStrategy ts )
         : width{ w }
         , height{ h }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double width{};
      double height{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Rectangle& rectangle, Vector2D const& v )
   {
      rectangle.center = rectangle.center + v;
   }
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon : public Shape
   {
      using TranslateStrategy = boost::function<void(Pentagon&, Vector2D const&)>;

      Pentagon( double s, TranslateStrategy ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double side{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Pentagon& pentagon, Vector2D const& v )
   {
      pentagon.center = pentagon.center + v;
   }
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon : public Shape
   {
      using TranslateStrategy = boost::function<void(Hexagon&, Vector2D const&)>;

      Hexagon( double s, TranslateStrategy ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double side{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Hexagon& hexagon, Vector2D const& v )
   {
      hexagon.center = hexagon.center + v;
   }
#endif


   struct Translate {
      template< typename T >
      void operator()( T& t, Vector2D const& v )
      {
         translate( t, v );
      }
   };


   using Shapes = std::vector<std::unique_ptr<Shape>>;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto& shape : shapes )
      {
         shape->translate( v );
      }
   }

} // namespace boost_function_solution
#endif


#if BENCHMARK_MANUAL_FUNCTION_SOLUTION
namespace manual_function_solution {

   template< typename Fn, size_t N >
   class Function;

   template< typename R, typename... Args, size_t N >
   class Function<R(Args...),N>
   {
    public:
      template< typename Fn >
      Function( Fn fn )
         : pimpl_{ reinterpret_cast<Concept*>( buffer ) }
      {
         static_assert( sizeof(Fn) <= N, "Given type is too large" );
         new (pimpl_) Model<Fn>( fn );
      }

      Function( Function const& f )
         : pimpl_{ reinterpret_cast<Concept*>( buffer ) }
      {
         f.pimpl_->clone( pimpl_ );
      }

      Function& operator=( Function f )
      {
         pimpl_->~Concept();
         f.pimpl_->clone( pimpl_ );
         return *this;
      }

      ~Function() { pimpl_->~Concept(); }

      R operator()( Args... args ) { return (*pimpl_)( std::forward<Args>( args )... ); }

    private:
      class Concept
      {
       public:
         virtual ~Concept() = default;
         virtual R operator()( Args... ) const = 0;
         virtual void clone( Concept* memory ) const = 0;
      };

      template< typename Fn >
      class Model : public Concept
      {
       public:
         explicit Model( Fn fn )
            : fn_{ fn }
         {}

         R operator()( Args... args ) const override { return fn_( std::forward<Args>( args )... ); }
         void clone( Concept* memory ) const override { new (memory) Model( fn_ ); }

       private:
         Fn fn_{};
      };

      Concept* pimpl_{ nullptr };

      char buffer[N+8UL];
   };


   struct Shape
   {
      virtual ~Shape() = default;
      virtual void translate( Vector2D const& v ) = 0;
   };


#if BENCHMARK_WITH_CIRCLE
   struct Circle : public Shape
   {
      using TranslateStrategy = Function<void(Circle&, Vector2D const&),8UL>;

      Circle( double r, TranslateStrategy ts )
         : radius{ r }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double radius{};
      Vector2D center{};
      TranslateStrategy strategy;
   };

   void translate( Circle& circle, Vector2D const& v )
   {
      circle.center = circle.center + v;
   }
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse : public Shape
   {
      using TranslateStrategy = Function<void(Ellipse&, Vector2D const&),8UL>;

      Ellipse( double r1, double r2, TranslateStrategy ts )
         : radius1{ r1 }
         , radius2{ r2 }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double radius1{};
      double radius2{};
      Vector2D center{};
      TranslateStrategy strategy;
   };

   void translate( Ellipse& ellipse, Vector2D const& v )
   {
      ellipse.center = ellipse.center + v;
   }
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square : public Shape
   {
      using TranslateStrategy = Function<void(Square&, Vector2D const&),8UL>;

      Square( double s, TranslateStrategy ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double side{};
      Vector2D center{};
      TranslateStrategy strategy;
   };

   void translate( Square& square, Vector2D const& v )
   {
      square.center = square.center + v;
   }
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle : public Shape
   {
      using TranslateStrategy = Function<void(Rectangle&, Vector2D const&),8UL>;

      Rectangle( double w, double h, TranslateStrategy ts )
         : width{ w }
         , height{ h }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double width{};
      double height{};
      Vector2D center{};
      TranslateStrategy strategy;
   };

   void translate( Rectangle& rectangle, Vector2D const& v )
   {
      rectangle.center = rectangle.center + v;
   }
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon : public Shape
   {
      using TranslateStrategy = Function<void(Pentagon&, Vector2D const&),8UL>;

      Pentagon( double s, TranslateStrategy ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double side{};
      Vector2D center{};
      TranslateStrategy strategy;
   };

   void translate( Pentagon& pentagon, Vector2D const& v )
   {
      pentagon.center = pentagon.center + v;
   }
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon : public Shape
   {
      using TranslateStrategy = Function<void(Hexagon&, Vector2D const&),8UL>;

      Hexagon( double s, TranslateStrategy ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( Vector2D const& v ) override { strategy( *this, v ); }

      double side{};
      Vector2D center{};
      TranslateStrategy strategy;
   };

   void translate( Hexagon& hexagon, Vector2D const& v )
   {
      hexagon.center = hexagon.center + v;
   }
#endif


   struct Translate {
      template< typename T >
      void operator()( T& t, Vector2D const& v ) const
      {
         translate( t, v );
      }
   };


   using Shapes = std::vector<std::unique_ptr<Shape>>;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto& shape : shapes )
      {
         shape->translate( v );
      }
   }

} // namespace manual_function_solution
#endif


#if BENCHMARK_TYPE_ERASURE_SOLUTION
namespace type_erasure_solution {

#if BENCHMARK_WITH_CIRCLE
   struct Circle
   {
      double radius{};
      Vector2D center{};
   };

   void translate( Circle& circle, Vector2D const& v )
   {
      circle.center = circle.center + v;
   }
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse
   {
      double radius1{};
      double radius2{};
      Vector2D center{};
   };

   void translate( Ellipse& ellipse, Vector2D const& v )
   {
      ellipse.center = ellipse.center + v;
   }
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square
   {
      double side{};
      Vector2D center{};
   };

   void translate( Square& square, Vector2D const& v )
   {
      square.center = square.center + v;
   }
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle
   {
      double width{};
      double height{};
      Vector2D center{};
   };

   void translate( Rectangle& rect, Vector2D const& v )
   {
      rect.center = rect.center + v;
   }
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon
   {
      double side{};
      Vector2D center{};
   };

   void translate( Pentagon& pentagon, Vector2D const& v )
   {
      pentagon.center = pentagon.center + v;
   }
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon
   {
      double side{};
      Vector2D center{};
   };

   void translate( Hexagon& hexagon, Vector2D const& v )
   {
      hexagon.center = hexagon.center + v;
   }
#endif


   class Shape
   {
    public:
      template< typename T >
      Shape( T const& shape )
         : pimpl_{ new Model<T>( shape ) }
      {}

      Shape( Shape const& s ) : pimpl_{ s.pimpl_->clone() } {}
      Shape( Shape&& ) = default;
      ~Shape() = default;
      Shape& operator=( Shape const& s ) { Shape tmp( s ); std::swap( pimpl_, tmp.pimpl_ ); return *this; }
      Shape& operator=( Shape&& ) = default;

    private:
      struct Concept
      {
         virtual ~Concept() = default;
         virtual Concept* clone() const = 0;
         virtual void doTranslate( Vector2D const& ) = 0;
      };

      template< typename T >
      struct Model : public Concept
      {
         explicit Model( T const& shape ) : shape_( shape ) {}
         Concept* clone() const override { return new Model(*this); }
         void doTranslate( Vector2D const& v ) override { translate( shape_, v ); }
         T shape_;
      };

      friend void translate( Shape& s, Vector2D const& v )
      {
         s.pimpl_->doTranslate( v );
      }

      std::unique_ptr<Concept> pimpl_{};
   };

   using Shapes = std::vector<Shape>;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto& shape : shapes )
      {
         translate( shape, v );
      }
   }

} // namespace type_erasure_solution
#endif


#if BENCHMARK_TYPE_ERASURE_SBO_SOLUTION
namespace type_erasure_sbo_solution {

constexpr size_t maxsize( 32UL );

#if BENCHMARK_WITH_CIRCLE
   struct Circle
   {
      double radius{};
      Vector2D center{};
   };

   void translate( Circle& circle, Vector2D const& v )
   {
      circle.center = circle.center + v;
   }

   static_assert( sizeof(Circle) <= maxsize );
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse
   {
      double radius1{};
      double radius2{};
      Vector2D center{};
   };

   void translate( Ellipse& ellipse, Vector2D const& v )
   {
      ellipse.center = ellipse.center + v;
   }

   static_assert( sizeof(Ellipse) <= maxsize );
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square
   {
      double side{};
      Vector2D center{};
   };

   void translate( Square& square, Vector2D const& v )
   {
      square.center = square.center + v;
   }

   static_assert( sizeof(Square) <= maxsize );
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle
   {
      double width{};
      double height{};
      Vector2D center{};
   };

   void translate( Rectangle& rectangle, Vector2D const& v )
   {
      rectangle.center = rectangle.center + v;
   }

   static_assert( sizeof(Rectangle) <= maxsize );
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon
   {
      double side{};
      Vector2D center{};
   };

   void translate( Pentagon& pentagon, Vector2D const& v )
   {
      pentagon.center = pentagon.center + v;
   }

   static_assert( sizeof(Pentagon) <= maxsize );
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon
   {
      double side{};
      Vector2D center{};
   };

   void translate( Hexagon& hexagon, Vector2D const& v )
   {
      hexagon.center = hexagon.center + v;
   }

   static_assert( sizeof(Hexagon) <= maxsize );
#endif


   template< size_t Capacity, size_t Alignment >
   class Shape
   {
    private:
      struct Concept
      {
         virtual ~Concept() = default;
         virtual void clone( Concept* ) const = 0;
         virtual void doTranslate( Vector2D const& ) = 0;
      };

      template< typename T >
      struct Model : public Concept
      {
         explicit Model( T const& shape ) : shape_( shape ) {}
         void clone( Concept* ptr ) const override { new (ptr) Model(*this); }
         void doTranslate( Vector2D const& v ) override { translate( shape_, v ); }
         T shape_{};
      };

    public:
      template< typename T >
      Shape( T const& shape )
         // data_ intentionally not initialized
      {
         new ( pimpl() ) Model<T>( shape );
      }

      Shape( Shape const& s ) { s.pimpl()->clone( pimpl() ); }
      ~Shape() { pimpl()->~Concept(); }
      Shape& operator=( Shape const& s ) { pimpl()->~Concept(); s.pimpl()->clone( pimpl() ); return *this; }

    private:
      Concept* pimpl()
      {
         return reinterpret_cast<Concept*>( data_.data() );
      };

      Concept const* pimpl() const
      {
         return reinterpret_cast<Concept const*>( data_.data() );
      };

      friend void translate( Shape& s, Vector2D const& v )
      {
         s.pimpl()->doTranslate( v );
      }

      alignas(Alignment) std::array<std::byte,Capacity+8UL> data_;
   };

   using Shapes = std::vector<Shape<maxsize,16UL>>;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto& shape : shapes )
      {
         translate( shape, v );
      }
   }

} // namespace type_erasure_sbo_solution
#endif


#if BENCHMARK_TYPE_ERASURE_MANUAL_SOLUTION
namespace type_erasure_manual_solution {

#if BENCHMARK_WITH_CIRCLE
   struct Circle
   {
      double radius{};
      Vector2D center{};
   };

   void translate( Circle& circle, Vector2D const& v )
   {
      circle.center = circle.center + v;
   }
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse
   {
      double radius1{};
      double radius2{};
      Vector2D center{};
   };

   void translate( Ellipse& ellipse, Vector2D const& v )
   {
      ellipse.center = ellipse.center + v;
   }
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square
   {
      double side{};
      Vector2D center{};
   };

   void translate( Square& square, Vector2D const& v )
   {
      square.center = square.center + v;
   }
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle
   {
      double width{};
      double height{};
      Vector2D center{};
   };

   void translate( Rectangle& rect, Vector2D const& v )
   {
      rect.center = rect.center + v;
   }
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon
   {
      double side{};
      Vector2D center{};
   };

   void translate( Pentagon& pentagon, Vector2D const& v )
   {
      pentagon.center = pentagon.center + v;
   }
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon
   {
      double side{};
      Vector2D center{};
   };

   void translate( Hexagon& hexagon, Vector2D const& v )
   {
      hexagon.center = hexagon.center + v;
   }
#endif


   class Shape
   {
    public:
      template< typename T >
      Shape( T const& x )
         : translate_( []( Concept* c, Vector2D const& v ){ auto model( static_cast<Model<T>*>(c) ); translate( model->object, v ); } )
         , clone_    ( []( Concept* c ){ auto model( static_cast<Model<T>*>(c) ); return static_cast<Concept*>( new Model<T>( *model ) ); } )
         , destroy_  ( []( Concept* c ){ auto model( static_cast<Model<T>*>(c) ); delete model; } )
         , pimpl_    ( new Model<T>( x ) )
      {}

      Shape( Shape const& s )
         : translate_( s.translate_ )
         , clone_    ( s.clone_ )
         , destroy_  ( s.destroy_ )
         , pimpl_    ( clone_( s.pimpl_ ) )
      {}

      Shape( Shape&& s )
         : translate_( std::exchange( s.translate_, nullptr ) )
         , clone_    ( std::exchange( s.clone_    , nullptr ) )
         , destroy_  ( std::exchange( s.destroy_  , nullptr ) )
         , pimpl_    ( std::exchange( s.pimpl_    , nullptr ) )
      {}

      ~Shape()
      {
         if( pimpl_ ) {
            destroy_( pimpl_ );
         }
      }

      Shape& operator=( Shape s )
      {
         swap( s );
         return *this;
      }

      void swap( Shape& s )
      {
         std::swap( translate_, s.translate_ );
         std::swap( clone_, s.clone_ );
         std::swap( destroy_, s.destroy_ );
         std::swap( pimpl_, s.pimpl_ );
      }

    private:
      friend void translate( Shape& s, Vector2D const& v )
      {
         s.translate_( s.pimpl_, v );
      }

      struct Concept
      {};

      template< typename T >
      struct Model : Concept
      {
         Model( T const& value ) : object( value ) {}
         T object;
      };

      void (*translate_)( Concept*, Vector2D const& ){};
      Concept* (*clone_)( Concept* ){};
      void (*destroy_)( Concept* ){};
      Concept* pimpl_{};
   };

   using Shapes = std::vector<Shape>;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto& shape : shapes )
      {
         translate( shape, v );
      }
   }

} // namespace type_erasure_manual_solution
#endif


#if BENCHMARK_TYPE_ERASURE_DYNO_SOLUTION

struct ShapeConcept : decltype( dyno::requires_(
   dyno::CopyConstructible{},
   dyno::MoveConstructible{},
   dyno::Destructible{},
   "translate"_s = dyno::function<void (dyno::T&, Vector2D const&)>
)) { };

template <typename T>
auto const dyno::default_concept_map<ShapeConcept, T> = dyno::make_concept_map(
   "translate"_s = []( T& self, Vector2D const& v ) { translate( self, v ); }
);

namespace type_erasure_dyno_solution {

#if BENCHMARK_WITH_CIRCLE
   struct Circle
   {
      double radius{};
      Vector2D center{};
   };

   void translate( Circle& circle, Vector2D const& v )
   {
      circle.center = circle.center + v;
   }
#endif


#if BENCHMARK_WITH_ELLIPSE
   struct Ellipse
   {
      double radius1{};
      double radius2{};
      Vector2D center{};
   };

   void translate( Ellipse& ellipse, Vector2D const& v )
   {
      ellipse.center = ellipse.center + v;
   }
#endif


#if BENCHMARK_WITH_SQUARE
   struct Square
   {
      double side{};
      Vector2D center{};
   };

   void translate( Square& square, Vector2D const& v )
   {
      square.center = square.center + v;
   }
#endif


#if BENCHMARK_WITH_RECTANGLE
   struct Rectangle
   {
      double width{};
      double height{};
      Vector2D center{};
   };

   void translate( Rectangle& rectangle, Vector2D const& v )
   {
      rectangle.center = rectangle.center + v;
   }
#endif


#if BENCHMARK_WITH_PENTAGON
   struct Pentagon
   {
      double side{};
      Vector2D center{};
   };

   void translate( Pentagon& pentagon, Vector2D const& v )
   {
      pentagon.center = pentagon.center + v;
   }
#endif


#if BENCHMARK_WITH_HEXAGON
   struct Hexagon
   {
      double side{};
      Vector2D center{};
   };

   void translate( Hexagon& hexagon, Vector2D const& v )
   {
      hexagon.center = hexagon.center + v;
   }
#endif


   class Shape
   {
    public:
      template <typename T>
      Shape( T x ) : poly_{x} { }

      void translate( Vector2D const& v )
      { poly_.virtual_( "translate"_s )( poly_, v ); }

    private:
      dyno::poly<ShapeConcept> poly_;
   };

   void translate( Shape& shape, Vector2D const& v )
   {
      shape.translate( v );
   }


   using Shapes = std::vector<Shape>;

   void translate( Shapes& shapes, Vector2D const& v )
   {
      for( auto& shape : shapes )
      {
         translate( shape, v );
      }
   }

} // namespace type_erasure_dyno_solution
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

#if BENCHMARK_OO_SOLUTION
   {
      using namespace object_oriented_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         double const random_value( int_dist(rng) );

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
         else if( random_value == 4) {
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

      std::cout << " OO solution runtime                  : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_STRATEGY_SOLUTION
   {
      using namespace strategy_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         double const random_value( int_dist(rng) );

         if( random_value == 1 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back(
               std::make_unique<Circle>( real_dist(rng)
                  , std::make_unique<ConcreteTranslateStrategy<Circle>>() ) );
#endif
         }
         else if( random_value == 2 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back(
               std::make_unique<Ellipse>( real_dist(rng), real_dist(rng)
                  , std::make_unique<ConcreteTranslateStrategy<Ellipse>>() ) );
#endif
         }
         else if( random_value == 3 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back(
               std::make_unique<Square>( real_dist(rng)
                  , std::make_unique<ConcreteTranslateStrategy<Square>>() ) );
#endif
         }
         else if( random_value == 4 ) {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back(
               std::make_unique<Rectangle>( real_dist(rng), real_dist(rng)
                  , std::make_unique<ConcreteTranslateStrategy<Rectangle>>() ) );
#endif
         }
         else if( random_value == 5 ) {
#if BENCHMARK_WITH_PENTAGON
            shapes.emplace_back(
               std::make_unique<Pentagon>( real_dist(rng)
                  , std::make_unique<ConcreteTranslateStrategy<Pentagon>>() ) );
#endif
         }
         else {
#if BENCHMARK_WITH_HEXAGON
            shapes.emplace_back(
               std::make_unique<Hexagon>( real_dist(rng)
                  , std::make_unique<ConcreteTranslateStrategy<Hexagon>>() ) );
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

      std::cout << " Classic strategy solution runtime    : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_STD_FUNCTION_SOLUTION
   {
      using namespace std_function_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         double const random_value( int_dist(rng) );

         if( random_value == 1 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( std::make_unique<Circle>( real_dist(rng), Translate{} ) );
#endif
         }
         else if( random_value == 2 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( std::make_unique<Ellipse>( real_dist(rng), real_dist(rng), Translate{} ) );
#endif
         }
         else if( random_value == 3 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( std::make_unique<Square>( real_dist(rng), Translate{} ) );
#endif
         }
         else if( random_value == 4 ) {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( std::make_unique<Rectangle>( real_dist(rng), real_dist(rng), Translate{} ) );
#endif
         }
         else if( random_value == 5 ) {
#if BENCHMARK_WITH_PENTAGON
            shapes.emplace_back( std::make_unique<Pentagon>( real_dist(rng), Translate{} ) );
#endif
         }
         else {
#if BENCHMARK_WITH_HEXAGON
            shapes.emplace_back( std::make_unique<Hexagon>( real_dist(rng), Translate{} ) );
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

      std::cout << " std::function solution runtime       : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_BOOST_FUNCTION_SOLUTION
   {
      using namespace boost_function_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         double const random_value( int_dist(rng) );

         if( random_value == 1 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( std::make_unique<Circle>( real_dist(rng), Translate{} ) );
#endif
         }
         else if( random_value == 2 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( std::make_unique<Ellipse>( real_dist(rng), real_dist(rng), Translate{} ) );
#endif
         }
         else if( random_value == 3 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( std::make_unique<Square>( real_dist(rng), Translate{} ) );
#endif
         }
         else if( random_value == 4 ) {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( std::make_unique<Rectangle>( real_dist(rng), real_dist(rng), Translate{} ) );
#endif
         }
         else if( random_value == 5 ) {
#if BENCHMARK_WITH_PENTAGON
            shapes.emplace_back( std::make_unique<Pentagon>( real_dist(rng), Translate{} ) );
#endif
         }
         else {
#if BENCHMARK_WITH_HEXAGON
            shapes.emplace_back( std::make_unique<Hexagon>( real_dist(rng), Translate{} ) );
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

      std::cout << " boost::function solution runtime     : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_MANUAL_FUNCTION_SOLUTION
   {
      using namespace manual_function_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         double const random_value( int_dist(rng) );

         if( random_value == 1 ) {
#if BENCHMARK_WITH_CIRCLE
            shapes.emplace_back( std::make_unique<Circle>( real_dist(rng), Translate{} ) );
#endif
         }
         else if( random_value == 2 ) {
#if BENCHMARK_WITH_ELLIPSE
            shapes.emplace_back( std::make_unique<Ellipse>( real_dist(rng), real_dist(rng), Translate{} ) );
#endif
         }
         else if( random_value == 3 ) {
#if BENCHMARK_WITH_SQUARE
            shapes.emplace_back( std::make_unique<Square>( real_dist(rng), Translate{} ) );
#endif
         }
         else if( random_value == 4 ) {
#if BENCHMARK_WITH_RECTANGLE
            shapes.emplace_back( std::make_unique<Rectangle>( real_dist(rng), real_dist(rng), Translate{} ) );
#endif
         }
         else if( random_value == 5 ) {
#if BENCHMARK_WITH_PENTAGON
            shapes.emplace_back( std::make_unique<Pentagon>( real_dist(rng), Translate{} ) );
#endif
         }
         else {
#if BENCHMARK_WITH_HEXAGON
            shapes.emplace_back( std::make_unique<Hexagon>( real_dist(rng), Translate{} ) );
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

      std::cout << " Manual function solution runtime     : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_TYPE_ERASURE_SOLUTION
   {
      using namespace type_erasure_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         double const random_value( int_dist(rng) );

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

      std::cout << " Type erasure solution runtime        : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_TYPE_ERASURE_SBO_SOLUTION
   {
      using namespace type_erasure_sbo_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         double const random_value( int_dist(rng) );

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

      std::cout << " Type erasure SBO solution runtime    : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_TYPE_ERASURE_MANUAL_SOLUTION
   {
      using namespace type_erasure_manual_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         double const random_value( int_dist(rng) );

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

      std::cout << " Type erasure manual solution runtime : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_TYPE_ERASURE_DYNO_SOLUTION
   {
      using namespace type_erasure_dyno_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         double const random_value( int_dist(rng) );

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

      std::cout << " Type erasure dyno solution runtime   : " << seconds << "s\n";
   }
#endif

   std::cout << std::endl;

   return EXIT_SUCCESS;
}

