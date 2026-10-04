/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/

/* FILE NAME   : trg.cpp
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

/* Class constructor.
 * ARGUMENTS: None. 
 */
arvk::target::target( VOID ) : RndBufId(0), FBOId(0), Width(0), Height(0), Attachments(6), Screen(nullptr), SkyBox(nullptr)
{
} /* End of 'target' function */

/* Class desstructor */
arvk::target::~target( VOID )
{
  Free();
  Rnd->PrimFree(Screen);
  Rnd->PrimFree(SkyBox);
} /* End of '~target' function */

/* Init target function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::target::Init( VOID )
{
  TargetTex.resize(Attachments);

  material *mtl = Rnd->MtlCreate("Target material");
 
  mtl->Shd = Rnd->shader_manager::Find("target0");
  for (INT i = 0; i < Attachments; i++)
  {
    //mtl->Tex[i] = Rnd->texture_manager::TexCreateFmt("Attachment" + i, Rnd->FrameW, Rnd->FrameH, GL_RGBA32F);
    TargetTex[i] = mtl->Tex[i];
  }
  Screen = Rnd->PrimCreate(prim_type::POINTS, 1);
  Screen->Mtl = mtl;

  Create(Rnd->FrameW, Rnd->FrameH);
} /* End of 'Init' function */

/* Create target function.
 * ARGUMENTS:
 *   - frame size:
 *       INT W, INT H;
 * RETURNS:
 *   (target&) New target.
 */
arvk::target& arvk::target::Create( INT W, INT H )
{
  //INT status;
  std::vector<UINT> DrawBuffer(Attachments);
 
  //glGenFramebuffers(1, &FBOId);
  //glBindFramebuffer(GL_FRAMEBUFFER, FBOId);
 
  //for (INT i = 0; i < Attachments; i++)
  //{ 
  //  if (TargetTex[i]->TexNo != 0)
  //    glDeleteTextures(1, &TargetTex[i]->TexNo);
  //  glGenTextures(1, &TargetTex[i]->TexNo);
  //  glBindTexture(GL_TEXTURE_2D, TargetTex[i]->TexNo);
  //  glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, W, H);
  //  TargetTex[i]->W = W;
  //  TargetTex[i]->H = H;
  //  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, TargetTex[i]->TexNo, 0);
  //  DrawBuffer[i] = GL_COLOR_ATTACHMENT0 + i;
  //}
  //glDrawBuffers(Attachments, DrawBuffer.data());
 
  //if (RndBufId != 0)
  //  glDeleteRenderbuffers(1, &RndBufId);
  //glGenRenderbuffers(1, &RndBufId);
  //glBindRenderbuffer(GL_RENDERBUFFER, RndBufId);
  //glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, W, H);
  //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, RndBufId);
 
  //status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  //if (status != GL_FRAMEBUFFER_COMPLETE)
  //  OutputDebugString("\nFrame buffer error\n");

  Width = W;
  Height = H;
  return *this;
} /* End of 'Create' function */

/* Free target function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::target::Free( VOID )
{ 
  //glBindFramebuffer(GL_FRAMEBUFFER, FBOId);
  //for (INT i = 0; i < Attachments; i++)
  //  glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, 0, 0);
  //glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);
 
  //glDeleteRenderbuffers(1, &RndBufId);
  //RndBufId = 0;
  //glDeleteFramebuffers(1, &FBOId);
  //FBOId = 0;
} /* End of 'Free' function */

/* Target resize function.
 * ARGUMENTS:
 *   - new target size:
 *       INT W, H;
 * RETURNS: 
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
VOID arvk::target::Resize( INT W, INT H )
{
  Free();
  Create(W, H);
  //glViewport(0, 0, W, H);
} /* End of 'Resize' function */

/* Start target frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::target::Start( VOID )
{
  //vec4 col(0);
  //FLT depth = 1;
 
  //glBindFramebuffer(GL_FRAMEBUFFER, FBOId);
  //glViewport(0, 0, Width, Height);
 
  //for (INT i = 0; i < Attachments; i++)
  //  glClearBufferfv(GL_COLOR, i, &col.X);
  //glClearBufferfv(GL_DEPTH, 0, &depth);
} /* End of 'Start' function */

/* End target frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::target::End( VOID )
{
  //vec4 col(0);
  //INT modes[2];
 
  //glFinish();
 
  //glBindFramebuffer(GL_FRAMEBUFFER, 0);
  //glViewport(0, 0, Width, Height);

  //glClearBufferfv(GL_COLOR, 0, &col.X);
  //FLT depth = 1.0;
  //glClearBufferfv(GL_DEPTH, 0, &depth);

  //glGetIntegerv(GL_POLYGON_MODE, modes);
  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  //  
  //Rnd->Draw(Screen, matr::Identity());
 
  //glPolygonMode(GL_FRONT_AND_BACK, modes[0]);
  //glFinish();
} /* End of 'End' function */

/* END OF 'trg.cpp' FILE */
