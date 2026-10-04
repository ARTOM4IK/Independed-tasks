/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : sphere.h
 * PURPOSE     : Ray Tracing project.
 *               Sphere shape module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 21.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __sphere_h_
#define __sphere_h_

#include "rt/rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  /* Sphere class */
  class sphere: public shape
  {
  public:
    vec3 C;      // center
    DBL R, R2;   // radius and square radius
    vec3 Color;  // color
    envi env;    // environment
    surface Srf; // surface
    bound Bound; // bound

    /* Type constructor.
      * ARGUMENTS:
      *   - saphere parametrs:
      *       DBL r, vec3 c, vec3 color, envi e, surface S;
      */
    sphere( DBL r, vec3 c, vec3 color, envi e, surface S ): C(c), R(r), R2(r * r), Color(color), env(e), Srf(S)
    {
      Surf = Srf;
      Env = env;
      GetBound();
      MinBB = Bound.Bound1;
      MaxBB = Bound.Bound2;
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
    /* Get shape bound function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID GetBound( VOID );
  }; /* End of 'sphere' class */
} /* End of 'arrt' namespace */

#endif /* __sphere_h_ */
 
/* END OF 'sphere.h' FILE */
