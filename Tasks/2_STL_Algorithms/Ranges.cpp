/**************************************************************************************************
*
* \file Ranges.cpp
* \brief C++ Training - Programming Task for Expression Templates
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Step 1: Fix the implementation of the 'TransformExpr' expression to apply the given operation
*         on the given range.
*
* Step 2: Add the 'take()' operation, which restricts the given range to a specific number of
*         elements.
*
* Step 3: Consider the second code example (i.e. the code scaling all odd numbers). This code
*         contains a serious issue. What is the issue?
*
**************************************************************************************************/

#include <array>
#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <type_traits>
#include <vector>


//---- <Expression.h> -----------------------------------------------------------------------------

struct Expression {};

template< typename T >
using is_expression = std::is_base_of<Expression,T>;

template< typename T >
constexpr bool is_expression_v = is_expression<T>::value;




//---- <FilterExpr.h> -----------------------------------------------------------------------------

template< typename Range, typename OP >
class FilterExpr
   : public Expression
{
 private:
   class ConstIterator
   {
    private:
      typename Range::const_iterator pos_{};
      typename Range::const_iterator end_{};
      OP op_{};

    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type        = typename Range::value_type;
      using difference_type   = std::ptrdiff_t;

      ConstIterator() = default;

      ConstIterator( typename Range::const_iterator pos, typename Range::const_iterator end, OP op )
         : pos_( pos )
         , end_( end )
         , op_ ( op  )
      {
         for( ; pos_!=end_; ++pos_ ) {
            if( op_( *pos_ ) ) break;
         }
      }

      ConstIterator& operator++() {
         ++pos_;
         for( ; pos_!=end_; ++pos_ ) {
            if( op_( *pos_ ) ) break;
         }
         return *this;
      }

      const ConstIterator operator++( int ) {
         const ConstIterator tmp( *this );
         ++(*this);
         return tmp;
      }

      decltype(auto) operator*() const {
         return *pos_;
      }

      bool operator==( const ConstIterator& rhs ) const noexcept {
         return pos_ == rhs.pos_;
      }

      bool operator!=( const ConstIterator& rhs ) const noexcept {
         return !( *this == rhs );
      }
   };

 public:
   using value_type     = typename Range::value_type;
   using const_iterator = ConstIterator;
   using iterator       = ConstIterator;

   FilterExpr( const Range& range, OP op )
      : range_( range )
      , op_   ( op    )
   {}

   const_iterator begin() const
   {
      return ConstIterator( range_.begin(), range_.end(), op_ );
   }

   const_iterator end() const
   {
      return ConstIterator( range_.end(), range_.end(), op_ );
   }

 private:
   using Range_ = std::conditional_t< is_expression_v<Range>, const Range, const Range& >;

   Range_ range_;
   OP     op_;
};

template< typename OP >
struct FilterOperation
{
   OP op_;
};

template< typename OP >
FilterOperation<OP> filter( OP op )
{
   return FilterOperation<OP>{ op };
}

template< typename Range, typename OP >
FilterExpr<Range,OP> operator|( const Range& range, FilterOperation<OP> op )
{
   return FilterExpr<Range,OP>( range, op.op_ );
}




//---- <TransformExpr.h> --------------------------------------------------------------------------

template< typename Range, typename OP >
class TransformExpr
   : public Expression
{
 private:
   class ConstIterator
   {
    private:
      typename Range::const_iterator pos_{};
      OP op_{};

    public:
      using iterator_category = std::forward_iterator_tag;
      using value_type        = typename Range::value_type;
      using difference_type   = std::ptrdiff_t;

      ConstIterator() = default;

      ConstIterator( typename Range::const_iterator pos, OP op )
         : pos_( pos )
         , op_ ( op  )
      {}

      ConstIterator& operator++() {
         ++pos_;
         return *this;
      }

      const ConstIterator operator++( int ) {
         const ConstIterator tmp( *this );
         ++(*this);
         return tmp;
      }

      decltype(auto) operator*() const {
         return *pos_;
      }

      bool operator==( const ConstIterator& rhs ) const noexcept {
         return pos_ == rhs.pos_;
      }

      bool operator!=( const ConstIterator& rhs ) const noexcept {
         return !( *this == rhs );
      }
   };

 public:
   using value_type     = typename Range::value_type;
   using const_iterator = ConstIterator;
   using iterator       = ConstIterator;

   TransformExpr( const Range& range, OP op )
      : range_( range )
      , op_   ( op    )
   {}

   const_iterator begin() const
   {
      return ConstIterator( range_.begin(), op_ );
   }

   const_iterator end() const
   {
      return ConstIterator( range_.end(), op_ );
   }

 private:
   using Range_ = std::conditional_t< is_expression_v<Range>, const Range, const Range& >;

   Range_ range_;
   OP     op_;
};

template< typename OP >
struct TransformOperation
{
   OP op_;
};

template< typename OP >
TransformOperation<OP> transform( OP op )
{
   return TransformOperation<OP>{ op };
}

template< typename Range, typename OP >
TransformExpr<Range,OP> operator|( const Range& range, TransformOperation<OP> op )
{
   return TransformExpr<Range,OP>( range, op.op_ );
}




//---- <TakeExpr.h> --------------------------------------------------------------------------

// TODO: Add the 'take()' operation, which restricts the given range to a specific number
//       of elements.




//---- <Main.cpp> ---------------------------------------------------------------------------------

int compute( int i ) { return i*2; }
bool isEven( int i ) { return i%2==0; }
bool isOdd( int i ) { return i%2==1; }


template< typename T >
void print( const T& range )
{
   std::cout << "\n (";
   for( int i : range ) {
      std::cout << " " << i;
   }
   std::cout << " )\n\n";
}


int main()
{
   std::vector<int> numbers{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };

   auto scaledEvenNumbers = numbers
                          | filter( [](int n){ return isEven(n); } )
                          | transform( [](int n) { return compute(n); } );

   print( scaledEvenNumbers );


   /*
   auto scaledOddNumbers = std::array<int,12UL>{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 }
                         | filter( [](int n){ return isOdd(n); } )
                         | transform( [](int n) { return compute(n); } );

   print( scaledOddNumbers );
   */


   return EXIT_SUCCESS;
}
