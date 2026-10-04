/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : test_system.h
 * PURPOSE     : Ray Tracing project.
 *               Test system module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'tst'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __test_system_h_
#define __test_system_h_
 
#include "def.h"
 
/* Generate passed result macro */
#define TEST_PASSED(Str) \
  std::cout << tst::SetColor(0xFFFFFF, 0x008800) << "PASSED: " << tst::SetColor(0xFFFFFF) << Str << std::endl
/* Generate failed result macro */
#define TEST_FAILED(Str) \
  do                                                                                                             \
  {                                                                                                              \
    std::cout << tst::SetColor(0xFFFF00, 0xFF0000) << "FAILED: " << tst::SetColor(0xFFFFFF) << Str << std::endl; \
    throw std::logic_error("");                                                                                  \
  } while (FALSE)
 
/* Check equivalence macro function */
#define EXPECT_EQ(a, b) \
  do                                                                     \
  {                                                                      \
    if ((a) != (b))                                                      \
      TEST_FAILED(std::format("{} != {} ({} vs {})", #a, #b, (a), (b))); \
    else                                                                 \
      TEST_PASSED(std::format("{} == {}", #a, #b));                      \
  } while (FALSE)
 
/* Check mostly equivalence macro function */
#define EXPECT_NEAR(a, b, epsilon) \
  do                                                                                        \
  {                                                                                         \
    if (std::abs((a) - (b)) > epsilon)                                                      \
      TEST_FAILED(std::format("{} != {} within {} ({} vs {})", #a, #b, epsilon, (a), (b))); \
    else                                                                                    \
      TEST_PASSED(std::format("{} ~= {} (epsilon {})", #a, #b, epsilon));                   \
  } while (FALSE)
 
/* Check equivalence for float type macro function */
#define EXPECT_FLT_EQ(a, b) \
    EXPECT_NEAR((a), (b), 1e-5F)
 
/* Check equivalence for double type macro function */
#define EXPECT_DBL_EQ(a, b) \
    EXPECT_NEAR((a), (b), 1e-12F)
 
/* Check for conditional TRUE value macro function */
#define EXPECT_TRUE(condition) \
  do                                       \
  {                                        \
    if (!(condition))                      \
      TEST_FAILED(#condition " is false"); \
    else                                   \
      TEST_PASSED(#condition " is true");  \
  } while (FALSE)
 
/* Check mostly equivalence macro function */
#define EXPECT_VEC_NEAR(v1, v2, epsilon) \
  do                                                                                                                                            \
  {                                                                                                                                             \
    if (std::abs((v1).X - (v2).X) > (epsilon) || std::abs((v1).Y - (v2).Y) > epsilon || std::abs((v1).Z - (v2).Z) > (epsilon))                  \
      TEST_FAILED(std::format("vec3({}, {}, {}) != vec3({}, {}, {}) within {}", (v1).X, (v1).Y, (v1).Z, (v2).X, (v2).Y, (v2).Z, (epsilon)));    \
    else                                                                                                                                        \
      TEST_PASSED(std::format("vec3({}, {}, {}) ~= vec3({}, {}, {}) (epsilon {})", (v1).X, (v1).Y, (v1).Z, (v2).X, (v2).Y, (v2).Z, (epsilon))); \
  } while (FALSE)
 
/* Check near equivalence of 4x4 matrices macro function */
#define EXPECT_MATR_NEAR(m1, m2, eps, t) \
  do                                                       \
  {                                                        \
    BOOL ok = TRUE;                                        \
                                                           \
    for (INT i = 0; i < 4; i++)                            \
      for (INT j = 0; j < 4; j++)                          \
        if (std::abs((m1).M[i][j] - (m2).M[i][j]) > (eps)) \
          ok = FALSE;                                      \
    if (ok)                                                \
      TEST_PASSED(std::format("{}: matr1 == matr2", #t));  \
    else                                                   \
      TEST_FAILED(std::format("{}: matr1 != matr2", #t));  \
                                                           \
  } while (FALSE)
 
/* Test declaration macro code */
#define TEST(TestSuiteName, TestName) \
  VOID TestSuiteName ## TestName( VOID );                                      \
  struct TestSuiteName ## TestName ## _Register                                \
  {                                                                            \
    TestSuiteName ## TestName ## _Register( VOID )                             \
    {                                                                          \
      tst::RegisterTest(#TestSuiteName, #TestName, TestSuiteName ## TestName); \
    }                                                                          \
  } TestSuiteName ## TestName ## _Instance;                                    \
  VOID TestSuiteName ## TestName( VOID )
 
/* Check vec3 equivalence macro function */
#define EXPECT_VEC3_EQ(v1, v2) \
  do                                                                                                                                 \
  {                                                                                                                                  \
    if ((v1).X != (v2).X || (v1).Y != (v2).Y || (v1).Z != (v2).Z)                                                                    \
      TEST_FAILED(std::format("{} != {} (({}, {}, {}) vs ({}, {}, {}))", #v1, #v2, (v1).X, (v1).Y, (v1).Z, (v2).X, (v2).Y, (v2).Z)); \
    else                                                                                                                             \
      TEST_PASSED(std::format("{} == {}", #v1, #v2));                                                                                \
  } while (FALSE)
 
/* Check vec3 equivalence float macro function */
#define EXPECT_FLT_VEC3_EQ(v1, v2) \
  do                                                                                                                                              \
  {                                                                                                                                               \
    if (std::abs((v1).X - (v2).X) > 1e-5F || std::abs((v1).Y - (v2).Y) > 1e-5F || std::abs((v1).Z - (v2).Z) > 1e-5F)                              \
      TEST_FAILED(std::format("{} != {} within {} (({} {} {}) vs ({} {} {}))", #v1, #v2, 1e-5F, (v1).X, (v1).Y, (v1).Z, (v2).X, (v2).Y, (v2).Z)); \
    else                                                                                                                                          \
      TEST_PASSED(std::format("{} ~= {} (epsilon {})", #v1, #v2, 1e-5F));                                                                         \
  } while (FALSE)
 
/* Check vec3 equivalence double macro function */
#define EXPECT_DBL_VEC3_EQ(v1, v2) \
  do                                                                                                                                               \
  {                                                                                                                                                \
    if (std::abs((v1).X - (v2).X) > 1e-12F || std::abs((v1).Y - (v2).Y) > 1e-12F || std::abs((v1).Z - (v2).Z) > 1e-12F)                            \
      TEST_FAILED(std::format("{} != {} within {} (({} {} {}) vs ({} {} {}))", #v1, #v2, 1e-12F, (v1).X, (v1).Y, (v1).Z, (v2).X, (v2).Y, (v2).Z)); \
    else                                                                                                                                           \
      TEST_PASSED(std::format("{} ~= {} (epsilon {})", #v1, #v2, 1e-12F));                                                                         \
  } while (FALSE)
 
/* Test support namespace */
namespace tst
{
  /* Change output color function.
   * ARGUMENTS:
   *   - foreground and background colors (RGB in DWORD pack):
   *       DWORD ForeColor, BackColor;
   * RETURNS: None.
   */
  inline std::string SetColor( DWORD ForeColor, DWORD BackColor = 0 )
  {
    return std::format("\x1b[38;2;{};{};{}m\x1b[48;2;{};{};{}m",
      COM_LONGBYTE2(ForeColor), COM_LONGBYTE1(ForeColor), COM_LONGBYTE0(ForeColor),
      COM_LONGBYTE2(BackColor), COM_LONGBYTE1(BackColor), COM_LONGBYTE0(BackColor));
  } /* End of 'SetColor' function */
 
  // Function type
  using test_func_type = VOID(*)( VOID );
  /* Store test function type */
  struct test_case
  {
    std::string Suite;   // Suite name
    std::string Name;    // Subtask name
    test_func_type Func; // Test function
  }; /* End of 'test_case' structure */
 
  /* Get all test single ton vector function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (std::vector<test_case> &) result test subtasks vector.
   */
  inline std::vector<test_case> & GetTests( VOID )
  {
    static std::vector<test_case> Tests;
    return Tests;
  } /* End of 'GetTests' function */
 
  /* Register test function.
   * ARGUMENTS:
   *   - test suite name:
   *       const std::string &Suite;
   *   - test name:
   *       const std::string &Name;
   *   - test function:
   *       test_func_type Func
   * RETURNS: None.
   */
  inline VOID RegisterTest( const std::string &Suite, const std::string &Name, test_func_type Func )
  {
    GetTests().push_back({Suite, Name, Func});
  } /* End of 'RegisterTest' function */
 
  /* Run all registered tests function.
   * ARGUMENTS: None.
   * RETURNS:
   *   (BOOL) TRUE if all tests are passed.
   */
  inline BOOL RunAllTests( VOID )
  {
    INT passed = 0, failed = 0;
 
    for (const auto &test : GetTests())
    {
      std::cout << "[ RUN      ] " << test.Suite << "." << test.Name << std::endl;
      try
      {
        test.Func();
        std::cout << "[       OK ] " << test.Suite << "." << test.Name << std::endl;
        passed++;
      }
      catch (...)
      {
        std::cerr << "[  FAILED  ] " << test.Suite << "." << test.Name << std::endl;
        failed++;
      }
    }
    std::cout << "TESTS PASSED: " << passed << ", FAILED: " << failed << std::endl;
    return failed == 0;
  } /* End of 'RunAllTests' function */
} /* end of 'tst' namespace */
 
#endif /* __test_system_h_ */
 
/* END OF 'test_system.h' FILE */
 