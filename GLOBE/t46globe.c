/* FILE NAME: t46globe.c
 * PROGRAMMER: AA4
 * DATE: 05.01.2025
 * PURPOSE: draw sphere
*/

#include <windows.h>
//#include <commondf.h>
#include <time.h>
#include "globe.h"

#define WND_CLASS_NAME "CGSG solo"

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
  WNDCLASS wc; /* Window class */
  HWND hWnd;   /* Window descriptor */
  MSG msg;     /* Message */

  wc.style = CS_VREDRAW | CS_HREDRAW;       /* Window style */

  wc.cbClsExtra = 0;                        /* Extra bytes for class */
  wc.cbWndExtra = 0;                        /* Extra bytes for window */
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;  /* Background color */
  wc.hCursor = LoadCursor(NULL, IDC_CROSS); /* Cursor loader */
  wc.hIcon = LoadIcon(NULL, IDI_HAND);      /* Pictogram loader */
  wc.lpszMenuName = NULL;                   /* Resourse menu name */
  wc.hInstance = hInstance;                 /* Application descriptor */
  wc.lpfnWndProc = MyWindowFunc;
  wc.lpszClassName = WND_CLASS_NAME;        /* Class name */

  /* Register class in system */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }

  /* Create window */
  hWnd =
    CreateWindow(WND_CLASS_NAME ,  /* Class name */
    "CGSG solo",                   /* Window title */
    WS_OVERLAPPEDWINDOW,           /* Window style */
    CW_USEDEFAULT, CW_USEDEFAULT,  /* Window position */
    CW_USEDEFAULT, CW_USEDEFAULT,  /* Window size */
    NULL,                          /* Parent window descriptor */
    NULL,                          /* Loaded menu descriptor */
    hInstance,                     /* Application descriptor */
    NULL);                         /* Pointer to extra parametrs */

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

/* Fullscreen function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   Nothing.
 */

VOID FlipFullScreen( HWND hWnd )
{
  static BOOL IsFullScreen = FALSE;  /* Current mode */
  static RECT SaveRC;                /* Saved size */

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    GetWindowRect(hWnd, &SaveRC);

    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top + 201,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    SetWindowPos(hWnd, HWND_TOP,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'FlipFullScreen' function */

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
  HDC hDC;             /* Handle to the DC */
  BYTE Keys[256];      /* Keyboard key varialbe */
  PAINTSTRUCT ps;      /* Paint handle */
  static INT W, H;     /* Point for saving cursor position variable */
  static HDC hMemDC;   /* Paint descriptor */
  static HBITMAP hBm;  /* DC handles */
  static BITMAP bm;    /* Bitmap */
  static INT T;        /* Time variable */
  HBRUSH hBr, hOldBr;  /* Brush handle */
  HPEN hPen, hOldPen;  /* Pen handle */

  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    ReleaseDC(hWnd, hDC);
    SetTimer(hWnd, 30, 1, NULL);
    T = (INT)time(NULL);
    GLB_INIT(4);
    hBm = NULL;
    return 0;
  case WM_SIZE:
    H = HIWORD(lParam);
    W = LOWORD(lParam);
    GLB_RESIZE(W, H);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 30, 0);
    return 0;
  case WM_KEYDOWN:
    GetKeyboardState(Keys);
    if (Keys['F'] & 0x80)
      FlipFullScreen(hWnd);
  case WM_LBUTTONDBLCLK:
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_TIMER:
    Rectangle(hMemDC, 0, 0, W, H);

    hPen = CreatePen(PS_SOLID, 5, RGB(0, 255, 0));
    hOldPen = SelectObject(hMemDC, hPen);
    SelectObject(hMemDC, GetStockObject(DC_PEN));
    SetDCPenColor(hMemDC, RGB(0, 255, 0));

    hBr = CreateSolidBrush(RGB(0, 0, 0));
    hOldBr = SelectObject(hMemDC, hBr);
    SetDCBrushColor(hMemDC, RGB(0, 0, 0));

    Rectangle(hMemDC, 0, 0, W, H);
    GLB_DRAW(hMemDC);

    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0 ,0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_ERASEBKGND:
    return 1;
  case WM_DESTROY:
    if (hBm != NULL)
      DeleteObject(hBm);
    DeleteDC(hMemDC);
    KillTimer(hWnd, 30);
    PostQuitMessage(30);
    return 0;
  }
  /* Call to process in deafult mode */
  return DefWindowProc(hWnd, Msg, wParam, lParam);
} /* End of 'MyWindowFunc' function */

/* END OF 't46globe.c' FILE */