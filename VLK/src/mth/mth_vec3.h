/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_vec3.h
 * PURPOSE     : Ray tracing project.
 *               Main entry point module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 22.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_vec3_h_
#define __mth_vec3_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* 3D vector representation type */
  template<typename Type>
    class vec3
    {
    public:
      Type X, Y, Z;  // vec3 coordinates

      vec3( VOID ): X(0), Y(0), Z(0)
      {
      } /* End of 'vec3' function */

      vec3( Type a, Type b, Type c ): X(a), Y(b), Z(c)
      {
      } /* End of 'vec3' function */

      explicit vec3( Type a ): X(a), Y(a), Z(a)
      {
      } /* End of 'vec3' function */

      /* Obtain vector length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) vector length element.
       */
      Type operator!( VOID ) const
      {
        Type len = X * X + Y * Y + Z * Z;
        if (len == 1 || len == 0)
          return len;
        return sqrt(len);
      } /* End of 'operator!' function */

      /* Scalar product of 2 vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (Type) scalar product.
       */
      Type operator&( const vec3 &b ) const
      {
        return X * b.X + Y * b.Y + Z * b.Z;
      } /* End of 'operator&' function */

      /* Vector product of 2 vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (Type) scalar product.
       */
      vec3 operator%( const vec3 &b ) const
      {
        return vec3(Y * b.Z - Z * b.Y, Z * b.X - X * b.Z, X * b.Y - Y * b.X);
      } /* End of 'operator%' function */

      /* Product of 2 vectors' components function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 operator*( const vec3 &b ) const
      {
        return vec3(X * b.X, Y * b.Y, Z * b.Z);
      } /* End of 'operator*' function */

      /* Add two vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator+( const vec3 &b ) const
      {
        return vec3(X + b.X, Y + b.Y, Z + b.Z);
      } /* End of 'operator+' function */

      /* Subtract two vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator-( const vec3 &b ) const
      {
        return vec3(X - b.X, Y - b.Y, Z - b.Z);
      } /* End of 'operator-' function */

      /* Set negative vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator-( VOID ) const
      {
        return vec3(-X, -Y, -Z);
      } /* End of 'operator-' function */

      /* Product of vector's components and number function.
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator*( const Type &n ) const
      {
        return vec3(X * n, Y * n, Z * n);
      } /* End of 'operator*' function */

      /* Divide vector's components and number function.
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec3 operator/( const Type &n ) const
      {
        return vec3(X / n, Y / n, Z / n);
      } /* End of 'operator/' function */

      /* Add vector to this vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (vec3 &) updated vector.
       */
      vec3 & operator+=( const vec3 &b )
      {
        X += b.X;
        Y += b.Y;
        Z += b.Z;
        return *this;
      } /* End of 'operator+=' function */

      /* Subtract vector from this vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (vec3 &) updated vector.
       */
      vec3 & operator-=( const vec3 &b )
      {
        X -= b.X;
        Y -= b.Y;
        Z -= b.Z;
        return *this;
      } /* End of 'operator-=' function */

      /* Multiply vector with this vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (vec3 &) updated vector.
       */
      vec3 & operator*=( const vec3 &b )
      {
        X *= b.X;
        Y *= b.Y;
        Z *= b.Z;
        return *this;
      } /* End of 'operator*=' function */

      /* Multiply number with this vector function.
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec3 &) updated vector.
       */
      vec3 & operator*=( const Type &n )
      {
        X *= n;
        Y *= n;
        Z *= n;
        return *this;
      } /* End of 'operator*=' function */

      /* Divide vector with this vector function.
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec3 &) updated vector.
       */
      vec3 & operator/=( const Type &n )
      {
        if (n == 0)
        {
          X = 0;
          Y = 0;
          Z = 0;
        }
        else
        {
          X /= n;
          Y /= n;
          Z /= n;
        }
        return *this;
      } /* End of 'operator/=' function */

      /* Normalize this vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec3) normalized vector.
       */
      vec3 & Normalize( VOID )
      {
        *this /= !*this;
        return *this;
      } /* End of 'Normalize' function */

      /* Obtain normalized vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec3) normalized vector.
       */
      vec3 Normalizing( VOID ) const
      {
        return *this / !*this;
      } /* End of 'Normalizing' function */

      /* Create zero vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec3) zero vector.
       */
      static vec3 Zero( VOID )
      {
        return vec3(0, 0, 0);
      } /* End of 'Zero' function */

      /* Create random (0 to 1) vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec3) new vector.
       */
      static vec3 Rnd0( VOID )
      {
        return vec3(rand() / (DBL)RAND_MAX, rand() / (DBL)RAND_MAX,  rand() / (DBL)RAND_MAX);
      } /* End of 'Rnd0' function */

      /* Create random (-1 to 1) vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec3) new vector.
       */
      static vec3 Rnd1( VOID )
      {
        return vec3(rand() / (DBL)RAND_MAX * 2 - 1, rand() / (DBL)RAND_MAX * 2 - 1,  rand() / (DBL)RAND_MAX * 2 - 1);
      } /* End of 'Rnd1' function */

      /* Obtain vector's i component function.
       *   - index:
       *       const INT i;
       * RETURNS:
       *   (Type &) updated vector.
       */
      Type operator[]( INT i ) const
      {
        return i == 0 ? X : i == 1 ? Y : i == 2 ? Z : X;
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
       *       const vec3 &V;
       * RETURNS:
       *   (Type) distance.
       */
      Type Distance( const vec3 &P )
      {
        return !(P + (-(*this)));
      } /* End of 'Distance' function */

      Type Length2( VOID )
      {
        return X * X + Y * Y + Z * Z;
      }

      Type MaxC( VOID )
      {
        return X ? X > Y && X > Z : Y ? Y > X && Y > Z : Z ? Z > Y && Z > X : X;
      }

      /* Minimum of two vectors  function.
       * ARGUMENTS:
       *   - vector to be compared to:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 Min( const vec3 &V ) const
      {
        return vec3(mth::Min(X, V.X), mth::Min(Y, V.Y), mth::Min(Z, V.Z));
      } /* End of 'Min' function */

      /* Minimum of two vectors  function.
       * ARGUMENTS:
       *   - vector to be compared to:
       *       const vec3 &V;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec3 Max( const vec3 &V ) const
      {
        return vec3(mth::Max(X, V.X), mth::Max(Y, V.Y), mth::Max(Z, V.Z));
      } /* End of 'Max' function */

      //template<typename Type1>
      //  friend class matr<Type1>;
    }; /* End of 'vec3' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec3_h_ */

/* END OF 'mth_vec3.h' FILE */
