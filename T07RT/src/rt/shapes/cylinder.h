/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : cylinder.h
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

#ifndef __cylinder_h_
#define __cylinder_h_

#include "rt/rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  /* Cylinder class */
  class cylinder: public shape
  {
  public:
    vec3 Color, Axis, C; // color and direction
    DBL R, r;            // radius
    surface surf;        // surface
    envi env;            // environment

    /* Type constructor.
      * ARGUMENTS:
      *   - cylinder parametrs:
      *       vec3 C, vec3 Axis, DBL R, vec3 color, envi e, surface S;
      */
    cylinder( vec3 C, vec3 Axis, DBL R, vec3 color, envi e, surface S ): C(C), Axis(Axis), R(R), Color(color), env(e), surf(S)
    {
      Surf = surf;
      Env = env;
    } /* End of 'cylinder' function */

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
  }; /* End of 'cylinder' class */
} /* End of 'arrt' namespace */

#endif /* __cylinder_h_ */
 
/* END OF 'cylinder.h' FILE */
