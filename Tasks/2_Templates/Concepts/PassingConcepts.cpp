/**************************************************************************************************
*
* \file PassingConcepts.cpp
* \brief C++ Training - Example for passing constraints as template parameters
*
* Copyright (C) 2015-2024 Klaus Iglberger - All Rights Reserved
*
* This file is part of the C++ training by Klaus Iglberger. The file may only be used in the
* context of the C++ training or with explicit agreement by Klaus Iglberger.
*
* Task: Consider the following example for how to pass constraints as template parameters.
*       Explain how the mechanics work. What are the pros and cons?
*
*       See also:
*       * Ed Catmur, "Higher-Order Template Metaprogramming (in C++23)"
*            (https://youtu.be/KENynEQoqCo?feature=shared)
*       * Filip Sajdak, "Advancing cppfront with Modern C++":
*            (https://youtu.be/nN3CPzioX_A?feature=shared)
*
**************************************************************************************************/

#include <cstdlib>
#include <concepts>


template< auto Constraint  // Non-type template parameter representing a constraint
        , typename T >     // The type to be constraint
concept satisfies_constraint =
   requires {
      { Constraint.template operator()<T>() };
   };

template< auto BoxConstraint, typename T >
   requires satisfies_constraint<BoxConstraint,T>
struct BoundingBox
{
   // Data member of type 'T'
};

template< typename T >
using IntegralBoundingBox = BoundingBox<[]<std::integral>{},T>;

template< typename T >
using FloatingBoundingBox = BoundingBox<[]<std::floating_point>{},T>;


int main()
{
   [[maybe_unused]] IntegralBoundingBox<int> a1;
   [[maybe_unused]] FloatingBoundingBox<float> b1;

   //[[maybe_unused]] IntegralBoundingBox<float> a2;  // Compilation error
   //[[maybe_unused]] FloatingBoundingBox<int> b2;    // Compilation error

   return EXIT_SUCCESS;
}

