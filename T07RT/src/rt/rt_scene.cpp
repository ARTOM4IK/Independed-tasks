/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : rt_scene.cpp
 * PURPOSE     : Ray Tracing project.
 *               Ray tracing scene module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 25.07.2025.
 * NOTE        : Module namespace 'arrt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "arrt.h"
#include <algorithm>

/* Get shadow coefficient function.
 *   - shadow parametrs:
 *       const vec3 &P, light_info *L;
 * RETURNS:
 *   (DBL) shadow coef.
 */
DBL arrt::light::Shadow( const vec3 &P, light_info *L )
{
  return 0;
} /* End of 'Shadow' function */

/* Trace ray function.
 *   - ray:
 *       const ray &R;
 *   - trace parametrs:
 *       const envi &Media, DBL Weight, INT RecLevel;
 * RETURNS:
 *   (vec3) traced ray's vector.
 */
arrt::vec3 arrt::scene::Trace( const ray &R, const envi &Media, DBL Weight, INT RecLevel )
{
  vec3 color = BackgroundColor;
  intr closest_intersection;
  DBL fog;

  if (RecLevel < MaxRecLevel)
  {
    if (Intersect(R, &closest_intersection))
    {
      closest_intersection.P = R(closest_intersection.T);
      closest_intersection.Shp->GetNormal(&closest_intersection);
      closest_intersection.Shp->GetColor(&closest_intersection);
      fog  = (closest_intersection.T - FogStart) / (FogEnd - FogStart);
      if (fog < 0)
        fog = 0;
      else if (fog > 1)
        fog = 1;
      shade_info sh;
      closest_intersection.Shp->GetShadeInfo(&sh, &closest_intersection);
      color = Shade(R.Dir, Media, &sh, Weight, RecLevel);
      color = vec3(FogColor.X * fog + color.X * (1 - fog), FogColor.Y * fog + color.Y * (1 - fog), FogColor.Z * fog + color.Z * (1 - fog));
      //fog = exp(-closest_intersection.T);
    }
  }
  else 
    color = BackgroundColor;
  return color;
} /* End of 'Trace' function */
           
/* Shade color function.
 *   - light:
 *       shape *Lgh;
 * RETURNS:
 *   (vec3) shaded color.
 */
arrt::vec3 arrt::scene::Shade( const vec3 &V, const envi &Env, shade_info *Sh, DBL Weight, INT RecLevel )
{
  // Result color
  vec3 res_color(0);
 
  DBL vn = V & Sh->N;
  // Check: enter or leave
  BOOL IsEnter = TRUE;
  if (vn > 0)
  {
    // leave
    Sh->N = -Sh->N;
    vn = V & Sh->N;
    IsEnter = FALSE;
  }
 
  // Reflected ray evaluation
  vec3 R = V - Sh->N * (2 * vn);
 
  // Accounting ambient reflection
  if (Sh->Surf.Ka.IsUsage)
    res_color += Sh->Surf.Ka.K;/* * AmbientColor;*/

  // Accounting light sources
  for (auto lig : Lights)
  {
    light_info light;
     DBL s = lig->Shadow(Sh->P, &light);
    s *= min(1.0, 1 / (lig->Cc + lig->Cl * light.Dist + lig->Cq * light.Dist * light.Dist));
    if (s < Theshold)
      continue;
 
    // Shadow cast
    ray LightRay(Sh->P + light.L * Theshold, light.L);      
 
    // Enumerate all scene objects
    if (intr_list ilist; AllIntersect(LightRay, ilist) > 0)
    {
      for (auto &i : ilist)
        if (i.T < light.Dist)
        {
          // Correct intersection data
          if (!i.IsP)
            i.P = LightRay(i.T);
          if (!i.IsN)
            i.Shp->GetNormal(&i);
          shade_info sh;
          i.Shp->GetShadeInfo(&sh, &i);
 
          light.Color *= Sh->Surf.Kt;

          if (!coef(light.Color).IsUsage)
          {
            s = 0;
            break;
          }
        }
    }
    // Light reflection
    if (s > Theshold)
    {
      // Accounting diffuse reflection
      DBL nl = Sh->N & light.L;
      if (nl > Theshold)
      {
        res_color += Sh->Surf.Kd.K * light.Color * nl * s;
 
        // Accounting specular reflection
        DBL rl = R & light.L;
        if (rl > Theshold)
          res_color += Sh->Surf.Ks.K * light.Color * pow(rl, Sh->Surf.Ph) * s;
      }
    }
  }
 
  // Reflected ray accounting
  if (Sh->Surf.Kr.IsUsage && coef(Sh->Surf.Kr.K * Weight).IsUsage)
    res_color += Trace(ray(Sh->P + R * Theshold, R), Env,
      Weight * Sh->Surf.Kr.K.MaxC(), RecLevel + 1) * Sh->Surf.Kr.K * Weight;
 
  // Refracted ray accounting
  if (Sh->Surf.Kt.IsUsage && coef(Sh->Surf.Kt.K * Weight).IsUsage)
  {
    vec3 V1 = V;
    DBL
      eta =
        IsEnter ?
          Sh->Env.RefractionCoef / Env.RefractionCoef :
          Air.RefractionCoef / Env.RefractionCoef,
          factor = (1 - (1 - vn * vn)) * eta * eta;
        //factor = (1 + eta * eta * (vn * vn - 1));
 
    // Check for full inner reflection
    if (factor > Theshold)
    {   
      //vec3 T = (V - Sh->N * (V & Sh->N)) * eta - Sh->N * sqrt(factor);
      vec3 T = V * eta + Sh->N * (-vn * eta - sqrt(factor));
      
      //vec3 T = V * eta + Sh->N * ((-V & Sh->N) * eta - sqrt(factor)); 

      //vec3 T = V * eta + Sh->N * (eta * (-V & Sh->N ) - sqrt(factor));
      res_color += Trace(ray(Sh->P + T * Theshold, T), IsEnter ? Sh->Env : Air,
        Weight * Sh->Surf.Kt.K.MaxC(), RecLevel + 1) * Sh->Surf.Kt.K * Weight;
    }
  }
  //return Sh->N;
  return res_color;
} /* End of 'Shade' function */

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::scene::IsIntersect( const ray &R )
{
  for (auto Shp: Shapes)
  {
    if (Shp->Intersect(R, nullptr))
      return TRUE;
  }
  return FALSE;
} /* End of 'IsIntersect' function */

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::shape::IsIntersect( const ray &R )
{
  return FALSE;
} /* End of 'IsIntersect' function */

/* Finder intersection an object function.
 * ARGUMENTS:
 *   - ray:
 *       const ray &Ray;
 *   - intersection structure:
 *       intr_list &IList;
 *   (BOOL) Is intersect sign.
 */
BOOL arrt::scene::Intersect( const ray &R, intr *In )
{
  intr closest_intr {};

  for (auto Shp: Shapes)
  {
    intr cur_intr {};

    if (Shp->Intersect(R, &cur_intr))
      if (closest_intr.Shp == nullptr || (closest_intr.T > cur_intr.T))
        closest_intr = cur_intr, closest_intr.Shp = Shp;
  }
  if (closest_intr.Shp == nullptr)
    return FALSE;
  if (In != nullptr)
    *In = closest_intr;
  return TRUE;
} /* End of 'Intersect' function */

/* Render scene function.
 *   - camera:
 *       camera &Cam;
 *   - frame:
 *       frame &Frm;
 * RETURNS: None.
 */
VOID arrt::scene::Render( camera &Cam, frame &Frm )             
{                                                        
  //for (INT y = 0; y < Frm.H; y++)                        
  //  for (INT x = 0; x < Frm.W; x++)                      
  //  {                                                    
  //    ray R = Cam.FrameRay(x, y);                        
  //    vec3 color = Trace(R);                              
  //    Frm.PutPixel(x, y, color);                         
  //  }                     
  Cam.Resize(Frm.W, Frm.H);
  INT n = std::thread::hardware_concurrency() - 1;
  std::vector<std::thread> Ths;
  //n = 1;
  Ths.resize(n);
  StartRow = 0;
  for (INT i = 0; i < n; i++)
  {
    Ths[i] = std::thread(
      [&]( VOID )
      {
        INT y = 0;
        while (y < Frm.H)
        {
          y = StartRow++;
          for (INT x = 0; x < Frm.W; x++)
          {
            ray r = Cam.FrameRay(x + 0.5, y + 0.5);
            vec3 c = Trace(r, Air, 1, 0);
            Frm.PutPixel(x, y, Frm.ToRGB(c[0], c[1], c[2]));

            //INT Sub = 5;
            //DBL ds = 1.0 / Sub;
 
            //INT n = 0;
            //vec3 c(0), c2(0), empty;
            //while (n < 300)
            //{
            //  for (INT kx = 0; kx < Sub; kx++)
            //    for (INT ky = 0; ky < Sub; ky++)
            //    {
            //      ray r = Cam.FrameRay(x + kx * ds + ds * empty.Rnd1().X,
            //                            y + ky * ds + ds * empty.Rnd1().X);
            //      vec3 c1 = Trace(r, Air, 1, 0);
            //      c += c1;
            //      c2 += c1 * c1;
            //      n++;
            //    }
            //  vec3 disp2 = (c2 / n - (c  / n) * (c / n)) * n / (n - 1);
            //  DBL d = COM_SQR(disp2.X) + COM_SQR(disp2.Y) + COM_SQR(disp2.Z);
            //  if (d < 0.00001)
            //    break;
            //}
            //c /= n;
            //Frm.PutPixel(x, y, frame::ToRGB(c.X, c.Y, c.Z));
          }
        }
      });
  }
  for (INT i = 0; i < n; i++)
    Ths[i].join();
  //. . .
} /* End of 'Render' function*/

/* Add point light to stock function.
 *   - point light parametrs:
 *       const vec3 &pos, const vec3 &color, const DBL &dist, const vec3 &att;
 * RETURNS: None.
 */
VOID arrt::scene::AddSphere( const DBL &radius, const vec3 &centre, const vec3 &color, const envi &env, const surface &srf )
{  
  Shapes << new sphere(radius, centre, color, env, srf);
} /* End of 'AddSphere' function */

/* Add triangle to stock function.
 *   - triangle paramtrs:
 *       const vec3 &p0, const vec3 &p1, const vec3 &p2, const vec3 &color, const envi &e, const surface &S;
 * RETURNS: None.
 */
VOID arrt::scene::AddPointL( const vec3 &pos, const vec3 &color, const DBL &dist, const vec3 &att )
{
  Lights << new pointL(pos, color, dist, att);
} /* End of 'AddPointL' function */

/* Add plane to stock function.
 *   - plane parametrs:
 *       const DBL &d, const vec3 &n, const vec3 &color, const envi &env, const surface &srf;
 * RETURNS: None.
 */
VOID arrt::scene::AddPlane( const DBL &d, const vec3 &n, const vec3 &color, const envi &env, const surface &srf )
{
  Shapes << new plane(d, n, color, env, srf);
} /* End of 'AddPlane' function */

/* Add quadric to stock function.
 *   - quadric parametrs:
 *       const vec3 &col, const DBL &A, const DBL &B, const DBL &C, const DBL &D, const DBL &E, 
 *       const DBL &F, const DBL &G, const DBL &H, const DBL &I, const DBL &J, const envi &env, const surface &srf;
 * RETURNS: None.
 */
VOID arrt::scene::AddQuadric( const vec3 &col, const DBL &A, const DBL &B, const DBL &C, const DBL &D, const DBL &E, const DBL &F, const DBL &G, const DBL &H, const DBL &I, const DBL &J, const envi &env, const surface &srf )  
{
  Shapes << new quadric(col, A, B, C, D, E, F, G, H, J, I, env, srf);
} /* End of 'AddQuadric' function */

/* Add triangle to stock function.
 *   - triangle paramtrs:
 *       const vec3 &p0, const vec3 &p1, const vec3 &p2, const vec3 &color, const envi &e, const surface &S;
 * RETURNS: None.
 */
VOID arrt::scene::AddTriangle( const vec3 &p0, const vec3 &p1, const vec3 &p2, const vec3 &color, const envi &e, const surface &S )
{
  Shapes << new triangle(p0, p1, p2, color, e, S);
} /* End of 'AddTriangle' function */

/* Add cylinder to stock function.
 *   - cylinder parametrs:
 *       const vec3 &C, const vec3 &Axis, const DBL &R, const vec3 &color, const envi &e, const surface &S;
 * RETURNS: None.
 */
VOID arrt::scene::AddCylinder( const vec3 &C, const vec3 &Axis, const DBL &R, const vec3 &color, const envi &e, const surface &S )
{
  Shapes << new cylinder(C, Axis, R, color, e, S);
} /* End of 'AddCylinder' function */

/* Add box to stock function.
 *   - box parametrs:
 *       const vec3 &B1, const vec3 &B2, const vec3 &color, const envi &e, const surface &S;
 * RETURNS: None.
 */
VOID arrt::scene::AddBox( const vec3 &B1, const vec3 &B2, const vec3 &color, const envi &e, const surface &S )
{
  Shapes << new box(B1, B2, color, e, S);
} /* End of 'AddBox' function */

arrt::scene::~scene( VOID )
{
  for (auto Shp : Shapes)
  {
    delete Shp;
  }
  for (auto Lig : Lights)
  {
    delete Lig;
  }
} /* End of '~scene' function */

/* Get ray scane shapes all intersections function.
 * ARGUMENTS:
 *   - ray to intersect with:
 *       const ray &R;
 *   - result intersection list:
 *       intr_list &IList;
 * RETURNS:
 *   (INT) number of intersecion points.
 */
INT arrt::scene::AllIntersect( const ray &Ray, intr_list &IList )
{
  intr closest_intersection, intersection;
  shape *closest_shape = nullptr;
 
  // Enum all scene shapes
  INT n = 0;
  for (auto s : Shapes)
    n += s->AllIntersect(Ray, IList);
  std::sort(IList.begin(), IList.end(),
    []( const intr &A, const intr &B )
    {
      return A.T < B.T;
    });
  return n;
} /* End of 'arrt::scene::AllIntersect' function */

/* Get ray scane shapes all intersections function.
 * ARGUMENTS:
 *   - ray to intersect with:
 *       const ray &R;
 *   - result intersection list:
 *       intr_list &IList;
 * RETURNS:
 *   (INT) number of intersecion points.
 */
INT arrt::shape::AllIntersect( const ray &Ray, intr_list &IList )
{
  return 0;
} /* End of 'arrt::scene::AllIntersect' function */

/* Get shape bound function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arrt::shape::GetBound( VOID )
{
} /* End of 'GetBound' fucntion */

/* END OF 'rt_scene.cpp' FILE */
