/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : plane.h
 * PURPOSE     : Ray Tracing project.
 *               Frame module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 21.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __plane_h_
#define __plane_h_

#include "rt/rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  class plane: public shape
  {
  public:
    vec3 N;       // normal
    DBL D;        // height
    vec3 Color;   // color
    surface surf; // surface
    envi env;     // environment

    /* Type constructor.
      * ARGUMENTS:
      *   - plane parametrs:
      *       DBL D, vec3 N, vec3 color, envi e, surface S;
      */
    plane( DBL D, vec3 N, vec3 color, envi e, surface S ): D(D), N(N.Normalizing()), Color(color), env(e), surf(S)
    {
      Surf = surf;
      Env = env;
    } /* End of 'plane' funciton */

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

    /* Get color function.
     * ARGUMENTS:
     *   - intersection structure:
     *       intr *I;
     * RETURNS: None.
     */
    virtual VOID GetColor( intr *Intr );

    /* Find intersection with all objects function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     * RETURNS: None.
     */
    virtual INT AllIntersect( const ray &Ray, intr_list &IList ) override;
  }; /* End of 'plane' class */
} /* End of 'arrt' namespace */

#endif /* __plane_h_ */
 
/* END OF 'plane.h' FILE */
