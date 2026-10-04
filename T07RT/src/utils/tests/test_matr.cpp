/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : test_matr.cpp
 * PURPOSE     : Ray Tracing project.
 *               Space mathematics test module.
 *               Matrices test.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'tst'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#include "arrt.h"
 
/* Test function */
TEST(VecTest, JustEqualities)
{
  EXPECT_VEC3_EQ(mth::vec3<INT>(1, 1, 1), mth::vec3<INT>(1, 1, 1));
  EXPECT_VEC_NEAR((mth::vec3<DBL>(1, 1, 1) * 2), mth::vec3<DBL>(2, 2, 2), 0.00005);
} /* End of 'AnyTest.Fail' test */
 
/* Test vec function */
TEST(MatrTest, Transpose)
{
  mth::matr<DBL> M1 = mth::matr<DBL>::Translate(mth::vec3<DBL>(10, 20, 30));
  mth::matr<DBL> M2 = M1.Transpose().Transpose();
  EXPECT_MATR_NEAR(M1, M2, 0.001, DBL);
  mth::matr<INT> M3 = mth::matr<INT>::Translate(mth::vec3<INT>(10, 20, 30));
  mth::matr<INT> M4 = M3.Transpose().Transpose();
  EXPECT_MATR_NEAR(M3, M4, 0.001, INT);
} /* End of 'MatrTest.Transpose' test */
 
/* Test Normal transform function */
TEST(MatrTest, TransformNormal)
{
  mth::vec3<DBL> N = mth::vec3<DBL>(0, 1, 0);
  mth::matr<DBL> M1 = mth::matr<DBL>::Translate(  mth::vec3<DBL>(10, 20, 30));
  N = M1.TransformNormal(N);
  EXPECT_VEC_NEAR(N, mth::vec3<DBL>(0, 1, 0), 0.001);
 
  mth::vec3<DBL> N1 = mth::vec3<DBL>(1, 0, 0);
  mth::matr<DBL> M2 = mth::matr<DBL>::RotateY(90);
  N1 = M2.TransformNormal(N1);
  EXPECT_VEC_NEAR(N1, mth::vec3<DBL>(0, 0, -1), 0.00001);
} /* End of 'MatrTest.TransformNormal' test */
 
/* Test Normal inverse transform function */
TEST(MatrTest, InvTranslateNormal)
{
  mth::vec3<DBL> N = mth::vec3<DBL>(0, 1, 0);
  mth::matr<DBL> M1 = mth::matr<DBL>::Translate(  mth::vec3<DBL>(10, 20, 30));
  N = M1.TransformNormal(N);
  N = M1.InvTransformNormal(N);
  EXPECT_VEC_NEAR(N, mth::vec3<DBL>(0, 1, 0), 0.00001);
 
  mth::vec3<DBL> N1 = mth::vec3<DBL>(1, 0, 0);
  mth::matr<DBL> M2 = mth::matr<DBL>::RotateY(90);
  N1 = M2.TransformNormal(N1);
  N1 = M2.InvTransformNormal(N1);
  EXPECT_VEC_NEAR(N1, mth::vec3<DBL>(1, 0, 0), 0.00001);
} /* End of 'MatrTest.InvTranslateNormal' test */
 
/* Test scale matrix function */
TEST(MathMatrTest, ScaleTest)
{
  mth::matr<DBL> msmpd = mth::matr<DBL>(2, 0, 0, 0, 
                              0, 2, 0, 0,
                              0, 0, 2, 0,
                              0, 0, 0, 1);
  mth::vec3<DBL> vsmpd = mth::vec3<DBL>(2, 2, 2);
  mth::matr<FLT> msmpf = mth::matr<FLT>(-30, 0, 0, 0, 
                              0, -30, 0, 0,
                              0, 0, -47, 0,
                              0, 0, 0, 1);
  mth::vec3<FLT> vsmpf = mth::vec3<FLT>(-30, -30, -47);
 
  EXPECT_MATR_NEAR(msmpd, mth::matr<DBL>::Scale(vsmpd), 1e-12, DBL);
  EXPECT_MATR_NEAR(msmpf, mth::matr<FLT>::Scale(vsmpf), 1e-5, FLT);
} /* End of 'MathMatrTest.ScaleTest' test */
 
/* Test rotateX matrix function */
TEST(MathMatrTest, RotateXTest)
{
  DBL angle1 = 30.0, angle2 = 45.0;
  mth::matr<DBL> msmpd = mth::matr<DBL>(1, 0, 0, 0, 
                                        0, sqrt(3) / 2, 0.5, 0,
                                        0, -0.5, sqrt(3) / 2, 0,
                                        0, 0, 0, 1);
  
  mth::matr<FLT> msmpf = mth::matr<FLT>(1, 0, 0, 0, 
                                        0, sqrt(2) / 2, sqrt(2) / 2, 0,
                                        0, -sqrt(2) / 2, sqrt(2) / 2, 0,
                                        0, 0, 0, 1);
 
  EXPECT_MATR_NEAR(msmpd, mth::matr<DBL>::RotateX(angle1), 1e-7, DBL);
  EXPECT_MATR_NEAR(msmpf, mth::matr<FLT>::RotateX(angle2), 1e-5, FLT);
} /* End of 'MathMatrTest.RotateXTest' test */
 
/* Test rotateY matrix function */
TEST(MathMatrTest, RotateYTest)
{
  DBL angle1 = 30.0, angle2 = 45.0;
  mth::matr<DBL> msmpd = mth::matr<DBL>(sqrt(3) / 2, 0, -0.5, 0, 
                                        0, 1, 0, 0,
                                        0.5, 0, sqrt(3) / 2, 0,
                                        0, 0, 0, 1);
  
  mth::matr<FLT> msmpf = mth::matr<FLT>(sqrt(2) / 2, 0, -sqrt(2) / 2, 0, 
                                        0, 1, 0, 0,
                                        sqrt(2) / 2, 0, sqrt(2) / 2, 0,
                                        0, 0, 0, 1);
 
  EXPECT_MATR_NEAR(msmpd, mth::matr<DBL>::RotateY(angle1), 1e-7, DBL);
  EXPECT_MATR_NEAR(msmpf, mth::matr<FLT>::RotateY(angle2), 1e-5, FLT);
} /* End of 'MathMatrTest.RotateYTest' test */
 
/* Test rotateZ matrix function */
TEST(MathMatrTest, RotateZTest)
{
  DBL angle1 = 30.0, angle2 = 45.0;
  mth::matr<DBL> msmpd = mth::matr<DBL>(sqrt(3) / 2, 0.5, 0, 0, 
                              -0.5, sqrt(3) / 2, 0, 0,
                              0, 0, 1, 0,
                              0, 0, 0, 1);
  
  mth::matr<FLT> msmpf = mth::matr<FLT>(sqrt(2) / 2, sqrt(2) / 2, 0, 0, 
                              -sqrt(2) / 2, sqrt(2) / 2, 0, 0,
                              0, 0, 1, 0,
                              0, 0, 0, 1);
 
  EXPECT_MATR_NEAR(msmpd, mth::matr<DBL>::RotateZ(angle1), 1e-7, DBL);
  EXPECT_MATR_NEAR(msmpf, mth::matr<FLT>::RotateZ(angle2), 1e-5, FLT);
} /* End of 'MathMatrTest.RotateZTest' test */
 
/* Test rotateZ matrix function */
TEST(MathMatrTest, RotateTest)
{
  DBL angle1 = 90.0;
  mth::vec3<DBL> vsmpd = mth::vec3<DBL>(0, 0, 1);
  mth::vec3<FLT> vsmpf = mth::vec3<FLT>(0, 0, 1);
  mth::matr<DBL> msmpd = mth::matr<DBL>(0, -1, 0, 0, 
                                        1, 0, 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, 0, 0);
  
  mth::matr<FLT> msmpf = mth::matr<FLT>(0, -1, 0, 0, 
                                        1, 0, 0, 0,
                                        0, 0, 1, 0,
                                        0, 0, 0, 0);
  EXPECT_MATR_NEAR(msmpd, mth::matr<DBL>::Rotate(angle1, vsmpd), 1e-5, DBL);
  EXPECT_MATR_NEAR(msmpf, mth::matr<FLT>::Rotate(angle1, vsmpf), 1e-5, FLT);
 
} /* End of 'MathMatrTest.RotateTest' test */
 
/// /* Determ3x3 testing function */
/// TEST(MatrTest, Determ3x3)
/// {
///   EXPECT_EQ(mth::matr<INT>::Determ3x3(0, 0, 1,
///                                       0, 1, 0,
///                                       1, 0, 0), -1);
/// 
///   EXPECT_EQ(mth::matr<INT>::Determ3x3(1, 2, 3,
///                                       3, 7, 1,
///                                       4, 5, 6), -30);
/// } /* End of 'MatrTest.Determ3x3' test */
 
/* Determinant evaluation testing function */
TEST(MatrTest, Determ)
{
  mth::matr<DBL> m = mth::matr(2.4,   23.4,  45.412, 43.23,
                               4.4,   5.5,   3.3,    7.45, 
                               12.11, 3.3,   54.8,   856.45,
                               32.3,  34.2,  8.9,    74.423);
  EXPECT_NEAR(m.Determ(), -365074.555034, 0.0005);
} /* End of 'MatrTest.Determ' test */
 
/* Inverse matrix testing function */
//TEST(MatrTest, Inverse)
//{
//  mth::matr<INT> m = mth::matr<INT>::Identity();
//  mth::matr<INT> InvTransM = m.Inverse();
//  mth::matr<INT> ResM = m * InvTransM;
//  EXPECT_MATR_NEAR(ResM, mth::matr<INT>::Identity(), 0.0005, INT);
//} /* End of 'MatrTest.Inverse' test */
 
/* Transform point testing function */
TEST(MatrTest, TransformPoint)
{
  mth::vec3<INT> v = mth::vec3<INT>(0, 0, 1);
 
  mth::matr<INT> m1 = mth::matr<INT>::Translate(10, 10, 10);
  mth::vec3<INT> v1 = m1.TransformPoint(v);
  EXPECT_VEC_NEAR(v1, mth::vec3(10, 10, 11), 0.0005);
 
  mth::vec3<DBL> V = mth::vec3<DBL>(0, 0, 1);
  mth::matr<DBL> m2 = mth::matr<DBL>::RotateX(90);
  mth::vec3<DBL> v2 = m2.TransformPoint(V);
  EXPECT_VEC_NEAR(v2, mth::vec3(0.0, -1.0, 0.0), 0.0005);
} /* End of 'MatrTest.TransformPoint' test */
 
/* Inverse transform point testing function */
TEST(MatrTest, InvTransformPoint)
{
  mth::vec3<INT> v = mth::vec3<INT>(0, 0, 1);
 
  mth::matr<INT> m1 = mth::matr<INT>::Translate(10, 10, 10);
  mth::vec3<INT> v1 = m1.TransformPoint(v);
  mth::vec3<INT> v2 = m1.InvTransformPoint(v1);
  EXPECT_VEC_NEAR(v2, mth::vec3(0, 0, 1), 0.0005);
 
  mth::vec3<DBL> V = mth::vec3<DBL>(10.0, 12.0, 6.0);
  mth::matr<DBL> m2 = mth::matr<DBL>::Rotate(90, mth::vec3(30.0, 18.0, 47.0));
  mth::vec3<DBL> v3 = m2.TransformPoint(V);
  mth::vec3<DBL> v4 = m2.InvTransformPoint(v3);
  EXPECT_VEC_NEAR(v4, mth::vec3(10.0, 12.0, 6.0), 0.0005);
} /* End of 'MatrTest.InvTransformPoint' test */
 
/* Test matrices multiplication function */
TEST(MatrTest, MatrMulMatr)
{
  mth::matr<DBL> M1 = mth::matr<DBL>::Translate(mth::vec3<DBL>(10, 20, 30));
  mth::matr<DBL> M2 = mth::matr<DBL>(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
  EXPECT_MATR_NEAR((M1 * M2), M1, 0.001, DBL);
  EXPECT_MATR_NEAR((M2 * M1), M1, 0.001, DBL);
 
  mth::matr<DBL> M3 = mth::matr<DBL>::Scale(mth::vec3<DBL>(18.47, 30.18, 102.30));
  mth::matr<DBL> M4 = M3.Inverse().Transpose();
  EXPECT_MATR_NEAR((M3 * M4), M2, 0.001, DBL);
  EXPECT_MATR_NEAR((M4 * M3), M2, 0.001, DBL);
 
  mth::vec3<DBL> P = mth::vec3<DBL>(1, 0, 0);
  mth::matr<DBL> M5 = mth::matr<DBL>::Translate(9, 0, 0);
  mth::matr<DBL> M6 = mth::matr<DBL>::RotateY(180);
  EXPECT_VEC_NEAR(((M5 * M6).TransformPoint(P)), mth::vec3<DBL>(-10, 0, 0), 0.00001);
} /* End of 'MatrTest.MatrMulMatr' test */
 
/* Ortho matrix testing function */
TEST(MatrTest, Ortho)
{
  mth::matr<DBL> ortho = mth::matr<DBL>::Ortho(0.5, 2.5, 0.8, 1.2, 4.4, 1.5);
  EXPECT_MATR_NEAR(ortho, mth::matr<DBL>(1.0, 0, 0, 0,
                                         0, 5.0, 0, 0,
                                         0, 0, 0.68965517, 0,
                                         -1.5, -5.0, 2.034482758, 1), 0.0005, DBL);
} /* End of 'MatrTest.Ortho' test */
 
/* END OF 'matr_test.cpp' FILE */