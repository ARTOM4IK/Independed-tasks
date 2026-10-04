/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : anim.cpp
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

/* Render units function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::anim::Render( VOID )
{
  if (IsRenderActive)
    return;
  IsRenderActive = TRUE;
  timer::Response();
  if (IsActive)
  {
    input::mouse::Wheel = win::MouseWheel;
    render::Timer.Response();
    input::Response();
    win::MouseWheel = 0;
  }
  Units.walk([this](unit *Uni)
  {
    Uni->Response(this);
  });
  render::FrameStart();
  Units.walk([this](unit *Uni)
  {
    Uni->Render(this);
  });
  render::FrameEnd();
  IsRenderActive = FALSE;
} /* End of 'Render' function */

/* Render units function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::anim::ReRender( VOID )
{
  Units.walk([this](unit *Uni)
  {
    Uni->Render(this);
  });
} /* End of 'ReRender' function */

/* WM_CREATE window message handle function.
 * ARGUMENTS:
 *   - structure with creation data:
 *       CREATESTRUCT *CS;
 * RETURNS:
 *   (BOOL) TRUE to continue creation window, FALSE to terminate.
 */
BOOL arvk::anim::OnCreate( CREATESTRUCT *CS ) 
{
  SetTimer(win::hWnd, 30, 0, nullptr);
  render::Init();

  return TRUE;
} /* End of 'OnCreate' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::anim::OnDestroy( VOID ) 
{
  KillTimer(win::hWnd, 30);
  render::Close();
  PostQuitMessage(30);
} /* End of 'OnDestroy' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL arvk::anim::OnEraseBkgnd( HDC hDC ) 
{
  return TRUE;
} /* End of 'OnEraseBkgnd' function */

/* WM_PAINT window message handle function.
 * ARGUMENTS:
 *   - window device context:
 *       HDC hDC;
 *   - paint message structure pointer:
 *       PAINTSTRUCT *PS;
 * RETURNS: None.
 */
VOID arvk::anim::OnPaint( HDC hDC, PAINTSTRUCT *Ps ) 
{
  Render();
} /* End of 'OnPaint' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT W, H;
 * RETURNS: None.
 */
VOID arvk::anim::OnSize( UINT State, INT W, INT H ) 
{
  render::Resize(W, H);
} /* End of 'OnSize' function */

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID arvk::anim::OnTimer( INT Id ) 
{
  //render::FrameStart();

  ////glEnd();

  //render::FrameEnd();
  Render();
} /* End of 'OnTimer' function */

/* WM_EXITSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::anim::OnExitSizeMove( VOID ) 
{
  IsActive = TRUE;
} /* End od 'OnExitSizeMove' function */

/* WM_ENTERSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::anim::OnEnterSizeMove( VOID ) 
{
  IsActive = FALSE;
} /* End of 'OnEnterSizeMove' function */

/* Window message universal handle function.
 * Should be returned 'DefWindowProc' call result.
 * ARGUMENTS:
 *   - message type (see WM_***):
 *      UINT Msg;
 *   - message 'word' parameter:
 *      WPARAM wParam;
 *   - message 'long' parameter:
 *      LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */
LRESULT arvk::anim::OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam ) 
{
  return DefWindowProc(win::hWnd, Msg, wParam, lParam);
} /* End of 'win::OnMessage' function */

/* WM_MOUSEWHEEL window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse wheel relative delta value:
 *       INT Z;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID arvk::anim::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys ) 
{
  win::MouseWheel = Z;
} /* End of 'OnMouseWheel' function */

/* WM_*BUTTONDOWN window message handle function.
 * ARGUMENTS:
 *   - double click flag:
 *       BOOL IsDoubleClick;
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID arvk::anim::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys ) 
{
  SetCapture(win::hWnd);
} /* End of 'OnButtonDown' function */

/* WM_*BUTTONUP window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID arvk::anim::OnButtonUp( INT X, INT Y, UINT Keys ) 
{
} /* End of 'OnButtonUp' function */

VOID arvk::anim::Run( VOID ) 
{
  MSG msg;

  while (TRUE)
  {
    /* Check message at window message queue */
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
      if (msg.message == WM_QUIT)
        break;
      else
      {
        /* Displatch message to window */
        //TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    else
    {
      SendMessage(hWnd, WM_TIMER, 30, 0);
      //Render();
    }
  }
} /* End of 'Run' function */

/* END OF 'anim.cpp' FILE */
