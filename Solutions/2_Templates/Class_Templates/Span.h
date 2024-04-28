/**************************************************************************************************
*
* \file Span.h
* \brief C++ Training - Simplified implementation of the C++20 std::span
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
**************************************************************************************************/

#include <array>
#include <cassert>
#include <cstddef>
#include <type_traits>
#include <utility>


namespace std {

//*************************************************************************************************
// Namespace functions
//*************************************************************************************************

// Utility functions for pre-C++17 compilers
/*
template< typename Container >
constexpr auto data( Container& cont ) -> decltype( cont.data() )
{
   return cont.data();
}

template< typename Container >
constexpr auto data( const Container& cont ) -> decltype( cont.data() )
{
   return cont.data();
}

template< typename T, size_t N >
constexpr T* data( T (&arr)[N] ) noexcept
{
   return arr;
}

template< typename Container >
constexpr auto size( const Container& cont ) noexcept -> decltype( cont.size() )
{
   return cont.size();
}

template< typename T, size_t N >
constexpr size_t size( T (&)[N] ) noexcept
{
   return N;
}
*/


//*************************************************************************************************
// Implementation details
//*************************************************************************************************

template< class T > class span;

namespace detail {

template< typename T >
true_type eval_is_span( const span<T>& );

template< typename T >
false_type eval_is_span( T );

template< typename T >
using is_span = decltype( detail::eval_is_span( declval<T>() ) );

template< typename T >
constexpr bool is_span_v = is_span<T>::value;

} // namespace detail


//*************************************************************************************************
// Class definition
//*************************************************************************************************

template< typename T >
class span
{
 public:
   using element_type    = T;
   using value_type      = remove_cv<T>;
   using index_type      = size_t;
   using difference_type = ptrdiff_t;

   using pointer       = T*;
   using const_pointer = const T*;

   using reference       = T&;
   using const_reference = const T&;

   using iterator       = T*;
   using const_iterator = const T*;

   using reverse_iterator       = T*;
   using const_reverse_iterator = const T*;

 private:
   template< typename Container >
   using enable_if_is_neither_array_nor_span =
      enable_if_t< !is_array<Container>::value && !detail::is_span_v<Container> >;

   template< typename From, typename To >
   using enable_if_is_convertible_array =
      enable_if_t< is_convertible<From(*)[],To(*)[]>::value >;

 public:
   constexpr span() noexcept = default;
   constexpr span( pointer ptr, index_type count );
   constexpr span( pointer first, pointer last );

   template< size_t N >
   constexpr span( element_type (&arr)[N] ) noexcept;

   template< size_t N >
   constexpr span( array<value_type,N>& arr ) noexcept;

   template< size_t N >
   constexpr span( const array<value_type,N>& arr ) noexcept;

   template< typename Container >
   constexpr span( Container& cont, enable_if_is_neither_array_nor_span<Container>* = nullptr );

   template< typename Container >
   constexpr span( const Container& cont, enable_if_is_neither_array_nor_span<Container>* = nullptr );

   template< typename U >
   constexpr span( const span<U>& s, enable_if_is_convertible_array<U,element_type>* = nullptr ) noexcept;

   constexpr span( const span& other ) noexcept = default;
   constexpr span& operator=( const span& other ) noexcept = default;

   constexpr auto begin () const noexcept -> iterator;
   constexpr auto cbegin() const noexcept -> const_iterator;

   constexpr auto end () const noexcept -> iterator;
   constexpr auto cend() const noexcept -> const_iterator;

   constexpr auto rbegin () const noexcept -> reverse_iterator;
   constexpr auto crbegin() const noexcept -> const_reverse_iterator;

   constexpr auto rend () const noexcept -> reverse_iterator;
   constexpr auto crend() const noexcept -> const_reverse_iterator;

   constexpr auto front() const -> reference;
   constexpr auto back () const -> reference;

   constexpr auto operator[]( index_type idx ) const -> reference;

   constexpr auto data() const noexcept -> pointer;

   constexpr auto size() const noexcept -> index_type;
   /*[[nodiscard]]*/ constexpr bool empty() const noexcept;

   constexpr auto first( size_t count ) const -> span;
   constexpr auto last( size_t count ) const -> span;
   constexpr auto subspan( size_t offset, size_t count ) const -> span;

 private:
   T*     ptr_ { nullptr };
   size_t size_{ 0UL };
};


template< typename T >
constexpr span<T>::span( pointer ptr, index_type count )
   : ptr_ ( ptr )
   , size_( count )
{}

template< typename T >
constexpr span<T>::span( pointer first, pointer last )
   : ptr_ ( first )
   , size_( last - first )
{}

template< typename T >
template< size_t N >
constexpr span<T>::span( element_type (&arr)[N] ) noexcept
   : ptr_ ( arr )
   , size_( N )
{}

template< typename T >
template< size_t N >
constexpr span<T>::span( array<value_type,N>& arr ) noexcept
   : ptr_ ( arr.data() )
   , size_( N )
{}

template< typename T >
template< size_t N >
constexpr span<T>::span( const array<value_type,N>& arr ) noexcept
   : ptr_ ( arr.data() )
   , size_( N )
{}

template< typename T >
template< typename Container >
constexpr span<T>::span( Container& cont, enable_if_is_neither_array_nor_span<Container>* )
   : ptr_ ( data(cont) )
   , size_( size(cont) )
{}

template< typename T >
template< typename Container >
constexpr span<T>::span( const Container& cont, enable_if_is_neither_array_nor_span<Container>* )
   : ptr_ ( data(cont) )
   , size_( size(cont) )
{}

template< typename T >
template< typename U >
constexpr span<T>::span( const span<U>& s, enable_if_is_convertible_array<U,element_type>* ) noexcept
   : ptr_ ( s.data() )
   , size_( s.size() )
{}

template< typename T >
constexpr auto span<T>::begin() const noexcept -> iterator
{
   return ptr_;
}

template< typename T >
constexpr auto span<T>::cbegin() const noexcept -> const_iterator
{
   return ptr_;
}

template< typename T >
constexpr auto span<T>::end() const noexcept -> iterator
{
   return ptr_ + size_;
}

template< typename T >
constexpr auto span<T>::cend() const noexcept -> const_iterator
{
   return ptr_ + size_;
}

template< typename T >
constexpr auto span<T>::rbegin() const noexcept -> reverse_iterator
{
   return end() - 1UL;
}

template< typename T >
constexpr auto span<T>::crbegin() const noexcept -> const_reverse_iterator
{
   return end() - 1UL;
}

template< typename T >
constexpr auto span<T>::rend() const noexcept -> reverse_iterator
{
   return begin() - 1UL;
}

template< typename T >
constexpr auto span<T>::crend() const noexcept -> const_reverse_iterator
{
   return begin() - 1UL;
}

template< typename T >
constexpr auto span<T>::front() const -> reference
{
   assert( size_ > 0UL );
   return *begin();
}

template< typename T >
constexpr auto span<T>::back() const -> reference
{
   assert( size_ > 0UL );
   return *(end()-1UL);
}

template< typename T >
constexpr auto span<T>::operator[]( index_type idx ) const -> reference
{
   assert( idx < size_ );
   return ptr_[idx];
}

template< typename T >
constexpr auto span<T>::data() const noexcept -> pointer
{
   return ptr_;
}

template< typename T >
constexpr auto span<T>::size() const noexcept -> index_type
{
   return size_;
}

template< typename T >
/*[[nodiscard]]*/ constexpr bool span<T>::empty() const noexcept
{
   return size_ == 0UL;
}

template< typename T >
constexpr auto span<T>::first( size_t count ) const -> span
{
   assert( count <= size() );
   return span( ptr_, count );
}

template< typename T >
constexpr auto span<T>::last( size_t count ) const -> span
{
   assert( count <= size() );
   return span( ptr_+size_-count, count );
}

template< typename T >
constexpr auto span<T>::subspan( size_t offset, size_t count ) const -> span
{
   assert( offset < size() );
   assert( offset + count < size() );
   return span( ptr_+offset, count );
}


//*************************************************************************************************
// C++17 Deduction Guides
//*************************************************************************************************

template< typename T, size_t N >
span( T(&)[N] ) -> span<T>;

template< typename T, size_t N >
span( std::array<T,N>& ) -> span<T>;

template< typename T, size_t N >
span( const array<T,N>& ) -> span<const T>;

template< typename Container >
span( Container& ) -> span< typename Container::value_type >;

template< typename Container >
span( const Container& ) -> span< const typename Container::value_type >;


//*************************************************************************************************
// Namespace functions
//*************************************************************************************************

template< typename T >
constexpr auto begin( span<T> s ) noexcept
{
   return s.begin();
}

template< typename T >
constexpr auto end( span<T> s ) noexcept
{
   return s.end();
}

template< size_t I, class T >
constexpr T& get( span<T> s ) noexcept
{
   return s[I];
}

} // namespace std
