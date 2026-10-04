/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : box.h
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

#ifndef __box_h_
#define __box_h_

#include "rt/rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  /* Box class */
  class box: public shape
  {
  public:
    vec3 Color, B1, B2; // color, min point, max point
    surface surf;       // surface
    envi env;           // environment
    bound Bound;            // bound

    /* Type constructor.
      * ARGUMENTS:
      *   - box parametrs:
      *       vec3 B1, vec3 B2, vec3 color, envi e, surface S;
      */
    box( vec3 B1, vec3 B2, vec3 color, envi e, surface S ): B1(B1), B2(B2), Color(color), env(e), surf(S)
    {
      Surf = surf;
      Env = env;
      GetBound();
      MinBB = Bound.Bound1;
      MaxBB = Bound.Bound2;
    } /* End of 'box' function */

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
  }; /* End of 'box' class */
} /* End of 'arrt' namespace */

#endif /* __box_h_ */
 
/* END OF 'box.h' FILE */
