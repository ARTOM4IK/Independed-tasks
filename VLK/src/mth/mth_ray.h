/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_ray.h
 * PURPOSE     : Ray Tracing project.
 *               Default common definition module.
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

namespace mth
{
  template<typename type>
  class ray
  {
  public:
    vec3<type> Org, Dir;

    ray( VOID )
    {
    }

    ray( const vec3<type> &O, const vec3<type> &D ): Org(O), Dir(D.Normalizing())
    {
    }

    vec3<type> operator()(type T) const
    {
      return Org + Dir * T;
    }
  };
}

#endif /* __mth_ray_h_ */

/* END OF 'mth_ray.h' FILE */