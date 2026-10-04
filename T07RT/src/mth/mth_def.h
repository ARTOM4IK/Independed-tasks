/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_def.h
 * PURPOSE     : Ray tracing project.
 *               Math definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 22.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __mth_def_h_
#define __mth_def_h_

#include <commondf.h>
#include <cmath>

typedef DOUBLE DBL;
typedef FLOAT FLT;

#define Infinity INFINITY
#define Theshold 0.0001
#define PI 3.14159265358979323846    /* PI constant */
#define D2R(A) ((A) * (PI / 180.0))  /* Convert degrees to radians */
#define R2D(A) ((A) * (180.0 / PI))  /* Convert radians to degrees */

namespace mth
{
  template<typename type>
    auto Min( type N1, type N2 ) -> decltype(N1 + N2)
    {
      if (N1 > N2)
        return N2;
      return N1;
    } /* End of 'Min' functiopn */

  /* Get maximum function.
   * ARGUMENTS: 
   *   - numbers:
   *      type N1, N2;
   * RETURNS:
   *   (type) result number.
   */
  template<typename type>
    auto Max( type N1, type N2 ) -> decltype(N1 + N2)
    {
      if (N1 < N2)
        return N2;
      return N1;
    } /* End of 'Max' functiopn */

  template<typename type>
    type sign( type a )
    {
      if (a == 0)
        return 0;
      if (a > 0)
        return 1;
      else
        return -1;
    } /* End of 'Max' functiopn */
}

#endif /* __mth_def_h_ */

/* END OF 'mth_def.h' FILE */
