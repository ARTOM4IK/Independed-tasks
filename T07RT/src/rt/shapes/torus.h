/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : torus.h
 * PURPOSE     : Ray Tracing project.
 *               Torus shape module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 21.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __torus_h_
#define __torus_h_

#include "rt/rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  /* Sphere class */
  class torus: public shape
  {
  public:
    vec3 C;      // center
    DBL R, r, R2, r2;   // radius and square radius
    vec3 Color;  // color
    envi env;    // environment
    surface Srf; // surface

    /* Type constructor.
      * ARGUMENTS:
      *   - tore parametrs:
      *       DBL R, DBL r, vec3 c, vec3 color, envi e, surface S;
      */
    torus( DBL R, DBL r, vec3 c, vec3 color, envi e, surface S ): C(c), R(R), r(r), Color(color), env(e), Srf(S), R2(R * R), r2(r * r)
    {
      Surf = Srf;
      Env = env;
    } /* End of 'sphere' function */

    /* Finder intersection an object function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     *   (BOOL) Is intersect sign.
     */
    virtual BOOL Intersect( const ray &R, intr *Intr ) override;      

    /* Finder intersection an object function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     *   (BOOL) Is intersect sign.
     */
    virtual BOOL IsIntersect( const ray &Ray ) override;

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
    /* Check if ray starts inside function.
     * ARGUMENTS:
     *   - position:
     *       const vec3 &P;
     * RETURNS:
     *   (BOOL) Is inside sign.
     */
    virtual BOOL IsInside( const vec3 &P ) override;
  }; /* End of 'torus' class */
} /* End of 'arrt' namespace */

#endif /* __torus_h_ */
 
/* END OF 'torus.h' FILE */
