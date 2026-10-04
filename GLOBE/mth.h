/* FILE NAME: t46globe.c
 * PROGRAMMER: AA4
 * DATE: 05.01.2025
 * PURPOSE: 3D math implementation module.
*/

#ifndef __mth_h_
#define __mth_h_

#include <math.h>

#define PI 3.14159265358979323846    /* PI constant */
#define D2R(A) ((A) * (PI / 180.0))  /* Convert degrees to radians */
#define Degree2Radian(a) D2R(a)      /* Convert degrees to radians */

/* Base float point types */
typedef double DBL;
typedef double FLT;

typedef struct tagVEC
{
  DBL X, Y, Z; /* Vector coordinates */
} VEC;

typedef struct tagVEC2
{
  DBL X, Y; /* Vector coordinates */
} VEC2;

typedef struct tagVEC4
{
  DBL X, Y, Z, W; /* Vector coordinates */
} VEC4;

typedef struct tagMATR
{
  DBL A[4][4];  /* Array for matrix */
} MATR;

__inline VEC VecSet( DBL X, DBL Y, DBL Z )
{
  VEC v = {X, Y, Z};
 
  return v;
} /* End of 'VecSet' function */
 
__inline VEC VecSet1( DBL A )
{
  VEC v = {A, A, A};
 
  return v;
} /* End of 'VecSet' function */

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
}

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
}

/* Multiply two vectors function.
 * ARGUMENTS:
 *   - vectors to be multiplied:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecMulNum( VEC V1, DBL N )
{
  VEC v; /* New vector */
 
  v.X = V1.X * N;
  v.Y = V1.Y * N;
  v.Z = V1.Z * N;
  return v;
}

/* Divide two vectors function.
 * ARGUMENTS:
 *   - vectors to be divided:
 *       VEC V1, V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecDivNum( VEC V1, DBL N )
{
  VEC v; /* New vector */
 
  v.X = V1.X / N;
  v.Y = V1.Y / N;
  v.Z = V1.Z / N;
  return v;
} 

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
}
 
/* Scalar product of 2 vectors function.
 * ARGUMENTS:
 *   - vectors to be scalar multiplied:
 *       VEC V1, VEC V2;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline DBL VecDotVec( VEC V1, VEC V2 )
{
  return V1.X * V2.X + V1.Y * V2.Y + V1.Z * V2.Z;
}

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
}

/* Square of len of vector function.
 * ARGUMENTS:
 *   - vectors to get its length:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline DBL VecLen2( VEC V )
{
  DBL len = VecDotVec(V, V);  /* Vector length */

  return len;
}

/* Len of vector function.
 * ARGUMENTS:
 *   - vectors to get its length:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline DBL VecLen( VEC V )
{
  DBL len = VecDotVec(V, V); /* Vector length */
 
  if (len == 1 || len == 0)
    return len;
  return sqrt(len);
}

/* Normalize vector function.
 * ARGUMENTS:
 *   - vectors to be normalized:
 *       VEC V;
 * RETURNS:
 *   (VEC) result vector.
 */
__inline VEC VecNormalize( VEC V )
{
  DBL len = VecDotVec(V, V); /* Vector length */
 
  if (len == 1 || len == 0)
    return V;
  return VecDivNum(V, sqrt(len));
}

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
}

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
}

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
  DBL w = V.X * M.A[0][3] + V.Y * M.A[1][3] + V.Z * M.A[2][3] + M.A[3][3]; /* Variable for homogenious division */

  return
    VecSet((V.X * M.A[0][0] + V.Y * M.A[1][0] + V.Z * M.A[2][0] + M.A[3][0]) / w,
           (V.X * M.A[0][1] + V.Y * M.A[1][1] + V.Z * M.A[2][1] + M.A[3][1]) / w,
           (V.X * M.A[0][2] + V.Y * M.A[1][2] + V.Z * M.A[2][2] + M.A[3][2]) / w);
}

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
}

/* Set matrix function.
 * ARGUMENTS:
 *   - Elements of matrix:
 *       DBL A00, DBL A01, DBL A02, DBL A03,
 *       DBL A10, DBL A11, DBL A12, DBL A13,
 *       DBL A20, DBL A21, DBL A22, DBL A23,
 *       DBL A30, DBL A31, DBL A32, DBL A33.
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrSet( DBL A00, DBL A01, DBL A02, DBL A03,
              DBL A10, DBL A11, DBL A12, DBL A13,
              DBL A20, DBL A21, DBL A22, DBL A23,
              DBL A30, DBL A31, DBL A32, DBL A33 )
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
}

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
}

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

}

/* Rotate matrix by axis Z function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateZ( DBL AngleInDegree )
{
  DBL co = cos(AngleInDegree), si = sin(AngleInDegree); /* Cos and sin of an angle */

  return MatrSet(co, si, 0, 0,
                 -si, co, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1);

}

/* Rotate matrix by axis X function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateX( DBL AngleInDegree )
{
  DBL co = cos(AngleInDegree), si = sin(AngleInDegree); /* Cos and sin of an angle */

  return MatrSet(1, 0, 0, 0,
                 0, co, si, 0,
                 0, -si, co, 0,
                 0, 0, 0, 1);
}

/* Rotate matrix by axis Y function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       DBL AngleInDegree;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotateY( DBL AngleInDegree )
{
  DBL co = cos(AngleInDegree), si = sin(AngleInDegree); /* Cos and sin of an angle */

  return MatrSet(co, 0, -si, 0,
                 0, 1, 0, 0,
                 si, 0, co, 0,
                 0, 0, 0, 1);
}

/* Rotate vector function.
 * ARGUMENTS:
 *   - Angle in degrees:
 *       DBL AngleInDegree;
 *   - Vector:
 *       VEC V;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline MATR MatrRotate( DBL AngleInDegree, VEC V )
{
  DBL
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
}

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
}
 
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
}

/* 3x3 matrix determination function.
 * ARGUMENTS:
 *   - 3x3 matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline DBL MatrDeterm3x3( DBL A11, DBL A12, DBL A13, DBL A21, DBL A22, DBL A23, DBL A31, DBL A32, DBL A33 )
{
  return A11 * A22 * A33 + A12 * A23 * A31 + A13 * A21 * A32 - A11 * A23 * A32 - A12 * A21 * A33 - A13 * A22 * A31;
}

/* Matrix determination function.
 * ARGUMENTS:
 *   - Matrix:
 *       MATR M;
 * RETURNS:
 *   (MATR) result matrix.
 */
__inline DBL MatrDeterm( MATR M )
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
}

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
  DBL det = MatrDeterm(M); /* Determinant */
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
}

#endif /* __mth_h_ */

/* END OF 'mth.h' FILE */
