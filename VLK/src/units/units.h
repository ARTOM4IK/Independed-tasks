/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : units.h
 * PURPOSE     : Ray Tracing project.
 *               Units definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'arvk'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __units_h_
#define __units_h_

#include "anim/anim.h"

/* Animation namespace */
namespace arvk
{
  /* control class */
  class control_unit: public unit
  {
  public:
    font fnt;
    BOOL IsWire = FALSE;
    /* Class constructor.
     * ARGUMENTS: 
     *   - animation pointer:
     *       anim *Ani;
     */
    control_unit( anim *Ani )
    {
      fnt.Load("bin/fonts/Consolas.g3df");
    } /* End of 'control_unit' funciton */

    /* Render unit function.
     * ARGUMENTS: 
     *   - animation pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Render( anim *Ani ) override
    {
      matr SaveWVP = Ani->Cam.VP;
      static CHAR Buf[102];
      sprintf(Buf, "CGSG Animation: FPS = %.5f", Ani->FPS);

      Ani->Cam.VP = matr::Ortho(0, (Ani->FrameW - 1) / 30.0, -(Ani->FrameH - 1) / 30.0, 0, -1, 1);
      fnt.Draw(Buf, vec3(-30, 15, 0), 1);
      Ani->Cam.VP = SaveWVP;
      SetWindowText(Ani->GetHWnd(), Buf);
    } /* End of 'Render' funciton */

    /* Response unit function.
     * ARGUMENTS: 
     *   - animation pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Response( anim *Ani ) override
    {
      if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['P'])
        Ani->IsPause = !Ani->IsPause;
      if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['W'])
      {
        //IsWire = !IsWire;
        //Ani->ChangeWireMode(IsWire);

        //INT mods[2];

        //glGetIntegerv(GL_POLYGON_MODE, mods);
        //glPolygonMode(GL_FRONT_AND_BACK, mods[0] == GL_FILL ? GL_LINE : GL_FILL);
      }
      if (Ani->Keys[VK_ESCAPE])
        (VOID)0;//Ani->DoExit();
      if (Ani->IsPause || Ani->Keys[VK_CONTROL])
      {
        /* Rotate handle */
        FLT
          Dist = !(Ani->Cam.At - Ani->Cam.Loc),
          cosT = (Ani->Cam.Loc.Y - Ani->Cam.At.Y) / Dist,
          sinT = sqrt(1 - cosT * cosT),
          plen = Dist * sinT,
          cosP = (Ani->Cam.Loc.Z - Ani->Cam.At.Z) / plen,
          sinP = (Ani->Cam.Loc.X - Ani->Cam.At.X) / plen,
          Azimuth = R2D(atan2(sinP, cosP)),
          Elevator = R2D(atan2(sinT, cosT));

        Azimuth += 
          (-1 * Ani->Keys[VK_LBUTTON] * Ani->Mdx +
           Ani->GlobalDeltaTime * 100 * -(Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]));

        Elevator += 
          (-1 * Ani->Keys[VK_LBUTTON] * Ani->Mdy +
           Ani->GlobalDeltaTime * 100 * (Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]));

        if (Elevator < 0.08)
          Elevator = 0.08;
        else if (Elevator > 178.90)
          Elevator = 178.90;
 
        Dist += (1 + Ani->Keys[VK_SHIFT] * 30) *
          (0.01 * Ani->Mdz +
           Ani->GlobalDeltaTime * 100 * (Ani->Keys[VK_NEXT] - Ani->Keys[VK_PRIOR]));
        if (Dist < 0.1)
          Dist = 0.1;
 
        /* Handle camera position */
        if (Ani->Keys[VK_RBUTTON])
        {
          FLT Wp, Hp, sx, sy;
          vec3 dv;
 
          Wp = Ani->Cam.Size;
          Hp = Ani->Cam.Size;
 
          if (Ani->FrameW > Ani->FrameH)
            Wp *= (FLT)Ani->FrameW / Ani->FrameH;
          else
            Hp *= (FLT)Ani->FrameH / Ani->FrameW;
 
          sx = -Ani->Mdx * Wp / Ani->FrameW * Dist / Ani->Cam.ProjDist;
          sy = Ani->Mdy * Hp / Ani->FrameH * Dist / Ani->Cam.ProjDist;

          dv = (Ani->Cam.Right * sx) + (Ani->Cam.Up * sy);
          Ani->Cam.At = Ani->Cam.At + dv;
          Ani->Cam.Loc = Ani->Cam.Loc + dv;
        }
        Ani->Cam.SetLocAtUp((matr::RotateX(Elevator) * matr::RotateY(Azimuth) * matr::Translate(Ani->Cam.At)).TransformPoint(vec3(0, Dist, 0)), Ani->Cam.At, vec3(0, 1, 0));
      }
    } /* End of 'Response' funciton */
  }; /* End of 'control_unit' class */

  /* skybox class */
  class skybox_unit: public unit
  {
  public:
    prim *SkyBox;                

    /* Class constructor.
     * ARGUMENTS: 
     *   - animation pointer:
     *       anim *Ani;
     */
    skybox_unit( anim *Ani )
    {
      //set skybox
      material *SkyMtl = Ani->MtlCreate("Skybox material");
      SkyMtl->Shd = Ani->shader_manager::Find("SkyBox");
      SkyMtl->Tex[0] = Ani->texture_manager::TexCreateCubeMap("bluecloud");
      SkyBox = Ani->PrimCreate(prim_type::POINTS, 1);
      SkyBox->Mtl = SkyMtl;
    } /* End of 'skybox_unit' funciton */

    /* Render unit function.
     * ARGUMENTS: 
     *   - animation pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Render( anim *Ani ) override
    {
      //glDisable(GL_DEPTH_TEST);
      //glDepthMask(FALSE);

      //if (SkyBox->Mtl->Shd != nullptr)
      //  SkyBox->Mtl->Shd->Apply();
    
      //glActiveTexture(GL_TEXTURE0);
      //glBindTexture(GL_TEXTURE_CUBE_MAP, SkyBox->Mtl->Tex[0]->TexNo);

      //Ani->Draw(SkyBox, matr::Identity());
      //glEnable(GL_DEPTH_TEST);
      //glDepthMask(TRUE);
    } /* End of 'Render' funciton */

    /* Response unit function.
     * ARGUMENTS: 
     *   - animation pointer:
     *       anim *Ani;
     * RETURNS: None.
     */
    VOID Response( anim *Ani ) override
    {
    } /* End of 'Response' funciton */
  }; /* End of 'skybox_unit' class */
} /* End of 'arvk' namespace*/

#endif /* __units_h_ */

/* END OF 'units.h' FILE */
