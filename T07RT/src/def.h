/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : def.h
 * PURPOSE     : Ray Tracing project.
 *               Default common definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'arrt'.
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
 
/* Debug memory allocation support */
#ifndef NDEBUG 
# define _CRTDBG_MAP_ALLOC
# include <crtdbg.h> 
# define SetDbgMemHooks() \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
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
#include <fstream>
#include <exception>
#include <map> 
#include <wincodec.h>  
#include <functional>
 
#include <iostream>
#include <format>
 
/* Base large integer types */
typedef unsigned long long UINT64;
typedef long long INT64;

/* Project namespace */
namespace arrt
{
  /* Math types definitions */
  typedef mth::vec2<DBL> vec2;
  typedef mth::vec3<DBL> vec3;
  typedef mth::vec4<DBL> vec4;
  typedef mth::matr<DBL> matr;
  typedef mth::ray<DBL> ray;
  typedef mth::camera<DBL> camera;
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
} /* end of 'arrt' namespace */

#endif /* __def_h_ */
 
/* END OF 'def.h' FILE */