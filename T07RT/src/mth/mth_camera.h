/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mth_camera.h
 * PURPOSE     : Ray Tracing project.
 *               Math camera module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 24.07.2025.
 * NOTE        : Module namespace 'arrt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */
 
#ifndef __mth_camera_h_
#define __mth_camera_h_
 
#include "mth_def.h"

/* Math namespace */
namespace mth
{
  /* Camera handle class */
  template<typename type>
  class camera
  {
  public:
    vec3<type> 
      Loc,              // Camera location
      Dir, Up, Right,   // Basis camera directions
      At;               // Camera pivot point

    type
      ProjDist,         // Near project plane distance
      FarClip,          // Far project plane distance
      Size,             // Inner project plane rectangle size
      Wp, Hp;           // Project plane size

    INT FrameW, FrameH; // Frame size

    matr<type>
      View,             // View matrix
      Proj,             // Projection matrix
      VP;               // View projection matrix

    /* Class constructor.
     * ARGUMENTS: None.
     */
    camera( VOID ): Loc(0, 0, 5), Dir(0, 0, -1), Up(0, 1, 0), Right(1, 0, 0), At(0, 0, 0), ProjDist(0.1), FarClip(500), Size(0.1), FrameW(500), FrameH(500)
    {
      UpdateProj();
    } /* End of 'camera' function */

    /* Set projection function.
     *   - projection options:
     *       type NewProjDist, type NewSize, type NewFarClip;
     * RETURNS:
     *   (camera &) this camera.
     */
    camera &SetProj( type NewProjDist, type NewSize, type NewFarClip )
    {
      ProjDist = NewProjDist;
      Size = NewSize;
      FarClip = NewFarClip;

      UpdateProj();
      return *this;
    } /* End of 'SetProj' function */

    /* Frame resize function.
     *   - frame size:
     *       INT NewFrameW, INT NewFrameH;
     * RETURNS:
     *   (camera &) this camera.
     */
    camera &Resize( INT NewFrameW, INT NewFrameH )
    {
      FrameW = NewFrameW;
      FrameH = NewFrameH;
 
      UpdateProj();
      return *this;
    } /* End of 'Resize' function */

    /* Set options for camera function.
     * ARGUMENTS:
     *   - location vector:
     *       const vec3<type> &L;
     *   - direction vector:
     *       const vec3<type> &A;
     *   - up vector:
     *       const vec3<type> &U;
     * RETURNS:
     *   (camera &) this camera.
     */
    camera &SetLocAtUp( const vec3<type> &L, const vec3<type> &A, const vec3<type> &U )
    {
      Loc = L;
      At = A;
      Up = U;

      Dir = (At - Loc).Normalizing();
      Right = (Dir % Up).Normalizing();
      Up = Right % Dir;

      UpdateProj();
      return *this;
    } /* End of 'SetLocAtUp' function */

    /* Get ray from camera to frame function.
     * ARGUMENTS:
     *   - frame ratios:
     *       type xs, typem ys;
     * RETURNS:
     *   (ray<type>) camera-to-frame ray.
     */
    ray<type> FrameRay( type xs, type ys )
    {
      vec3<type> Q = Dir * ProjDist + Right * ((xs - FrameW / 2.0) * Wp / FrameW) + Up * ((-ys + FrameH / 2.0) * Hp / FrameH);
      return ray(Loc + Q, Q);
    } /* End of 'FrameRay' function */

  private:
    /* Update projection function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID UpdateProj( VOID )
    {
      type rx = Size / 2, ry = Size / 2;

      if (FrameW > FrameH)
        rx *= (type)FrameW / FrameH;
      else
        ry *= (type)FrameH / FrameW;

      Wp = rx * 2;
      Hp = ry * 2;

      Proj = matr<type>::Frustum(-rx, rx, -ry, ry, ProjDist, FarClip);
    } /* End of 'UpdateProj' function */
  }; /* End of 'camera' class */
} /* end of 'mth' namespace */

#endif /* __mth_camera_h_ */

/* END OF 'mth_camera.h' FILE */