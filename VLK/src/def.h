/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : def.h
 * PURPOSE     : Ray Tracing project.
 *               Default common definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev.
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __def_h_
#define __def_h_
 
#include <cassert>
 
#ifndef WIN32
#define WIN32
#include <commondf.h>
#undef WIN32
#else
#include <commondf.h>
#endif /* WIN32 */
#define BOOL bool
 
/* Math support */
#include "mth/mth.h"
//#define GLEW_STATIC
//#include <glew.h>
//#include <wglew.h>
//#include <gl/wglext.h>
#define VK_USE_PLATFORM_WIN32_KHR
#include <vulkan.h>
#define VK_CHECK(f)                                \
{                                                  \
    VkResult res = (f);                            \
    if (res != VK_SUCCESS)                         \
    {                                              \
      std::runtime_error("Error: Not VK_SUCCESS"); \
    }                                              \
}

/* Debug memory allocation support */
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h> 
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF/* | _CRTDBG_CHECK_ALWAYS_DF | */\
  /*_CRTDBG_ALLOC_MEM_DF */| _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
static class __Dummy
 {
public:
  /* Class constructor */
  __Dummy(VOID)
  {
    SetDbgMemHooks();
  } /* End of '__Dummy' constructor */
} __oops;
 
#endif /* _DEBUG */ 
 
#ifdef _DEBUG 
# ifdef _CRTDBG_MAP_ALLOC 
#   define new new(_NORMAL_BLOCK, __FILE__, __LINE__) 
# endif /* _CRTDBG_MAP_ALLOC */ 
#endif /* _DEBUG */
 
#include <string>
#include <vector>
#include <exception>
 
#include <functional>
#include <wincodec.h>  
#include <iostream>
#include <format>
#include <map>
#include <span>
#include <fstream>
#include <array>
#include <optional>
#include <filesystem>
#include <variant>
#include <source_location>

/* Base large integer types */
typedef unsigned long long UINT64;
typedef long long INT64;

/* Convert 4-symbol string to double word integer function.
 * ARGUMENTS:
 *   - string constant:
 *       const CHAR *Str;
 *   - string length:
 *       std::size_t Len;
 * RETURNS:
 *   (UINT) result convertet double word integer value.
 */
inline constexpr UINT operator""_dword( const CHAR *Str, std::size_t Len )
{
  UINT res {};
  if (Len > 0)
    res |= Str[0];
  if (Len > 1)
    res |= Str[1] << 8;
  if (Len > 2)
    res |= Str[2] << 16;
  if (Len > 3)
    res |= Str[3] << 24;
  return res;
} /* End of 'operator""_dword' function */

/* Project namespace */
namespace arvk
{
  /* Math types definitions */
  typedef mth::vec2<FLT> vec2;
  typedef mth::vec3<FLT> vec3;
  typedef mth::vec4<FLT> vec4;
  typedef mth::matr<FLT> matr;
  typedef mth::vec2<DBL> dvec2;
  typedef mth::vec3<DBL> dvec3;
  typedef mth::vec4<DBL> dvec4;
  typedef mth::matr<DBL> dmatr;
  typedef mth::ray<FLT> ray;
  typedef mth::camera<FLT> camera;

  template<typename T>
  class stock: public std::vector<T>
  {
  public:
    stock & operator<<( const T &X )
    {
      std::vector<T>::push_back(X);
      return *this;
    }

    template<class WalkType>
      VOID walk( WalkType WalkFunc )
      {
        for (auto &x : *this)
          WalkFunc(x);
      } /* End of 'walk' function */
  };

} /* end of 'arvk' namespace */
 
#endif /* __def_h_ */
 
/* END OF 'def.h' FILE */
