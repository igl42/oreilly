/**************************************************************************************************
*
* \file RandomAccessIterator.cpp
* \brief C++ Training - STL Programming Task
*
* Copyright (C) 2015-2023 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Discuss the implementation of the following 'RandomAccessIterator'.
*
**************************************************************************************************/

#include <cstddef>
#include <cstdlib>
#include <iostream>
#include <iterator>


template< typename Type >
class RandomAccessIterator
{
 public:
   using iterator_category = std::random_access_iterator_tag;
   using value_type        = Type;
   using pointer           = Type*;
   using reference         = Type&;
   using difference_type   = ptrdiff_t;

   constexpr RandomAccessIterator() noexcept = default;
   explicit constexpr RandomAccessIterator( Type* ptr ) noexcept;

   template< typename Other >
   constexpr RandomAccessIterator( const RandomAccessIterator<Other>& other ) noexcept;

   constexpr RandomAccessIterator& operator+=( ptrdiff_t inc ) noexcept;
   constexpr RandomAccessIterator& operator-=( ptrdiff_t inc ) noexcept;

   constexpr RandomAccessIterator& operator++()      noexcept;
   constexpr RandomAccessIterator  operator++( int ) noexcept;
   constexpr RandomAccessIterator& operator--()      noexcept;
   constexpr RandomAccessIterator  operator--( int ) noexcept;

   [[nodiscard]] constexpr reference operator[]( size_t index ) const noexcept;
   [[nodiscard]] constexpr reference operator* () const noexcept;
   [[nodiscard]] constexpr pointer   operator->() const noexcept;

   [[nodiscard]] constexpr pointer base() const noexcept;

 private:
   pointer ptr_{ nullptr };
};




template< typename Type >
constexpr RandomAccessIterator<Type>::RandomAccessIterator( Type* ptr ) noexcept
   : ptr_{ ptr }
{}

template< typename Type >
template< typename Other >
constexpr RandomAccessIterator<Type>::RandomAccessIterator( const RandomAccessIterator<Other>& other ) noexcept
   : ptr_{ other.base() }
{}




template< typename Type >
constexpr RandomAccessIterator<Type>&
   RandomAccessIterator<Type>::operator+=( ptrdiff_t inc ) noexcept
{
   ptr_ += inc;
   return *this;
}

template< typename Type >
constexpr RandomAccessIterator<Type>&
   RandomAccessIterator<Type>::operator-=( ptrdiff_t dec ) noexcept
{
   ptr_ -= dec;
   return *this;
}




template< typename Type >
constexpr RandomAccessIterator<Type>& RandomAccessIterator<Type>::operator++() noexcept
{
   ++ptr_;
   return *this;
}

template< typename Type >
constexpr RandomAccessIterator<Type> RandomAccessIterator<Type>::operator++( int ) noexcept
{
   return RandomAccessIterator( ptr_++ );
}

template< typename Type >
constexpr RandomAccessIterator<Type>& RandomAccessIterator<Type>::operator--() noexcept
{
   --ptr_;
   return *this;
}

template< typename Type >
constexpr RandomAccessIterator<Type> RandomAccessIterator<Type>::operator--( int ) noexcept
{
   return RandomAccessIterator( ptr_-- );
}




template< typename Type >
[[nodiscard]] constexpr auto
   RandomAccessIterator<Type>::operator[]( size_t index ) const noexcept -> reference
{
   return ptr_[index];
}

template< typename Type >
[[nodiscard]] constexpr auto
   RandomAccessIterator<Type>::operator*() const noexcept -> reference
{
   return *ptr_;
}

template< typename Type >
[[nodiscard]] constexpr auto
   RandomAccessIterator<Type>::operator->() const noexcept -> pointer
{
   return ptr_;
}




template< typename Type >
constexpr auto RandomAccessIterator<Type>::base() const noexcept -> pointer
{
   return ptr_;
}




template< typename T1, typename T2 >
[[nodiscard]] constexpr bool
   operator==( const RandomAccessIterator<T1>& lhs, const RandomAccessIterator<T2>& rhs ) noexcept
{
   return lhs.base() == rhs.base();
}

template< typename T1, typename T2 >
[[nodiscard]] constexpr bool
   operator!=( const RandomAccessIterator<T1>& lhs, const RandomAccessIterator<T2>& rhs ) noexcept
{
   return lhs.base() != rhs.base();
}

template< typename T1, typename T2 >
[[nodiscard]] constexpr bool
   operator<( const RandomAccessIterator<T1>& lhs, const RandomAccessIterator<T2>& rhs ) noexcept
{
   return lhs.base() < rhs.base();
}

template< typename T1, typename T2 >
[[nodiscard]] constexpr bool
   operator>( const RandomAccessIterator<T1>& lhs, const RandomAccessIterator<T2>& rhs ) noexcept
{
   return lhs.base() > rhs.base();
}

template< typename T1, typename T2 >
[[nodiscard]] constexpr bool
   operator<=( const RandomAccessIterator<T1>& lhs, const RandomAccessIterator<T2>& rhs ) noexcept
{
   return lhs.base() <= rhs.base();
}

template< typename T1, typename T2 >
[[nodiscard]] constexpr bool
   operator>=( const RandomAccessIterator<T1>& lhs, const RandomAccessIterator<T2>& rhs ) noexcept
{
   return lhs.base() >= rhs.base();
}

template< typename Type >
[[nodiscard]] constexpr RandomAccessIterator<Type>
   operator+( const RandomAccessIterator<Type>& it, ptrdiff_t inc ) noexcept
{
   return RandomAccessIterator<Type>( it.base() + inc );
}

template< typename Type >
[[nodiscard]] constexpr RandomAccessIterator<Type>
   operator+( ptrdiff_t inc, const RandomAccessIterator<Type>& it ) noexcept
{
   return RandomAccessIterator<Type>( it.base() + inc );
}

template< typename Type >
[[nodiscard]] constexpr RandomAccessIterator<Type>
   operator-( const RandomAccessIterator<Type>& it, ptrdiff_t dec ) noexcept
{
   return RandomAccessIterator<Type>( it.base() - dec );
}

template< typename Type >
[[nodiscard]] constexpr ptrdiff_t
   operator-( const RandomAccessIterator<Type>& lhs, const RandomAccessIterator<Type>& rhs ) noexcept
{
   return lhs.base() - rhs.base();
}




template< typename Type, size_t N >
class Array
{
 public:
   using iterator       = RandomAccessIterator<Type>;
   using const_iterator = RandomAccessIterator<const Type>;

   [[nodiscard]] constexpr size_t size() const noexcept { return N; }
   [[nodiscard]] constexpr size_t capacity() const noexcept { return N; }

   [[nodiscard]] constexpr iterator       begin()        { return RandomAccessIterator( values_ ); }
   [[nodiscard]] constexpr const_iterator begin()  const { return RandomAccessIterator( values_ ); }
   [[nodiscard]] constexpr const_iterator cbegin() const { return RandomAccessIterator( values_ ); }
   [[nodiscard]] constexpr iterator       end()          { return RandomAccessIterator( values_+N ); }
   [[nodiscard]] constexpr const_iterator end()    const { return RandomAccessIterator( values_+N ); }
   [[nodiscard]] constexpr const_iterator cend()   const { return RandomAccessIterator( values_+N ); }

   Type values_[N];
};




template< typename I >
//template< std::random_access_iterator I >  // C++20 constraint to check the random_access_iterator requirements
void print( I first, I last )
{
   std::cout << "\n (";
   for( ; first!=last; ++first ) {
      std::cout << " " << *first;
   }
   std::cout << " )\n\n";
}




int main()
{
   const Array<int,5> array{ 1, 2, 3, 4, 5 };

   print( array.cbegin(), array.cend() );

   return EXIT_SUCCESS;
}

