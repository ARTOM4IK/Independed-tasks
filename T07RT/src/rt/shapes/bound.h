/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : bound.h
 * PURPOSE     : Ray Tracing project.
 *               Bound shape module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 21.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __bound_h_
#define __bound_h_

#include "rt/rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  /* Bound class */
  class bound: public shape
  {
  public:
    vec3 Bound1, Bound2; // color, min point, max point

    /* Type constructor.
      * ARGUMENTS:
      *   - box parametrs:
      *       vec3 B1, vec3 B2, vec3 color, envi e, surface S;
      */
    bound( vec3 B1, vec3 B2 ): Bound1(B1), Bound2(B2)
    {
    } /* End of 'box' function */
    /* Type constructor.
      * ARGUMENTS:
      *   - box parametrs:
      *       vec3 B1, vec3 B2, vec3 color, envi e, surface S;
      */
    bound( VOID ): Bound1(vec3(0)), Bound2(vec3(0))
    {
    } /* End of 'box' function */

    /* Finder intersection an object function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     *   (BOOL) Is intersect sign.
     */
    virtual BOOL IsIntersect( const ray &R );      

    ///* Find intersection with all objects function.
    // * ARGUMENTS:
    // *   - ray:
    // *       const ray &Ray;
    // *   - intersection structure:
    // *       intr_list &IList;
    // * RETURNS: None.
    // */
    //virtual INT AllIntersect( const ray &Ray, intr_list &IList ) override;

    /* Check if ray starts inside function.
     * ARGUMENTS:
     *   - position:
     *       const vec3 &P;
     * RETURNS:
     *   (BOOL) Is inside sign.
     */
    virtual BOOL IsInside( const vec3 &P ) override;

    /* Find CSG union bound function.
     * ARGUMENTS:
     *   - ShpA bound:
     *       const bound &A;
     *   - ShpB bound:
     *       const bound &B;
     * RETURNS: None.
     */
    virtual VOID Union( const vec3 &A1, const vec3 &A2, const vec3 &B1, const vec3 &B2 );

    /* Find CSG intersection bound function.
     * ARGUMENTS:
     *   - ShpA bound:
     *       const bound &A;
     *   - ShpB bound:
     *       const bound &B;
     * RETURNS: None.
     */
    virtual VOID Intersection( const vec3 &A1, const vec3 &A2, const vec3 &B1, const vec3 &B2 );
  }; /* End of 'bound' class */
} /* End of 'arrt' namespace */

#endif /* __bound_h_ */
 
/* END OF 'bound.h' FILE */
