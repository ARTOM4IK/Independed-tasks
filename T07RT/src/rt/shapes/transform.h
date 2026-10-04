/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : transform.h
 * PURPOSE     : Fractal project.
 *               Transformation shape module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 21.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __transform_h_
#define __transform_h_

#include "rt/rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  /* Transformation shape class */
  class transform : public shape
  {
  public:
    shape *TransformedObject;
    matr Trans;

    transform( shape *Shp, const matr &M ) : TransformedObject(Shp), Trans(M)
    {
      Surf = Shp->Surf;
      Env = Shp->Env;
    } /* End of 'transform' function */

    ~transform( VOID )
    {
      delete TransformedObject;
    } /* End of '~transform' function */

    BOOL Intersect( const ray &R, intr *I ) override
    {
      ray r1;
      r1.Org = Trans.InvTransformPoint(R.Org);
      r1.Dir = Trans.InvtransformVector(R.Dir);

      DBL scale = !r1.Dir;
      r1.Dir /= scale;

      if (TransformedObject->Intersect(r1, I))
      {
        if (!I->IsP)
          I->P = r1(I->T), I->IsP = TRUE;

        if (!I->IsN)
          I->Shp->GetNormal(I), I->IsN = TRUE;
        I->P = Trans.TransformPoint(I->P);
        I->N = Trans.TransformNormal(I->N).Normalize();
        I->T /= scale;

        return TRUE;
      }

      return FALSE;
    } /* End of 'Intersect' function */

    VOID GetNormal( intr *I ) override
    {
      intr intr = *I;

      intr.P = Trans.InvTransformPoint(I->P);
      TransformedObject->GetNormal(&intr);
      I->N = Trans.TransformNormal(intr.N).Normalize();
    } /* End of 'GetNormal' function */
  }; /* End of 'transform' class */
} /* End of 'arrt' namespace */

#endif /* __transform_h_ */
 
/* END OF 'transform.h' FILE */
