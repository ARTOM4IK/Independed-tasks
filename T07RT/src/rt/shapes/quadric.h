/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : quadric.h
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

#ifndef __quadric_h_
#define __quadric_h_

#include "rt/rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  class quadric: public shape
  {
  public:
    DBL A, B, C, D, E, F, G, H, I, J; // parametrs
    vec3 Color;                       // color
    surface surf;                     // surface
    envi env;                         // environment

    /* Type constructor.
      * ARGUMENTS:
      *   - quadric parametrs:
      *       vec3 color, DBL A, DBL B, DBL C, DBL D, DBL E, DBL F, DBL G, DBL H, DBL I, DBL J, envi en, surface srf;
      */
    quadric( vec3 color, DBL A, DBL B, DBL C, DBL D, DBL E, DBL F, DBL G, DBL H, DBL I, DBL J, envi en, surface srf ): A(A), B(B), C(C), D(D), E(E), F(F), G(G), H(H), I(I), J(J), Color(color), env(en), surf(srf)
    {
      Surf = surf;
      Env = env;
    } /* End of 'quadric' funciton */

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
  }; /* End of 'quartic' class */
} /* End of 'arrt' namespace */

#endif /* __quadric_h_ */
 
/* END OF 'quadric.h' FILE */
                                                                                                                