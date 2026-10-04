/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : CSG.h
 * PURPOSE     : Fractal project.
 *               CSG module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 21.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __CSG_h_
#define __CSG_h_

#include "rt/rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  /* CSG def class */
  class csg : public shape
  {
  }; /* End of 'csg' class */

  /* CSG intersection def class */
  class csg_intersection : public shape
  {
  public:
    shape *ShpA, *ShpB; // shapes
    surface surf;       // surface
    envi env;           // environment
    bound Bound;
    /* Type constructor.
      * ARGUMENTS:
      *   - shapes:
      *       shape *A, shape *B;
      */
    csg_intersection( shape *A, shape *B, envi en, surface srf ) : ShpA(A), ShpB(B), surf(srf), env(en)
    {
      Surf = surf;
      Env = env;
      Bound.Intersection(B->MinBB, B->MaxBB, A->MinBB, A->MaxBB);
      MinBB = Bound.Bound1;
      MaxBB = Bound.Bound2;
    } /* End of 'csg_intersection' function */
 
    ~csg_intersection( VOID ) override
    {
      delete ShpA;
      delete ShpB;
    } /* End of '~csg_intersection' function */
 
    /* Check if ray starts inside function.
      * ARGUMENTS:
      *   - position:
      *       const vec3 &P;
      * RETURNS:
      *   (BOOL) Is inside sign.
      */
    BOOL IsInside( const vec3 &P )
    {
      if (ShpA->IsInside(P) && ShpB->IsInside(P))
        return TRUE;
      return FALSE;
    } /* End of 'IsInside' function */

    /* Finder intersection an object function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     *   (BOOL) Is intersect sign.
     */
    BOOL Intersect( const ray &R, intr *I ) override
    {
      intr_list il1, il2; 
 
      if (ShpA->AllIntersect(R, il1) > 0 &&
          ShpB->AllIntersect(R, il2) > 0)
      {
        intr best_in(nullptr, 0);
 
        for (auto &i : il1)
        {
          i.P = R(i.T);
          if (ShpB->IsInside(i.P))
            if (best_in.Shp == nullptr || best_in.T > i.T)
              best_in = i;
        }

        for (auto &i : il2)
        {
          i.P = R(i.T);
          if (ShpA->IsInside(i.P))
            if (best_in.Shp == nullptr || best_in.T > i.T)
              best_in = i;
        }

        *I = best_in;
        return best_in.Shp != nullptr;
      }
      return FALSE;
    } /* End of 'Intersect' function */

    /* Get all ray shape intersection function.
      * ARGUMENTS:
      *   - ray to intersect with:
      *       const ray &R;
      *   - result intersection list:
      *       intr_list &IList;
      * RETURNS:
      *   (INT) number of intersecion points.
      */
    INT AllIntersect( const ray &R, intr_list &IList )
    {
      intr_list il1, il2; 
 
      if (ShpA->AllIntersect(R, il1) > 0 &&
          ShpB->AllIntersect(R, il2) > 0)
      {
        for (auto &i : il1)
        {
          i.P = R(i.T);
          if (ShpB->IsInside(i.P))
          {
            intr result = i;
            result.EnterFlag = intr::ENTER;
            result.Shp = this;
            IList << result;
          }
        }

        for (auto &i : il2)
        {
          i.P = R(i.T);
          if (ShpA->IsInside(i.P))
          {
            intr result = i;
            result.EnterFlag = intr::ENTER;
            result.Shp = this;
            IList << result;
          }
        }
        
        return (INT)IList.size();
      }
      return 0;
    } /* End of 'AllIntersect' function */

    /* Get normal function.
     * ARGUMENTS:
     *   - intersection structure:
     *       intr *I;
     * RETURNS: None.
     */
    VOID GetNormal( intr *Intr )
    {
      //if (ShpA->IsInside(Intr->P) && ShpB->IsInside(Intr->P))
      ShpB->GetNormal(Intr);
    } /* End of 'GetNormal' function */

  }; /* End of 'csg_intersection' class */
  /* CSG union def class */
  class csg_union : public csg
  {
  public:
    shape *ShpA, *ShpB; // shapes
    surface surf;       // surface
    envi env;           // environment
    bound Bound;

    /* Type constructor.
      * ARGUMENTS:
      *   - shapes:
      *       shape *A, shape *B;
      */
    csg_union( shape *A, shape *B, envi en, surface srf ) : ShpA(A), ShpB(B), surf(srf), env(en)
    {
      Surf = surf;
      Env = env;
      Bound.Union(ShpA->MinBB, ShpA->MaxBB, ShpB->MinBB, ShpB->MaxBB);
      MinBB = Bound.Bound1;
      MaxBB = Bound.Bound2;
    } /* End of 'csg_union' function */
 
    ~csg_union( VOID ) override
    {
      delete ShpA;
      delete ShpB;
    } /* End of '~csg_union' function */
 
    /* Check if ray starts inside function.
      * ARGUMENTS:
      *   - position:
      *       const vec3 &P;
      * RETURNS:
      *   (BOOL) Is inside sign.
      */
    BOOL IsInside( const vec3 &P )
    {
      return ShpA->IsInside(P) || ShpB->IsInside(P);
    } /* End of 'IsInside' function */

    /* Finder intersection an object function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     *   (BOOL) Is intersect sign.
     */
    BOOL Intersect( const ray &R, intr *I ) override
    {
      intr_list il1, il2; 
 
      ShpA->AllIntersect(R, il1);
      ShpB->AllIntersect(R, il2);
  
      intr best_in(nullptr, DBL_MAX);

      for (auto &i : il1)
      {
        i.P = R(i.T);
        if (!ShpB->IsInside(i.P))
        {
          if (i.T < best_in.T && i.T >= 0)
            best_in = i;
        }
      }

      for (auto &i : il2)
      {
        i.P = R(i.T);
        if (!ShpA->IsInside(i.P))
        {
          if (i.T < best_in.T && i.T >= 0)
            best_in = i;
        }
      }

      if (best_in.Shp != nullptr && best_in.T != DBL_MAX && best_in.T >= 0)
      {
        *I = best_in;
        return TRUE;
      }
  
      return FALSE;
    } /* End of 'Intersect' function */

    /* Get all ray shape intersection function.
      * ARGUMENTS:
      *   - ray to intersect with:
      *       const ray &R;
      *   - result intersection list:
      *       intr_list &IList;
      * RETURNS:
      *   (INT) number of intersecion points.
      */
    INT AllIntersect( const ray &R, intr_list &IList ) override
    {
      intr_list il1, il2; 
  
      ShpA->AllIntersect(R, il1);
      ShpB->AllIntersect(R, il2);
  
      for (auto &i : il1)
      {
        i.P = R(i.T);
        if (!ShpB->IsInside(i.P) && i.T >= 0)
        {
          intr result = i;
          result.EnterFlag = intr::ENTER;
          result.Shp = this;
          IList << result;
        }
      }

      for (auto &i : il2)
      {
        i.P = R(i.T);
        if (!ShpA->IsInside(i.P) && i.T >= 0)
        {
          intr result = i;
          result.EnterFlag = intr::ENTER;
          result.Shp = this;
          IList << result;
        }
      }
  
      return (INT)IList.size();
    } /* End of 'AllIntersect' function */

    /* Get normal function.
     * ARGUMENTS:
     *   - intersection structure:
     *       intr *I;
     * RETURNS: None.
     */
    VOID GetNormal( intr *Intr ) override
    {
      ShpA->GetNormal(Intr);
  
      intr tempB = *Intr;
      ShpB->GetNormal(&tempB);
  
      if (tempB.N.Length2() > Intr->N.Length2() * 1.5)
      {
        Intr->N = tempB.N;
      }  
      Intr->N.Normalize();
    }/* End of 'GetNormal' function */
  }; /* End of 'csg_union' class */

  /* CSG subtrack def class */
  class csg_subtrack : public csg
  {
  public:
    shape *ShpA, *ShpB; // shapes
    surface surf;       // surface
    envi env;           // environment
    bound Bound;

    /* Type constructor.
      * ARGUMENTS:
      *   - shapes:
      *       shape *A, shape *B;
      */
    csg_subtrack( shape *A, shape *B, envi en, surface srf ) : ShpA(A), ShpB(B), surf(srf), env(en)
    {
      Surf = surf;
      Env = env;
      Bound.Bound1 = ShpA->MinBB;
      Bound.Bound2 = ShpA->MaxBB;
      MinBB = Bound.Bound1;
      MaxBB = Bound.Bound2;
    } /* End of 'csg_subtrack' function */
 
    ~csg_subtrack( VOID ) override
    {
      delete ShpA;
      delete ShpB;
    } /* End of '~csg_subtrack' function */
 
    /* Check if ray starts inside function.
      * ARGUMENTS:
      *   - position:
      *       const vec3 &P;
      * RETURNS:
      *   (BOOL) Is inside sign.
      */
    BOOL IsInside( const vec3 &P )
    {
      return ShpA->IsInside(P) && !ShpB->IsInside(P);
    } /* End of 'IsInside' function */

    /* Finder intersection an object function.
     * ARGUMENTS:
     *   - ray:
     *       const ray &Ray;
     *   - intersection structure:
     *       intr_list &IList;
     *   (BOOL) Is intersect sign.
     */
    BOOL Intersect( const ray &R, intr *I ) override
    {
      if (Bound.IsIntersect(R) == FALSE)
        return FALSE;
      intr_list il1, il2; 
 
      INT countA = ShpA->AllIntersect(R, il1);
      INT countB = ShpB->AllIntersect(R, il2);
  
      intr best_in(nullptr, DBL_MAX);

      for (auto &i : il1)
      {
        i.P = R(i.T);
        if (!ShpB->IsInside(i.P))
        {
          if (i.T < best_in.T && i.T >= 0)
            best_in = i;
        }
      }
  
      for (auto &i : il2)
      {
        i.P = R(i.T);
        if (ShpA->IsInside(i.P))
        {
          if (i.T < best_in.T && i.T >= 0)
            best_in = i;
        }
      }
  
      if (best_in.Shp == nullptr || best_in.T == DBL_MAX)
      {
        vec3 startPoint = R.Org;
        if (ShpA->IsInside(startPoint) && !ShpB->IsInside(startPoint))
        {
          for (auto &i : il1)
          {
            if (i.T < best_in.T && i.T >= 0)
              best_in = i;
          }
          for (auto &i : il2)
          {
            if (i.T < best_in.T && i.T >= 0)
              best_in = i;
          }
        }
      }

      if (best_in.Shp != nullptr && best_in.T != DBL_MAX && best_in.T >= 0)
      {
        *I = best_in;
        return TRUE;
      }
  
      return FALSE;
    } /* End of 'Intersect' function */

    /* Get all ray shape intersection function.
      * ARGUMENTS:
      *   - ray to intersect with:
      *       const ray &R;
      *   - result intersection list:
      *       intr_list &IList;
      * RETURNS:
      *   (INT) number of intersecion points.
      */
    INT AllIntersect( const ray &R, intr_list &IList ) override
    {
      intr_list il1, il2; 
 
      if (Bound.IsIntersect(R) == FALSE)
        return FALSE;

      INT countA = ShpA->AllIntersect(R, il1);
      INT countB = ShpB->AllIntersect(R, il2);
  
      for (auto &i : il1)
      {
        i.P = R(i.T);
        if (!ShpB->IsInside(i.P) && i.T >= 0)
        {
          intr result = i;
          result.EnterFlag = intr::ENTER;
          result.Shp = this;
          IList << result;
        }
      }

      for (auto &i : il2)
      {
        i.P = R(i.T);
        if (ShpA->IsInside(i.P) && i.T >= 0)
        {
          intr result = i;
          result.EnterFlag = intr::LEAVE;
          result.Shp = this;
          IList << result;
        }
      }

      vec3 startPoint = R.Org;
      if (ShpA->IsInside(startPoint) && !ShpB->IsInside(startPoint))
      {
        for (auto &i : il1)
        {
          if (i.T >= 0)
          {
            intr result = i;
            result.EnterFlag = intr::LEAVE;
            result.Shp = this;
            IList << result;
          }
        }
        for (auto &i : il2)
        {
          if (i.T >= 0)
          {
            intr result = i;
            result.EnterFlag = intr::LEAVE;
            result.Shp = this;
            IList << result;
          }
        }
      }
  
      return (INT)IList.size();
    } /* End of 'AllIntersect' function */

    /* Get normal function.
     * ARGUMENTS:
     *   - intersection structure:
     *       intr *I;
     * RETURNS: None.
     */
    VOID GetNormal( intr *Intr ) override
    {  
      ShpA->GetNormal(Intr);
  
      if (ShpB->IsInside(Intr->P))
      {
        vec3 normalA = Intr->N;
    
        ShpB->GetNormal(Intr);
        vec3 normalB = -Intr->N;
    
        Intr->N = normalA;
      }
  
      Intr->N.Normalize();
    } /* End of 'GetNormal' funciton */
  }; /* End of 'csg_subtrack' class */
} /* End of 'arrt' namespace */

#endif /* __CSG_h_ */
 
/* END OF 'CSG.h' FILE */
