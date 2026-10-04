/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : point.h
 * PURPOSE     : Ray tracing project.
 *               Point light module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 28.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __point_h_
#define __point_h_

#include "rt/rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  /* Point light class */
  class pointL: public light
  {
  public:
    vec3 pos;      // position
    vec3 color;    // color
    DBL distance;  // distance
    vec3 Att;      // attanuation   

    /* Class constructor.
     * ARGUMENTS:
     *   - light parametrs:
     *       vec3 dir, vec3 c, DBL d, vec3 att;
     */
    pointL( vec3 pos, vec3 c, DBL d, vec3 att ): pos(pos), color(c), distance(d), Att(att)
    {
      Cc = Att[0];
      Cl = Att[1];
      Cq = Att[2];
    } /* End of 'pointL' function */

    /* Get shadow coefficient function.
     *   - shadow parametrs:
     *       const vec3 &P, light_info *L;
     * RETURNS:
     *   (DBL) shadow coef.
     */
    virtual DBL Shadow( const vec3 &P, light_info *L ) override;
  }; /* End of 'pointL' class */
} /* End of 'arrt' namespace */

#endif /* __point_h_ */
 
/* END OF 'point.h' FILE */
