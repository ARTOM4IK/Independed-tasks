/* FILE NAME: t46globe.c
 * PROGRAMMER: AA4
 * DATE: 05.01.2025
 * PURPOSE: 3D math implementation module.
 *          Math module.
*/

#ifndef __mth_h_
#define __mth_h_

#include <math.h>

#define PI 3.14159265358979323846    /* PI constant */
#define D2R(A) ((A) * (PI / 180.0))  /* Convert degrees to radians */
#define R2D(A) ((A) * (180.0 / PI))  /* Convert radians to degrees */
#define Degree2Radian(a) D2R(a)      /* Convert degrees to radians */

/* Base float point types */
typedef float FLT;
typedef double DBL;

typedef struct tagVEC
{
  FLT X, Y, Z; /* Vector coordinates */
} VEC;

typedef struct tagVEC2
{
  FLT X, Y; /* Vector coordinates */
} VEC2;

typedef struct tagVEC4
{
  FLT X, Y, Z, W; /* Vector coordinates */
} VEC4;

typedef struct tagMATR
{
  FLT A[4][4];  /* Array for matrix */
} MATR;

/*****
*Keyboard
*********/

/* Set vector function.
 * ARGUMENTS:
 *   - numbers to be add:
 *       FLT X, FLT Y, FLT Z;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSet( FLT X, FLT Y, FLT Z )
{
  VEC v = {X, Y, Z};
 
  return v;
} /* End of 'VecSet' function */
 
/* Set vector function.
 * ARGUMENTS:
 *   - numbers to be add:
 *       FLT X, FLT Y, FLT Z;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSet1( FLT A )
{
  VEC v = {A, A, A};
 
  return v;
} /* End of 'VecSet1' function */

/* Set 4vector function.
 * ARGUMENTS:
 *   - numbers to be add:
 *       FLT A, FLT B, FLT C, FLT D;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC4 Vec4Set( FLT A, FLT B, FLT C, FLT D )
{
  VEC4 v = {A, B, C, D};

  return v;
} /* End of 'Vec4Set' function */

/* Set 4vector by one number function.
 * ARGUMENTS:
 *   - numbers to be add:
 *       FLT A;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC4 Vec4Set1( FLT A )
{
  return Vec4Set(A, A, A, A);
} /* End of 'Vec4Set1' function */

/* Set 2vector function.
 * ARGUMENTS:
 *   - numbers to be add:
 *       FLT A, FLT B;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC2 Vec2Set( FLT A, FLT B )
{
  VEC2 v = {A, B};

  return v;
} /* End of 'VecSet' function */

/* Set 2vector by one number function.
 * ARGUMENTS:
 *   - numbers to be add:
 *       FLT A, FLT B;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC2 Vec2Set1( FLT A )
{
  return Vec2Set(A, A);
} /* End of 'Vec2Set1' function */

/* Add two vectors function.
 * ARGUMENTS:
 *   - vectors to be add:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecAddVec( VEC V1, VEC V2 )
{
  return VecSet(V1.X + V2.X, V1.Y + V2.Y, V1.Z + V2.Z);
} /* End of 'VecAddVec' function */

/* Subtract two vectors function.
 * ARGUMENTS:
 *   - vectors to be substracted:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecSubVec( VEC V1, VEC V2 )
{
  VEC v;  /* New vector */
 
  v.X = V1.X - V2.X;
  v.Y = V1.Y - V2.Y;
  v.Z = V1.Z - V2.Z;
  return v;
} /* End of 'VecSubVec' function */

/* Multiply two vectors function.
 * ARGUMENTS:
 *   - vectors to be multiplied:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulNum( VEC V1, FLT N )
{
  VEC v; /* New vector */
 
  v.X = V1.X * N;
  v.Y = V1.Y * N;
  v.Z = V1.Z * N;
  return v;
} /* End of 'VecMulNum' function */

/* Divide two vectors function.
 * ARGUMENTS:
 *   - vectors to be divided:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecDivNum( VEC V1, FLT N )
{
  VEC v; /* New vector */
 
  v.X = V1.X / N;
  v.Y = V1.Y / N;
  v.Z = V1.Z / N;
  return v;
} /* End of 'VecDivNum' function */

/* Set negative vector function.
 * ARGUMENTS:
 *   - vector to be translated to negative vector:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNeg( VEC V )
 {
  return VecSet(-V.X, -V.Y, -V.Z);
} /* End of 'VecNeg' function */
 
/* Scalar product of 2 vectors function.
 * ARGUMENTS:
 *   - vectors to be scalar multiplied:
 *       VEC V1, VEC V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline FLT VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
} /* End of 'VecDotVec' function */

/* Vector product of 2 vectors function.
 * ARGUMENTS:
 *   - vectors to be vector multiplied:
 *       VEC V1, VEC V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecCrossVec( VEC V1, VEC V2 )
{
  return VecSet(V1.Y * V2.Z - V1.Z * V2.Y, V1.Z * V2.X - V1.X * V2.Z, V1.X * V2.Y - V1.Y * V2.X );
} /* End of 'VecCrossVec' function */

/* Square of len of vector function.
 * ARGUMENTS:
 *   - vectors to get its length:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline FLT VecLen2( VEC V )
{
  FLT len = VecDotVec(V, V);  /* Vector length */

  return len;
} /* End of 'VecLen2' function */

/* Len of vector function.
 * ARGUMENTS:
 *   - vectors to get its length:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline FLT VecLen( VEC V )
{
  FLT len = VecDotVec(V, V); /* Vector length */
 
  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
} /* End of 'VecLen' function */

/* Normalize vector function.
 * ARGUMENTS:
 *   - vectors to be normalized:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNormalize( VEC V )
{
  FLT len = VecDotVec(V, V); /* Vector length */
 
  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
} /* End of 'VecNormalize' function */

/* Transform matrix to point function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC PointTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0],
    V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1],
    V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]);
} /* End of 'PointTransform' function */

/* Transform matrix to vector function.
 * ARGUMENTS:
 *   - vector:
 *       VEC V;
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VectorTransform( VEC V, MATR M )
{
  return VecSet(V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0],
           V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1],
           V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2]);
} /* End of 'VectorTransform' function */

/* Vector by matrix multiplication (with homogenious devide) function.
 * ARGUMENTS:
 *   - source vector:
 *       VEC V;
 *   - multiplied matrix:
 *       MATR M;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulMatr( VEC V, MATR M )
{
  FLT w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3]; /* Variable for homogenious division */

  return
    VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
           (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
           (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
} /* End of 'VecMulMatr' function */

/*****
*MATRIXES
********/

/* Unit Matrix variable */
static MATR UnitMatrix =
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }
};

/* Get Unit matrix function.
 * ARGUMENTS:
 *   Nothing.
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrIdentity( VOID )
{
  return UnitMatrix;
} /* End of 'MatrIdentity' function */

/* Set matrix function.
 * ARGUMENTS:
 *   - Elements of matrix:
 *       FLT A00, FLT A01, FLT A02, FLT A03,
 *       FLT A10, FLT A11, FLT A12, FLT A13,
 *       FLT A20, FLT A21, FLT A22, FLT A23,
 *       FLT A30, FLT A31, FLT A32, FLT A33.
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrSet( FLT A00, FLT A01, FLT A02, FLT A03,
              FLT A10, FLT A11, FLT A12, FLT A13,
              FLT A20, FLT A21, FLT A22, FLT A23,
              FLT A30, FLT A31, FLT A32, FLT A33 )
{
  MATR m =  /* New matrix */
  {
    {
      {A00, A01, A02, A03},
      {A10, A11, A12, A13},
      {A20, A21, A22, A23},
      {A30, A31, A32, A33},
    }
  };
  return m;
} /* End of 'MatrSet' function */

/* Set point in space function.
 * ARGUMENTS:
 *   - Parametrs of point:
 *       FLT l, FLT r, FLT b, FLT t, FLT n, FLT f.
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrFrustum( FLT l, FLT r, FLT b, FLT t, FLT n, FLT f )
{
  return MatrSet(2 * n / (r - l), 0, 0, 0, 0, 2 * n / (t - b), 0, 0, (r + l) / (r - l), (t + b) / (t - b), -((f + n) / (f - n)), -1, 0, 0, -(2 * n * f / (f - n)), 0);
} /* End of 'MatrFrustum' function */

/* Orthographic projection function.
 * ARGUMENTS:
 *   - Parametrs of point:
 *       FLT Left, FLT Right, FLT Bottom, FLT Top, FLT Near, FLT Far.
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrOrtho( FLT Left, FLT Right, FLT Bottom, FLT Top, FLT Near, FLT Far )
{                                                                                                      /*-(Right + Left) / (Right - Left), -(Top + Bottom) / (Top - Bottom)*/
  return MatrSet(2 / (Right - Left), 0, 0, 0, 0, 2 / (Top - Bottom), 0, 0, 0, 0, -2 / (Far - Near), 0, 0, 0, -(Near + Far) / (Far - Near), 1);
} /* End of 'MatrOrtho' function */

/* Translate vector to matrix function.
 * ARGUMENTS:
 *   - Vector:
 *       VEC T;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrTranslate( VEC T )
{
  return MatrSet(1, 0, 0, 0,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 T.X, T.Y, T.Z, 1);
} /* End of 'MatrTranslate' function */

/* Set view with matrix function.
 * ARGUMENTS:
 *   - View parametrs:
 *       VEC Loc, VEC At, VEC Up1.
 * RETURNS:
 *   (MATR) Matrix.
 */
__inline MATR MatrView( VEC Loc, VEC At, VEC Up1 )
{
  VEC
    Dir = VecNormalize(VecSubVec(At, Loc)),
    Right = VecNormalize(VecCrossVec(Dir, Up1)),
    Up = VecCrossVec(Right, Dir);
  MATR m =
  {
    {
      {Right.X, Up.X, -Dir.X, 0},
      {Right.Y, Up.Y, -Dir.Y, 0},
      {Right.Z, Up.Z, -Dir.Z, 0},
      {-VecDotVec(Loc, Right), - VecDotVec(Loc, Up), VecDotVec(Loc, Dir), 1}
    }
  };
  return m;
} /* End of 'MatrView' function */

/* Matrix scale function.
 * ARGUMENTS:
 *   - Matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrScale( VEC S )
{
  return MatrSet(S.X, 0, 0, 0,
                 0, S.Y, 0, 0,
                 0, 0, S.Z, 0,
                 0, 0, 0, 1);

} /* End of 'MatrScale' function */

/* Rotate matrix by axis Z function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateZ( FLT AngleInDegree )
{
  FLT co = cos(D2R(AngleInDegree)), si = sin(D2R(AngleInDegree)); /* Cos and sin of an angle */

  return MatrSet(co, si, 0, 0,
                 -si, co, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1);

} /* End of 'MatrRotateZ' function */

/* Rotate matrix by axis X function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateX( FLT AngleInDegree )
{
  FLT co = cos(D2R(AngleInDegree)), si = sin(D2R(AngleInDegree)); /* Cos and sin of an angle */

  return MatrSet(1, 0, 0, 0,
                 0, co, si, 0,
                 0, -si, co, 0,
                 0, 0, 0, 1);
} /* End of 'MatrRotateX' function */

/* Rotate matrix by axis Y function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       FLT AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateY( FLT AngleInDegree )
{
  FLT co = cos(D2R(AngleInDegree)), si = sin(D2R(AngleInDegree)); /* Cos and sin of an angle */

  return MatrSet(co, 0, -si, 0,
                 0, 1, 0, 0,
                 si, 0, co, 0,
                 0, 0, 0, 1);
} /* End of 'MatrRotateY' function */

/* Rotate vector function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       FLT AngleInDegree;
 *   - Vector:
 *       VEC V;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotate( FLT AngleInDegree, VEC V )
{
  FLT
    A = D2R(AngleInDegree),   /* Angle in radians */
    si = sin(A), co = cos(A); /* Cos and sin of an angle */
  VEC R = VecNormalize(V);    /* Normalized vector */
  MATR M =                    /* Rotated matrix */
  {
    {
      {co + R.X * R.X * (1 - co),
        R.X * R.Y *(1 - co) + R.Z * si,
        R.X * R.Z * (1 - co) - R.Y * si, 0},
      {R.Y * R.X * (1 - co) - R.Z * si,
        co + R.Y * R.Y * (1 - co),
        R.Y * R.Z * (1 - co) + R.X * si, 0},
      {R.Z * R.X * (1 - co) + R.Y * si,
        R.Z * R.Y * (1 - co) - R.X * si,
        co + R.Z * R.Z * (1 - co), 0},
      {0, 0, 0, 1}
    }
  };

  return M;
} /* End of 'MatrRotate' function */

/* Matrix by matrix multiplication function.
 * ARGUMENTS:
 *   - multiplied matrixes:
 *       MATR M1, MATR M2;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrMulMatr( MATR M1, MATR M2 )
{
  MATR r = {{{0}}}; /* New matrix */
  INT i, j, k;      /* Counter variables */

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      for (k = 0; k < 4; k++)
        r.A[i][j] += M1.A[i][k] * M2.A[k][j];
  return r;
} /* End of 'MatrMulMatr' function */
 
/* Matrix transpose function.
 * ARGUMENTS:
 *   - Matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrTranspose( MATR M )
{
  return MatrSet(M.A[1][1], M.A[2][1], M.A[3][1], M.A[4][1],
                 M.A[1][2], M.A[2][2], M.A[3][2], M.A[4][2],
                 M.A[1][3], M.A[2][3], M.A[3][3], M.A[4][3],
                 M.A[1][4], M.A[2][4], M.A[3][4], M.A[4][4]);
}  /* End of 'MatrTranspose' function */

/* 3x3 matrix determination function.
 * ARGUMENTS:
 *   - 3x3 matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline FLT MatrDeterm3x3( FLT A11, FLT A12, FLT A13, FLT A21, FLT A22, FLT A23, FLT A31, FLT A32, FLT A33 )
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
__inline FLT MatrDeterm( MATR M )
{
  return
    M.A[0][0] * MatrDeterm3x3(M.A[1][1], M.A[1][2], M.A[1][3],
                              M.A[2][1], M.A[2][2], M.A[2][3],
                              M.A[3][1], M.A[3][2], M.A[3][3]) +
    -M.A[0][1] * MatrDeterm3x3(M.A[1][0], M.A[1][2], M.A[1][3],
                               M.A[2][0], M.A[2][2], M.A[2][3],
                               M.A[3][0], M.A[3][2], M.A[3][3]) +
    M.A[0][2] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][3],
                              M.A[2][0], M.A[2][1], M.A[2][3],
                              M.A[3][0], M.A[3][1], M.A[3][3]) +
    -M.A[0][3] * MatrDeterm3x3(M.A[1][0], M.A[1][1], M.A[1][2],
                               M.A[2][0], M.A[2][1], M.A[2][2],
                               M.A[3][0], M.A[3][1], M.A[3][2]);
} /* End of 'MatrDeterm' function */

/* Inverse matrix function.
 * ARGUMENTS:
 *   - matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrInverse( MATR M )
{
  MATR r;                  /* Inversed matrix */
  FLT det = MatrDeterm(M); /* Determinant */
  INT                      /* Arrays for quick calculation */
    s[] = {1, -1},
    P[][3] = {{1, 2, 3}, {0, 2, 3}, {0, 1, 3}, {0, 1, 2}},
    i, j;
 
  if (det == 0)
    return MatrIdentity();
 
  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      r.A[j][i] =
        s[(i + j) % 2] *
        MatrDeterm3x3(M.A[P[i][0]][P[j][0]], M.A[P[i][0]][P[j][1]], M.A[P[i][0]][P[j][2]],
                      M.A[P[i][1]][P[j][0]], M.A[P[i][1]][P[j][1]], M.A[P[i][1]][P[j][2]],
                      M.A[P[i][2]][P[j][0]], M.A[P[i][2]][P[j][1]], M.A[P[i][2]][P[j][2]]) / det;
  return r;
} /* End of 'MatrInverse' function */

#endif /* __mth_h_ */

/* END OF 'mth.h' FILE */
