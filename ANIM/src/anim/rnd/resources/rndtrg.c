/* FILE NAME  : rndtrg.c
 * PROGRAMMER : AA4
 * LAST UPDATE: 14.03.2025
 * PURPOSE    : 3D animation project.
 *              Rendering system target handle module.
 */

#include "anim/rnd/rnd.h"

/*** Target semiglobal data ***/

/* Render target FBO Id */
static UINT AA4_RndTargetFBO;

/* Depth buffer as render buffer Id */
static INT AA4_RndTargetRndBuf;

/* Full screen target draw primitive */
static aa4PRIM AA4_RndTargetScreenPrim;

/* Render target create frame buffer function.
 * ARGUMENTS:
 *   - frame buffer size (in pixels):
 *       INT W, H;
 * RETURNS: None.
 */
static VOID AA4_RndTargetCreate( INT W, INT H )
{
  INT i, status;
  UINT DrawBuffer[AA4_RND_NUM_OF_TARGETS];

  glGenFramebuffers(1, &AA4_RndTargetFBO);
  glBindFramebuffer(GL_FRAMEBUFFER, AA4_RndTargetFBO);

  for (i = 0; i < AA4_RND_NUM_OF_TARGETS; i++)
  {
    INT tn = AA4_RndTargetTexNo[i];

    if (AA4_RndTextures[tn].TexId != 0)
      glDeleteTextures(1, &AA4_RndTextures[tn].TexId);
    glGenTextures(1, &AA4_RndTextures[tn].TexId);
    glBindTexture(GL_TEXTURE_2D, AA4_RndTextures[tn].TexId);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGBA32F, W, H);
    AA4_RndTextures[tn].W = W;
    AA4_RndTextures[tn].H = H;
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, AA4_RndTextures[tn].TexId, 0);
    DrawBuffer[i] = GL_COLOR_ATTACHMENT0 + i;
  }
  glDrawBuffers(AA4_RND_NUM_OF_TARGETS, DrawBuffer);

  if (AA4_RndTargetRndBuf != 0)
    glDeleteRenderbuffers(1, &AA4_RndTargetRndBuf);
  glGenRenderbuffers(1, &AA4_RndTargetRndBuf);
  glBindRenderbuffer(GL_RENDERBUFFER, AA4_RndTargetRndBuf);
  glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, W, H);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, AA4_RndTargetRndBuf);

  status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
  if (status != GL_FRAMEBUFFER_COMPLETE)
    OutputDebugString("\nFrame buffer error\n");
} /* End of 'AA4_RndTargetCreate' function */

/* Render target free frame buffer function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
static VOID AA4_RndTargetFree( VOID )
{
  INT i;

  glBindFramebuffer(GL_FRAMEBUFFER, AA4_RndTargetFBO);
  for (i = 0; i < AA4_RND_NUM_OF_TARGETS; i++)
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, 0, 0);
  glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, 0);

  glDeleteRenderbuffers(1, &AA4_RndTargetRndBuf);
  AA4_RndTargetRndBuf = 0;
  glDeleteFramebuffers(1, &AA4_RndTargetFBO);
  AA4_RndTargetFBO = 0;
} /* End of 'AA4_RndTargetFree' function */

/* Render target initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndTargetInit( VOID )
{
  INT i;
  aa4MATERIAL mtl = AA4_RndMtlGetDef();

  strcpy(mtl.Name, "Target material");
  mtl.ShdNo = AA4_RndShdAdd("target0");
  for (i = 0; i < AA4_RND_NUM_OF_TARGETS; i++)
    mtl.Tex[i] = AA4_RndTargetTexNo[i] = AA4_RndTexAddFmt("Attachment", AA4_RndFrameW, AA4_RndFrameH, GL_RGBA32F);
  AA4_RndPrimCreate(&AA4_RndTargetScreenPrim, AA4_RND_PRIM_POINTS, NULL, 1, NULL, 0);
  AA4_RndTargetScreenPrim.MtlNo = AA4_RndMtlAdd(&mtl);

  AA4_RndTargetCreate(AA4_RndFrameW, AA4_RndFrameH);
} /* End of 'AA4_RndTargetInit' function */

/* Render target deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndTargetClose( VOID )
{
  AA4_RndTargetFree();
  AA4_RndPrimFree(&AA4_RndTargetScreenPrim);
} /* End of 'AA4_RndTargetClose' function */

/* Render target resize function.
 * ARGUMENTS:
 *   - new render target size (in pixels):
 *       INT W, H;
 * RETURNS: None.
 */
VOID AA4_RndTargetResize( INT W, INT H )
{
  AA4_RndTargetFree();
  AA4_RndTargetCreate(W, H);
  glViewport(0, 0, W, H);
} /* End of 'AA4_RndTargetResize' function */

/* Start render target usage function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndTargetStart( VOID )
{
  INT i;
  VEC4 col = {0, 0, 0, 0};
  FLT depth = 1;

  glBindFramebuffer(GL_FRAMEBUFFER, AA4_RndTargetFBO);
  glViewport(0, 0, AA4_RndFrameW, AA4_RndFrameH);
  glBlendFunc(GL_ONE, GL_ZERO); //

  for (i = 0; i < AA4_RND_NUM_OF_TARGETS; i++)
    glClearBufferfv(GL_COLOR, i, &col.X);
  glClearBufferfv(GL_DEPTH, 0, &depth);
} /* End of 'AA4_RndTargetStart' function */

/* Finalize render target output function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndTargetEnd( VOID )
{
  VEC4 col = {0}; /* {0.30, 0.47, 0.8, 0}; */
  INT modes[2];

  glFinish();

  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glViewport(0, 0, AA4_RndFrameW, AA4_RndFrameH);
  glClearBufferfv(GL_COLOR, 0, &col.X);

  glGetIntegerv(GL_POLYGON_MODE, modes);
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glDisable(GL_DEPTH_TEST);

  //AA4_RndPrimDraw(&AA4_RndTargetScreenPrim, MatrIdentity());
  AA4_RndLightRedraw();

  glEnable(GL_DEPTH_TEST);
  glPolygonMode(GL_FRONT_AND_BACK, modes[0]);
  glFinish();
} /* End of 'AA4_RndTargetEnd' function */

/* END OF 'rndtrg.c' FILE */
