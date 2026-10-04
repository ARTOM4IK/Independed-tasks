/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_ray.h
 * PURPOSE     : Ray Tracing project.
 *               Math ray module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 24.07.2025.
 * NOTE        : Module namespace 'arrt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __mth_ray_h_
#define __mth_ray_h_
 
#include "mth_def.h"

/* Math library namespace */
namespace mth
{
  /* Math ray type */
  template<typename type>
  class ray
  {
  public:
    vec3<type> Org, Dir;

    /* Class constructor 
     * ARGUMENTS: None.
     */
    ray( VOID )
    {
    } /* End of 'ray' function */

    /* Class constructor 
     * ARGUMENTS:
     *   - ray beggining:
     *       const vec3<type> &O;
     *   - ray dirrection:
     *       const vec3<type> &D;
     */
    ray( const vec3<type> &O, const vec3<type> &D ): Org(O), Dir(D.Normalizing())
    {
    } /* End of 'ray' function */

    /* Get vector from org to intersection function.
     *   - vector length:
     *       type T;
     * RETURNS:
     *   (vec3<type>) vector from org to intersection.
     */
    vec3<type> operator()( type T ) const
    {
      return Org + Dir * T;
    } /* End of 'operator()' function */
  }; /* End of 'ray' class */
} /* end of 'mth' namespace */

#endif /* __mth_ray_h_ */

/* END OF 'mth_ray.h' FILE */