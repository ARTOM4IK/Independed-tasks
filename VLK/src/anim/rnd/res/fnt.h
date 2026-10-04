/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : fnt.h
 * PURPOSE     : Ray Tracing project.
 *               Precompiled header definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __fnt_h_
#define __fnt_h_

#include "resources.h"

/* Animation namespace */
namespace arvk
{
  /* Font class */
  class font: public resource
  {
  public:
    DWORD LineH {}, BaseH {}; /* Font line height and base line height in pixels */
    FLT AdvanceX[256] {};  /* Every letter shift right value (0 if no letter present) */
    material *Mat {};
    prim *Chars[256] {};

    font( render &rnd ) : Mat(nullptr)
    {
      Rnd = &rnd;
      memset(Chars, 0, sizeof(Chars));
      memset(Chars, 0, sizeof(Chars));
      memset(AdvanceX, 0, sizeof(AdvanceX));
      LineH = BaseH = 0;
    } /* End of 'font' fucntion */

    font( VOID ) : LineH(0), BaseH(0), Mat(nullptr)
    {
    } /* End of 'buffer' function */

    ~font( VOID )
    {
      //for (INT i = 0; i < 256; i++)
      //  arvk::anim::Get()->PrimFree(&Chars[i]);
      memset(Chars, 0, sizeof(Chars));
    } /* End of '~font' fucntion */

    /* Load font from .G3DF file function */
    font & Load( const std::string &FileName );

    /* Draw string function */
    VOID Draw( const CHAR *Str, vec3 Pos, FLT Size );
  }; /* End of 'font' class */
} /* End of 'namespace' namespace */

#endif /* __fnt_h_ */

/* END OF 'fnt.h' FILE */
