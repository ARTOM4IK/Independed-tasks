/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : scene_00_default.cpp
 * PURPOSE     : Ray tracing project.
 *               Default scene module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 24.08.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "arrt.h"

/* Ray tracing namespace */
namespace arrt
{
  /* Anonymous namespace */
  namespace
  {
    /* Scene smaple class */
    class scene_sample
    {
    public:
      /* Class constructor.
       * ARGUMENTS:
       *   - ray tracing window:
       *       rt_win &RT;
       */
      scene_sample( rt_win &RT )
      {
        //RT.Scn.Clear();
      }
    }; /* End of 'scene_sample' class */

    static arrt::rt_win::scene_register<scene_sample> _("Default");
  } /* End of anonymous namespace */
} /* End of 'arrt' namespace */

/* END OF 'scene_00_default.cpp' FILE */
