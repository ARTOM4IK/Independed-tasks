/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : modifiers.h
 * PURPOSE     : Ray Tracing project.
 *               Modifiers module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 21.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __modifiers_h_
#define __modifiers_h_

#include "rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  /* Mods namespace */
  namespace mods
  {
    /* Checker mod class */
    class checker : public modifier
    {
    private:
      DBL Color1, Color0; // colors to make checker

      /* Apply modification function.
       * ARGUMENTS:
       *   - shade information:
       *       shade_info *Sh;
       * RETURNS: None.
       */
      VOID Apply( shade_info *Sh ) override
      {
        Sh->Surf.Ka = Sh->Surf.Ka.K * (1 & (static_cast< INT>(std::floor(Sh->MapP.X)) ^ static_cast<INT>(std::floor(Sh->MapP.Y)) ^ static_cast<INT>(std::floor(Sh->MapP.Z))) ? Color0 : Color1);
        //Sh->Surf.Ka = Sh->Surf.Ka.K * 52;
      } /* End of 'Apply' function */
    public:
      /* Type constructor.
       * ARGUMENTS:
       *   - first color:
       *       DBL C1;
       *   - seconf color:
       *       DBL C0;
       */
      checker( DBL C1 = 1, DBL C0 = 0.8 ) : Color1(C1), Color0(C0)
      {
      } /* End of 'checker' function */
    }; /* End of 'checker' class */

    /* Texture mod class */
    class texture : public modifier
    {
    private:
      image *img;
      DBL U0, V0, U, V, W;
      vec3 V1, U1;
      vec2 T0, T1, T2;
      /* Apply modification function.
       * ARGUMENTS:
       *   - shade information:
       *       shade_info *Sh;
       * RETURNS: None.
       */
      VOID Apply( shade_info *Sh ) override
      {
        U = (Sh->P & U1) - U0;
        V = (Sh->P & V1) - V0;
        vec3 sampl = img->Sample(T0 * V + T1 * U + T2 * (1 - U - V));
        Sh->Surf.Ka.K = arrt::coef(sampl);
      } /* End of 'Apply' function */
    public:
      /* Type constructor.
       * ARGUMENTS:
       *   - texture image:
       *       image i;
       */
      texture( image *i, DBL u0, DBL v0, vec3 v1, vec3 u1, vec2 t0, vec2 t1, vec2 t2 ) : img(i), U0(u0), V0(v0), U1(u1), V1(v1), T0(t0), T1(t1), T2(t2)
      {
      } /* End of 'texture' function */
    }; /* End of 'texture' class */

    /* Test mod class */
    class test : public modifier
    {
    private:
      vec3 Color;
      /* Apply modification function.
       * ARGUMENTS:
       *   - shade information:
       *       shade_info *Sh;
       * RETURNS: None.
       */
      VOID Apply( shade_info *Sh ) override
      {
        Sh->Surf.Ka = arrt::coef(Color);
      } /* End of 'Apply' function */
    public:
      /* Type constructor.
       * ARGUMENTS:
       *   - texture image:
       *       image i;
       */
      test( vec3 c ) : Color(c)
      {
      } /* End of 'test' function */
    }; /* End of 'test' class */
  } /* End of 'mods' namespace */
} /* End of 'arrt' namespace */

#endif /* __modifiers_h_ */
 
/* END OF 'modifiers.h' FILE */
