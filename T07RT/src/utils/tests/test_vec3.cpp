/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : test_vec3.cpp
 * PURPOSE     : Ray-Tracing project.
 *               Space mathematics test module.
 *               3D space vector test.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'tst'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#include "arrt.h"
 
/* Test operator+ method function */
TEST(MathVec3Test, AddVectorFloat)
{
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(0.0) + mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(1.5, 3.2, 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(3.0, 4.7, 1.3) + mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(3.0 + 1.5, 4.7 + 3.2, 1.3 + 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) + mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(-3.0 + 1.5, 4.7 - 3.2, -1.3 + 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) + mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(1.5, -3.2, 4.1) + mth::vec3<FLT>(-3.0, 4.7, -1.3));
} /* End of 'MathVec3Test.AddVectorFloat' test */
 
/* Test operator+= method function */
TEST(MathVec3Test, AddEqVectorFloat)
{
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(0.0) += mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(1.5, 3.2, 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(3.0, 4.7, 1.3) += mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(3.0 + 1.5, 4.7 + 3.2, 1.3 + 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) += mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(-3.0 + 1.5, 4.7 - 3.2, -1.3 + 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) += mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(1.5, -3.2, 4.1) += mth::vec3<FLT>(-3.0, 4.7, -1.3));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) += mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(1.5, -3.2, 4.1) + mth::vec3<FLT>(-3.0, 4.7, -1.3));
} /* End of 'MathVec3Test.AddEqVectorFloat' test */
 
/* Test operator- method function */
TEST(MathVec3Test, SubVectorFloat)
{
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(0.0) - mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(-1.5, -3.2, -4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(3.0, 4.7, 1.3) - mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(3.0 - 1.5, 4.7 - 3.2, 1.3 - 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) - mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(-3.0 - 1.5, 4.7 + 3.2, -1.3 - 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) - mth::vec3<FLT>(1.5, -3.2, 4.1), -(mth::vec3<FLT>(1.5, -3.2, 4.1) - mth::vec3<FLT>(-3.0, 4.7, -1.3)));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(0.0) -= mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(-1.5, -3.2, -4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(3.0, 4.7, 1.3) -= mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(3.0 - 1.5, 4.7 - 3.2, 1.3 - 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) -= mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(-3.0 - 1.5, 4.7 + 3.2, -1.3 - 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) -= mth::vec3<FLT>(1.5, -3.2, 4.1), -(mth::vec3<FLT>(1.5, -3.2, 4.1) -= mth::vec3<FLT>(-3.0, 4.7, -1.3)));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) -= mth::vec3<FLT>(1.5, -3.2, 4.1), -(mth::vec3<FLT>(1.5, -3.2, 4.1) - mth::vec3<FLT>(-3.0, 4.7, -1.3)));
} /* End of 'MathVec3Test.SubEqVectorFloat' test */
 
/* Test operator* method function */
TEST(MathVec3Test, MulVectorFloat)
{
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(0.0) * mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(0.0));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(3.0, 4.7, 1.3) * mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(3.0 * 1.5, 4.7 * 3.2, 1.3 * 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) * mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>((-3.0) * 1.5, 4.7 * (-3.2), (-1.3) * 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) * mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(1.5, -3.2, 4.1) * mth::vec3<FLT>(-3.0, 4.7, -1.3));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-1.0) * mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(-1.5, 3.2, -4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(1.0) * mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(1.5, -3.2, 4.1));
} /* End of 'MathVec3Test.MulVectorFloat' test */
 
/* Test operator*= method function */
TEST(MathVec3Test, MulEqVectorFloat)
{
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(0.0) *= mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(0.0));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(3.0, 4.7, 1.3) *= mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(3.0 * 1.5, 4.7 * 3.2, 1.3 * 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) *= mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>((-3.0) * 1.5, 4.7 * (-3.2), (-1.3) * 4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) *= mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(1.5, -3.2, 4.1) *= mth::vec3<FLT>(-3.0, 4.7, -1.3));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-3.0, 4.7, -1.3) *= mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(1.5, -3.2, 4.1) * mth::vec3<FLT>(-3.0, 4.7, -1.3));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-1.0) *= mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(-1.5, 3.2, -4.1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(1.0) *= mth::vec3<FLT>(1.5, -3.2, 4.1), mth::vec3<FLT>(1.5, -3.2, 4.1));
} /* End of 'MathVec3Test.MulEqVectorFloat' test */
 
/* Test operator+ method function */
TEST(MathVec3Test, AddVectorDouble)
{
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(0.0) + mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(1.5, 3.2, 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(3.0, 4.7, 1.3) + mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(3.0 + 1.5, 4.7 + 3.2, 1.3 + 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) + mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(-3.0 + 1.5, 4.7 - 3.2, -1.3 + 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) + mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(1.5, -3.2, 4.1) + mth::vec3<DBL>(-3.0, 4.7, -1.3));
} /* End of 'MathVec3Test.AddVectorDouble' test */
 
/* Test operator+= method function */
TEST(MathVec3Test, AddEqVectorDouble)
{
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(0.0) += mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(1.5, 3.2, 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(3.0, 4.7, 1.3) += mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(3.0 + 1.5, 4.7 + 3.2, 1.3 + 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) += mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(-3.0 + 1.5, 4.7 - 3.2, -1.3 + 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) += mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(1.5, -3.2, 4.1) += mth::vec3<DBL>(-3.0, 4.7, -1.3));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) += mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(1.5, -3.2, 4.1) + mth::vec3<DBL>(-3.0, 4.7, -1.3));
} /* End of 'MathVec3Test.AddEqVectorDouble' test */
 
/* Test operator- method function */
TEST(MathVec3Test, SubVectorDouble)
{
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(0.0) - mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(-1.5, -3.2, -4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(3.0, 4.7, 1.3) - mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(3.0 - 1.5, 4.7 - 3.2, 1.3 - 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) - mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(-3.0 - 1.5, 4.7 + 3.2, -1.3 - 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) - mth::vec3<DBL>(1.5, -3.2, 4.1), -(mth::vec3<DBL>(1.5, -3.2, 4.1) - mth::vec3<DBL>(-3.0, 4.7, -1.3)));
} /* End of 'MathVec3Test.SubVectorDouble' test */
 
/* Test operator-= method function */
TEST(MathVec3Test, SubEqVectorDouble)
{
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(0.0) -= mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(-1.5, -3.2, -4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(3.0, 4.7, 1.3) -= mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(3.0 - 1.5, 4.7 - 3.2, 1.3 - 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) -= mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(-3.0 - 1.5, 4.7 + 3.2, -1.3 - 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) -= mth::vec3<DBL>(1.5, -3.2, 4.1), -(mth::vec3<DBL>(1.5, -3.2, 4.1) -= mth::vec3<DBL>(-3.0, 4.7, -1.3)));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) -= mth::vec3<DBL>(1.5, -3.2, 4.1), -(mth::vec3<DBL>(1.5, -3.2, 4.1) - mth::vec3<DBL>(-3.0, 4.7, -1.3)));
} /* End of 'MathVec3Test.SubEqVectorDouble' test */
 
/* Test operator* method function */
TEST(MathVec3Test, MulVectorDouble)
{
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(0.0) * mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(0.0));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(3.0, 4.7, 1.3) * mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(3.0 * 1.5, 4.7 * 3.2, 1.3 * 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) * mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>((-3.0) * 1.5, 4.7 * (-3.2), (-1.3) * 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) * mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(1.5, -3.2, 4.1) * mth::vec3<DBL>(-3.0, 4.7, -1.3));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-1.0) * mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(-1.5, 3.2, -4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(1.0) * mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(1.5, -3.2, 4.1));
} /* End of 'MathVec3Test.MulVectorDouble' test */
 
/* Test operator*= method function */
TEST(MathVec3Test, MulEqVectorDouble)
{
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(0.0) *= mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(0.0));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(3.0, 4.7, 1.3) *= mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(3.0 * 1.5, 4.7 * 3.2, 1.3 * 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) *= mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>((-3.0) * 1.5, 4.7 * (-3.2), (-1.3) * 4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) *= mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(1.5, -3.2, 4.1) *= mth::vec3<DBL>(-3.0, 4.7, -1.3));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-3.0, 4.7, -1.3) *= mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(1.5, -3.2, 4.1) * mth::vec3<DBL>(-3.0, 4.7, -1.3));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-1.0) *= mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(-1.5, 3.2, -4.1));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(1.0) *= mth::vec3<DBL>(1.5, -3.2, 4.1), mth::vec3<DBL>(1.5, -3.2, 4.1));
} /* End of 'MathVec3Test.MulEqVectorDouble' test */
 
/* Test *N method function */
TEST(MathVec3Test, MultiplyNumber)
{
  EXPECT_VEC3_EQ(mth::vec3<INT>(-24, 0, 123) * 13.2, mth::vec3<INT>(-312, 0, 1599));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-24, 0, 123) * 13.2, mth::vec3<FLT>(-316.8, 0, 1623.6));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-24, 0, 123) * 13.2, mth::vec3<DBL>(-316.8, 0, 1623.6));
} /* End of 'MathTest.MultiplyNumber' test */
 
/* Test /N method function */
TEST(MathVec3Test, DivideNumber)
{
  EXPECT_VEC3_EQ(mth::vec3<INT>(52, 42, 47) / 30, mth::vec3<INT>(1, 1, 1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(52, 42, 47) / 30, mth::vec3<FLT>(1.733333333333333, 1.4, 1.566666666666667));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(52, 42, 47) / 30, mth::vec3<DBL>(1.733333333333333, 1.4, 1.566666666666667));
} /* End of 'MathTest.DivideNumber' test */
 
/* Test *=N method function */
TEST(MathVec3Test, MultiplyEqNumber)
{
  EXPECT_VEC3_EQ(mth::vec3<INT>(-24, 0, 30) *= 13.2, mth::vec3<INT> (-312, 0, 390));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(-24, 0, 30) *= 13.2, mth::vec3<FLT> (-316.8, 0, 396));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(-24, 0, 30) *= 13.2, mth::vec3<DBL> (-316.8, 0, 396));
} /* End of 'MathVec3Test.MultiplyEqNumber' test */
 
/* Test /=N method function */
TEST(MathVec3Test, DivideEqNumber)
{
  EXPECT_VEC3_EQ(mth::vec3<INT>(52, 42, 47) /= 30, mth::vec3<INT>(1, 1, 1));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(52, 42, 47) /= 30, mth::vec3<FLT>(1.733333333333333, 1.4, 1.566666666666667));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(52, 42, 47) /= 30, mth::vec3<DBL>(1.733333333333333, 1.4, 1.566666666666667));
} /* End of 'MathVec3Test.DivideEqNumber' test */
 
/* Test operator- method function */
TEST(MathVec3Test, Neg)
{
  EXPECT_VEC3_EQ(-mth::vec3<INT>(52, 42, 47), mth::vec3<INT>(-52, -42, -47));
  EXPECT_FLT_VEC3_EQ(-mth::vec3<FLT>(52, 42, 47), mth::vec3<FLT>(-52, -42, -47));
  EXPECT_DBL_VEC3_EQ(-mth::vec3<DBL>(52, 42, 47), mth::vec3<DBL>(-52, -42, -47));
} /* End of 'MathVec3Test.Neg' test */
 
/* Test Normalize method function */
TEST(MathVec3Test, Normalize)
{
  mth::vec3<DBL> V0 = mth::vec3<DBL>(3, 4, 5);
  EXPECT_DBL_VEC3_EQ(V0.Normalize(), mth::vec3<DBL>(0.4242640687119, 0.5656854249492380230, 0.7071067811865));
  mth::vec3<FLT> V1 = mth::vec3<FLT>(3, 4, 5);
  EXPECT_FLT_VEC3_EQ(V1.Normalize(), mth::vec3<FLT>(0.4242640687119f, 0.5656854249492380230f, 0.7071067811865f));
  mth::vec3<INT> V2 = mth::vec3<INT>(3, 4, 5);
  EXPECT_VEC3_EQ(V2.Normalize(), mth::vec3<INT>(0, 0, 0));
} /* End of 'MathVec3Test.Normalize' test */
 
/* Test Normalizing method function */
TEST(MathVec3Test, Normalizing)
{
  mth::vec3<DBL> V0 = mth::vec3<DBL>(14, 65, 2);
  EXPECT_DBL_VEC3_EQ(V0.Normalizing(), mth::vec3<DBL>(14.0 / 66.5206734782503536252301, 65.0 / 66.5206734782503536252301, 2.0 / 66.5206734782503536252301));
  mth::vec3<FLT> V1 = mth::vec3<FLT>(14, 65, 2);
  EXPECT_FLT_VEC3_EQ(V1.Normalizing(), mth::vec3<FLT>(14.0f / 66.5206734782503536252301f, 65.0f / 66.5206734782503536252301f, 2.0f / 66.5206734782503536252301f));
  mth::vec3<INT> V2 = mth::vec3<INT>(14, 65, 2);
  EXPECT_VEC3_EQ(V2.Normalizing(), mth::vec3<INT>(0, 0, 0));
} /* End of 'MathVec3Test.Normalizing' test */
 
/// /* Test mth::vec3() ctor function */
/// TEST(MathVec3Test, ConstructorEmpty)
/// {
///   EXPECT_VEC3_EQ(mth::vec3<INT>(), mth::vec3<INT>(0, 0, 0));
///   EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(), mth::vec3<FLT>(0.0f, 0.0f, 0.0f));
///   EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(), mth::vec3<DBL>(0.0, 0.0, 0.0));
/// } /* End of 'MathVec3Test.ConstructorEmpty' test */
 
/* Test mth::vec3(A) ctor function */
TEST(MathVec3Test, ConstructorSingle)
{
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(107.5312352341), mth::vec3<DBL>(107.5312352341, 107.5312352341, 107.5312352341));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(107.58902), mth::vec3<FLT>(107.58902, 107.58902, 107.58902));
  EXPECT_VEC3_EQ(mth::vec3<INT>(107), mth::vec3<INT>(107, 107, 107));
} /* End of 'MathVec3Test.ConstructorSingle' test */
 
/* Test mth::vec3(A, B, C) ctor function */
TEST(MathVec3Test, ConstructorFull)
{
  EXPECT_VEC3_EQ(mth::vec3<INT>(30, 30, 30), mth::vec3<INT>(30, 30, 30));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(30.9132568312f, 2354.75342376f, 752.29623541f), mth::vec3<FLT>(30.9132568312f, 2354.75342376f, 752.29623541f));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(30.9132568312, 2354.75342376, 752.29623541), mth::vec3<DBL>(30.9132568312, 2354.75342376, 752.29623541));
} /* End of 'MathVec3Test.ConstructorFull' test */
 
/* Test operator! function */
TEST(MathTest, Length)
{
  EXPECT_EQ(!mth::vec3<INT>(30, 30, 30), 51);
  EXPECT_DBL_EQ(!mth::vec3<DBL>(30.9132568312, 2354.75342376, 752.29623541), 2472.1992116270509);
  EXPECT_FLT_EQ(!mth::vec3<FLT>(30.9132568312, 2354.75342376, 752.29623541), 2472.1992f);
} /* End of 'MathVec3Test.Length' test */
 
/* Test static 'Length2' method function */
TEST(MathVec3Test, Length2)
{
  EXPECT_EQ(mth::vec3<INT>(3, 4, 5).Length2(), 50);
  EXPECT_FLT_EQ(mth::vec3<FLT>(1.0, 0, 0).Length2(), 1.0);
  EXPECT_DBL_EQ(mth::vec3<DBL>(0, 0, 0).Length2(), 0);
  EXPECT_DBL_EQ(mth::vec3<DBL>(5, 4.7, 6).Length2(), 83.09);
} /* End of 'MathVec3Test.Length2' test */
 
/* Test static 'Distance' method function */
TEST(MathVec3Test, Distance)
{
  EXPECT_EQ(mth::vec3<INT>(3, 0, 0).Distance(mth::vec3<INT>(0, 4, 0)), 5);
  EXPECT_FLT_EQ(mth::vec3<FLT>(1.0, 0, 0).Distance(mth::vec3<FLT>(1.0, 0, 0)), 0.0);
  EXPECT_DBL_EQ(mth::vec3<DBL>(3.018080, 0, 0).Distance(mth::vec3<DBL>(1.018, 0, 0)), 2.00008);
  EXPECT_DBL_EQ(mth::vec3<DBL>(2.0, 0, 0).Distance(mth::vec3<DBL>(1.0, 0, 0)), 1.0);
} /* End of 'MathVec3Test.Distance' test */
 
/* Test static 'Zero' method function */
TEST(MathVec3Test, GetStaticZero)
{
  EXPECT_VEC3_EQ(mth::vec3<INT>::Zero(), mth::vec3<INT>(0, 0, 0));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>::Zero(), mth::vec3<FLT>(0, 0, 0));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>::Zero(), mth::vec3<DBL>(0, 0, 0));
} /* End of 'MathVec3Test.GetStaticZero' test */
 
/* Test static 'Rnd0' method function */
TEST(MathVec3Test, GetStaticRnd0)
{
  mth::vec3<FLT> a = mth::vec3<FLT>::Rnd0();
  EXPECT_NEAR(a.X, 0.5f, 0.5f);
  EXPECT_NEAR(a.Y, 0.5f, 0.5f);
  EXPECT_NEAR(a.Z, 0.5f, 0.5f);
  mth::vec3<DBL> b = mth::vec3<DBL>::Rnd0();
  EXPECT_NEAR(b.X, 0.5, 0.5);
  EXPECT_NEAR(b.Y, 0.5, 0.5);
  EXPECT_NEAR(b.Z, 0.5, 0.5);
} /* End of 'MathVec3Test.GetStaticRnd0' test */
 
/* Test static 'Rnd1' method function */
TEST(MathVec3Test, GetStaticRnd1)
{
  mth::vec3<FLT> a = mth::vec3<FLT>::Rnd1();
  EXPECT_NEAR(a.X, 0.0f, 1.0f);
  EXPECT_NEAR(a.Y, 0.0f, 1.0f);
  EXPECT_NEAR(a.Z, 0.0f, 1.0f);
  mth::vec3<DBL> b = mth::vec3<DBL>::Rnd1();
  EXPECT_NEAR(b.X, 0.0, 1.0);
  EXPECT_NEAR(b.Y, 0.0, 1.0);
  EXPECT_NEAR(b.Z, 0.0, 1.0);
} /* End of 'MathVec3Test.GetStaticRnd1' test */
 
/* Test operator[] method function */
TEST(MathVec3Test, GetVectorCoordIndex)
{
  mth::vec3<INT> a = mth::vec3<INT>(1, 2, 3);
  EXPECT_EQ(a.X, a[0]);
  EXPECT_EQ(a.Y, a[1]);
  EXPECT_EQ(a.Z, a[2]);
  mth::vec3<FLT> b = mth::vec3<FLT>(1.0f, 2.0f, 3.0f);
  EXPECT_FLT_EQ(b.X, b[0]);
  EXPECT_FLT_EQ(b.Y, b[1]);
  EXPECT_FLT_EQ(b.Z, b[2]);
  mth::vec3<DBL> c = mth::vec3<DBL>(1.0, 2.0, 3.0);
  EXPECT_DBL_EQ(c.X, c[0]);
  EXPECT_DBL_EQ(c.Y, c[1]);
  EXPECT_DBL_EQ(c.Z, c[2]);
} /* End of 'MathVec3Test.GetVectorCoordIndex' test */
 
/* Test operator& method function */
TEST(MathVec3Test, DotProduct)
{
  EXPECT_FLT_EQ(mth::vec3<FLT>(1.2, 1.6, 3.0) & mth::vec3<FLT>(1.5, 3.2, 4.1), 1.5 * 1.2 + 3.2 * 1.6 + 4.1 * 3.0);
  EXPECT_FLT_EQ(mth::vec3<FLT>(0.0, 0.0, 0.0) & mth::vec3<FLT>(1.5, 3.2, 4.1), 0);
  EXPECT_DBL_EQ(mth::vec3<DBL>(1.2, 1.6, 3.0) & mth::vec3<DBL>(1.5, 3.2, 4.1), 1.5 * 1.2 + 3.2 * 1.6 + 4.1 * 3.0);
  EXPECT_DBL_EQ(mth::vec3<DBL>(0.0, 0.0, 0.0) & mth::vec3<DBL>(1.5, 3.2, 4.1), 0);
} /* End of 'MathVec3Test.DotProduct' test */
 
/* Test operator% method function */
TEST(MathVec3Test, CrossProduct)
{
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(1.2, 1.6, 3.0) % mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(1.6 * 4.1 - 3.0 * 3.2, -(1.2 * 4.1 - 3.0 * 1.5), 1.2 * 3.2 - 1.6 * 1.5));
  EXPECT_FLT_VEC3_EQ(mth::vec3<FLT>(0.0, 0.0, 0.0) % mth::vec3<FLT>(1.5, 3.2, 4.1), mth::vec3<FLT>(0, 0, 0));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(1.2, 1.6, 3.0) % mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(1.6 * 4.1 - 3.0 * 3.2, -(1.2 * 4.1 - 3.0 * 1.5), 1.2 * 3.2 - 1.6 * 1.5));
  EXPECT_DBL_VEC3_EQ(mth::vec3<DBL>(0.0, 0.0, 0.0) % mth::vec3<DBL>(1.5, 3.2, 4.1), mth::vec3<DBL>(0, 0, 0));
} /* End of 'MathVec3Test.CrossProduct' test */
 
/* Test (Type *) function */
TEST(MathVec3Test, PointerCoord)
{
  mth::vec3<FLT> a = mth::vec3<FLT>(1.2f, 1.8f, 3.0f);
  EXPECT_EQ((INT)(FLT *)a, (INT)&a.X);
  mth::vec3<DBL> b = mth::vec3<DBL>(1.2, 1.8, 3.0);
  EXPECT_EQ((INT)(DBL *)b, (INT)&b.X);
  mth::vec3<INT> c = mth::vec3<INT>(1, 2, 3);
  EXPECT_EQ((INT)(INT *)c, (INT)&c.X);
} /* End of 'MathVec3Test.PointerCoord' test */
 
/* END OF 'test_vec3.cpp' FILE */
