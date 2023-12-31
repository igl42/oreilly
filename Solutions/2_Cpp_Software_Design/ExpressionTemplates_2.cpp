/**************************************************************************************************
*
* \file ExpressionTemplates.cpp
* \brief C++ Training - Expression Template Programming Task
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Use Expression Templates to implement the addition operation. Benchmark the addition
*         of two small (in-cache) and two large (out-of-cache) vectors.
*
* Step 2: Use Expression Templates to implement the subtraction operation and a sqrt()
*         operation for dense vectors.
*
* Step 3: Use the Strategy design pattern to combine element-wise operations such as addition
*         and subtraction into a single expression class.
*
**************************************************************************************************/

#include <cstddef>
using std::size_t;


//---- <Memory.h> ---------------------------------------------------------------------------------

#include <cstdlib>
#if WIN32_PLATFORM || WIN64_PLATFORM || MINGW32_PLATFORM || MINGW64_PLATFORM
#  include <malloc.h>
#endif
#include <new>
#include <type_traits>

using byte_t = unsigned char;


#if defined(_WIN32)
#  define WIN32_PLATFORM 1
#else
#  define WIN32_PLATFORM 0
#endif

#if defined(_WIN64)
#  define WIN64_PLATFORM 1
#else
#  define WIN64_PLATFORM 0
#endif

#if defined(__MINGW64_VERSION_MAJOR)
#  define MINGW64_PLATFORM 1
#else
#  define MINGW64_PLATFORM 0
#endif

#if defined(__MINGW32__)
#  define MINGW32_PLATFORM 1
#else
#  define MINGW32_PLATFORM 0
#endif


inline byte_t* alignedAllocate( size_t size, size_t alignment )
{
   void* raw( nullptr );

#if WIN32_PLATFORM || WIN64_PLATFORM || MINGW64_PLATFORM
   raw = _aligned_malloc( size, alignment );
   if( raw == nullptr ) {
#elif MINGW32_PLATFORM
   raw = __mingw_aligned_malloc( size, alignment );
   if( raw == nullptr ) {
#else
   alignment = ( alignment < sizeof(void*) ? sizeof(void*) : alignment );
   if( posix_memalign( &raw, alignment, size ) ) {
#endif
      throw std::bad_alloc();
   }

   return reinterpret_cast<byte_t*>( raw );
}

template< typename T >
T* allocate( size_t size )
{
   constexpr size_t alignment( alignof(T) );

   return reinterpret_cast<T*>( alignedAllocate( size*sizeof(T), alignment ) );
}


inline void alignedDeallocate( const void* address ) noexcept
{
#if WIN32_PLATFORM || WIN64_PLATFORM || MINGW64_PLATFORM
   _aligned_free( const_cast<void*>( address ) );
#elif BLAZE_MINGW32_PLATFORM
   __mingw_aligned_free( const_cast<void*>( address ) );
#else
   free( const_cast<void*>( address ) );
#endif
}

template< typename T >
void deallocate( T* address ) noexcept
{
   if( address == nullptr )
      return;

   alignedDeallocate( address );
}


//---- <DenseVector.h> ----------------------------------------------------------------------------

#include <ostream>

template< typename Derived >
class DenseVector
{
 protected:
   ~DenseVector() = default;

 public:
   constexpr Derived&       derived()       { return static_cast<Derived&>(*this); }
   constexpr Derived const& derived() const { return static_cast<Derived const&>(*this); }

   constexpr size_t size() const { return derived().size(); }

   constexpr decltype(auto) operator[]( size_t index )       { return derived()[index]; }
   constexpr decltype(auto) operator[]( size_t index ) const { return derived()[index]; }

   constexpr auto begin() const { return derived().begin(); }
   constexpr auto end()   const { return derived().end(); }
};

template< typename Derived >
std::ostream& operator<<( std::ostream& os, DenseVector<Derived> const& vector )
{
   size_t const size( vector.size() );

   os << "(";
   for( size_t i=0U; i<size; ++i ) {
      os << " " << vector[i];
   }
   os << " )";

   return os;
}


//---- <DynamicVector.h> --------------------------------------------------------------------------

//#include <DenseVector.h>
//#include <Memory.h>
#include <algorithm>
#include <stdexcept>
#include <type_traits>

template< typename Type >
class DynamicVector
   : public DenseVector< DynamicVector<Type> >
{
 public:
   using value_type     = Type;
   using iterator       = Type*;
   using const_iterator = Type const*;

   DynamicVector() = default;

   explicit DynamicVector( size_t n, Type value = Type{} )
      : size_    ( n )
      , capacity_( n )
      , v_       ( allocate<Type>( n ) )
   {
      std::fill( begin(), end(), value );
   }

   DynamicVector( DynamicVector const& rhs )
      : size_    ( rhs.size_ )
      , capacity_( rhs.size_ )
      , v_       ( allocate<Type>( rhs.size_ ) )
   {
      assign( rhs );
   }

   DynamicVector( DynamicVector&& rhs )
      : size_    ( rhs.size_ )
      , capacity_( rhs.capacity_ )
      , v_       ( rhs.v_ )
   {
      rhs.v_ = nullptr;
   }

   template< typename VT >
   DynamicVector( DenseVector<VT> const& rhs )
      : size_    ( rhs.size() )
      , capacity_( rhs.size() )
      , v_       ( allocate<Type>( rhs.size() ) )
   {
      assign( rhs.derived() );
   }

   ~DynamicVector()
   {
      deallocate( v_ );
   }

   size_t size()     const { return size_; }
   size_t capacity() const { return capacity_; }

   Type*       data()       { return v_; }
   Type const* data() const { return v_; }

   Type&       operator[]( size_t index )       { return v_[index]; }
   Type const& operator[]( size_t index ) const { return v_[index]; }

   iterator       begin()        { return v_; }
   const_iterator begin()  const { return v_; }
   const_iterator cbegin() const { return v_; }
   iterator       end()          { return v_ + size_; }
   const_iterator end()    const { return v_ + size_; }
   const_iterator cend()   const { return v_ + size_; }

   DynamicVector& operator=( DynamicVector const& rhs )
   {
      resize( rhs.size() );
      assign( rhs );
      return *this;
   }

   DynamicVector& operator=( DynamicVector&& rhs )
   {
      deallocate( v_ );

      size_     = rhs.size_;
      capacity_ = rhs.capacity_;
      v_        = rhs.v_;

      rhs.v_ = nullptr;

      return *this;
   }

   template< typename VT >
   DynamicVector& operator=( DenseVector<VT> const& v )
   {
      if( v.size() != size_ )
         throw std::invalid_argument( "Vector size does not match" );

      assign( v.derived() );

      return *this;
   }

 private:
   template< typename VT >
   void assign( VT const& v )
   {
      for( size_t i=0U; i<size_; ++i ) {
         v_[i] = v[i];
      }
   }

   size_t size_    { 0U };
   size_t capacity_{ 0U };
   Type* v_        { nullptr };

   static_assert( std::is_fundamental<Type>::value, "Invalid data type detected" );
};

/*
template< typename T >
DynamicVector<T> operator+( DynamicVector<T> const& lhs, DynamicVector<T> const& rhs )
{
   if( lhs.size() != rhs.size() )
      throw std::invalid_argument( "Vector size does not match" );

   DynamicVector<T> tmp( lhs.size() );

   for( size_t i=0U; i<lhs.size(); ++i ) {
      tmp[i] = lhs[i] + rhs[i];
   }

   return tmp;
}
*/

template< typename T >
void add( DynamicVector<T>& dst, DynamicVector<T> const& lhs, DynamicVector<T> const& rhs )
{
   if( dst.size() != lhs.size() || lhs.size() != rhs.size() )
      throw std::invalid_argument( "Vector sizes don't match" );

   for( size_t i=0U; i<dst.size(); ++i ) {
      dst[i] = lhs[i] + rhs[i];
   }
}


//---- <Addition.h> -------------------------------------------------------------------------------

//#include <DenseVector.h>
#include <cassert>
#include <stdexcept>
#include <utility>

template< typename VT1, typename VT2 >
struct VecVecAddExpr
   : public DenseVector< VecVecAddExpr<VT1,VT2> >
{
 public:
   using value_type = decltype( std::declval<VT1>()[0U] + std::declval<VT2>()[0U] );

   VecVecAddExpr( VT1 const& lhs, VT2 const& rhs )
      : lhs_( lhs )
      , rhs_( rhs )
   {
      assert( lhs_.size() == rhs_.size() );
   }

   size_t size() const { return lhs_.size(); }

   value_type operator[]( size_t index ) const
   {
      assert( index < size() );
      return lhs_[index] + rhs_[index];
   }

 private:
   VT1 const& lhs_;
   VT2 const& rhs_;
};

template< typename VT1, typename VT2 >
VecVecAddExpr<VT1,VT2> operator+( DenseVector<VT1> const& lhs, DenseVector<VT2> const& rhs )
{
   if( lhs.size() != rhs.size() )
      throw std::invalid_argument( "Vector size does not match" );

   return VecVecAddExpr<VT1,VT2>( lhs.derived(), rhs.derived() );
}


//---- <Subtraction.h> ----------------------------------------------------------------------------

//#include <DenseVector.h>
#include <cassert>
#include <stdexcept>
#include <utility>

template< typename VT1, typename VT2 >
struct VecVecSubExpr
   : public DenseVector< VecVecSubExpr<VT1,VT2> >
{
 public:
   using value_type = decltype( std::declval<VT1>()[0U] - std::declval<VT2>()[0U] );

   VecVecSubExpr( VT1 const& lhs, VT2 const& rhs )
      : lhs_( lhs )
      , rhs_( rhs )
   {
      assert( lhs_.size() == rhs_.size() );
   }

   size_t size() const { return lhs_.size(); }

   value_type operator[]( size_t index ) const
   {
      assert( index < size() );
      return lhs_[index] - rhs_[index];
   }

 private:
   VT1 const& lhs_;
   VT2 const& rhs_;
};

template< typename VT1, typename VT2 >
VecVecSubExpr<VT1,VT2> operator-( DenseVector<VT1> const& lhs, DenseVector<VT2> const& rhs )
{
   if( lhs.size() != rhs.size() )
      throw std::invalid_argument( "Vector size does not match" );

   return VecVecSubExpr<VT1,VT2>( lhs.derived(), rhs.derived() );
}


//---- <Sqrt.h> -----------------------------------------------------------------------------------

//#include <DenseVector.h>
#include <cassert>
#include <cmath>
#include <utility>

template< typename VT >
struct VecSqrtExpr
   : public DenseVector< VecSqrtExpr<VT> >
{
 public:
   using value_type = decltype( std::sqrt( std::declval<VT>()[0U] ) );

   VecSqrtExpr( VT const& vec )
      : vec_( vec )
   {}

   size_t size() const { return vec_.size(); }

   value_type operator[]( size_t index ) const
   {
      assert( index < size() );
      return std::sqrt( vec_[index] );
   }

 private:
   VT const& vec_;
};

template< typename VT >
VecSqrtExpr<VT> sqrt( DenseVector<VT> const& vec )
{
   return VecSqrtExpr<VT>( vec.derived() );
}


//---- <BinaryOperation.h> ------------------------------------------------------------------------

//#include <DenseVector.h>
#include <cassert>
#include <functional>
#include <utility>

// Step 3: Use the Strategy design pattern to combine element-wise operations such as addition
//         and subtraction into a single expression class.


//---- <Main.cpp> ---------------------------------------------------------------------------------

//#include <DynamicVector.h>
//#include <Addition.h>
//#include <Subtraction.h>
//#include <Sqrt.h>
#include <chrono>
#include <cstdlib>
#include <iostream>

int main()
{
   // Step 1: Use Expression Templates to implement the addition operation. Benchmark
   //         the addition of two small (in-cache) and two large (out-of-cache) vectors.
   {
      constexpr size_t N( 1000U );
      constexpr size_t repetitions( 3U );
      constexpr size_t steps( 1000000U );

      DynamicVector<double> a( N, 2.0 );
      DynamicVector<double> b( N, 3.0 );
      DynamicVector<double> c( N, 0.0 );

      c = a + b;

      for( size_t rep=0U; rep<repetitions; ++rep )
      {
         std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
         start = std::chrono::high_resolution_clock::now();

         for( size_t step=0U; step<steps; ++step )
         {
            c = a + b;
         }

         end = std::chrono::high_resolution_clock::now();
         std::chrono::duration<double> const elapsedTime = end - start;

         if( c[0U] != 5.0 ) { std::cerr << "\n ERROR DETECTED!\n\n"; }

         double const seconds( elapsedTime.count() );
         double const mflops ( ( N * steps ) / ( 1E6 * seconds ) );

         std::cout << " Run " << (rep+1U) << ": " << seconds << "s (" << mflops << " MFlops)\n";
      }
   }

   // Step 2: Use Expression Templates to implement the subtraction operation and a
   //         sqrt() operation for dense vectors.
   {
      DynamicVector<double> a( 3, 2.0 );
      DynamicVector<double> b( 3, 3.0 );
      DynamicVector<double> c( 3, 0.0 );

      c = a + b;
      std::cout << " c = " << c << "\n";

      c = a - b;
      std::cout << " c = " << c << "\n";

      c = sqrt(a);
      std::cout << " c = " << c << "\n";
   }

   return EXIT_SUCCESS;
}

