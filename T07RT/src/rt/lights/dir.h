/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : dir.h
 * PURPOSE     : Ray tracing project.
 *               Directional light module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 28.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __dir_h_
#define __dir_h_

#include "rt/rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  /* Directional light class */
  class dirL: public light
  {
  public:
    vec3 direction; // direction
    vec3 color;     // color
    vec3 Att;       // attanuation          

    /* Class constructor.
     * ARGUMENTS:
     *   - light parametrs:
     *       vec3 dir, vec3 c, DBL d, vec3 att;
     */
    dirL( vec3 dir, vec3 c, DBL d, vec3 att ): direction(dir), color(c), Att(att)
    {
      Cc = Att[0];
      Cl = Att[1];
      Cq = Att[2];
    } /* End of 'dirL' function */

    /* Get shadow coefficient function.
     *   - shadow parametrs:
     *       const vec3 &P, light_info *L;
     * RETURNS:
     *   (DBL) shadow coef.
     */
    virtual DBL Shadow( const vec3 &P, light_info *L ) override; 
  }; /* End of 'dirL' class */
} /* End of 'arrt' namespace */

#endif /* __dir_h_ */
 
/* END OF 'dir.h' FILE */
