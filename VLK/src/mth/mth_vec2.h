/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_vec2.h
 * PURPOSE     : Ray tracing project.
 *               Main entry point module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 23.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_vec2_h_
#define __mth_vec2_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* 3D vector representation type */
  template<typename Type>
    class vec2
    {
    public:
      Type X, Y;  // vec2 coordinates

      vec2( VOID ): X(0), Y(0)
      {
      } /* End of 'vec2' function */

      vec2( Type a, Type b ): X(a), Y(b)
      {
      } /* End of 'vec2' function */

      explicit vec2( Type a ): X(a), Y(a)
      {
      } /* End of 'vec2' function */

      /* Obtain vector length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) vector length element.
       */
      Type operator!( VOID )
      {
        Type len = X * X + Y * Y;
        if (len == 1 || len == 0)
          return len;
        return sqrt(len);
      } /* End of 'operator!' function */

      /* Scalar product of 2 vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &b;
       * RETURNS:
       *   (Type) scalar product.
       */
      Type operator&( const vec2 &b )
      {
        return X * b.X + Y * b.Y;
      } /* End of 'operator&' function */

      /* Product of 2 vectors' components function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &b;
       * RETURNS:
       *   (vec2) result vector.
       */
      vec2 operator*( const vec2 &b )
      {
        return vec2(X * b.X, Y * b.Y);
      } /* End of 'operator*' function */

      /* Add two vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &b;
       * RETURNS:
       *   (vec2) new vector.
       */
      vec2 operator+( const vec2 &b )
      {
        return vec2(X + b.X, Y + b.Y);
      } /* End of 'operator+' function */

      /* Subtract two vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &b;
       * RETURNS:
       *   (vec2) new vector.
       */
      vec2 operator-( const vec2 &b )
      {
        return vec2(X - b.X, Y - b.Y);
      } /* End of 'operator-' function */

      /* Set negative vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec2) new vector.
       */
      vec2 operator-( VOID )
      {
        return vec2(-X, -Y);
      } /* End of 'operator-' function */

      /* Product of vector's components and number function.
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec2) new vector.
       */
      vec2 operator*( const Type &n )
      {
        return vec2(X * n, Y * n);
      } /* End of 'operator*' function */

      /* Divide vector's components and number function.
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec2) new vector.
       */
      vec2 operator/( const Type &n )
      {
        return vec2(X / n, Y / n);
      } /* End of 'operator/' function */

      /* Add vector to this vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &b;
       * RETURNS:
       *   (vec2 &) updated vector.
       */
      vec2 & operator+=( const vec2 &b )
      {
        X += b.X;
        Y += b.Y;
        return *this;
      } /* End of 'operator+=' function */

      /* Subtract vector from this vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &b;
       * RETURNS:
       *   (vec2 &) updated vector.
       */
      vec2 & operator-=( const vec2 &b )
      {
        X -= b.X;
        Y -= b.Y;
        return *this;
      } /* End of 'operator-=' function */

      /* Multiply vector with this vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &b;
       * RETURNS:
       *   (vec2 &) updated vector.
       */
      vec2 & operator*=( const vec2 &b )
      {
        X *= b.X;
        Y *= b.Y;
        return *this;
      } /* End of 'operator*=' function */

      /* Multiply number with this vector function.
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec2 &) updated vector.
       */
      vec2 & operator*=( const Type &n )
      {
        X *= n;
        Y *= n;
        return *this;
      } /* End of 'operator*=' function */

      /* Divide vector with this vector function.
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec2 &) updated vector.
       */
      vec2 & operator/=( const Type &n )
      {
        X /= n;
        Y /= n;
        return *this;
      } /* End of 'operator/=' function */

      /* Normalize this vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec2) normalized vector.
       */
      vec2 & Normalize( VOID )
      {
        *this /= !*this;
        return *this;
      } /* End of 'Normalize' function */

      /* Obtain normalized vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec2) normalized vector.
       */
      vec2 Normalizing( VOID ) const
      {
        return *this / !*this;
      } /* End of 'Normalizing' function */

      /* Create zero vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec2) zero vector.
       */
      vec2 Zero( VOID )
      {
        return vec2(0, 0);
      } /* End of 'Zero' function */

      /* Create random (0 to 1) vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec2) new vector.
       */
      vec2 Rnd0( VOID )
      {
        return vec2(rand() / (DBL)RAND_MAX, rand() / (DBL)RAND_MAX,  rand() / (DBL)RAND_MAX);
      } /* End of 'Rnd0' function */

      /* Create random (-1 to 1) vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec2) new vector.
       */
      vec2 Rnd1( VOID )
      {
        return vec2(rand() / (DBL)RAND_MAX * 2 - 1, rand() / (DBL)RAND_MAX * 2 - 1,  rand() / (DBL)RAND_MAX * 2 - 1);
      } /* End of 'Rnd1' function */

      /* Obtain vector's i component function.
       *   - index:
       *       const INT i;
       * RETURNS:
       *   (Type &) updated vector.
       */
      Type & operator[]( const INT i )
      {
        return i == 0 ? X : i == 1 ? Y : X;
      } /* End of 'operator[]' function */

      /* Obtain vector's first component's pointer function.
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (Type*) vector component pointer.
       */
      operator Type *( VOID )
      {
        return &X;
      } /* End of 'operator Type *' function */
      
      /* Count distance between vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec2 &P;
       * RETURNS:
       *   (Type) distance.
       */
      Type & Distance( const vec2 &P )
      {
        return !(P + (-*this));
      } /* End of 'Distance' function */

      //template<typename Type1>
      //  friend class matr<Type1>;
    }; /* End of 'vec2' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec2_h_ */

/* END OF 'mth_vec2.h' FILE */
