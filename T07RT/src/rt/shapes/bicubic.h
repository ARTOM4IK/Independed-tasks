/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : bicubic.h
 * PURPOSE     : Ray Tracing project.
 *               Bicubic module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 23.09.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __bicubic_h_
#define __bicubic_h_

#include "rt/rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  /* Patch class */
  class patches
  {
  public:
    vec3 p[4][4];  // Patches
  }; /* End of 'patches' class*/

  /* Bicubic class */
  class bicubic: public shape
  {
  public:
    surface surf;               // surface
    envi env;                   // environment
    std::vector<patches> Patches;
    /* Type constructor.
      * ARGUMENTS:
      *   - box parametrs:
      *       vec3 B1, vec3 B2, vec3 color, envi e, surface S;
      */
    bicubic( envi e, surface S ): env(e), surf(S)
    {
      Surf = surf;
      Env = env;
    } /* End of 'bicubic' function */

    /* Finder intersection an object function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     *   (BOOL) Is intersect sign.
     */
    virtual BOOL Intersect( const ray &R, intr *Intr );      

    /* Get normal function.
     * ARGUMENTS:
     *   - intersection structure:
     *       intr *I;
     * RETURNS: None.
     */
    virtual VOID GetNormal( intr *Intr );

    /* Find intersection with all objects function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     * RETURNS: None.
     */
    virtual INT AllIntersect( const ray &Ray, intr_list &IList ) override;

    /* Load bicubic model function.
     * ARGUMENTS:
     *   - Model Filename:
     *       const std::string &FileName;
     *   (BOOL) Model is read.
     */
    BOOL Load ( const std::string &FileName );
  }; /* End of 'bicubic' class */
} /* End of 'arrt' namespace */

#endif /* __bicubic_h_ */
 
/* END OF 'bicubic.h' FILE */
