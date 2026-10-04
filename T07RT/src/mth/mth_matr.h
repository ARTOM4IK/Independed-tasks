/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_matr.h
 * PURPOSE     : Raytracing project.
 *               Mathematics library.
 *               Math matrix module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 23.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_matr_h_
#define __mth_matr_h_

#include "mth_def.h"

/* Math library namespace */
namespace mth
{
  /* Matrix bare data type */
  template<class type>
    struct matr_data
    {
    public:
      /* Transformation matrix */
      type M[4][4];
 
      /* Class constructor 
       * ARGUMENTS: None.
       */
      matr_data( VOID )
      {
      } /* End of 'matr_data' function */
 
      /* Class constructor.
        * ARGUMENTS:
        *   - source matrix:
        *       const type Mtr[4][4];
        */
      matr_data( const type Mtr[4][4] )
      {
        CopyMemory(M, Mtr, sizeof(type) * 16);
      } /* End of 'matr_data' function */
    }; /* End of 'matr_data' structure */
 
  /* Space transformation matrix handle class */
  template<class type>
    class matr : public matr_data<type>
    {
    private:
      /* Transformation matrix */
      //type M[4][4];
 
      /* Inverse matrix and it presence flag */
      mutable BOOL IsInverseObtain;
      mutable type InverseM[4][4];
 
    public:
      /* Class default constructor */
      matr( VOID ) : IsInverseObtain(FALSE)
      {
      } /* End of 'matr' function */

      /* Obtain matrix identity function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) matrix identity.
       */
      static matr Identity( VOID )
      {
        return matr(1, 0, 0, 0,
                    0, 1, 0, 0,
                    0, 0, 1, 0,
                    0, 0, 0, 1);
      } /* End of 'Identity' function */

      /* Count inversed matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) invesred matrix.
       */
      VOID EvaluateInverseMatrix( VOID ) const
      {
        if (IsInverseObtain)
          return;
        IsInverseObtain = TRUE;
        type det = Determ();
        const type (*M1)[4] = matr_data<type>::M;

        if (det == 0)
        {
          InverseM[0][0] = 1;
          InverseM[0][1] = 0;
          InverseM[0][2] = 0;
          InverseM[0][3] = 0;
          InverseM[1][0] = 0;
          InverseM[1][1] = 1;
          InverseM[1][2] = 0;
          InverseM[1][3] = 0;
          InverseM[2][0] = 0;
          InverseM[2][1] = 0;
          InverseM[2][2] = 1;
          InverseM[2][3] = 0;
          InverseM[3][0] = 0;
          InverseM[3][1] = 0;
          InverseM[3][2] = 0;
          InverseM[3][3] = 1;
          return;
        }

        /* Build adjoint matrix */
        InverseM[0][0] =  Determ3x3(M1[1][1], M1[1][2], M1[1][3],
                                 M1[2][1], M1[2][2], M1[2][3],
                                 M1[3][1], M1[3][2], M1[3][3]) / det;
        InverseM[1][0] = -Determ3x3(M1[1][0], M1[1][2], M1[1][3],
                                 M1[2][0], M1[2][2], M1[2][3],
                                 M1[3][0], M1[3][2], M1[3][3]) / det;
        InverseM[2][0] =  Determ3x3(M1[1][0], M1[1][1], M1[1][3],
                                 M1[2][0], M1[2][1], M1[2][3],
                                 M1[3][0], M1[3][1], M1[3][3]) / det;
        InverseM[3][0] = -Determ3x3(M1[1][0], M1[1][1], M1[1][2],
                                 M1[2][0], M1[2][1], M1[2][2],
                                 M1[3][0], M1[3][1], M1[3][2]) / det;
        InverseM[0][1] = -Determ3x3(M1[0][1], M1[0][2], M1[0][3],
                                 M1[2][1], M1[2][2], M1[2][3],
                                 M1[3][1], M1[3][2], M1[3][3]) / det;
        InverseM[1][1] =  Determ3x3(M1[0][0], M1[0][2], M1[0][3],
                                 M1[2][0], M1[2][2], M1[2][3],
                                 M1[3][0], M1[3][2], M1[3][3]) / det;
        InverseM[2][1] = -Determ3x3(M1[0][0], M1[0][1], M1[0][3],
                                 M1[2][0], M1[2][1], M1[2][3],
                                 M1[3][0], M1[3][1], M1[3][3]) / det;
        InverseM[3][1] =  Determ3x3(M1[0][0], M1[0][1], M1[0][2],
                                 M1[2][0], M1[2][1], M1[2][2],
                                 M1[3][0], M1[3][1], M1[3][2]) / det;
        InverseM[0][2] =  Determ3x3(M1[0][1], M1[0][2], M1[0][3],
                                 M1[1][1], M1[1][2], M1[1][3],
                                 M1[3][1], M1[3][2], M1[3][3]) / det;
        InverseM[1][2] = -Determ3x3(M1[0][0], M1[0][2], M1[0][3],
                                 M1[1][0], M1[1][2], M1[1][3],
                                 M1[3][0], M1[3][2], M1[3][3]) / det;
        InverseM[2][2] =  Determ3x3(M1[0][0], M1[0][1], M1[0][3],
                                 M1[1][0], M1[1][1], M1[1][3],
                                 M1[3][0], M1[3][1], M1[3][3]) / det;
        InverseM[3][2] = -Determ3x3(M1[0][0], M1[0][1], M1[0][2],
                                 M1[1][0], M1[1][1], M1[1][2],
                                 M1[3][0], M1[3][1], M1[3][2]) / det;
        InverseM[0][3] = -Determ3x3(M1[0][1], M1[0][2], M1[0][3],
                                 M1[1][1], M1[1][2], M1[1][3],
                                 M1[2][1], M1[2][2], M1[2][3]) / det;
        InverseM[1][3] =  Determ3x3(M1[0][0], M1[0][2], M1[0][3],
                                 M1[1][0], M1[1][2], M1[1][3],
                                 M1[2][0], M1[2][2], M1[2][3]) / det;
        InverseM[2][3] = -Determ3x3(M1[0][0], M1[0][1], M1[0][3],
                                 M1[1][0], M1[1][1], M1[1][3],
                                 M1[2][0], M1[2][1], M1[2][3]) / det;
        InverseM[3][3] =  Determ3x3(M1[0][0], M1[0][1], M1[0][2],
                                 M1[1][0], M1[1][1], M1[1][2],
                                 M1[2][0], M1[2][1], M1[2][2]) / det;
      } /* End of 'EvaluateInverseMatrix' function */

      /* Matrix constructor.
       * ARGUMENTS:
       *   - matrix 4x4 values:
       *       type
       *         A00, A01, A02, A03,
       *         A10, A11, A12, A13,
       *         A20, A21, A22, A23,
       *         A30, A31, A32, A33;
       */
      matr( type A00, type A01, type A02, type A03,
            type A10, type A11, type A12, type A13,
            type A20, type A21, type A22, type A23,
            type A30, type A31, type A32, type A33 ) : IsInverseObtain(FALSE)
      {
        type (*M)[4] = matr_data<type>::M;
 
        M[0][0] = A00, M[0][1] = A01, M[0][2] = A02, M[0][3] = A03;
        M[1][0] = A10, M[1][1] = A11, M[1][2] = A12, M[1][3] = A13;
        M[2][0] = A20, M[2][1] = A21, M[2][2] = A22, M[2][3] = A23;
        M[3][0] = A30, M[3][1] = A31, M[3][2] = A32, M[3][3] = A33;
      } /* End of 'matr' function */
 
      /* Class constructor.
       * ARGUMENTS:
       *   - matrix elements:
       *       type R[4][4];
       */
      matr( type R[4][4] ) : IsInverseObtain(FALSE)
      {
        CopyMemory(matr_data<type>::M, R, sizeof(matr_data<type>::M));
      } /* End of 'matr' function */
 
      /* Obtain matrix first element pointer function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (type *) pointer to A00 element.
       */
      operator type *( VOID )
      {
        return matr_data<type>::M[0];
      } /* End of 'operator type *' function */
 
       /* Obtain product of 2 matrixes function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr<type>) product.
       */
      matr<type> operator*( const matr &M )
      {
        type (*M1)[4] = matr_data<type>::M;
        return matr(M.M[0][0] * M1[0][0] + M.M[0][1] * M1[1][0] + M.M[0][2] * M1[2][0] + M.M[0][3] * M1[3][0],
                       M.M[0][0] * M1[0][1] + M.M[0][1] * M1[1][1] + M.M[0][2] * M1[2][1] + M.M[0][3] * M1[3][1],
                       M.M[0][0] * M1[0][2] + M.M[0][1] * M1[1][2] + M.M[0][2] * M1[2][2] + M.M[0][3] * M1[3][2],
                       M.M[0][0] * M1[0][3] + M.M[0][1] * M1[1][3] + M.M[0][2] * M1[2][3] + M.M[0][3] * M1[3][3],
                       M.M[1][0] * M1[0][0] + M.M[1][1] * M1[1][0] + M.M[1][2] * M1[2][0] + M.M[1][3] * M1[3][0],
                       M.M[1][0] * M1[0][1] + M.M[1][1] * M1[1][1] + M.M[1][2] * M1[2][1] + M.M[1][3] * M1[3][1],
                       M.M[1][0] * M1[0][2] + M.M[1][1] * M1[1][2] + M.M[1][2] * M1[2][2] + M.M[1][3] * M1[3][2],
                       M.M[1][0] * M1[0][3] + M.M[1][1] * M1[1][3] + M.M[1][2] * M1[2][3] + M.M[1][3] * M1[3][3],
                       M.M[2][0] * M1[0][0] + M.M[2][1] * M1[1][0] + M.M[2][2] * M1[2][0] + M.M[2][3] * M1[3][0],
                       M.M[2][0] * M1[0][1] + M.M[2][1] * M1[1][1] + M.M[2][2] * M1[2][1] + M.M[2][3] * M1[3][1],
                       M.M[2][0] * M1[0][2] + M.M[2][1] * M1[1][2] + M.M[2][2] * M1[2][2] + M.M[2][3] * M1[3][2],
                       M.M[2][0] * M1[0][3] + M.M[2][1] * M1[1][3] + M.M[2][2] * M1[2][3] + M.M[2][3] * M1[3][3],
                       M.M[3][0] * M1[0][0] + M.M[3][1] * M1[1][0] + M.M[3][2] * M1[2][0] + M.M[3][3] * M1[3][0],
                       M.M[3][0] * M1[0][1] + M.M[3][1] * M1[1][1] + M.M[3][2] * M1[2][1] + M.M[3][3] * M1[3][1],
                       M.M[3][0] * M1[0][2] + M.M[3][1] * M1[1][2] + M.M[3][2] * M1[2][2] + M.M[3][3] * M1[3][2],
                       M.M[3][0] * M1[0][3] + M.M[3][1] * M1[1][3] + M.M[3][2] * M1[2][3] + M.M[3][3] * M1[3][3]);
      } /* End of 'matr operator*' function */

      /* Obtain matrix first element pointer function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (const type *) pointer to A00 element.
       */
      operator const type *( VOID ) const
      {
        return matr_data<type>::M[0];
      } /* End of 'operator const type *' function */

      /* 3x3 matrix determination function.
       * ARGUMENTS:
       *   - 3x3 matrix:
       *       MATR M;
       * RETURNS:
       *   (MATR) result matrix.
       */
      static type Determ3x3( const type &A11, const type &A12, const type &A13, const type &A21, const type &A22, const type &A23, const type &A31, const type &A32, const type &A33 )
      {
        return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 - A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
      } /* End of 'MatrDeterm3x3' function */

      /* Matrix determination function.
       * ARGUMENTS:
       *   - Matrix:
       *       MATR M;
       * RETURNS:
       *   (MATR) result matrix.
       */
      type Determ( VOID ) const
      {
        const type (*M)[4] = matr_data<type>::M;
        return
          M[0][0] * Determ3x3(M[1][1], M[1][2], M[1][3],
                                    M[2][1], M[2][2], M[2][3],
                                    M[3][1], M[3][2], M[3][3]) +
          -M[0][1] * Determ3x3(M[1][0], M[1][2], M[1][3],
                                     M[2][0], M[2][2], M[2][3],
                                     M[3][0], M[3][2], M[3][3]) +
          M[0][2] * Determ3x3(M[1][0], M[1][1], M[1][3],
                                    M[2][0], M[2][1], M[2][3],
                                    M[3][0], M[3][1], M[3][3]) +
          -M[0][3] * Determ3x3(M[1][0], M[1][1], M[1][2],
                                     M[2][0], M[2][1], M[2][2],
                                     M[3][0], M[3][1], M[3][2]);
      } /* End of 'MatrDeterm' function */

      /* Obtain inverse matrix function.
       * ARGUMENTS: None.
       * RETURNS:
       *   (matr) result matrix.
       */
      matr<type> Inverse( VOID ) 
      {
        EvaluateInverseMatrix();
        return matr<type>(InverseM);
      } /* End of 'Inverse' function */

      /* Matrix transpose function.
       * ARGUMENTS:
       *   - Matrix:
       *       MATR M;
       * RETURNS:
       *   (matr<type>) result matrix.
       */
      matr<type> Transpose( VOID ) const
      {
        const type (*M)[4] = matr_data<type>::M;

        return matr<type>(M[0][0], M[1][0], M[2][0], M[3][0],
                       M[0][1], M[1][1], M[2][1], M[3][1],
                       M[0][2], M[1][2], M[2][2], M[3][2],
                       M[0][3], M[1][3], M[2][3], M[3][3]);

      }  /* End of 'MatrTranspose' function */
 
      /* Obtain translation matrix function.
       * ARGUMENTS:
       *   - coordinates delta values:
       *       type Dx, Dy, Dz;
       * RETURNS:
       *   (matr<type>) translate transformatrion matrix.
       */
      static matr<type> Translate( type Dx, type Dy, type Dz )
      {
        return matr<type>(1,  0,  0,  0,
                    0,  1,  0,  0,
                    0,  0,  1,  0,
                    Dx, Dy, Dz, 1);
      } /* End of 'Translate' function */
 
      /* Obtain translation matrix function.
       * ARGUMENTS:
       *   - vector delta value:
       *       const vec3<type> &D;
       * RETURNS:
       *   (matr) translate transformatrion matrix.
       */
      static matr<type> Translate( const vec3<type> &D )
      {
        return matr<type>(1,  0,  0,  0,
                    0,  1,  0,  0,
                    0,  0,  1,  0,
                    D.X, D.Y, D.Z, 1);
      } /* End of 'Translate' function */

      /* Matrix scale function.
       * ARGUMENTS:
       *   - vector:
       *       const vec3<type> &S;
       * RETURNS:
       *   (matr<type>) result matrix.
       */
      static matr<type> Scale( const vec3<type> &S )
      {
        return matr<type>(S.X, 0, 0, 0,
                       0, S.Y, 0, 0,
                       0, 0, S.Z, 0,
                       0, 0, 0, 1);

      } /* End of 'Scale' function */

      /* Rotate matrix by axis Z function.
       * ARGUMENTS:
       *   - Angle in degrees:
       *       const type &AngleInDegree;
       * RETURNS:
       *   (matr<type>) result matrix.
       */
      static matr<type> RotateZ( const type &AngleInDegree )
      {
        FLT co = cos(D2R(AngleInDegree)), si = sin(D2R(AngleInDegree)); /* Cos and sin of an angle */

        return matr<type>(co, si, 0, 0,
                       -si, co, 0, 0,
                       0, 0, 1, 0,
                       0, 0, 0, 1);

      } /* End of 'RotateZ' function */

      /* Rotate matrix by axis X function.
       * ARGUMENTS:
       *   - Angle in degrees:
       *       const type &AngleInDegree;
       * RETURNS:
       *   (matr<type>) result matrix.
       */
      static matr<type> RotateX( const type &AngleInDegree )
      {
        FLT co = cos(D2R(AngleInDegree)), si = sin(D2R(AngleInDegree)); /* Cos and sin of an angle */

        return matr<type>(1, 0, 0, 0,
                       0, co, si, 0,
                       0, -si, co, 0,
                       0, 0, 0, 1);
      } /* End of 'RotateX' function */

      /* Rotate matrix by axis Y function.
       * ARGUMENTS:
       *   - Angle in degrees:
       *       const type &AngleInDegree;
       * RETURNS:
       *   (matr<type>) result matrix.
       */
      static matr<type> RotateY( const type &AngleInDegree )
      {
        DBL co = cos(D2R(AngleInDegree)), si = sin(D2R(AngleInDegree)); /* Cos and sin of an angle */

        return matr<type>(co, 0, -si, 0,
                       0, 1, 0, 0,
                       si, 0, co, 0,
                       0, 0, 0, 1);
      } /* End of 'RotateY' function */

      /* Rotate vector function.
       * ARGUMENTS:
       *   - Angle in degrees:
       *       const type &AngleInDegree;
       *   - Vector:
       *       const vec3<type> &V;
       * RETURNS:
       *   (matr<type>) result matrix.
       */
      static matr<type> Rotate( const type &AngleInDegree, const vec3<type> &V )
      {
        type A = D2R(AngleInDegree), s = sin(A), c = cos(A); /* Cos and sin of an angle */
        vec3<type> R = V.Normalizing();                      /* Normalized vector */
        type x = R.X, y = R.Y, z = R.Z;

        return matr<type>(x * x * (1 - c) + c, x * y * (1 - c) + z * s, x * z * (1 - c) - y * s, 0,
                       x * y * (1 - c) - z * s, y * y * (1 - c) + c, y * z * (1 - c) + x * s, 0,
                       x * z * (1 - c) + y * s, y * z * (1 - c) - x * s, z * z * (1 - c) + c, 0,
                       0, 0, 0, 1);
      } /* End of 'Rotate' function */

      /* Set view with matrix function.
       * ARGUMENTS:
       *   - View parametrs:
       *       VEC Loc, VEC At, VEC Up1.
       * RETURNS:
       *   (matr<type>) Matrix.
       */
      static matr<type> View( const vec3<type> &Loc, const vec3<type> &At, const vec3<type> &Up1 )
      {
        vec3
          Dir = VecNormalize(VecSubVec(At, Loc)),
          Right = VecNormalize(VecCrossVec(Dir, Up1)),
          Up = VecCrossVec(Right, Dir);
        matr<type> m =
        {
          {
            {Right.X, Up.X, -Dir.X, 0},
            {Right.Y, Up.Y, -Dir.Y, 0},
            {Right.Z, Up.Z, -Dir.Z, 0},
            {-VecDotVec(Loc, Right), - VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
          }
        };
        return m;
      } /* End of 'View' function */
 
      /* Set point in space function.
       * ARGUMENTS:
       *   - Parametrs of point:
       *       const type &l, const type &r, const type &b, const type &t, const type &n, const type &f.
       * RETURNS:
       *   (matr<type>) result matrix.
       */
      static matr<type> Frustum( const type &Left, const type &Right, const type &Bottom, const type &Top, const type &Near, const type &Far )
      {
        return matr<type>(2 * Near / (Right - Left), 0, 0, 0,
                       0, 2 * Near / (Top - Bottom), 0, 0,
                       (Right + Left) / (Right - Left), (Top + Bottom) / (Top - Bottom),  -(Far + Near) / (Far - Near), -1,
                       0, 0, -2 * Near * Far / (Far - Near), 0);
      } /* End of 'Frustum' function */

      /* Orthographic projection function.
       * ARGUMENTS:
       *   - Parametrs of point:
       *       const type &Left, const type &Right, const type &Bottom, const type &Top, const type &Near, const type &Far.
       * RETURNS:
       *   (matr<type>) result matrix.
       */
      static matr<type> Ortho( const type &Left, const type &Right, const type &Bottom, const type &Top, const type &Near, const type &Far )
      {                                                                                                      
        return matr<type>(2 / (Right - Left), 0, 0, 0,
                       0, 2 / (Top - Bottom), 0, 0,
                       0, 0, -2 / (Far - Near), 0,
                       -(Right + Left) / (Right - Left), -(Top + Bottom) / (Top - Bottom), -(Far + Near) / (Far - Near), 1);
      } /* End of 'Ortho' function */

      /* Transformation point by matrix function.
       * ARGUMENTS:
       *   - vector to be tranform:
       *       const vec3<type> &V;
       * RETURNS:
       *   (vec3<vtype>) transformed vector.
       */
      template<typename vtype>
        vec3<vtype> TransformPoint( const vec3<vtype> &V ) const
        {
          const type (*M)[4] = matr_data<type>::M;
          vtype w = V.X * M[0][3] + V.Y * M[1][3] + V.Z * M[2][3] + M[3][3];
 
          return vec3<vtype>(V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0] + M[3][0], V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1] + M[3][1], V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2] + M[3][2]);
        } /* End of 'TransformPoint' function */
 
      /* Transformation point by matrix function.
       * ARGUMENTS:
       *   - vector to be tranform:
       *       const vec3<type> &V;
       * RETURNS:
       *   (vec3<vtype>) transformed vector.
       */
      template<typename vtype>
        vec3<vtype> InvTransformPoint( const vec3<vtype> &V ) const
        {
          const type (*M)[4] = matr_data<type>::M;
          vtype w = V.X * M[0][3] + V.Y * M[1][3] + V.Z * M[2][3] + M[3][3];
 
          EvaluateInverseMatrix();
          return vec3<vtype>(V.X * InverseM[0][0] + V.Y * InverseM[1][0] + V.Z * InverseM[2][0] + InverseM[3][0], V.X * InverseM[0][1] + V.Y * InverseM[1][1] + V.Z * InverseM[2][1] + InverseM[3][1], V.X * InverseM[0][2] + V.Y * InverseM[1][2] + V.Z * InverseM[2][2] + InverseM[3][2]);
        } /* End of 'TransformPoint' function */

      /* Transformation vector by matrix function.
       * ARGUMENTS:
       *   - vector to be tranform:
       *       const vec3<type> &V;
       * RETURNS:
       *   (vec3<vtype>) transformed vector.
       */
      template<typename vtype>
        vec3<vtype> TransformVector( const vec3<vtype> &V ) const
        {
          const type (*M)[4] = matr_data<type>::M;
          return vec3<vtype>(V.X * M[0][0] + V.Y * M[1][0] + V.Z * M[2][0],
                             V.X * M[0][1] + V.Y * M[1][1] + V.Z * M[2][1],
                             V.X * M[0][2] + V.Y * M[1][2] + V.Z * M[2][2]);
        } /* End of 'TransformVector' function */

      /* Transformation vector by matrix function.
       * ARGUMENTS:
       *   - vector to be tranform:
       *       const vec3<type> &V;
       * RETURNS:
       *   (vec3<vtype>) transformed vector.
       */
      template<typename vtype>
        vec3<vtype> InvtransformVector( const vec3<vtype> &V ) const
        {
          const type (*M)[4] = matr_data<type>::M;

          Transpose();
          EvaluateInverseMatrix();

          return vec3<vtype>(V.X * InverseM[0][0] + V.Y * InverseM[1][0] + V.Z * InverseM[2][0],
                             V.X * InverseM[0][1] + V.Y * InverseM[1][1] + V.Z * InverseM[2][1],
                             V.X * InverseM[0][2] + V.Y * InverseM[1][2] + V.Z * InverseM[2][2]);
        } /* End of 'TransformVector' function */

      /* Transformation normal vector by matrix function.
       * ARGUMENTS:
       *   - normal vector to be tranform:
       *       const vec3<type> &N;
       * RETURNS:
       *   (vec3<vtype>) transformed vector.
       */
      template<typename vtype>
        vec3<vtype> TransformNormal( const vec3<vtype> &N ) const
        {
          EvaluateInverseMatrix();
          return vec3<vtype>(N.X * InverseM[0][0] + N.Y * InverseM[0][1] + N.Z * InverseM[0][2],
                             N.X * InverseM[1][0] + N.Y * InverseM[1][1] + N.Z * InverseM[1][2],
                             N.X * InverseM[2][0] + N.Y * InverseM[2][1] + N.Z * InverseM[2][2]);
        } /* End of 'TransformNormal' function */

      /* Transformation normal vector by matrix function.
       * ARGUMENTS:
       *   - normal vector to be tranform:
       *       const vec3<type> &N;
       * RETURNS:
       *   (vec3<vtype>) transformed vector.
       */
      template<typename vtype>
        vec3<vtype> InvTransformNormal( const vec3<vtype> &N ) const
        {
          const type (*M)[4] = matr_data<type>::M;          
          return vec3<vtype>(N.X * M[0][0] + N.Y * M[0][1] + N.Z * M[0][2],
                             N.X * M[1][0] + N.Y * M[1][1] + N.Z * M[1][2],
                             N.X * M[2][0] + N.Y * M[2][1] + N.Z * M[2][2]);
        } /* End of 'InvTransformNormal' function */
    }; /* End of 'matr' class */
} /* end of 'mth' namespace */

#endif /* __mth_matr_h_ */

/* END OF 'mth_matr.h' FILE */
