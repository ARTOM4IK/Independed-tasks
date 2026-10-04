/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : win.cpp
 * PURPOSE     : Ray Tracing project.
 *               Window definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 24.07.2025.
 * NOTE        : Module namespace 'arrt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "arrt.h"

#define WindowClassName "Riy Tricing"

using namespace arrt;

/* Class constructor.
 * ARGUMENTS:
 *   - windows instance handle:
 *       HINSTANCE hInst;
 */
win::win( HINSTANCE hInst ) : hWnd(nullptr), W(0), H(0), hInstance(hInst), IsFullScreen(FALSE), FullScreenSaveRect({}), MouseWheel(0), IsActive(FALSE)
{
} /* End of 'win' fucntion */

win::~win( VOID )
{
} /* End of '~win' fucntion */

/* Window run function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (win) created window.
 */
win & win::Create( VOID )
{
  WNDCLASS wc;

  if (!GetClassInfo(hInstance, WindowClassName, &wc))
  {
    wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = sizeof(win *);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.hCursor = LoadCursor(nullptr, (CHAR*)IDC_HAND);
    wc.hIcon = LoadIcon(nullptr, (CHAR*)IDI_SHIELD);
    wc.lpszMenuName = nullptr;
    wc.hInstance = hInstance;
    wc.lpfnWndProc = WinFunc;
    wc.lpszClassName = WindowClassName;

    if (!RegisterClass(&wc))
    {
      MessageBox(nullptr, "Error register window class", "ERROR", MB_OK);
      throw std::runtime_error("Error register window class");
    }
  }

  hWnd =
    CreateWindow(WindowClassName,
      "CGSG Smmer Camp Riy Tricing",
      WS_OVERLAPPEDWINDOW | WS_VISIBLE,
      CW_USEDEFAULT, CW_USEDEFAULT,
      CW_USEDEFAULT, CW_USEDEFAULT,
      nullptr, nullptr, hInstance, reinterpret_cast<VOID *>(this));

  ShowWindow(hWnd, SW_SHOWNORMAL);
  return *this;
} /* End of 'Create' function */

/* Window run function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::Run( VOID )
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
        TranslateMessage(&msg);
        DispatchMessage(&msg);
      }
    else
    {
      /* Idle... */
    }
  }
} /* End of 'Run' function */

/* Window message handle function (CALLBACK version).
 *   - window handle:
 *       HWND hWnd;
 *   - message identifier (see WM_***):
 *       UINT Msg;
 *   - message first parameter ('word' param):
 *       WPARAM wParam;
 *   - message second parameter ('long' param):
 *       LPARAM lParam;
 * RETURNS:
 *   (LRESULT) message return code (depended to Msg type).
 */
LRESULT CALLBACK arrt::win::WinFunc( HWND hWnd, UINT Msg,
                               WPARAM wParam, LPARAM lParam )
{
  win *Win;
  HDC hDC;
  PAINTSTRUCT ps;
 
  switch (Msg)
  {
  case WM_GETMINMAXINFO:
    ((MINMAXINFO *)lParam)->ptMaxTrackSize.y =
      GetSystemMetrics(SM_CYMAXTRACK) +
      GetSystemMetrics(SM_CYCAPTION) +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
    ((MINMAXINFO *)lParam)->ptMinTrackSize.y =
      GetSystemMetrics(SM_CYCAPTION) * 8 +
      GetSystemMetrics(SM_CYMENU) +
      GetSystemMetrics(SM_CYBORDER) * 2;
    ((MINMAXINFO *)lParam)->ptMinTrackSize.x += 300;
    return 0;
  case WM_CREATE:
    /* Attach 'this' pointer to window class to window */
    SetWindowLongPtr(hWnd, 0, (UINT_PTR)((CREATESTRUCT *)lParam)->lpCreateParams);
  default:
    Win = reinterpret_cast<win *>(GetWindowLongPtr(hWnd, 0));
    if (Win != nullptr)
      switch (Msg)
      {
      case WM_CREATE:
        Win->hWnd = hWnd;
        return Win->OnCreate((CREATESTRUCT *)lParam) ? 0 : -1;
      case WM_SIZE:
        Win->W = (INT)(SHORT)LOWORD(lParam);
        Win->H = (INT)(SHORT)HIWORD(lParam);
        Win->OnSize(wParam, LOWORD(lParam), HIWORD(lParam));
        return 0;
      case WM_ACTIVATE:
        Win->IsActive = LOWORD(wParam) != WA_INACTIVE;
        Win->OnActivate((UINT)LOWORD(wParam), (HWND)(lParam),
                        (BOOL)HIWORD(wParam));
        return 0;
      case WM_ERASEBKGND:
        return (LRESULT)Win->OnEraseBkgnd((HDC)wParam);
      case WM_PAINT:
        hDC = BeginPaint(hWnd, &ps);
        Win->OnPaint(hDC, &ps);
        EndPaint(hWnd, &ps);
        return 0;
      case WM_DRAWITEM:
        Win->OnDrawItem((INT)wParam, (DRAWITEMSTRUCT *)lParam);
        return 0;
      case WM_TIMER:
        Win->OnTimer((UINT)wParam);
        return 0;
      case WM_MOUSEWHEEL:
        Win->OnMouseWheel((INT)(SHORT)LOWORD(lParam),
                          (INT)(SHORT)HIWORD(lParam),
                          (INT)(SHORT)HIWORD(wParam),
                          (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_LBUTTONDBLCLK:
        Win->OnButtonDown(TRUE, (INT)(SHORT)LOWORD(lParam),
                          (INT)(SHORT)HIWORD(lParam),
                          (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_LBUTTONDOWN:
        Win->OnButtonDown(FALSE, (INT)(SHORT)LOWORD(lParam),
                          (INT)(SHORT)HIWORD(lParam), (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_RBUTTONDOWN:
        return 0;
      case WM_LBUTTONUP:
        Win->OnButtonUp((INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam),
                        (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_MBUTTONDOWN:
        Win->OnLButtonDown(FALSE, (INT)(SHORT)LOWORD(lParam),
                           (INT)(SHORT)HIWORD(lParam),
                           (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_RBUTTONUP:
      case WM_MBUTTONUP:
        Win->OnLButtonUp((INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam), 
                         (UINT)(SHORT)LOWORD(wParam));

        return 0;
      case WM_INITDIALOG: 
        return Win->OnInitDialog((HWND)(wParam), lParam);
      case WM_MOUSEMOVE:
        Win->OnMouseMove((INT)(SHORT)LOWORD(lParam), (INT)(SHORT)HIWORD(lParam),
                         (UINT)(SHORT)LOWORD(wParam));
        return 0;
      case WM_KEYDOWN:
        Win->OnKey((UINT)(wParam), TRUE, (int)(short)LOWORD(lParam), (UINT)HIWORD(lParam));
        return 0;
      case WM_KEYUP:
        Win->OnKey((UINT)(wParam), FALSE, (int)(short)LOWORD(lParam), (UINT)HIWORD(lParam));
        return 0;
      case WM_DROPFILES:
        Win->OnDropFiles((HDROP)wParam);
        return 0;
      case WM_NOTIFY:
        return Win->OnNotify((INT)wParam, (NMHDR *)lParam);
      case WM_COMMAND:
        Win->OnCommand((INT)LOWORD(wParam), (HWND)lParam, (UINT)HIWORD(wParam));
        return 0;
      case WM_MENUSELECT:
        Win->OnMenuSelect((HMENU)lParam,
          (HIWORD(wParam) & MF_POPUP) ? 0L : (INT)LOWORD(wParam),
          (HIWORD(wParam) & MF_POPUP) ? GetSubMenu((HMENU)lParam, LOWORD(wParam)):0L,
          (UINT)(((SHORT)HIWORD(wParam) == -1) ? 0xFFFFFFFF : HIWORD(wParam)));
        return 0;
      case WM_INITMENUPOPUP:
        Win->OnInitMenuPopup((HMENU)wParam, (UINT)
          LOWORD(lParam), (BOOL)HIWORD(lParam));
        return 0;
      case WM_HSCROLL:
        Win->OnHScroll((HWND)lParam, LOWORD(wParam), HIWORD(wParam));
        return 0;
      case WM_VSCROLL:
        Win->OnVScroll((HWND)lParam, LOWORD(wParam), HIWORD(wParam));
        return 0;
      case WM_ENTERSIZEMOVE:
        Win->OnEnterSizeMove();
        return 0;
      case WM_EXITSIZEMOVE:
        Win->OnExitSizeMove();
        return 0;
      case WM_DESTROY:
        Win->OnDestroy();
        PostQuitMessage(30); // ???
      default:
        return Win->OnMessage(Msg, wParam, lParam);
      }
  }
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'WinFunc' function */

/* Flip full screen function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID win::FlipFullScreen( VOID )
{
  if (IsFullScreen)
  {
    SetWindowPos(hWnd, HWND_TOP,
      FullScreenSaveRect.left, FullScreenSaveRect.top,
      FullScreenSaveRect.right - FullScreenSaveRect.left,
      FullScreenSaveRect.bottom - FullScreenSaveRect.top,
      SWP_NOOWNERZORDER);
  }
  else
  {                                                                                 
    HMONITOR hmon;
    MONITORINFOEX moninfo;
    RECT rc;

    GetWindowRect(hWnd, &FullScreenSaveRect);
    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    rc = moninfo.rcMonitor;
    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), TRUE);

    SetWindowPos(hWnd, HWND_TOP,
      rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top,
      SWP_NOOWNERZORDER);
  }
  IsFullScreen = !IsFullScreen;
} /* End of 'FlipFullScreen' function */

/* END OF 'win.cpp' FILE*/
