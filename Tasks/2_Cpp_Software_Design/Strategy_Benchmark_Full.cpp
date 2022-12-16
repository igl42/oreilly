/**************************************************************************************************
*
* \file Strategy_Benchmark_2.cpp
* \brief C++ Training - Programming Task for the Strategy Design Pattern
*
* Copyright (C) 2015-2022 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
**************************************************************************************************/

#define BENCHMARK_OO_SOLUTION 0
#define BENCHMARK_STRATEGY_SOLUTION 0
#define BENCHMARK_STD_FUNCTION_SOLUTION 0
#define BENCHMARK_BOOST_FUNCTION_SOLUTION 0
#define BENCHMARK_MANUAL_FUNCTION_SOLUTION 0
#define BENCHMARK_TYPE_ERASURE_SOLUTION 1
#define BENCHMARK_TYPE_ERASURE_SBO_SOLUTION 1
#define BENCHMARK_TYPE_ERASURE_MANUAL_SOLUTION 1
#define BENCHMARK_TYPE_ERASURE_SBO_MANUAL_SOLUTION 1
#define BENCHMARK_TYPE_ERASURE_DYNO_SOLUTION 0


#include <array>
#include <chrono>
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

Vector2D operator+( const Vector2D& a, const Vector2D& b )
{
   return Vector2D{ a.x+b.x, a.y+b.y };
}


#if BENCHMARK_OO_SOLUTION
namespace object_oriented_solution {

   struct Shape
   {
      Shape() = default;
      Shape( const Shape& ) = default;
      Shape( Shape&& ) = default;
      virtual ~Shape() = default;
      Shape& operator=( const Shape& ) = default;
      Shape& operator=( Shape&& ) = default;

      virtual void translate( const Vector2D& v ) = 0;
   };


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


#if BENCHMARK_STRATEGY_SOLUTION
namespace strategy_solution {

   struct Circle;
   struct Ellipse;
   struct Square;
   struct Rectangle;

   struct TranslateCircleStrategy
   {
      TranslateCircleStrategy() = default;
      TranslateCircleStrategy( const TranslateCircleStrategy& ) = default;
      TranslateCircleStrategy( TranslateCircleStrategy&& ) = default;
      virtual ~TranslateCircleStrategy() = default;
      TranslateCircleStrategy& operator=( const TranslateCircleStrategy& ) = default;
      TranslateCircleStrategy& operator=( TranslateCircleStrategy&& ) = default;

      virtual void translate( Circle& circle, const Vector2D& v ) const = 0;
   };

   struct TranslateEllipseStrategy
   {
      TranslateEllipseStrategy() = default;
      TranslateEllipseStrategy( const TranslateEllipseStrategy& ) = default;
      TranslateEllipseStrategy( TranslateEllipseStrategy&& ) = default;
      virtual ~TranslateEllipseStrategy() = default;
      TranslateEllipseStrategy& operator=( const TranslateEllipseStrategy& ) = default;
      TranslateEllipseStrategy& operator=( TranslateEllipseStrategy&& ) = default;

      virtual void translate( Ellipse& ellipse, const Vector2D& v ) const = 0;
   };

   struct TranslateSquareStrategy
   {
      TranslateSquareStrategy() = default;
      TranslateSquareStrategy( const TranslateSquareStrategy& ) = default;
      TranslateSquareStrategy( TranslateSquareStrategy&& ) = default;
      virtual ~TranslateSquareStrategy() = default;
      TranslateSquareStrategy& operator=( const TranslateSquareStrategy& ) = default;
      TranslateSquareStrategy& operator=( TranslateSquareStrategy&& ) = default;

      virtual void translate( Square& square, const Vector2D& v ) const = 0;
   };

   struct TranslateRectangleStrategy
   {
      TranslateRectangleStrategy() = default;
      TranslateRectangleStrategy( const TranslateRectangleStrategy& ) = default;
      TranslateRectangleStrategy( TranslateRectangleStrategy&& ) = default;
      virtual ~TranslateRectangleStrategy() = default;
      TranslateRectangleStrategy& operator=( const TranslateRectangleStrategy& ) = default;
      TranslateRectangleStrategy& operator=( TranslateRectangleStrategy&& ) = default;

      virtual void translate( Rectangle& rect, const Vector2D& v ) const = 0;
   };


   struct Shape
   {
      Shape() = default;
      Shape( const Shape& ) = default;
      Shape( Shape&& ) = default;
      virtual ~Shape() = default;
      Shape& operator=( const Shape& ) = default;
      Shape& operator=( Shape&& ) = default;

      virtual void translate( const Vector2D& v ) = 0;
   };


   struct Circle : public Shape
   {
      Circle( double r, std::unique_ptr<TranslateCircleStrategy>&& ts )
         : radius{ r }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy->translate( *this, v ); }

      double radius{};
      Vector2D center{};
      std::unique_ptr<TranslateCircleStrategy> strategy{};
   };


   struct Ellipse : public Shape
   {
      Ellipse( double r1, double r2, std::unique_ptr<TranslateEllipseStrategy>&& ts )
         : radius1{ r1 }
         , radius2{ r2 }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy->translate( *this, v ); }

      double radius1{};
      double radius2{};
      Vector2D center{};
      std::unique_ptr<TranslateEllipseStrategy> strategy{};
   };


   struct Square : public Shape
   {
      Square( double s, std::unique_ptr<TranslateSquareStrategy>&& ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy->translate( *this, v ); }

      double side{};
      Vector2D center{};
      std::unique_ptr<TranslateSquareStrategy> strategy{};
   };


   struct Rectangle : public Shape
   {
      Rectangle( double w, double h, std::unique_ptr<TranslateRectangleStrategy>&& ts )
         : width{ w }
         , height{ h }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy->translate( *this, v ); }

      double width{};
      double height{};
      Vector2D center{};
      std::unique_ptr<TranslateRectangleStrategy> strategy{};
   };


   struct ConcreteTranslateCircleStrategy : public TranslateCircleStrategy
   {
      void translate( Circle& circle, const Vector2D& v ) const override
      {
         circle.center = circle.center + v;
      }
   };

   struct ConcreteTranslateEllipseStrategy : public TranslateEllipseStrategy
   {
      void translate( Ellipse& ellipse, const Vector2D& v ) const override
      {
         ellipse.center = ellipse.center + v;
      }
   };

   struct ConcreteTranslateSquareStrategy : public TranslateSquareStrategy
   {
      void translate( Square& square, const Vector2D& v ) const override
      {
         square.center = square.center + v;
      }
   };

   struct ConcreteTranslateRectangleStrategy : public TranslateRectangleStrategy
   {
      void translate( Rectangle& rectangle, const Vector2D& v ) const override
      {
         rectangle.center = rectangle.center + v;
      }
   };

   using Shapes = std::vector< std::unique_ptr<Shape> >;

   void translate( Shapes& shapes, const Vector2D& v )
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
      Shape() = default;
      Shape( const Shape& ) = default;
      Shape( Shape&& ) = default;
      virtual ~Shape() = default;
      Shape& operator=( const Shape& ) = default;
      Shape& operator=( Shape&& ) = default;

      virtual void translate( const Vector2D& v ) = 0;
   };


   struct Circle : public Shape
   {
      using TranslateStrategy = std::function<void(Circle&, const Vector2D&)>;

      Circle( double r, TranslateStrategy ts )
         : radius{ r }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy( *this, v ); }

      double radius{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Circle& circle, const Vector2D& v )
   {
      circle.center = circle.center + v;
   }


   struct Ellipse : public Shape
   {
      using TranslateStrategy = std::function<void(Ellipse&, const Vector2D&)>;

      Ellipse( double r1, double r2, TranslateStrategy ts )
         : radius1{ r1 }
         , radius2{ r2 }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy( *this, v ); }

      double radius1{};
      double radius2{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Ellipse& ellipse, const Vector2D& v )
   {
      ellipse.center = ellipse.center + v;
   }


   struct Square : public Shape
   {
      using TranslateStrategy = std::function<void(Square&, const Vector2D&)>;

      Square( double s, TranslateStrategy ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy( *this, v ); }

      double side{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Square& square, const Vector2D& v )
   {
      square.center = square.center + v;
   }


   struct Rectangle : public Shape
   {
      using TranslateStrategy = std::function<void(Rectangle&, const Vector2D&)>;

      Rectangle( double w, double h, TranslateStrategy ts )
         : width{ w }
         , height{ h }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy( *this, v ); }

      double width{};
      double height{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Rectangle& rectangle, const Vector2D& v )
   {
      rectangle.center = rectangle.center + v;
   }


   struct Translate {
      template< typename T >
      void operator()( T& t, const Vector2D& v )
      {
         translate( t, v );
      }
   };


   using Shapes = std::vector< std::unique_ptr<Shape> >;

   void translate( Shapes& shapes, const Vector2D& v )
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
      Shape() = default;
      Shape( const Shape& ) = default;
      Shape( Shape&& ) = default;
      virtual ~Shape() = default;
      Shape& operator=( const Shape& ) = default;
      Shape& operator=( Shape&& ) = default;

      virtual void translate( const Vector2D& v ) = 0;
   };


   struct Circle : public Shape
   {
      using TranslateStrategy = boost::function<void(Circle&, const Vector2D&)>;

      Circle( double r, TranslateStrategy ts )
         : radius{ r }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy( *this, v ); }

      double radius{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Circle& circle, const Vector2D& v )
   {
      circle.center = circle.center + v;
   }


   struct Ellipse : public Shape
   {
      using TranslateStrategy = boost::function<void(Ellipse&, const Vector2D&)>;

      Ellipse( double r1, double r2, TranslateStrategy ts )
         : radius1{ r1 }
         , radius2{ r2 }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy( *this, v ); }

      double radius1{};
      double radius2{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Ellipse& ellipse, const Vector2D& v )
   {
      ellipse.center = ellipse.center + v;
   }


   struct Square : public Shape
   {
      using TranslateStrategy = boost::function<void(Square&, const Vector2D&)>;

      Square( double s, TranslateStrategy ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy( *this, v ); }

      double side{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Square& square, const Vector2D& v )
   {
      square.center = square.center + v;
   }


   struct Rectangle : public Shape
   {
      using TranslateStrategy = boost::function<void(Rectangle&, const Vector2D&)>;

      Rectangle( double w, double h, TranslateStrategy ts )
         : width{ w }
         , height{ h }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy( *this, v ); }

      double width{};
      double height{};
      Vector2D center{};
      TranslateStrategy strategy{};
   };

   void translate( Rectangle& rectangle, const Vector2D& v )
   {
      rectangle.center = rectangle.center + v;
   }


   struct Translate {
      template< typename T >
      void operator()( T& t, const Vector2D& v )
      {
         translate( t, v );
      }
   };


   using Shapes = std::vector< std::unique_ptr<Shape> >;

   void translate( Shapes& shapes, const Vector2D& v )
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
      Shape() = default;
      Shape( const Shape& ) = default;
      Shape( Shape&& ) = default;
      virtual ~Shape() = default;
      Shape& operator=( const Shape& ) = default;
      Shape& operator=( Shape&& ) = default;

      virtual void translate( const Vector2D& v ) = 0;
   };


   struct Circle : public Shape
   {
      using TranslateStrategy = Function<void(Circle&, const Vector2D&),8UL>;

      Circle( double r, TranslateStrategy ts )
         : radius{ r }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy( *this, v ); }

      double radius{};
      Vector2D center{};
      TranslateStrategy strategy;
   };

   void translate( Circle& circle, const Vector2D& v )
   {
      circle.center = circle.center + v;
   }


   struct Ellipse : public Shape
   {
      using TranslateStrategy = Function<void(Ellipse&, const Vector2D&),8UL>;

      Ellipse( double r1, double r2, TranslateStrategy ts )
         : radius1{ r1 }
         , radius2{ r2 }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy( *this, v ); }

      double radius1{};
      double radius2{};
      Vector2D center{};
      TranslateStrategy strategy;
   };

   void translate( Ellipse& ellipse, const Vector2D& v )
   {
      ellipse.center = ellipse.center + v;
   }


   struct Square : public Shape
   {
      using TranslateStrategy = Function<void(Square&, const Vector2D&),8UL>;

      Square( double s, TranslateStrategy ts )
         : side{ s }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy( *this, v ); }

      double side{};
      Vector2D center{};
      TranslateStrategy strategy;
   };

   void translate( Square& square, const Vector2D& v )
   {
      square.center = square.center + v;
   }



   struct Rectangle : public Shape
   {
      using TranslateStrategy = Function<void(Rectangle&, const Vector2D&),8UL>;

      Rectangle( double w, double h, TranslateStrategy ts )
         : width{ w }
         , height{ h }
         , strategy{ std::move(ts) }
      {}

      void translate( const Vector2D& v ) override { strategy( *this, v ); }

      double width{};
      double height{};
      Vector2D center{};
      TranslateStrategy strategy;
   };

   void translate( Rectangle& rectangle, const Vector2D& v )
   {
      rectangle.center = rectangle.center + v;
   }


   struct Translate {
      template< typename T >
      void operator()( T& t, const Vector2D& v ) const
      {
         translate( t, v );
      }
   };


   using Shapes = std::vector< std::unique_ptr<Shape> >;

   void translate( Shapes& shapes, const Vector2D& v )
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

   struct Circle
   {
      double radius{};
      Vector2D center{};
   };

   void translate( Circle& circle, const Vector2D& v )
   {
      circle.center = circle.center + v;
   }


   struct Ellipse
   {
      double radius1{};
      double radius2{};
      Vector2D center{};
   };

   void translate( Ellipse& ellipse, const Vector2D& v )
   {
      ellipse.center = ellipse.center + v;
   }


   struct Square
   {
      double side{};
      Vector2D center{};
   };

   void translate( Square& square, const Vector2D& v )
   {
      square.center = square.center + v;
   }


   struct Rectangle
   {
      double width{};
      double height{};
      Vector2D center{};
   };

   void translate( Rectangle& rect, const Vector2D& v )
   {
      rect.center = rect.center + v;
   }


   class Shape
   {
    public:
      template< typename T >
      Shape( const T& shape )
         : pimpl_{ new Model<T>( shape ) }
      {}

      Shape( const Shape& s ) : pimpl_{ s.pimpl_->clone() } {}
      Shape( Shape&& ) = default;
      ~Shape() = default;
      Shape& operator=( const Shape& s ) { Shape tmp( s ); std::swap( pimpl_, tmp.pimpl_ ); return *this; }
      Shape& operator=( Shape&& ) = default;

    private:
      struct Concept
      {
         virtual ~Concept() = default;
         virtual Concept* clone() const = 0;
         virtual void doTranslate( const Vector2D& ) = 0;
      };

      template< typename T >
      struct Model : public Concept
      {
         explicit Model( const T& shape ) : shape_( shape ) {}
         Concept* clone() const override { return new Model(*this); }
         void doTranslate( const Vector2D& v ) override { translate( shape_, v ); }
         T shape_;
      };

      friend void translate( Shape& s, const Vector2D& v )
      {
         s.pimpl_->doTranslate( v );
      }

      std::unique_ptr<Concept> pimpl_{};
   };

   using Shapes = std::vector<Shape>;

   void translate( Shapes& shapes, const Vector2D& v )
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

   struct Circle
   {
      double radius{};
      Vector2D center{};
   };

   void translate( Circle& circle, const Vector2D& v )
   {
      circle.center = circle.center + v;
   }


   struct Ellipse
   {
      double radius1{};
      double radius2{};
      Vector2D center{};
   };

   void translate( Ellipse& ellipse, const Vector2D& v )
   {
      ellipse.center = ellipse.center + v;
   }


   struct Square
   {
      double side{};
      Vector2D center{};
   };

   void translate( Square& square, const Vector2D& v )
   {
      square.center = square.center + v;
   }


   struct Rectangle
   {
      double width{};
      double height{};
      Vector2D center{};
   };

   void translate( Rectangle& rectangle, const Vector2D& v )
   {
      rectangle.center = rectangle.center + v;
   }


   template< size_t Capacity, size_t Alignment >
   class Shape
   {
    private:
      struct Concept
      {
         virtual ~Concept() = default;
         virtual void clone( Concept* ) const = 0;
         virtual void doTranslate( const Vector2D& ) = 0;
      };

      template< typename T >
      struct Model : public Concept
      {
         explicit Model( const T& shape ) : shape_( shape ) {}
         void clone( Concept* ptr ) const override { new (ptr) Model(*this); }
         void doTranslate( const Vector2D& v ) override { translate( shape_, v ); }
         T shape_{};
      };

    public:
      template< typename T >
      Shape( const T& shape )
         // data_ intentionally not initialized
      {
         new ( pimpl() ) Model<T>( shape );
      }

      Shape( const Shape& s ) { s.pimpl()->clone( pimpl() ); }
      ~Shape() { pimpl()->~Concept(); }
      Shape& operator=( const Shape& s ) { pimpl()->~Concept(); s.pimpl()->clone( pimpl() ); return *this; }

    private:
      Concept* pimpl()
      {
         return reinterpret_cast<Concept*>( &data_ );
      };

      const Concept* pimpl() const
      {
         return reinterpret_cast<const Concept*>( &data_ );
      };

      friend void translate( Shape& s, const Vector2D& v )
      {
         s.pimpl()->doTranslate( v );
      }

      std::aligned_storage_t<Capacity+8UL,Alignment> data_{};
   };

   using Shapes = std::vector<Shape<sizeof(Rectangle),16UL>>;

   void translate( Shapes& shapes, const Vector2D& v )
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

   struct Circle
   {
      double radius{};
      Vector2D center{};
   };

   void translate( Circle& circle, const Vector2D& v )
   {
      circle.center = circle.center + v;
   }


   struct Ellipse
   {
      double radius1{};
      double radius2{};
      Vector2D center{};
   };

   void translate( Ellipse& ellipse, const Vector2D& v )
   {
      ellipse.center = ellipse.center + v;
   }


   struct Square
   {
      double side{};
      Vector2D center{};
   };

   void translate( Square& square, const Vector2D& v )
   {
      square.center = square.center + v;
   }


   struct Rectangle
   {
      double width{};
      double height{};
      Vector2D center{};
   };

   void translate( Rectangle& rect, const Vector2D& v )
   {
      rect.center = rect.center + v;
   }


   class Shape
   {
    public:
      template< typename ShapeT >
      Shape( ShapeT const& shape )
         : translate_( []( void* c, const Vector2D& v ){
                          auto model( static_cast<ShapeT*>(c) );
                          translate( *model, v );
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
         : translate_( other.translate_ )
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
         std::swap( translate_, s.translate_ );
         std::swap( clone_, s.clone_ );
         std::swap( pimpl_, s.pimpl_ );
      }

    private:
      friend void translate( Shape& shape, const Vector2D& v )
      {
         shape.translate_( shape.pimpl_.get(), v );
      }

      using TranslateOperation = void(void*,const Vector2D&);
      using CloneOperation     = void*(void const*);
      using DestroyOperation   = void(void*);

      TranslateOperation* translate_{ nullptr };
      CloneOperation* clone_{ nullptr };
      std::unique_ptr<void,DestroyOperation*> pimpl_;
   };

   using Shapes = std::vector<Shape>;

   void translate( Shapes& shapes, const Vector2D& v )
   {
      for( auto& shape : shapes )
      {
         translate( shape, v );
      }
   }

} // namespace type_erasure_manual_solution
#endif


#if BENCHMARK_TYPE_ERASURE_SBO_MANUAL_SOLUTION
namespace type_erasure_sbo_manual_solution {

   struct Circle
   {
      double radius{};
      Vector2D center{};
   };

   void translate( Circle& circle, const Vector2D& v )
   {
      circle.center = circle.center + v;
   }


   struct Ellipse
   {
      double radius1{};
      double radius2{};
      Vector2D center{};
   };

   void translate( Ellipse& ellipse, const Vector2D& v )
   {
      ellipse.center = ellipse.center + v;
   }


   struct Square
   {
      double side{};
      Vector2D center{};
   };

   void translate( Square& square, const Vector2D& v )
   {
      square.center = square.center + v;
   }


   struct Rectangle
   {
      double width{};
      double height{};
      Vector2D center{};
   };

   void translate( Rectangle& rect, const Vector2D& v )
   {
      rect.center = rect.center + v;
   }


   class Shape
   {
    public:
      template< typename ShapeT >
      Shape( ShapeT const& shape )
         : translate_( []( void* c, const Vector2D& v ){
                          auto model( static_cast<ShapeT*>(c) );
                          translate( *model, v );
                       } )
         , clone_( []( void const* c, std::byte* raw ) {
                      auto const* model = static_cast<ShapeT const*>(c);
                      ::new (raw) ShapeT( *model );
                   } )
         , destroy_( []( void* c ){
                        auto* model = static_cast<ShapeT*>(c);
                        model->~ShapeT();
                     } )
      {
         static_assert( sizeof(ShapeT) <= buffersize, "Given type is too large" );
         static_assert( alignof(ShapeT) <= alignment, "Given type is overaligned" );
         ::new (buffer_.data()) ShapeT( shape );
      }

      Shape( Shape const& other )
         : translate_( other.translate_ )
         , clone_    ( other.clone_ )
         , destroy_  ( other.destroy_ )
      {
         clone_( other.buffer_.data(), buffer_.data() );
      }

      Shape& operator=( const Shape& other )
      {
         Shape tmp( other );
         swap( tmp );
         return *this;
      }

      // Move operations intentionally ignored!

      ~Shape() { destroy_( buffer_.data() ); }

      void swap( Shape& s )
      {
         std::swap( translate_, s.translate_ );
         std::swap( clone_, s.clone_ );
         std::swap( destroy_, s.destroy_ );
         std::swap( buffer_, s.buffer_ );
      }

    private:
      friend void translate( Shape& s, const Vector2D& v )
      {
         s.translate_( s.buffer_.data(), v );
      }

      using TranslateOperation = void(void*, const Vector2D&);
      using CloneOperation     = void(void const*,std::byte*);
      using DestroyOperation   = void(void*);

      TranslateOperation* translate_{ nullptr };
      CloneOperation*     clone_    { nullptr };
      DestroyOperation*   destroy_  { nullptr };

      static constexpr size_t buffersize = 32UL;
      static constexpr size_t alignment  = 16UL;

      alignas(alignment) std::array<std::byte,buffersize> buffer_;
   };

   using Shapes = std::vector<Shape>;

   void translate( Shapes& shapes, const Vector2D& v )
   {
      for( auto& shape : shapes )
      {
         translate( shape, v );
      }
   }

} // namespace type_erasure_sbo_manual_solution
#endif


#if BENCHMARK_TYPE_ERASURE_DYNO_SOLUTION

struct ShapeConcept : decltype( dyno::requires_(
   dyno::CopyConstructible{},
   dyno::MoveConstructible{},
   dyno::Destructible{},
   "translate"_s = dyno::function<void (dyno::T&, const Vector2D&)>
)) { };

template <typename T>
auto const dyno::default_concept_map<ShapeConcept, T> = dyno::make_concept_map(
   "translate"_s = []( T& self, const Vector2D& v ) { translate( self, v ); }
);

namespace type_erasure_dyno_solution {

   struct Circle
   {
      double radius{};
      Vector2D center{};
   };

   void translate( Circle& circle, const Vector2D& v )
   {
      circle.center = circle.center + v;
   }


   struct Ellipse
   {
      double radius1{};
      double radius2{};
      Vector2D center{};
   };

   void translate( Ellipse& ellipse, const Vector2D& v )
   {
      ellipse.center = ellipse.center + v;
   }


   struct Square
   {
      double side{};
      Vector2D center{};
   };

   void translate( Square& square, const Vector2D& v )
   {
      square.center = square.center + v;
   }


   struct Rectangle
   {
      double width{};
      double height{};
      Vector2D center{};
   };

   void translate( Rectangle& rectangle, const Vector2D& v )
   {
      rectangle.center = rectangle.center + v;
   }


   class Shape
   {
    public:
      template <typename T>
      Shape( T x ) : poly_{x} { }

      void translate( const Vector2D& v )
      { poly_.virtual_( "translate"_s )( poly_, v ); }

    private:
      dyno::poly<ShapeConcept> poly_;
   };

   void translate( Shape& shape, const Vector2D& v )
   {
      shape.translate( v );
   }


   using Shapes = std::vector<Shape>;

   void translate( Shapes& shapes, const Vector2D& v )
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
   const size_t N    ( 10000UL );
   const size_t steps( 25000UL );

   std::random_device rd{};
   const unsigned int seed( rd() );

   std::mt19937 rng{};
   std::uniform_real_distribution<double> dist( 0.0, 1.0 );

   std::cout << std::endl;

#if BENCHMARK_OO_SOLUTION
   {
      using namespace object_oriented_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         const double r( dist(rng) );

         if( r < 0.25 )
            shapes.emplace_back( std::make_unique<Circle>( dist(rng) ) );
         else if( r < 0.5 )
            shapes.emplace_back( std::make_unique<Ellipse>( dist(rng), dist(rng) ) );
         else if( r < 0.75 )
            shapes.emplace_back( std::make_unique<Square>( dist(rng) ) );
         else
            shapes.emplace_back( std::make_unique<Rectangle>( dist(rng), dist(rng) ) );
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

      std::cout << " OO solution runtime                      : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_STRATEGY_SOLUTION
   {
      using namespace strategy_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         const double r( dist(rng) );

         if( r < 0.25 )
            shapes.emplace_back( std::make_unique<Circle>( dist(rng)
                                                      , std::make_unique<ConcreteTranslateCircleStrategy>() ) );
         else if( r < 0.5 )
            shapes.emplace_back( std::make_unique<Ellipse>( dist(rng), dist(rng)
                                                       , std::make_unique<ConcreteTranslateEllipseStrategy>() ) );
         else if( r < 0.75 )
            shapes.emplace_back( std::make_unique<Square>( dist(rng)
                                                      , std::make_unique<ConcreteTranslateSquareStrategy>() ) );
         else
            shapes.emplace_back( std::make_unique<Rectangle>( dist(rng), dist(rng)
                                                         , std::make_unique<ConcreteTranslateRectangleStrategy>() ) );
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

      std::cout << " Classic strategy solution runtime        : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_STD_FUNCTION_SOLUTION
   {
      using namespace std_function_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         const double r( dist(rng) );

         if( r < 0.25 )
            shapes.emplace_back( std::make_unique<Circle>( dist(rng), Translate{} ) );
         else if( r < 0.5 )
            shapes.emplace_back( std::make_unique<Ellipse>( dist(rng), dist(rng), Translate{} ) );
         else if( r < 0.75 )
            shapes.emplace_back( std::make_unique<Square>( dist(rng), Translate{} ) );
         else
            shapes.emplace_back( std::make_unique<Rectangle>( dist(rng), dist(rng), Translate{} ) );
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

      std::cout << " std::function solution runtime           : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_BOOST_FUNCTION_SOLUTION
   {
      using namespace boost_function_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         const double r( dist(rng) );

         if( r < 0.25 )
            shapes.emplace_back( std::make_unique<Circle>( dist(rng), Translate{} ) );
         else if( r < 0.5 )
            shapes.emplace_back( std::make_unique<Ellipse>( dist(rng), dist(rng), Translate{} ) );
         else if( r < 0.75 )
            shapes.emplace_back( std::make_unique<Square>( dist(rng), Translate{} ) );
         else
            shapes.emplace_back( std::make_unique<Rectangle>( dist(rng), dist(rng), Translate{} ) );
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

      std::cout << " boost::function solution runtime         : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_MANUAL_FUNCTION_SOLUTION
   {
      using namespace manual_function_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         const double r( dist(rng) );

         if( r < 0.25 )
            shapes.emplace_back( std::make_unique<Circle>( dist(rng), Translate{} ) );
         else if( r < 0.5 )
            shapes.emplace_back( std::make_unique<Ellipse>( dist(rng), dist(rng), Translate{} ) );
         else if( r < 0.75 )
            shapes.emplace_back( std::make_unique<Square>( dist(rng), Translate{} ) );
         else
            shapes.emplace_back( std::make_unique<Rectangle>( dist(rng), dist(rng), Translate{} ) );
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

      std::cout << " Manual function solution runtime         : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_TYPE_ERASURE_SOLUTION
   {
      using namespace type_erasure_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         const double r( dist(rng) );

         if( r < 0.25 )
            shapes.emplace_back( Circle{ dist(rng) } );
         else if( r < 0.5 )
            shapes.emplace_back( Ellipse{ dist(rng), dist(rng) } );
         else if( r < 0.75 )
            shapes.emplace_back( Square{ dist(rng) } );
         else
            shapes.emplace_back( Rectangle{ dist(rng), dist(rng) } );
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

      std::cout << " Type erasure solution runtime            : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_TYPE_ERASURE_SBO_SOLUTION
   {
      using namespace type_erasure_sbo_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         const double r( dist(rng) );

         if( r < 0.25 )
            shapes.emplace_back( Circle{ dist(rng) } );
         else if( r < 0.5 )
            shapes.emplace_back( Ellipse{ dist(rng), dist(rng) } );
         else if( r < 0.75 )
            shapes.emplace_back( Square{ dist(rng) } );
         else
            shapes.emplace_back( Rectangle{ dist(rng), dist(rng) } );
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

      std::cout << " Type erasure SBO solution runtime        : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_TYPE_ERASURE_MANUAL_SOLUTION
   {
      using namespace type_erasure_manual_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         const double r( dist(rng) );

         if( r < 0.25 )
            shapes.emplace_back( Circle{ dist(rng) } );
         else if( r < 0.5 )
            shapes.emplace_back( Ellipse{ dist(rng), dist(rng) } );
         else if( r < 0.75 )
            shapes.emplace_back( Square{ dist(rng) } );
         else
            shapes.emplace_back( Rectangle{ dist(rng), dist(rng) } );
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

      std::cout << " Type erasure manual solution runtime     : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_TYPE_ERASURE_SBO_MANUAL_SOLUTION
   {
      using namespace type_erasure_sbo_manual_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         const double r( dist(rng) );

         if( r < 0.25 )
            shapes.emplace_back( Circle{ dist(rng) } );
         else if( r < 0.5 )
            shapes.emplace_back( Ellipse{ dist(rng), dist(rng) } );
         else if( r < 0.75 )
            shapes.emplace_back( Square{ dist(rng) } );
         else
            shapes.emplace_back( Rectangle{ dist(rng), dist(rng) } );
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

      std::cout << " Type erasure SBO+manual solution runtime : " << seconds << "s\n";
   }
#endif

#if BENCHMARK_TYPE_ERASURE_DYNO_SOLUTION
   {
      using namespace type_erasure_dyno_solution;

      rng.seed( seed );

      Shapes shapes;

      for( size_t i=0UL; i<N; ++i )
      {
         const double r( dist(rng) );

         if( r < 0.25 )
            shapes.emplace_back( Circle{ dist(rng) } );
         else if( r < 0.5 )
            shapes.emplace_back( Ellipse{ dist(rng), dist(rng) } );
         else if( r < 0.75 )
            shapes.emplace_back( Square{ dist(rng) } );
         else
            shapes.emplace_back( Rectangle{ dist(rng), dist(rng) } );
      }

      std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
      start = std::chrono::high_resolution_clock::now();

      for( size_t s=0UL; s<steps; ++s ) {
         translate( shapes, Vector2D{ dist(rng), dist(rng) } );
      }

      end = std::chrono::high_resolution_clock::now();
      const std::chrono::duration<double> elapsedTime( end - start );
      const double seconds( elapsedTime.count() );

      std::cout << " Type erasure dyno solution runtime       : " << seconds << "s\n";
   }
#endif

   std::cout << std::endl;

   return EXIT_SUCCESS;
}

