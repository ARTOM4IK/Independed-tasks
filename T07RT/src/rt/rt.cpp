/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : rt.cpp                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
 * PURPOSE     : Ray Tracing project.
 *               Ray tracing definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 25.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "arrt.h"

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::shape::Intersect( const arrt::ray &R, intr *Intr )
{
  return FALSE;
} /* End of 'Intersect' function */

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::sphere::Intersect( const ray &Ray, intr *Intr )
{
  //DBL D = (Ray.Dir & (Ray.Org - C)) * (Ray.Dir & (Ray.Org - C)) - ((Ray.Org - C) & (Ray.Org - C)) + (R * R);

  //if (D < Theshold)
  //  return FALSE;

  //DBL t0 = (-Ray.Dir & (Ray.Org - C)) - sqrt(D);
  //DBL t1 = (-Ray.Dir & (Ray.Org - C)) + sqrt(D);

  //if (Intr != nullptr)
  //  if (min(t0, t1) < 0 && max(t0, t1) < 0)
  //    return FALSE;
  //  else if (min(t0, t1) < 0)
  //    Intr->T = max(t0 ,t1);
  //  else
  //    Intr->T = min(t0 ,t1);
  //return TRUE;

  //bound check
  //if (Bound.IsIntersect(Ray) == FALSE)
  //  return FALSE;

  vec3 OC = C - Ray.Org;
  DBL 
    oc2 = OC & OC,
    ok = OC & Ray.Dir,
    ok2 = ok * ok,
    h2 = R2 - (oc2 - ok2);

  if (ok < 0)
  {
    if (h2 < ok2)
      return FALSE;
    Intr->T = ok + sqrt(h2);
    Intr->Shp = this;
    return TRUE;
  }

  if (h2 < Theshold)
    return FALSE;

  DBL h = sqrt(h2);
  if (h < ok)
  {
    Intr->T = ok - h;
    Intr->Shp = this;
    return TRUE;
  }

  Intr->T = ok + h;
  Intr->Shp = this;
  return TRUE;
} /* End of 'Intersect' function */

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::plane::Intersect( const ray &R, intr *Intr )
{
  DBL nd = N & R.Dir;
  if (abs(nd) < Theshold)
    return FALSE;

  DBL t = -((N & R.Org) + D) / (nd);

  if (t > Theshold)
  {
    if (Intr != nullptr)
      Intr->T = t;
    return TRUE;
  }
  return FALSE;
} /* End of 'Intersect' function */

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::quadric::Intersect( const ray &R, intr *Intr )
{
  DBL a = A * R.Dir.X * R.Dir.X + 2 * B * R.Dir.X * R.Dir.Y + 2 * C * R.Dir.X * R.Dir.Z +
    E * R.Dir.Y * R.Dir.Y + 2 * F * R.Dir.Y * R.Dir.Z + H * R.Dir.Z * R.Dir.Z,
      b = 2 * (A * R.Org.X * R.Dir.X + B * (R.Org.X * R.Dir.Y + R.Dir.X * R.Org.Y) + C * (R.Org.X * R.Dir.Z + R.Dir.X * R.Org.Z) +
      D * R.Dir.X + E * R.Org.Y * R.Dir.Y + F * (R.Org.Y * R.Dir.Z + R.Dir.Y * R.Org.Z) + G * R.Dir.Y + H * R.Org.Z * R.Dir.Z + I * R.Dir.Z),
    c = A * R.Org.X * R.Org.X + 2 * B * R.Org.X * R.Org.Y + 2 * C * R.Org.X * R.Org.Z + 2 * D * R.Org.X +
      E * R.Org.Y * R.Org.Y + 2 * F * R.Org.Y * R.Org.Z + 2 * G * R.Org.Y + H * R.Org.Z * R.Org.Z + 2 * I * R.Org.Z + J,
    D = b * b - 4 * a * c;

  if (D < Theshold)
    return FALSE;
  if (fabs(a) < Theshold)
  {
    DBL t = -c / b;
    if (Intr != nullptr)    
    {
      Intr->Shp = this;
      Intr->T = t;
    }
    return TRUE;
  }
  

  DBL t0 = (-b - D) / (2 * a);
  DBL t1 = (-b + D) / (2 * a);

  if (Intr != nullptr)
    if (min(t0, t1) < 0 && max(t0, t1) < 0)
      return FALSE;
    else if (min(t0, t1) < 0)
    {
      Intr->Shp = this;
      Intr->T = max(t0 ,t1);
    }
    else
    {
      Intr->Shp = this;
      Intr->T = min(t0 ,t1);
    }
  return TRUE;
} /* End of 'Intersect' function */

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::box::Intersect( const ray &R, intr *Intr )
{
  DBL tnear = -DBL_MAX, tfar = DBL_MAX; 
  INT tnear_no = -1, tfar_no = -1;
 
  for (INT i = 0; i < 3; i++)
  {
    if (std::abs(R.Dir[i]) < Theshold)
    {
      if (R.Org[i] < B1[i] || R.Org[i] > B2[i])
        return FALSE;
      continue;
    }
    
    DBL t1 = (B1[i] - R.Org[i]) / R.Dir[i];
    DBL t2 = (B2[i] - R.Org[i]) / R.Dir[i];
    
    if (t1 > t2)
      std::swap(t1, t2);
    
    if (t1 > tnear)
    {
      tnear = t1;
      tnear_no = (R.Dir[i] > 0) ? i * 2 + 0 : i * 2 + 1;
    }
    
    if (t2 < tfar)
    {
      tfar = t2;
      tfar_no = (R.Dir[i] > 0) ? i * 2 + 1 : i * 2 + 0;
    }
    
    if (tnear > tfar)
      return FALSE;
      
    if (tfar < 0)
      return FALSE;
  }
  
  if (tnear < 0)
  {
    if (tfar < 0)
      return FALSE;
    Intr->T = tfar;
    Intr->I[0] = tfar_no;
  }
  else
  {
    Intr->T = tnear;
    Intr->I[0] = tnear_no;
  }
  
  Intr->Shp = this;
  return TRUE;
} /* End of '' function */

VOID arrt::box::GetNormal( intr *Intr )
{
  static vec3 normals[6] =
  {
    vec3(-1, 0, 0), vec3(1, 0, 0),
    vec3(0, -1, 0), vec3(0, 1, 0),
    vec3(0, 0, -1), vec3(0, 0, 1),
  };
  
  if (Intr == nullptr || Intr->I == nullptr)
    return;
  
  assert(Intr->I[0] >= 0 && Intr->I[0] < 6);
  
  Intr->N = normals[Intr->I[0]];
} /* End of 'GetNormal' function */

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::triangle::Intersect( const ray &R, intr *Intr )
{
  DBL nd = N & R.Dir;
  if (abs(nd) < Theshold)
    return FALSE;

  DBL t = -((N & R.Org) - D) / (nd);
  if (t > Theshold)
  {
    vec3 P = R(t);
    DBL u = (P & U1) - u0, v = (P & V1) - v0;

    if (u >= 0 && u <= 1 && v >= 0 && v <= 1 && (u + v) <= 1)
    {
      if (Intr != nullptr)
      {
        Intr->Shp = this;
        Intr->T = t;
        Intr->N = N;
        Intr->P = P;
      }
      return TRUE;
    }
  }
  return FALSE;
} /* End of 'Intersect' function */

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::cylinder::Intersect(const ray &Ray, intr *Intr) 
{
    vec3 NormalizedAxis = Axis.Normalizing();
    vec3 CO = Ray.Org - C;
    DBL a = (Ray.Dir & Ray.Dir) - pow(Ray.Dir & NormalizedAxis, 2);
    DBL b = 2 * ((Ray.Dir & CO) - (Ray.Dir & NormalizedAxis) * (CO & NormalizedAxis));
    DBL c = (CO & CO) - pow(CO & NormalizedAxis, 2) - R * R;
    DBL discr = b * b - 4 * a * c;
    if (discr < 0)
        return FALSE;
    
    DBL sqrt_discr = sqrt(discr);
    DBL t1 = (-b - sqrt_discr) / (2 * a);
    DBL t2 = (-b + sqrt_discr) / (2 * a);
    
    if (t1 > t2)
        std::swap(t1, t2);
    
    if (t2 < Theshold)
        return FALSE;
    DBL t = (t1 < Theshold) ? t2 : t1;
    
    vec3 P = Ray.Org + Ray.Dir * t;
    
    if (Intr != nullptr)
    {
        Intr->Shp = this;
        Intr->T = t;
        Intr->V[0] = P;
        vec3 CP = P - C;
        vec3 Normal = (CP - NormalizedAxis * (CP & NormalizedAxis)).Normalizing();
        Intr->N = Normal;
    }
    return TRUE;
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
INT arrt::cylinder::AllIntersect( const ray &Ray, intr_list &IList )
{
  vec3 NormalizedAxis = Axis.Normalizing();
  vec3 CO = Ray.Org - C;
  DBL a = (Ray.Dir & Ray.Dir) - pow(Ray.Dir & NormalizedAxis, 2);
  DBL b = 2 * ((Ray.Dir & CO) - (Ray.Dir & NormalizedAxis) * (CO & NormalizedAxis));
  DBL c = (CO & CO) - pow(CO & NormalizedAxis, 2) - R * R;
  DBL discr = b * b - 4 * a * c;
  if (discr < 0)
      return 0;
    
  DBL sqrt_discr = sqrt(discr);
  DBL t1 = (-b - sqrt_discr) / (2 * a);
  DBL t2 = (-b + sqrt_discr) / (2 * a);
    
  if (t1 > t2)
      std::swap(t1, t2);
    
  if (t2 < Theshold)
      return 0;
  DBL t;
  intr Intr;

  if (t1 < Theshold)
  {
    t = t2;
    Intr.EnterFlag = intr::ENTER_TYPE::LEAVE;
  }
  else
  {
    t = t1;
    Intr.EnterFlag = intr::ENTER_TYPE::ENTER;
  }

  vec3 P = Ray.Org + Ray.Dir * t;
   
  Intr.Shp = this;
  Intr.T = t;
  Intr.V[0] = P;
  vec3 CP = P - C;
  vec3 Normal = (CP - NormalizedAxis * (CP & NormalizedAxis)).Normalizing();
  Intr.N = Normal;

  IList << Intr;

  return 1;
} /* End of 'AllIntersect' function */

/* Get all ray shape intersection function.
 * ARGUMENTS:
 *   - ray to intersect with:
 *       const ray &R;
 *   - result intersection list:
 *       intr_list &IList;
 * RETURNS:
 *   (INT) number of intersecion points.
 */
INT arrt::triangle::AllIntersect( const ray &R, intr_list &IList )
{
  plane pln(D, N, vec3(0), env, surf);
  intr in;
  if (pln.Intersect(R, &in))
  {
    vec3 P = R(in.T);
    DBL u = (P & U1) - u0, v = (P & V1) - v0;

    if (u >= 0 && v >= 0 && (u + v) <= 1)
    {
      IList << intr(this, in.T, intr::ENTER);
      return 1;
    }
  }
  return 0;
} /* End of 'AllIntersect' function */

/* Get all ray shape intersection function.
 * ARGUMENTS:
 *   - ray to intersect with:
 *       const ray &R;
 *   - result intersection list:
 *       intr_list &IList;
 * RETURNS:
 *   (INT) number of intersecion points.
 */
INT arrt::box::AllIntersect( const ray &R, intr_list &IList )
{
  DBL tnear = -DBL_MAX, tfar = DBL_MAX;
  INT tnear_no = -1, tfar_no = -1;
  INT count = 0;
 
  for (INT i = 0; i < 3; i++)
  {
    if (std::abs(R.Dir[i]) < Theshold)
    {
      if (R.Org[i] < B1[i] || R.Org[i] > B2[i])
        return 0;
      continue;
    }
    
    DBL t1 = (B1[i] - R.Org[i]) / R.Dir[i];
    DBL t2 = (B2[i] - R.Org[i]) / R.Dir[i];
    
    if (t1 > t2)
      std::swap(t1, t2);
    
    if (t1 > tnear)
    {
      tnear = t1;
      tnear_no = (R.Dir[i] > 0) ? i * 2 + 0 : i * 2 + 1;
    }
    
    if (t2 < tfar)
    {
      tfar = t2;
      tfar_no = (R.Dir[i] > 0) ? i * 2 + 1 : i * 2 + 0;
    }
    
    if (tnear > tfar)
      return 0;
      
    if (tfar < 0)
      return 0;
  }
  
  if (tnear >= 0 && tnear <= tfar)
  {
    intr Intr1;
    Intr1.T = tnear;
    Intr1.Shp = this;
    Intr1.I[0] = tnear_no;
    Intr1.EnterFlag = intr::ENTER;
    IList << Intr1;
    count++;
  }
  
  if (tfar >= 0 && tfar >= tnear)
  {
    intr Intr2;
    Intr2.T = tfar;
    Intr2.Shp = this;
    Intr2.I[0] = tfar_no;
    Intr2.EnterFlag = intr::LEAVE;
    IList << Intr2;
    count++;
  }
  
  return count;
} /* End of 'AllIntersect' function */

/* Get normal function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::quadric::GetNormal( intr *Intr )
{
  Intr->N = vec3(2 * A * Intr->P[0] + 2 * B * Intr->P[1] + 2 * C * Intr->P[2] + 2 * D, 2 * B * Intr->P[0] + 2 * E * Intr->P[1] + 2 * F * Intr->P[2] + 2 * G, 2 * C * Intr->P[0] + 2 * F * Intr->P[1] + 2 * H * Intr->P[2] + 2 * I);
} /* End of 'GetNormal' function */

/* Get color function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::quadric::GetColor( intr *Intr )
{
  Intr->Color = Color;
} /* End of 'GetColor' function */

/* Get normal function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::cylinder::GetNormal( intr *Intr )
{
  //Intr->N = (Intr->P - Intr->V[0]) / R;
} /* End of 'GetNormal' function */

/* Get color function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::cylinder::GetColor( intr *Intr )
{
  Intr->Color = Color;
} /* End of 'GetColor' function */

/* Get color function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::box::GetColor( intr *Intr )
{
  Intr->Color = Color;
} /* End of 'GetColor' function */

/* Get normal function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::triangle::GetNormal( intr *Intr )
{
  Intr->N = N;
} /* End of 'GetNormal' function */

/* Get color function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::triangle::GetColor( intr *Intr )
{
  Intr->Color = Color;
} /* End of 'GetColor' function */

/* Get normal function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::shape::GetNormal( intr *Intr )
{
} /* End of 'GetNormal' function */

/* Get color function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::shape::GetColor( intr *Intr )
{
} /* End of 'GetColor' function */

/* Get normal function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::sphere::GetNormal( intr *Intr )
{
  Intr->N = (Intr->P - C).Normalizing();
} /* End of 'GetNormal' function */

/* Get color function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::sphere::GetColor( intr *Intr )
{
  Intr->Color = Color;
} /* End of 'GetColor' function */

/* Get normal function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::plane::GetNormal( intr *Intr )
{
  Intr->N = N;
} /* End of 'GetNormal' function */

/* Get color function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::plane::GetColor( intr *Intr )
{
  Intr->Color = Color;
} /* End of 'GetColor' function */

/* Get all ray shape intersection function.
 * ARGUMENTS:
 *   - ray to intersect with:
 *       const ray &R;
 *   - result intersection list:
 *       intr_list &IList;
 * RETURNS:
 *   (INT) number of intersecion points.
 */
INT arrt::sphere::AllIntersect( const ray &Ray, intr_list &IList )
{
  // Check for intersection
  vec3 OC = C - Ray.Org;
  DBL
    oc2 = OC & OC,
    ok = OC & Ray.Dir,
    ok2 = ok * ok,
    h2 = R * R - (oc2 - ok2);
 
  // Ray leaves sphere behind
  if (ok < 0)
  {
    // Check for ray starts outside sphere
    if (h2 < ok2)
      return 0;
    // Ray starts inside sphere
    IList << intr(this, ok + sqrt(h2), intr::LEAVE);
    return 1;
  }
 
  // Ray starts before sphere
  if (h2 < Theshold)
    return 0;
 
  DBL h = sqrt(h2);
  if (h < ok)
  {
    // Ray starts outside sphere
    IList << intr(this, ok - h, intr::ENTER);
    IList << intr(this, ok + h, intr::LEAVE);
    return 2;
  }
  // Ray starts inside sphere
  IList << intr(this, ok + h, intr::LEAVE);
  return 1;
} /* End of 'AllIntersect' function */

/* Get all ray shape intersection function.
 * ARGUMENTS:
 *   - ray to intersect with:
 *       const ray &R;
 *   - result intersection list:
 *       intr_list &IList;
 * RETURNS:
 *   (INT) number of intersecion points.
 */
INT arrt::quadric::AllIntersect( const ray &R, intr_list &IList )
{
  DBL a = A * R.Dir.X * R.Dir.X + 2 * B * R.Dir.X * R.Dir.Y + 2 * C * R.Dir.X * R.Dir.Z +
    E * R.Dir.Y * R.Dir.Y + 2 * F * R.Dir.Y * R.Dir.Z + H * R.Dir.Z * R.Dir.Z,
      b = 2 * (A * R.Org.X * R.Dir.X + B * (R.Org.X * R.Dir.Y + R.Dir.X * R.Org.Y) + C * (R.Org.X * R.Dir.Z + R.Dir.X * R.Org.Z) +
      D * R.Dir.X + E * R.Org.Y * R.Dir.Y + F * (R.Org.Y * R.Dir.Z + R.Dir.Y * R.Org.Z) + G * R.Dir.Y + H * R.Org.Z * R.Dir.Z + I * R.Dir.Z),
    c = A * R.Org.X * R.Org.X + 2 * B * R.Org.X * R.Org.Y + 2 * C * R.Org.X * R.Org.Z + 2 * D * R.Org.X +
      E * R.Org.Y * R.Org.Y + 2 * F * R.Org.Y * R.Org.Z + 2 * G * R.Org.Y + H * R.Org.Z * R.Org.Z + 2 * I * R.Org.Z + J,
    D = (b * b) - (4 * a * c);

  if (D < Theshold)
    return 0;
  if (fabs(a) < Theshold)
  {
    DBL t = -c / b;
    IList << intr(this, t, intr::LEAVE);
    return 1;
  }
  
  DBL t0 = (-b - D) / (2 * a);
  DBL t1 = (-b + D) / (2 * a);

  // Ray starts after shape 
  if (t0 < 0 && t1 < 0)
    return 0;
  // Ray starts inside shape
  else if (t0 < 0)
    IList << intr(this, t1, intr::LEAVE);
  // Ray starts before shape
  else
  {
    IList << intr(this, t0, intr::ENTER);
    IList << intr(this, t1, intr::LEAVE);
  }
  return 1;
} /* End of 'AllIntersect' function */

/* Get all ray shape intersection function.
 * ARGUMENTS:
 *   - ray to intersect with:
 *       const ray &R;
 *   - result intersection list:
 *       intr_list &IList;
 * RETURNS:
 *   (INT) number of intersecion points.
 */
INT arrt::plane::AllIntersect( const ray &Ray, intr_list &IList )
{
  DBL nd = N & Ray.Dir;
  if (abs(nd) < Theshold)
    return 0;

  DBL t = -((N & Ray.Org) + D) / (nd);

  if (t < Theshold)
    return 0;

  IList << intr(this, t, (nd > 0) ? intr::LEAVE : intr::ENTER);
  return 1;
} /* End of 'AllIntersect' function */

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::sphere::IsIntersect( const ray &Ray )
{

   vec3 OC = C - Ray.Org;
   DBL 
     oc2 = OC & OC,
     ok = OC & Ray.Dir,
     ok2 = ok * ok,
     h2 = R2 - (oc2 - ok2);
  
   if (ok < 0)
   {
     if (h2 < ok2)
       return FALSE;
     return TRUE;
   }
  
   if (h2 < Theshold)
     return FALSE;
  
   return TRUE;
} /* End of 'IsIntersect' function */

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::bound::IsIntersect( const ray &R )
{
  DBL tnear = -DBL_MAX, tfar = DBL_MAX;
  INT tnear_no = -1, tfar_no = -1;
 
  for (INT i = 0; i < 3; i++)
  {
    if (std::abs(R.Dir[i]) < Theshold)
    {
      if (R.Org[i] < Bound1[i] || R.Org[i] > Bound2[i])
        return FALSE;
      continue;
    }
    
    DBL t1 = (Bound1[i] - R.Org[i]) / R.Dir[i];
    DBL t2 = (Bound2[i] - R.Org[i]) / R.Dir[i];
    
    if (t1 > t2)
      std::swap(t1, t2);
    
    if (t1 > tnear)
      tnear = t1;
    
    if (t2 < tfar)
      tfar = t2;
    
    if (tnear > tfar)
      return FALSE;
      
    if (tfar < 0)
      return FALSE;
  }
  
  if (tnear < 0)
  {
    if (tfar < 0)
      return FALSE;
  }
  
  return TRUE;
} /* End of 'IsIntersect' function */

/* Get shadow coefficient function.
 *   - shadow parametrs:
 *       const vec3 &P, light_info *L;
 * RETURNS:
 *   (DBL) shadow coef.
 */
DBL arrt::pointL::Shadow( const vec3 &P, light_info *L )
{
  L->Color = color;
  L->Dist = distance;
  L->L = (pos - P).Normalizing();
  
  return Att[0] - Att[1];
} /* End of 'Shadow' function */

/* Get shadow coefficient function.
 *   - shadow parametrs:
 *       const vec3 &P, light_info *L;
 * RETURNS:
 *   (DBL) shadow coef.
 */
DBL arrt::dirL::Shadow( const vec3 &P, light_info *L )
{
  L->Color = color;
  L->Dist = Infinity;
  L->L = direction;

  return Att[0] - Att[1];
} /* End of 'Shadow' function */

/* Check if ray starts inside function.
  * ARGUMENTS:
  *   - position:
  *       const vec3 &P;
  * RETURNS:
  *   (BOOL) Is inside sign.
  */
BOOL arrt::shape::IsInside( const vec3 &P )
{
  return FALSE;
} /* End of 'IsInside' function */

/* Check if ray starts inside function.
 * ARGUMENTS:
 *   - position:
 *       const vec3 &P;
 * RETURNS:
 *   (BOOL) Is inside sign.
 */
BOOL arrt::box::IsInside( const vec3 &P )
{
  if (P.X <= B2.X && P.X >= B1.X && P.Y <= B2.Y && P.Y >= B1.Y && P.Z <= B2.Z && P.Z >= B1.Z)
    return TRUE;
  return FALSE;
} /* End of 'IsInside' function */

/* Check if ray starts inside function.
 * ARGUMENTS:
 *   - position:
 *       const vec3 &P;
 * RETURNS:
 *   (BOOL) Is inside sign.
 */
BOOL arrt::bound::IsInside( const vec3 &P )
{
  if (P.X <= Bound2.X && P.X >= Bound1.X && P.Y <= Bound2.Y && P.Y >= Bound1.Y && P.Z <= Bound2.Z && P.Z >= Bound1.Z)
    return TRUE;
  return FALSE;
} /* End of 'IsInside' function 

/* Check if ray starts inside function.
 * ARGUMENTS:
 *   - position:
 *       const vec3 &P;
 * RETURNS:
 *   (BOOL) Is inside sign.
 */
BOOL arrt::sphere::IsInside( const vec3 &P )
{
  vec3 res = P - C;
  if (!res <= R)
    return TRUE;
  return FALSE;
} /* End of 'IsInside' function */

/* Get shape bound function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arrt::box::GetBound( VOID )
{
  Bound.Bound1 = B1;
  Bound.Bound2 = B2;
} /* End of '' function */

/* Get shape bound function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arrt::sphere::GetBound( VOID )
{
  Bound.Bound1 = C - vec3(R);
  Bound.Bound2 = C + vec3(R);
} /* End of '' function */

/* Find CSG union bound function.
 * ARGUMENTS:
 *   - ShpA bound:
 *       const bound &A;
 *   - ShpB bound:
 *       const bound &B;
 * RETURNS: None.
 */
VOID arrt::bound::Union( const vec3 &A1, const vec3 &A2, const vec3 &B1, const vec3 &B2 )
{
  Bound1 = A1.Min(B1);
  Bound2 = A2.Max(B2);
} /* End of 'Union' function */

/* Find CSG intersection bound function.
 * ARGUMENTS:
 *   - ShpA bound:
 *       const bound &A;
 *   - ShpB bound:
 *       const bound &B;
 * RETURNS: None.
 */
VOID arrt::bound::Intersection( const vec3 &A1, const vec3 &A2, const vec3 &B1, const vec3 &B2 )
{
  Bound1 = A1.Max(B1);
  Bound2 = A2.Min(B2);
  //if (Bound1.X > Bound2.X || Bound1.Y > Bound2.Y || Bound1.Z > Bound2.Z)
  //{
  //  Bound1 = vec3(0);
  //  Bound2 = vec3(0);
  //}
} /* End of 'Intersection' function */

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::torus::Intersect(const ray &Ray, intr *Intr)
{
  DBL tmpA = (Ray.Org & Ray.Org) + (R2 - r2), tmpB = 2 * (Ray.Org & Ray.Dir),
    A = 2 * tmpB,
    B = tmpB * tmpB + 2 * tmpA - 4 * R2 * (Ray.Dir.Z * Ray.Dir.Z + Ray.Dir.X * Ray.Dir.X),
    C = 2 * tmpA * tmpB - 4 * R2 * 2 * (Ray.Org.Z * Ray.Dir.Z + Ray.Org.X * Ray.Dir.X),
    D = tmpA * tmpA - 4 * R2 * (Ray.Org.Z * Ray.Org.Z + Ray.Org.X * Ray.Org.X);

  // cubic resolver
  DBL b = -B,
    c = A * C - 4 * D,
    d = 4 * B * D - C * C - A * A * D;

  DBL p = c - (b * b / 3.0), 
    q = d - b * c / 3.0 + (2 * b * b * b / 27.0),
    Discr = q * q / 4.0 + p * p * p / 27.0;

  DBL y = 0,
    rootcubic1 = NAN,
    rootcubic2 = NAN,
    rootcubic3 = NAN;

  if (abs(Discr) < Theshold)
  {
    DBL root = cbrt(-q / 2.0);
    rootcubic1 = 2 * root - b / 3.0;
    rootcubic2 = -root - b / 3.0;
    //rootcubic3 = -root - b / 3.0;
  }

  else if (Discr > Theshold)
  {
    DBL sqrt_Disc = sqrt(Discr);
    DBL alpha = cbrt(-q / 2.0 + sqrt_Disc);
    DBL beta = cbrt(-q / 2.0 - sqrt_Disc);
    rootcubic1 = alpha + beta - b / 3.0;
  }

  else
  {
    DBL r = sqrt(-(p * p * p) / 27.0);
    DBL theta = acos(-q / (2.0 * r));

    rootcubic1 = 2 * sqrt(-p / 3.0) * cos(theta / 3.0) - b / 3.0;
    rootcubic2 = 2 * sqrt(-p / 3.0) * cos((theta + 2 * PI) / 3.0) - b / 3.0;
    rootcubic3 = 2 * sqrt(-p / 3.0) * cos((theta + 4 * PI) / 3.0) - b / 3.0;
  }

  DBL RootsCubic[3] = { rootcubic1, rootcubic2, rootcubic3 };

  std::vector<DBL> RootsQuartic;

  for (INT i = 0; i < 3; i++)
  {
    if (std::isnan(RootsCubic[i]))
      continue;
    DBL y1 = RootsCubic[i];

    DBL alpha = A * A / 4.0 - B + y1;
    DBL beta = A * y1 / 2.0 - C;
    DBL gamma = y1 * y1 / 4.0 - D;

    DBL t1 = NAN, t2 = NAN, t3 = NAN, t4 = NAN;

    if (alpha > 0 && abs(alpha * gamma - beta * beta) >= 0)
    {
      DBL sqrt_alpha = sqrt(alpha);
      DBL discriminant1 = (A / 2.0 - sqrt_alpha) * (A / 2.0 - sqrt_alpha) - 4.0 * (y1 / 2.0 - beta / (2.0 * sqrt_alpha));
      DBL discriminant2 = (A / 2.0 + sqrt_alpha) * (A / 2.0 + sqrt_alpha) - 4.0 * (y1 / 2.0 + beta / (2.0 * sqrt_alpha));

      // find discriminants of 2 quadratic equals
      if (discriminant1 < Theshold && discriminant2 < Theshold)
        continue;
      DBL sqrt_disc1 = sqrt(discriminant1);
      DBL sqrt_disc2 = sqrt(discriminant2);

      // find roots of 2 quadratic equals
      t1 = (-(A / 2.0 - sqrt_alpha) - sqrt_disc1) / 2.0;
      t2 = (-(A / 2.0 - sqrt_alpha) + sqrt_disc1) / 2.0;
      t3 = (-(A / 2.0 + sqrt_alpha) - sqrt_disc2) / 2.0;
      t4 = (-(A / 2.0 + sqrt_alpha) + sqrt_disc2) / 2.0;
    }

    if (t1 > Theshold && !std::isnan(t1))
      RootsQuartic.push_back(t1);
    if (t2 > Theshold && !std::isnan(t2))
      RootsQuartic.push_back(t2);
    if (t3 > Theshold && !std::isnan(t3))
      RootsQuartic.push_back(t3);
    if (t4 > Theshold && !std::isnan(t4))
      RootsQuartic.push_back(t4);
  }

  DBL t_min = INFINITY;

  for (auto &root : RootsQuartic)
  {
    if (root < t_min)
      t_min = root;
  }

  if (t_min == INFINITY)
    return FALSE;

  Intr->T = t_min;
  return TRUE;
} /* End of 'Intersect' function */

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::torus::IsIntersect( const ray &Ray )
{
  DBL tmpA = (Ray.Org & Ray.Org) + (R2 - r2), tmpB = 2 * (Ray.Org & Ray.Dir),
    A = 2 * tmpB,
    B = tmpB * tmpB + 2 * tmpA - 4 * R2 * (Ray.Dir.Z * Ray.Dir.Z + Ray.Dir.X * Ray.Dir.X),
    C = 2 * tmpA * tmpB - 4 * R2 * 2 * (Ray.Org.Z * Ray.Dir.Z + Ray.Org.X * Ray.Dir.X),
    D = tmpA * tmpA - 4 * R2 * (Ray.Org.Z * Ray.Org.Z + Ray.Org.X * Ray.Org.X);

  // cubic resolver
  DBL b = -B,
    c = A * C - 4 * D,
    d = 4 * B * D - C * C - A * A * D;

  DBL p = c - (b * b / 3.0), 
    q = d - b * c / 3.0 + (2 * b * b * b / 27.0),
    Discr = q * q / 4.0 + p * p * p / 27.0;

  DBL y = 0,
    rootcubic1 = NAN,
    rootcubic2 = NAN,
    rootcubic3 = NAN;

  if (abs(Discr) < Theshold)
  {
    DBL root = cbrt(-q / 2.0);
    rootcubic1 = 2 * root - b / 3.0;
    rootcubic2 = -root - b / 3.0;
    //rootcubic3 = -root - b / 3.0;
  }

  else if (Discr > Theshold)
  {
    DBL sqrt_Disc = sqrt(Discr);
    DBL alpha = cbrt(-q / 2.0 + sqrt_Disc);
    DBL beta = cbrt(-q / 2.0 - sqrt_Disc);
    rootcubic1 = alpha + beta - b / 3.0;
  }

  else
  {
    DBL r = sqrt(-(p * p * p) / 27.0);
    DBL theta = acos(-q / (2.0 * r));

    rootcubic1 = 2 * sqrt(-p / 3.0) * cos(theta / 3.0) - b / 3.0;
    rootcubic2 = 2 * sqrt(-p / 3.0) * cos((theta + 2 * PI) / 3.0) - b / 3.0;
    rootcubic3 = 2 * sqrt(-p / 3.0) * cos((theta + 4 * PI) / 3.0) - b / 3.0;
  }

  DBL RootsCubic[3] = { rootcubic1, rootcubic2, rootcubic3 };

  std::vector<DBL> RootsQuartic;

  for (INT i = 0; i < 3; i++)
  {
    if (std::isnan(RootsCubic[i]))
      continue;
    DBL y1 = RootsCubic[i];

    DBL alpha = A * A / 4.0 - B + y1;
    DBL beta = A * y1 / 2.0 - C;
    DBL gamma = y1 * y1 / 4.0 - D;

    DBL t1 = NAN, t2 = NAN, t3 = NAN, t4 = NAN;

    if (alpha > 0 && abs(alpha * gamma - beta * beta) >= 0)
    {
      DBL sqrt_alpha = sqrt(alpha);
      DBL discriminant1 = (A / 2.0 - sqrt_alpha) * (A / 2.0 - sqrt_alpha) - 4.0 * (y1 / 2.0 - beta / (2.0 * sqrt_alpha));
      DBL discriminant2 = (A / 2.0 + sqrt_alpha) * (A / 2.0 + sqrt_alpha) - 4.0 * (y1 / 2.0 + beta / (2.0 * sqrt_alpha));

      // find discriminants of 2 quadratic equals
      if (discriminant1 < Theshold && discriminant2 < Theshold)
        continue;
      DBL sqrt_disc1 = sqrt(discriminant1);
      DBL sqrt_disc2 = sqrt(discriminant2);

      // find roots of 2 quadratic equals
      t1 = (-(A / 2.0 - sqrt_alpha) - sqrt_disc1) / 2.0;
      t2 = (-(A / 2.0 - sqrt_alpha) + sqrt_disc1) / 2.0;
      t3 = (-(A / 2.0 + sqrt_alpha) - sqrt_disc2) / 2.0;
      t4 = (-(A / 2.0 + sqrt_alpha) + sqrt_disc2) / 2.0;
    }

    if (t1 > Theshold && !std::isnan(t1))
      RootsQuartic.push_back(t1);
    if (t2 > Theshold && !std::isnan(t2))
      RootsQuartic.push_back(t2);
    if (t3 > Theshold && !std::isnan(t3))
      RootsQuartic.push_back(t3);
    if (t4 > Theshold && !std::isnan(t4))
      RootsQuartic.push_back(t4);
  }

  DBL t_min = INFINITY;

  for (auto &root : RootsQuartic)
  {
    if (root < t_min)
      t_min = root;
  }

  if (t_min == INFINITY)
    return FALSE;

  return TRUE;
} /* End of 'IsIntersect' function */

/* Get normal function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::torus::GetNormal( intr *Intr )
{
  vec3 P = Intr->P;
  DBL len_proj = !vec2(P.X, P.Z);
  vec3 N = vec3(P.X * (1 - R / len_proj), P.Y, P.Z * (1 - R / len_proj));

  Intr->N = N.Normalize();
} /* End of 'GetNormal' function */

/* Get color function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::torus::GetColor( intr *Intr )
{
} /* End of 'GetColor' function */

/* Get all ray shape intersection function.
 * ARGUMENTS:
 *   - ray to intersect with:
 *       const ray &R;
 *   - result intersection list:
 *       intr_list &IList;
 * RETURNS:
 *   (INT) number of intersecion points.
 */
INT arrt::torus::AllIntersect( const ray &Ray, intr_list &IList )
{
  return 0;
} /* End of 'AllIntersect' function */

/* Check if ray starts inside function.
 * ARGUMENTS:
 *   - position:
 *       const vec3 &P;
 * RETURNS:
 *   (BOOL) Is inside sign.
 */
BOOL arrt::torus::IsInside( const vec3 &P )
{
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
BOOL arrt::bicubic::Intersect( const ray &R, intr *Intr )      
{
  BOOL found = FALSE;
  DBL closest_t = DBL_MAX;
  INT p = 2;

  for (auto pt : Patches)
  {
    for (INT i = 0; i < 3; i++)
      for (INT j = 0; j < 3; j++)
      {
        for (INT v = 0; v <= p; v++)
          for (INT u = 0; u <= p; u++)
            {
              vec3 p00 = pt.p[i + 1][j] * u / DBL(p) + pt.p[i][j] * (p - u) / DBL(p);       // (0,0)
              vec3 p03 = pt.p[i + 1][j + 1] * v / DBL(p) + pt.p[i + 1][j] * (p - v) / DBL(p);       // (0,0)
              vec3 p30 = pt.p[i][j] * v / DBL(p) + pt.p[i][j + 1] * (p - v) / DBL(p);
              vec3 p33 = pt.p[i][j + 1] * u / DBL(p) + pt.p[i + 1][j + 1] * (p - u) / DBL(p);
              //vec3 p03 = pt.p[i + 1][j + 1];   // (0,1)
              //vec3 p30 = pt.p[i][j];           // (1,0)
              //vec3 p33 = pt.p[i][j + 1];       // (1,1)

              intr tmp_intr;

              arrt::triangle triangl = arrt::triangle(p00, p03, p33, vec3(0), Env, Surf);
              if (triangl.Intersect(R, &tmp_intr))
              {
                  if (tmp_intr.T > 0 && tmp_intr.T < closest_t)
                  {
                      closest_t = tmp_intr.T;
                      found = TRUE;
                  }
              }

              triangl = arrt::triangle(p00, p33, p30, vec3(0), Env, Surf);
              if (triangl.Intersect(R, &tmp_intr))
              {
                  if (tmp_intr.T > 0 && tmp_intr.T < closest_t)
                  {
                      closest_t = tmp_intr.T;
                      found = TRUE;
                  }
              }

            }
        }
  }
  
  if (found && Intr != nullptr)
  {
    Intr->T = closest_t;
    Intr->Shp = this;
  }
  
  return found;
} /* End of 'Intersect' function */

/* Get normal function.
 * ARGUMENTS:
 *   - intersection structure:
 *       intr *I;
 * RETURNS: None.
 */
VOID arrt::bicubic::GetNormal( intr *Intr )
{
} /* End of 'GetNormal' function */

/* Find intersection with all objects function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 * RETURNS: None.
 */
INT arrt::bicubic::AllIntersect( const ray &Ray, intr_list &IList )
{
  return 0;
} /* End of 'AllIntersect' function */

/* Load bicubic model function.
 * ARGUMENTS:
 *   - Model Filename:
 *       const std::string &FileName;
 *   (BOOL) Model is read.
 */
BOOL arrt::bicubic::Load( const std::string &FileName )
{
  std::fstream f(FileName, std::fstream::in);

  if (!f.is_open())
    return FALSE;

  INT faces;
  f >> faces;
  Patches.resize(faces);

  for (auto &pt : Patches)
    for (INT i = 0; i < 4; i++)
      for (INT j = 0; j < 4; j++)
        f >> pt.p[i][j].X >> pt.p[i][j].Y >> pt.p[i][j].Z;
  return TRUE;
} /* End of 'Load' function */

/* END OF 'rt.cpp' FILE */
