/* FILE NAME: main.c
 * PROGRAMMER: AA4
 * LAST UPDATE: 20.01.2025
 * PURPOSE: 3D animation project.
*/

#include "units/units.h"

#define WND_CLASS_NAME "AA4 T48ANIM"

/* Link for function for processing */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

/* Main startup program function.
 * ARGUMENTS:
 *   - application instance handle:
 *       HINSTANCE hInstance;
 *   - previouse application instance handle
 *     (not used, alway NULL):
 *       HINSTANCE hPrevInstance;
 *   - command line string:
 *       CHAR *CmdLine;
 *   - command line window show parameter (see SW_***):
 *       INT CmdShow;
 * RETURNS:
 *   (INT) system error level value.
 */

/* Main program function */
INT WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, CHAR *CmdLine, INT ShowCmd )
{
  WNDCLASS wc;
  HWND hWnd;
  MSG msg;

  wc.style = CS_VREDRAW | CS_HREDRAW;

  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
  wc.hCursor = LoadCursor(NULL, IDC_CROSS);
  wc.hIcon = LoadIcon(NULL, IDI_HAND);
  wc.lpszMenuName = NULL;
  wc.hInstance = hInstance;
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;

  /* Register class in system */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }

  /* Create window */
  hWnd =
    CreateWindow(WND_CLASS_NAME ,
    "AA4 T48ANIM",
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, CW_USEDEFAULT,
    CW_USEDEFAULT, CW_USEDEFAULT,
    NULL,
    NULL,
    hInstance,
    NULL);

  /* Init Animtaion */
  AA4_AnimUnitAdd(AA4_AnimSkyCreate());
  AA4_AnimUnitAdd(AA4_UnitCamCreate());
 /* AA4_AnimUnitAdd(AA4_UnitCowCreate());
 
 AA4_AnimUnitAdd(AA4_AnimGridCreate()); */
  AA4_AnimUnitAdd(AA4_UnitPrimsCreate());
  //AA4_AnimUnitAdd(AA4_AnimTessCreate());
  /* Show and redraw window */
  ShowWindow(hWnd, SW_SHOWNORMAL);
  UpdateWindow(hWnd);

  /* Loop of processing messages */
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return msg.wParam;
} /* End of 'WinMain' function */

/* Window handle function.
 * ARGUMENTS:
 *   - window handle:
 *       HWND hWnd;
 *   - message type (see WM_***):
 *       UINT Msg;
 *   - message 'word' parameter:
 *       WPARAM wParam;
 *   - message 'long' parameter:
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message depende return value.
 */

/* Function to process window's message */
LRESULT CALLBACK MyWindowFunc( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam )
{
  HDC hDC;
  PAINTSTRUCT ps;
  static DWORD *Bits;
  static HDC hMemDC;
  static INT W, H;
  static INT T;
  static aa4PRIM Pr;

  switch (Msg)
  {
  case WM_CREATE:
    SetTimer(hWnd, 30, 1, NULL);
    AA4_AnimInit(hWnd);
    AA4_TimerInit();

    SetTimer(hWnd, 30, 1, NULL);
    AA4_TimerInit();
    return 0;
  case WM_SIZE:
    AA4_AnimResize(W = LOWORD(lParam), H = HIWORD(lParam));
    SendMessage(hWnd, WM_TIMER, 30, 0);
    return 0;
  case WM_TIMER:
    AA4_AnimResponse();
    AA4_AnimRender();
    /* Copy frame */
    hDC = GetDC(hWnd);
    AA4_RndCopyFrame();
    ReleaseDC(hWnd, hDC);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    AA4_RndCopyFrame();
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_MOUSEWHEEL:
    AA4_MouseWheel += (SHORT)HIWORD(wParam);
    return 0;
  case WM_DESTROY:
    KillTimer(hWnd, 30);
    AA4_AnimClose();
    PostQuitMessage(30);
    return 0;
  }
  /* Call to process in deafult mode */
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' function */

/* END OF 'main.c' FILE */
