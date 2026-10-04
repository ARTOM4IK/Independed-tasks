/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_vec4.h
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

#ifndef __mth_vec4_h_
#define __mth_vec4_h_

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* 3D vector representation type */
  template<typename Type>
    class vec4
    {
    public:
      Type X, Y, Z, W;  // vec4 coordinates

      vec4( VOID ): X(0), Y(0), Z(0), W(0)
      {
      } /* End of 'vec4' function */

      vec4( Type a, Type b, Type c, Type d ): X(a), Y(b), Z(c), W(d)
      {
      } /* End of 'vec4' function */
      vec4( vec3<Type> a ): X(a.X), Y(a.Y), Z(a.Z), W(0)
      {
      } /* End of 'vec4' function */
      vec4( vec3<Type> a, Type b ): X(a.X), Y(a.Y), Z(a.Z), W(b)
      {
      } /* End of 'vec4' function */

      explicit vec4( Type a ): X(a), Y(a), Z(a), W(a)
      {
      } /* End of 'vec4' function */

      /* Obtain vector length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) vector length element.
       */
      Type operator!( VOID )
      {
        Type len = X * X + Y * Y + Z * Z + W * W;
        if (len == 1 || len == 0)
          return len;
        return sqrt(len);
      }

      /* Scalar product of 2 vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (Type) scalar product.
       */
      vec4 operator&( const vec4 &b )
      {
        return X * b.X + Y * b.Y + Z * b.Z + W * b.W;
      }

      /* Product of 2 vectors' components function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (vec3) result vector.
       */
      vec4 operator*( const vec4 &b )
      {
        return vec4(X * b.X, Y * b.Y, Z * b.Z, W * b.W);
      }

      /* Add two vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec4 operator+( const vec4 &b )
      {
        return vec4(X + b.X, Y + b.Y, Z + b.Z, W + b.W);
      }

      /* Subtract two vectors function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec4 operator-( const vec4 &b )
      {
        return vec4(X - b.X, Y - b.Y, Z - b.Z, W - b.W);
      } /* End of 'operator-' function */

      /* Set negative vector function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3) new vector.
       */
      vec4 operator-( VOID ) 
      {
        return vec4(-X, -Y, -Z, -W);
      } /* End of 'operator-' function */
  
      /* Product of vector's components and number function.
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec4 operator*( const Type &n )
      {
        return vec4(X * n, Y * n, Z * n, W * n);
      } /* End of 'operator*' function */

      /* Divide vector's components and number function.
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec3) new vector.
       */
      vec4 operator/( const Type &n )
      {
        return vec4(X / n, Y / n, Z / n, W / n);
      } /* End of 'operator/' function */

      /* Add vector to this vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (vec3 &) updated vector.
       */
      vec4 & operator+=( const vec4 &b  )
      {
        X += b.X;
        Y += b.Y;
        Z += b.Z;
        W += b.W;
        return *this;
      } /* End of 'operator+=' function */

      /* Subtract vector from this vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (vec3 &) updated vector.
       */
      vec4 & operator-=( const vec4 &b )
      {
        X -= b.X;
        Y -= b.Y;
        Z -= b.Z;
        W -= b.W;
        return *this;
      } /* End of 'operator-=' function */

      /* Multiply vector with this vector function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3 &b;
       * RETURNS:
       *   (vec3 &) updated vector.
       */
      vec4 & operator*=( const vec4 &b )
      {
        X *= b.X;
        Y *= b.Y;
        Z *= b.Z;
        W /= b.W;
        return *this;
      } /* End of 'operator*=' function */

      /* Multiply number with this vector function.
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec3 &) updated vector.
       */
      vec4 & operator*=( const Type &n )
      {
        X *= n;
        Y *= n;
        Z *= n;
        W *= n;
        return *this;
      } /* End of 'operator*=' function */

      /* Divide vector with this vector function.
       *   - number:
       *       const Type &n;
       * RETURNS:
       *   (vec3 &) updated vector.
       */
      vec4 & operator/=( const Type &n )
      {
        X /= n;
        Y /= n;
        Z /= n;
        W /= n;
        return *this;
      } /* End of 'operator/=' function */

      /* Normalize this vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec3) normalized vector.
       */
      vec4 & Normalize( VOID )
      {
        *this /= !*this;
        return *this;
      } /* End of 'Normalize' function */

      /* Obtain normalized vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec3) normalized vector.
       */
      vec4 Normalizing( VOID ) const
      {
        return *this / !*this;
      } /* End of 'Normalizing' function */

      /* Create zero vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec2) zero vector.
       */
      vec4 Zero( VOID )
      {
        return vec4(0, 0, 0, 0);
      } /* End of 'Zero' function */

      /* Create random (0 to 1) vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec2) new vector.
       */
      vec4 Rnd0( VOID )
      {
        return vec4(rand() / (DBL)RAND_MAX, rand() / (DBL)RAND_MAX, rand() / (DBL)RAND_MAX, rand() / (DBL)RAND_MAX);
      } /* End of 'Rnd0' function */

      /* Create random (-1 to 1) vector function.
       * ARGUMENTS: None;
       * RETURNS: (vec2) new vector.
       */
      vec4 Rnd1( VOID )
      {
        return vec4(rand() / (DBL)RAND_MAX * 2 - 1, rand() / (DBL)RAND_MAX * 2 - 1, rand() / (DBL)RAND_MAX * 2 - 1, rand() / (DBL)RAND_MAX * 2 - 1);
      } /* End of 'Rnd1' function */

      /* Obtain vector's i component function.
       *   - index:
       *       const INT i;
       * RETURNS:
       *   (Type &) updated vector.
       */
      Type & operator[]( const INT i )
      {
        return i == 0 ? X : i == 1 ? Y : i == 2 ? Z : i == 3 ? W : X;
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
      Type & Distance( const vec4 &P )
      {
        return !(P + (-*this));
      } /* End of 'Distance' function */

      //template<typename Type1>
      //  friend class matr<Type1>;
    }; /* End of 'vec4' class */
} /* end of 'mth' namespace */

#endif /* __mth_vec4_h_ */

/* END OF 'mth_vec4.h' FILE */
