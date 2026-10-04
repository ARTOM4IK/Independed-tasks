/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : lights.cpp
 * PURPOSE     : Ray Tracing project.
 *               Lights system implementation.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'arvk'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "arvk.h"

// Light buffer structure
struct LIGHT_DATA
{
  arvk::vec4 PosCutOffAngle1;
  arvk::vec4 DirCutOffAngle2;
  arvk::vec4 ColorCutOffDist1;
  arvk::vec4 AttCutOffDist2;
  arvk::vec4 IsShadowLightTypeCutAngle12;
  arvk::matr ShadowMatr;
};

/* Type constructor.
 * ARGUMENTS: None.
 */
arvk::light::light( VOID ) : 
  Type(ltype::AMBIENT), Pos(0), Dir(0, 0, 1), Color(1), Att(1, 0, 0),
  CutOffAngle(30, 45), CutOffDist(10, 20), LightPrim(nullptr),
  BufferLight(nullptr), ShadowSize(1024), ShadowMatr(matr::Identity()),
  IsShadowCast(FALSE), ShadowFBO(0), ShadowTex(nullptr)
{
  CutOffAngleCos[0] = cos(CutOffAngle.X * PI / 180.0);
  CutOffAngleCos[1] = cos(CutOffAngle.Y * PI / 180.0);
} /* End of 'light' funciton */

/* Type destructor */
arvk::light::~light( VOID )
{
  if (BufferLight != nullptr)
    BufferLight->Free();
  
  if (IsShadowCast && ShadowFBO != 0)
  {
    //glBindFramebuffer(GL_FRAMEBUFFER, ShadowFBO);
    //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, 0, 0);
    //glBindFramebuffer(GL_FRAMEBUFFER, 0);
    //glDeleteFramebuffers(1, &ShadowFBO);
  }
  
  if (ShadowMtl->Tex[0] != nullptr)
    Rnd->texture_manager::Delete(ShadowMtl->Tex[0]);
} /* End of '~light' funciton */

/* Enable shadow function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::light::EnableShadow( VOID )
{
  if (IsShadowCast)
    return;

  //INT status;
  
  ShadowMtl = Rnd->material_manager::MtlCreate("Shadow material");
  ShadowMtl->Shd = Rnd->shader_manager::Find("shad");
  //ShadowMtl->Tex[0] = Rnd->texture_manager::TexCreateFmt("Shadow Map", ShadowSize, ShadowSize, GL_DEPTH_COMPONENT24);
  // Create shadow FBO
  //glGenFramebuffers(1, &ShadowFBO);
  //glBindFramebuffer(GL_FRAMEBUFFER, ShadowFBO);
  
  IsShadowCast = TRUE;
  ShadowSize = 1024;
  
  // Create shadow texture
  //ShadowTex = anim::Get()->texture_manager::TexCreateFmt(
  //  "Shadow Map", ShadowSize, ShadowSize, GL_DEPTH_COMPONENT24);
  
  //glGenTextures(1, &ShadowMtl->Tex[0]->TexNo);


  //glBindTexture(GL_TEXTURE_2D, ShadowMtl->Tex[0]->TexNo);
  //glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH_COMPONENT24, ShadowSize, ShadowSize);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
  //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
  //glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, ShadowMtl->Tex[0]->TexNo, 0);

  // Disable color buffer for shadow FBO
  //glDrawBuffer(GL_NONE);
  //glReadBuffer(GL_NONE);

  // Check framebuffer status
  //status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  //if (status != GL_FRAMEBUFFER_COMPLETE)
  //  OutputDebugString("\nError creating frame buffer\n");
  
  //glBindFramebuffer(GL_FRAMEBUFFER, 0);
} /* End of 'EnableShadow' funciton */

/* Update lights function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::light::Update( VOID )
{
  if (BufferLight == nullptr)
    BufferLight = Rnd->buffer_manager::BufCreate<LIGHT_DATA>(4, nullptr);
  
  LIGHT_DATA LigData;
  LigData.PosCutOffAngle1 = vec4(Pos, CutOffAngleCos[0]);
  LigData.DirCutOffAngle2 = vec4(Dir, CutOffAngleCos[1]);
  LigData.ColorCutOffDist1 = vec4(Color, CutOffDist.X);
  LigData.AttCutOffDist2 = vec4(Att, CutOffDist.Y);
  LigData.IsShadowLightTypeCutAngle12 = vec4(
    IsShadowCast ? 1.0 : 0.0, 
    (FLT)Type, 
    CutOffAngle.X, 
    CutOffAngle.Y
  );
  LigData.ShadowMatr = ShadowMatr;
  
  //BufferLight->Update(&LigData);
} /* End of 'Update' funciton */

/* Class constructor.
 * ARGUMENTS:
 *   - reference to render:
 *       render &Rnd;
 */
arvk::light_manager::light_manager( render &Rnd ) : Rnd(Rnd), LightPrimFullScreen(nullptr), LightMtl(nullptr)
{
  // Create light shaders
  LightShaders[0] = Rnd.shader_manager::Find("lights/ambient");
  LightShaders[1] = Rnd.shader_manager::Find("lights/point");
  LightShaders[2] = Rnd.shader_manager::Find("lights/dir");
  LightShaders[3] = Rnd.shader_manager::Find("lights/spot");
  
  // Create fullscreen primitive for light rendering
  LightPrimFullScreen = Rnd.primitive_manager::PrimCreate(prim_type::POINTS, 1);
  
  // Create light material
  LightMtl = Rnd.material_manager::MtlCreate("LightMaterial");
  LightMtl->Shd = LightShaders[0]; // Default to ambient
  
  // Default ambient light
  light *ambient = LightCreate(ltype::AMBIENT);
  ambient->Color = vec3(0.2);
} /* End of 'light_manager' funciton */

/* Class destructor */
arvk::light_manager::~light_manager( VOID )
{
  // Free all lights
  for (auto lig : Lights)
    LightFree(lig);
  
  if (LightPrimFullScreen != nullptr)
    Rnd.primitive_manager::PrimFree(LightPrimFullScreen);
} /* End of '~light_manager' funciton */

/* Create light function.
 * ARGUMENTS:
 *   - light:
 *       light *Lig;
 * RETURNS:
 *   (light *) created primitive interface.
 */
arvk::light * arvk::light_manager::LightCreate( ltype::LightType Type )
{
  light *Lig = new light();
  Lig->Type = Type;
  Lig->Update();
  Lights << Lig;
  return Lig;
} /* End of 'LightCreate' funciton */

/* Free light function.
 * ARGUMENTS:
 *   - light:
 *       light *Lig;
 * RETURNS: None.
 */
VOID arvk::light_manager::LightFree( light *Lig )
{
  if (Lig == nullptr)
    return;
  
  // Remove from list
  for (auto it = Lights.begin(); it != Lights.end(); ++it)
  {
    if (*it == Lig)
    {
      Lights.erase(it);
      break;
    }
  }
  
  delete Lig;
} /* End of 'LightFree' funciton */

/* Update all lights function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::light_manager::UpdateAll( VOID )
{
  for (auto lig : Lights)
    lig->Update();
} /* End of 'UpdateAll' funciton */

/* Redraw shadows function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::light_manager::RedrawShadows( VOID )
{
  // Save current camera state
  vec3 saveLoc = Rnd.Cam.Loc;
  vec3 saveAt = Rnd.Cam.At;
  vec3 saveUp = Rnd.Cam.Up;
  matr saveProj = Rnd.Cam.Proj;
  
  for (auto lig : Lights)
  {
    if (!lig->IsShadowCast)
      continue;
    
    if (lig->Type == ltype::DIR)
    {
      // Directional light shadow pass
      DBL size = 130, far_dist = 47 * 5;
      
      // Set orthographic projection for directional light
      Rnd.Cam.Resize(lig->ShadowSize, lig->ShadowSize);
      
      // Set camera looking from light direction
      Rnd.Cam.SetLocAtUp(lig->Pos, lig->Pos + lig->Dir, vec3(0, 1, 0));
      Rnd.Cam.Proj = matr::Ortho(-size, size, -size, size, -(size + 47.0), far_dist);
      Rnd.Cam.VP = Rnd.Cam.View * Rnd.Cam.Proj;

      render::BUF_CAM bc
      {
        Rnd.Cam.View,
        Rnd.Cam.Proj,
        Rnd.Cam.VP,
        vec4(Rnd.Cam.Loc, Rnd.Cam.FrameW),
        vec4(Rnd.Cam.Dir, Rnd.Cam.ProjDist),
        vec4(Rnd.Cam.Right, Rnd.Cam.Wp),
        vec4(Rnd.Cam.Up, Rnd.Cam.Hp),
        vec4(Rnd.Cam.At, Rnd.Cam.FrameH),
        vec4(Rnd.Cam.Wp, Rnd.Cam.Hp, Rnd.Cam.Size, Rnd.Cam.ProjDist)
      };
      //Rnd.BufCam->Update(&bc);      

      lig->ShadowMatr = Rnd.Cam.VP;
      lig->Update();
      
    //  // Bind shadow FBO
    //  glBindFramebuffer(GL_FRAMEBUFFER, lig->ShadowFBO);
    //  glViewport(0, 0, lig->ShadowSize, lig->ShadowSize);
    //  
    //  // Clear depth
    //  FLT depth = 1.0;
    //  glClearBufferfv(GL_DEPTH, 0, &depth);
    //  
    //  // Enable polygon offset to reduce shadow acne
    //  glEnable(GL_POLYGON_OFFSET_FILL);
    //  glPolygonOffset(4, 2);
    //  
    //  // Render scene here for shadow pass
    //  //End.ReRender();
    //  
    //  glDisable(GL_POLYGON_OFFSET_FILL);
    //  glFinish();
    //}
    //else if (lig->Type == ltype::SPOT)
    //{
    //  // Spot light shadow pass
    //  FLT proj_dist = 0.1, far_clip = lig->CutOffDist.Y * 1.2;
    //  FLT size = tan(lig->CutOffAngle.Y * PI / 180.0) * proj_dist;
    //  
    //  // Set perspective projection for spot light
    //  Rnd.Cam.Proj = matr::Frustum(-size, size, -size, size, proj_dist, far_clip);
    //  
    //  // Set camera at light position looking in light direction
    //  Rnd.Cam.SetLocAtUp(lig->Pos, lig->Pos + lig->Dir, vec3(0, 1, 0));
    //  
    //  lig->ShadowMatr = Rnd.Cam.VP;
    //  lig->Update();
    //  
    //  // Bind shadow FBO
    //  glBindFramebuffer(GL_FRAMEBUFFER, lig->ShadowFBO);
    //  glViewport(0, 0, lig->ShadowSize, lig->ShadowSize);
    //  
    //  // Clear depth
    //  FLT depth = 1.0;
    //  glClearBufferfv(GL_DEPTH, 0, &depth);
    //  
    //  // Enable polygon offset
    //  glEnable(GL_POLYGON_OFFSET_FILL);
    //  glPolygonOffset(4.0, 2.0);
    //  
    //  // Render scene here for shadow pass
    //  //anim::ReRender();
    //  
    //  glDisable(GL_POLYGON_OFFSET_FILL);
    //  glFinish();
    }
  }
  
  // Restore camera state
  Rnd.Cam.SetLocAtUp(saveLoc, saveAt, saveUp);
  Rnd.Cam.Proj = saveProj;
  Rnd.Cam.Resize(Rnd.FrameW, Rnd.FrameH);
} /* End of 'RedrawShadows' funciton */

/* Redraw lights function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::light_manager::Redraw( VOID )
{
  //// Switch to main framebuffer
  //glBindFramebuffer(GL_FRAMEBUFFER, 0);
  //glViewport(0, 0, Rnd.FrameW, Rnd.FrameH);
  //
  //// Set up blending for additive lighting
  //glBlendFunc(GL_ONE, GL_ONE);
  //glDepthMask(FALSE);
  //glDisable(GL_DEPTH_TEST);
  //
  //LightPrimFullScreen->Mtl = LightMtl;
  //
  //for (auto lig : Lights)
  //{
  //  // Set appropriate shader for light type
  //  LightMtl->Shd = LightShaders[lig->Type];
  //  
  //  // Apply light buffer
  //  if (lig->BufferLight != nullptr)
  //    lig->BufferLight->Apply();
  //  
  //  // Bind shadow texture if needed
  //  if (lig->IsShadowCast && lig->ShadowMtl->Tex[0] != nullptr)
  //  {
  //    glActiveTexture(GL_TEXTURE6);
  //    glBindTexture(GL_TEXTURE_2D, lig->ShadowMtl->Tex[0]->TexNo);
  //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_MODE, GL_COMPARE_REF_TO_TEXTURE);
  //    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_COMPARE_FUNC, GL_LEQUAL);
  //  }
  //  
  //  // Draw fullscreen quad for light contribution
  //  Rnd.Draw(LightPrimFullScreen, matr::Identity());
  //}
  //
  //// Restore render states
  //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  //glEnable(GL_DEPTH_TEST);
  //glDepthMask(TRUE);
} /* End of 'Redraw' function */

/* END OF 'lights.cpp' FILE */