/* FILE NAME: rndbase.c
 * PROGRAMMER: AA4
 * LAST UPDATE: 14.03.2025
 * PURPOSE: 3D animation project.
 *          Render module.
 */

#include "rnd.h"
#include "anim/anim.h"
#include <time.h>
#pragma comment(lib, "opengl32")

/* Start of render function.
 * ARGUMENTS:
 *       None.
 * RETURNS:
 *   None.
 */
VOID AA4_RndStart( VOID )
{
  VEC4 ClearColor = {0.70, 0.53, 0.20, 1}; /* super pooper color: {0.70, 0.53, 0.20, 1} corporative color: {0.30, 0.47, 0.8, 1} */
  FLT DepthClearValue = 1;
  INT t = clock();
  static INT OldTime = 0;

  /* Update shader */
  if (    t - OldTime > 3 * CLOCKS_PER_SEC)
  {
    AA4_RndShdUpdate();
    OldTime = t;
  }

  /* Clear frame */
/*  glClearBufferfv(GL_COLOR, 0, &ClearColor.X);
  glClearBufferfv(GL_DEPTH, 0, &DepthClearValue);
*/
  /* Update UBO Sync */
  AA4_RndUBOSyncUpdate();

  AA4_RndTargetStart();

} /* End of 'AA4_RndStart' function */

/* End of render function.
 * ARGUMENTS:
 *       None.
 * RETURNS:
 *   None.
 */
VOID AA4_RndEnd( VOID )
{
  /* glFinish(); */
  AA4_RndTargetEnd();
} /* End of 'AA4_RndEnd' function */

/* Set projection function.
 * ARGUMENTS:
 *       None.
 * RETURNS:
 *   None.
 */
VOID AA4_RndProjSet( VOID )
{
  DBL rx, ry;

  rx = ry = AA4_RndProjSize;

  /* Correct aspect ratio */
  if (AA4_RndFrameW >= AA4_RndFrameH)
    rx *= (DBL)AA4_RndFrameW / AA4_RndFrameH;
  else
    ry *= (DBL)AA4_RndFrameH / AA4_RndFrameW;

  AA4_RndMatrProj =
    MatrFrustum(-rx / 2, rx / 2, -ry / 2, ry / 2,
      AA4_RndProjDist, AA4_RndProjFarClip);
  AA4_RndMatrVP = MatrMulMatr(AA4_RndMatrView, AA4_RndMatrProj);

  /* Update UBO Cam */
  AA4_RndUBOCamUpdate();
} /* End of 'AA4_RndProjSet' function */

/* Set camera function.
 * ARGUMENTS:
 *   - View arguments:
 *       VEC Loc, VEC At, VEC Up;
 * RETURNS:
 *   None.
 */
VOID AA4_RndCamSet( VEC Loc, VEC At, VEC Up )
{
  AA4_RndMatrView = MatrView(Loc, At, Up);
  AA4_RndMatrVP = MatrMulMatr(AA4_RndMatrView, AA4_RndMatrProj);
  AA4_RndCamRight = VecSet(AA4_RndMatrView.A[0][0], AA4_RndMatrView.A[1][0], AA4_RndMatrView.A[2][0]);
  AA4_RndCamUp = VecSet(AA4_RndMatrView.A[0][1], AA4_RndMatrView.A[1][1], AA4_RndMatrView.A[2][1]);
  AA4_RndCamDir = VecSet(AA4_RndMatrView.A[0][2], AA4_RndMatrView.A[1][2], AA4_RndMatrView.A[2][2]);
  AA4_RndCamLoc = Loc;
  AA4_RndCamAt = At;
  /* Update UBO Cam */
  AA4_RndUBOCamUpdate();
} /* End of 'AA4_RndCamSet' function */

/* Resize function.
 * ARGUMENTS:
 *   - Window size:
 *       INT W, INT H;
 * RETURNS:
 *   None.
 */
VOID AA4_RndResize( INT W, INT H )
{
  glViewport(0, 0, W, H);

  /* Setup projection */
  AA4_RndFrameW = W;
  AA4_RndFrameH = H;
  AA4_Anim.W = W;
  AA4_Anim.H = H;
  /* Recalculate projection */
  AA4_RndProjSet();
  AA4_RndTargetResize(W, H);
} /* End of 'AA4_RndResize' function */

/* Copy frame function.
 * ARGUMENTS:
 *   - Handle:
 *       HDC hDC;
 * RETURNS:
 *   None.
 */
VOID AA4_RndCopyFrame( VOID )
{
  SwapBuffers(AA4_hRndDC);
} /* End of 'AA4_RndCopyFrame' function */

/* Init render function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
VOID AA4_RndInit( HWND hWnd )
{
  INT i, nums;
  PIXELFORMATDESCRIPTOR pfd = {0};
  HGLRC hRC;

  INT PixelAttribs[] =
  {
    WGL_DRAW_TO_WINDOW_ARB, TRUE,
    WGL_SUPPORT_OPENGL_ARB, TRUE,
    WGL_DOUBLE_BUFFER_ARB, TRUE,
    WGL_PIXEL_TYPE_ARB, WGL_TYPE_RGBA_ARB,
    WGL_ACCELERATION_ARB, WGL_FULL_ACCELERATION_ARB,
    WGL_COLOR_BITS_ARB, 32,
    WGL_DEPTH_BITS_ARB, 32,
    0
  };
  INT ContextAttribs[] =
  {
    WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
    WGL_CONTEXT_MINOR_VERSION_ARB, 6,
    WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
    0
  };

  AA4_hRndWnd = hWnd;

  /* Prepare frame compatible device contesxt */
  AA4_hRndDC = GetDC(hWnd);
 
  /* OpenGL init: pixel format setup */
  pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
  pfd.nVersion = 1;
  pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL;
  pfd.cColorBits = 32;
  pfd.cDepthBits = 32;
  i = ChoosePixelFormat(AA4_hRndDC, &pfd);

  DescribePixelFormat(AA4_hRndDC, i, sizeof(pfd), &pfd);
  SetPixelFormat(AA4_hRndDC, i, &pfd);
 
  /* OpenGL init: rendering context setup */
  AA4_hRndGLRC = wglCreateContext(AA4_hRndDC);
  wglMakeCurrent(AA4_hRndDC, AA4_hRndGLRC);

  if (glewInit() != GLEW_OK)
    exit(30);

  #ifndef NBEBUG
  OutputDebugString(glGetString(GL_VERSION));
  OutputDebugString("\n");
  OutputDebugString(glGetString(GL_VENDOR));
  OutputDebugString("\n");
  OutputDebugString(glGetString(GL_RENDERER));
  OutputDebugString("\n");
  #endif /* NBEBUG */

  #ifndef NBEBUG
  glEnable(GL_DEBUG_OUTPUT);
  glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
  glDebugMessageCallback(glDebugOutput, NULL);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, NULL, GL_TRUE);
  #endif /* NBEBUG */

  /* Enable a new OpenGL profile support */
  wglChoosePixelFormatARB(AA4_hRndDC, PixelAttribs, NULL, 1, &i, &nums);
  hRC = wglCreateContextAttribsARB(AA4_hRndDC, NULL, ContextAttribs);
 
  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(AA4_hRndGLRC);
 
  AA4_hRndGLRC = hRC;
  wglMakeCurrent(AA4_hRndDC, AA4_hRndGLRC);

  wglSwapIntervalEXT(1);

  /* Render parameters setup */
  AA4_RndProjSize = 0.1;
  AA4_RndProjDist = AA4_RndProjSize;
  AA4_RndProjFarClip = 300;
  AA4_RndFrameW = 47;
  AA4_RndFrameH = 47;
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_PRIMITIVE_RESTART);
  glPrimitiveRestartIndex(-1);
  glEnable(GL_BLEND);
  /*glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
  /*glShadeModel(GL_FLAT);*/ /* Make flat triangle draw */

  /* Init UBO */
  AA4_RndUBOInit();

  /* Init Resources */
  AA4_RndResInit();

  /* Create UBO */
  AA4_RndShdUBOCameraNo = AA4_RndUBOCreate("Camera UBO", AA4_RND_UBO_BIND_CAMERA, sizeof(aa4RND_UBO_CAMERA), &AA4_UboCam);
  AA4_RndShdUBOSyncNo = AA4_RndUBOCreate("Sync UBO", AA4_RND_UBO_BIND_SYNC, sizeof(aa4RND_UBO_SYNC), &AA4_UboSync);
  AA4_RndShdUBOPrimNo = AA4_RndUBOCreate("Prim UBO", AA4_RND_UBO_BIND_PRIM, sizeof(aa4RND_UBO_PRIM), &AA4_UboPrim);
  AA4_RndCamSet(VecSet1(20), VecSet1(1), VecSet(0, 1, 0));

  AA4_RndUBOApply(AA4_RndShdUBOCameraNo);
  AA4_RndUBOApply(AA4_RndShdUBOSyncNo);
  AA4_RndUBOApply(AA4_RndShdUBOPrimNo);

  AA4_RndMarkerInit();
  AA4_RndTargetInit();
  AA4_RndLightsInit();
} /* End of 'AA4_RndInit' function */

/* Close render function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_RndClose( VOID )
{
  AA4_RndLightsClose();
  AA4_RndTargetClose();
  AA4_RndMarkerClose();
  AA4_RndUBOClose();
  AA4_RndResClose();

  wglMakeCurrent(NULL, NULL);
  wglDeleteContext(AA4_hRndGLRC);
  ReleaseDC(AA4_hRndWnd, AA4_hRndDC);
} /* End of 'AA4_RndClose' function */

/* END OF 'rndbase.c' FILE */
