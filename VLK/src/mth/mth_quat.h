/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_quat.h
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

#ifndef _mth_quat_h
#define _mth_quat_h

#include "mth_def.h"

/* Space math namespace */
namespace mth
{
  /* Quaternion representation type */
  template<typename Type>
    class quat
    {
    public:
      Type X, Y, Z, W;

      /* Default constructor function.
       * ARGUMENTS: None.
       * RETURNS: None.
       */
      quat( VOID ) : X(0), Y(0), Z(0), W(1)
      {
      } /* End of 'quat' function */

      /* Component-based constructor function.
       * ARGUMENTS:
       *   - X, Y, Z, W components:
       *       Type NewX, NewY, NewZ, NewW;
       * RETURNS: None.
       */
      quat( Type NewX, Type NewY, Type NewZ, Type NewW ) : X(NewX), Y(NewY), Z(NewZ), W(NewW)
      {
      } /* End of 'quat' function */

      ///* Vector-scalar constructor function.
      // * ARGUMENTS:
      // *   - vector part:
      // *       const vec3<Type> &V;
      // *   - scalar part:
      // *       Type S;
      // * RETURNS: None.
      // */
      //quat( const vec3<Type> &V, Type S );

      /* Obtain quaternion length function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) quaternion length.
       */
      Type operator!( VOID ) const
      {
        Type len = X * X + Y * Y + Z * Z + W * W;
        if (len == 1 || len == 0)
          return len;
        return std::sqrt(len);
      } /* End of 'operator!' function */

      /* Dot product of 2 quaternions function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (Type) dot product.
       */
      Type operator&( const quat &Q ) const
      {
        return X * Q.X + Y * Q.Y + Z * Q.Z + W * Q.W;
      } /* End of 'operator&' function */

      /* Add two quaternions function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat) result quaternion.
       */
      quat operator+( const quat &Q ) const
      {
        return quat(X + Q.X, Y + Q.Y, Z + Q.Z, W + Q.W);
      } /* End of 'operator+' function */

      /* Subtract two quaternions function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat) result quaternion.
       */
      quat operator-( const quat &Q ) const
      {
        return quat(X - Q.X, Y - Q.Y, Z - Q.Z, W - Q.W);
      } /* End of 'operator-' function */

      /* Negate quaternion function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (quat) negated quaternion.
       */
      quat operator-( VOID ) const
      {
        return quat(-X, -Y, -Z, -W);
      } /* End of 'operator-' function */

      /* Multiply quaternion by scalar function.
       * ARGUMENTS:
       *   - scalar value:
       *       const Type &S;
       * RETURNS:
       *   (quat) result quaternion.
       */
      quat operator*( const Type &S ) const
      {
        return quat(X * S, Y * S, Z * S, W * S);
      } /* End of 'operator*' function */

      /* Divide quaternion by scalar function.
       * ARGUMENTS:
       *   - scalar value:
       *       const Type &S;
       * RETURNS:
       *   (quat) result quaternion.
       */
      quat operator/( const Type &S ) const
      {
        return quat(X / S, Y / S, Z / S, W / S);
      } /* End of 'operator/' function */

      /* Add quaternion to this quaternion function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat &) updated quaternion reference.
       */
      quat & operator+=( const quat &Q )
      {
        X += Q.X;
        Y += Q.Y;
        Z += Q.Z;
        W += Q.W;
        return *this;
      } /* End of 'operator+=' function */

      /* Subtract quaternion from this quaternion function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat &) updated quaternion reference.
       */
      quat & operator-=( const quat &Q )
      {
        X -= Q.X;
        Y -= Q.Y;
        Z -= Q.Z;
        W -= Q.W;
        return *this;
      } /* End of 'operator-=' function */

      /* Multiply this quaternion by scalar function.
       * ARGUMENTS:
       *   - scalar value:
       *       const Type &S;
       * RETURNS:
       *   (quat &) updated quaternion reference.
       */
      quat & operator*=( const Type &S )
      {
        X *= S;
        Y *= S;
        Z *= S;
        W *= S;
        return *this;
      } /* End of 'operator*=' function */

      /* Divide this quaternion by scalar function.
       * ARGUMENTS:
       *   - scalar value:
       *       const Type &S;
       * RETURNS:
       *   (quat &) updated quaternion reference.
       */
      quat & operator/=( const Type &S )
      {
        X /= S;
        Y /= S;
        Z /= S;
        W /= S;
        return *this;
      } /* End of 'operator/=' function */

      /* Identity quaternion function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (quat) identity quaternion.
       */
      static quat Identity( VOID )
      {
        return quat(0, 0, 0, 1);
      } /* End of 'Identity' function */

      /* Quaternion conjugate function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (quat) conjugate quaternion.
       */
      quat Conjugate( VOID ) const
      {
        return quat(-X, -Y, -Z, W);
      } /* End of 'Conjugate' function */

      /* Quaternion inverse function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (quat) inverse quaternion.
       */
      quat Inverse( VOID ) const
      {
        Type norm = X * X + Y * Y + Z * Z + W * W;
        if (norm == 0)
          return Identity();
        return Conjugate() / norm;
      } /* End of 'Inverse' function */

      /* Quaternion multiplication function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat) result quaternion.
       */
      quat operator*( const quat &Q ) const
      {
        return quat(
          W * Q.X + X * Q.W + Y * Q.Z - Z * Q.Y,
          W * Q.Y - X * Q.Z + Y * Q.W + Z * Q.X,
          W * Q.Z + X * Q.Y - Y * Q.X + Z * Q.W,
          W * Q.W - X * Q.X - Y * Q.Y - Z * Q.Z);
      } /* End of 'operator*' function */

      /* Quaternion multiplication with assignment function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat &) result quaternion reference.
       */
      quat & operator*=( const quat &Q )
      {
        *this = *this * Q;
        return *this;
      } /* End of 'operator*=' function */

      /* Quaternion division function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat) result quaternion.
       */
      quat operator/( const quat &Q ) const
      {
        return *this * Q.Inverse();
      } /* End of 'operator/' function */

      /* Quaternion division with assignment function.
       * ARGUMENTS:
       *   - quaternion:
       *       const quat &Q;
       * RETURNS:
       *   (quat &) result quaternion reference.
       */
      quat & operator/=( const quat &Q )
      {
        *this = *this / Q;
        return *this;
      } /* End of 'operator/=' function */

      /* Normalize this quaternion function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (quat &) normalized quaternion reference.
       */
      quat & Normalize( VOID )
      {
        Type len = !*this;
        if (len != 0 && len != 1)
        {
          X /= len;
          Y /= len;
          Z /= len;
          W /= len;
        }
        return *this;
      } /* End of 'Normalize' function */

      /* Get normalized quaternion function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (quat) normalized quaternion.
       */
      quat Normalizing( VOID ) const
      {
        Type len = !*this;
        if (len == 0 || len == 1)
          return *this;
        return quat(X / len, Y / len, Z / len, W / len);
      } /* End of 'Normalizing' function */

      /* Create rotation quaternion from axis and angle function.
       * ARGUMENTS:
       *   - axis:
       *       const vec3<Type> &Axis;
       *   - angle in radians:
       *       Type Angle;
       * RETURNS:
       *   (quat) rotation quaternion.
       */
      static quat Rotate( const vec3<Type> &Axis, Type Angle )
      {
        Type HalfAngle = Angle * 0.5;
        Type SinHalf = sin(HalfAngle);
    
        return quat(
          Axis.X * SinHalf,
          Axis.Y * SinHalf,
          Axis.Z * SinHalf,
          cos(HalfAngle)
        ).Normalize();
      } /* End of 'Rotate' function */

      /* Spherical linear interpolation function.
       * ARGUMENTS:
       *   - target quaternion:
       *       const quat &To;
       *   - interpolation parameter (0 to 1):
       *       Type T;
       * RETURNS:
       *   (quat) interpolated quaternion.
       */
      quat SLerp( const quat &To, Type T ) const
      {
        quat to = To;

        Type CoTetta = X * to.X + Y * to.Y + Z * to.Z + W * to.W;

        if (CoTetta < 0)
        {
          to = quat(-to.X, -to.Y, -to.Z, -to.W);
          CoTetta = -CoTetta;
        }

        Type k0, k1;
        if (CoTetta > 0.9999)
        {
          k0 = 1 - T;
          k1 = T;
        }
        else
        {
          Type SinTetta = sqrt(1 - CoTetta * CoTetta);
          Type Tetta = atan2(SinTetta, CoTetta);
          Type InvSinTetta = 1 / SinTetta;
  
          k0 = sin((1 - T) * Tetta) * InvSinTetta;
          k1 = sin(T * Tetta) * InvSinTetta;
        }

        return quat(
          X * k0 + to.X * k1,
          Y * k0 + to.Y * k1,
          Z * k0 + to.Z * k1,
          W * k0 + to.W * k1).Normalize();
      } /* End of 'SLerp' function */

      /* Get rotation axis function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (vec3<Type>) rotation axis.
       */
      vec3<Type> GetAxis( VOID ) const
      {
        Type sinTheta = sqrt(1 - W * W);
        if (sinTheta < 0.0001)
          return vec3<Type>(1, 0, 0);
        return vec3<Type>(X, Y, Z) / sinTheta;
      } /* End of 'GetAxis' function */

      /* Get rotation angle function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type) rotation angle in radians.
       */
      Type GetAngle( VOID ) const
      {
        return 2 * std::acos(W);
      } /* End of 'GetAngle' function */

      /* Obtain quaternion's i component function.
       * ARGUMENTS:
       *   - index:
       *       const INT i;
       * RETURNS:
       *   (Type &) component reference.
       */
      Type & operator[]( const INT i )
      {
        return i == 0 ? X : i == 1 ? Y : i == 2 ? Z : W;
      } /* End of 'operator[]' function */

      /* Obtain quaternion's i component function (const version).
       * ARGUMENTS:
       *   - index:
       *       const INT i;
       * RETURNS:
       *   (Type) component value.
       */
      Type operator[]( const INT i ) const
      {
        return i == 0 ? X : i == 1 ? Y : i == 2 ? Z : W;
      } /* End of 'operator[]' function */

      /* Obtain quaternion's first component's pointer function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (Type*) quaternion component pointer.
       */
      operator Type *( VOID )
      {
        return &X;
      } /* End of 'operator Type *' function */

      /* Obtain quaternion's first component's pointer function (const version).
       * ARGUMENTS: None.
       * RETURNS:
       *   (const Type*) quaternion component pointer.
       */
      operator const Type *( VOID ) const
      {
        return &X;
      } /* End of 'operator const Type *' function */
    }; /* End of 'quat' class */
} /* End of 'mth' namespace */

#endif /* _mth_quat_h */

/* END OF 'mth_quat.h' FILE */
