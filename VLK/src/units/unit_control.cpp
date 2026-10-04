/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : unit_control.cpp
 * PURPOSE     : Ray Tracing project.
 *               Precompiled header definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "arvk.h"

//namespace arvk
//{
//  class control_unit: public unit                                                                                                                                             
//  {
//  public:
//    control_unit( anim *Ani )
//    {
//    }
//
//    VOID Render( anim *Ani ) override
//    {
//    }
//
//    VOID Response( anim *Ani ) override
//    {
//      if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['P'])
//        Ani->IsPause = !Ani->IsPause;
//      if (Ani->Keys[VK_SHIFT] && Ani->KeysClick['W'])
//      {
//        INT mods[2];
//
//        glGetIntegerv(GL_POLYGON_MODE, mods);
//        glPolygonMode(GL_FRONT_AND_BACK, mods[0] == GL_FILL ? GL_LINE : GL_FILL);
//      }
//      if (Ani->Keys[VK_ESCAPE])
//        (VOID)0;//Ani->DoExit();
//      if (Ani->IsPause || Ani->Keys[VK_CONTROL])
//      {
//        FLT plen, cosT, sinT, sinP, cosP, Wp = Ani->Cam.Size, Hp = Ani->Cam.Size, sx, sy;
//        vec3 dv;
//        FLT Dist = !(Ani->Cam.Loc - Ani->Cam.At);
//        
//        if (Dist < 0.00102)
//          Dist = 0.00102;
//        if (Ani->Cam.FrameW >= Ani->Cam.FrameH)
//          Wp *= (FLT)Ani->Cam.FrameW / Ani->Cam.FrameH;
//        else
//          Hp *= (FLT)Ani->Cam.FrameH / Ani->Cam.FrameW;
//        sx = Wp / Ani->Cam.FrameW * Dist / Ani->Cam.ProjDist;
//        sy = Hp / Ani->Cam.FrameH * Dist / Ani->Cam.ProjDist;
//        dv = (Ani->Cam.Right * (-sx * Ani->Mdx) + Ani->Cam.Up * (-sy * Ani->Mdy)) * Ani->Keys[VK_RBUTTON];
//        Ani->Cam.At += dv;
//        Ani->Cam.Loc += dv;
//        cosT = (Ani->Cam.Loc[1] - Ani->Cam.At[1]) / Dist;
//        sinT = sqrt(1 - cosT * cosT);
//        plen = sinT * Dist;
//        sinP = (Ani->Cam.Loc[0] - Ani->Cam.At[0]) / plen;
//        cosP = (Ani->Cam.Loc[2] - Ani->Cam.At[2]) / plen;
//        FLT Azimuth = R2D(atan2(sinP, cosP));
//        FLT Elevator = R2D(PI / 2 + acos(cosT));
//
//        Dist += Ani->GlobalDeltaTime * (0.2 * Ani->Mdz + 8 * (1 + Ani->Keys[VK_SHIFT] * 26) * (Ani->Keys[VK_NEXT]));
//        Azimuth += Ani->GlobalDeltaTime * (-0.8 * 30 * Ani->Keys[VK_LBUTTON] * Ani->Mdz);
//        Elevator += Ani->GlobalDeltaTime * (-0.8 * 30 * Ani->Keys[VK_LBUTTON] * Ani->Mdz);
//
//        if (Elevator > 89.9)
//          Elevator = 89.9;
//        else if (Elevator < -89.9)
//          Elevator = -89.9;
//        if (Dist < 0.002)
//          Dist = 0.002;
//        if (Ani->Keys['F'])
//          Dist = 8, Azimuth = 45, Elevator = -45, Ani->Cam.At = vec3(0);
//
//        Ani->Cam.SetLocAtUp((matr::Rotate(Elevator, vec3(1, 0, 0)) * matr::Rotate(Azimuth, vec3(0, 1, 0)) * 
//            matr::Translate(Ani->Cam.At)).TransformPoint(vec3(0, 0, Dist)), Ani->Cam.At, vec3(0, 1, 0));       
//      }
//    }
//  };
//}

/* END OF 'unit_control.cpp' FILE */
