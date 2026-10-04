/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : main.cpp
 * PURPOSE     : Binary Search Tree project.
 *               Main entry point module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 19.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include <windows.h>
#include <cmath>
#include "rbt.h"
#define WND_CLASS_NAME "CGSG Summer Camp"
 
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
  WNDCLASS wc;  // Window class 
  HWND hWnd;    // Window descriptor 
  MSG msg;      // Message 

  wc.style = CS_VREDRAW | CS_HREDRAW;        // Window style 

  wc.cbClsExtra = 0;                         // Extra bytes for class 
  wc.cbWndExtra = 0;                         // Extra bytes for window 
  wc.hbrBackground = (HBRUSH)COLOR_WINDOW;   // Background color 
  wc.hCursor = LoadCursor(NULL, IDC_CROSS);  // Cursor loader 
  wc.hIcon = LoadIcon(NULL, IDI_HAND);       // Pictogram loader 
  wc.lpszMenuName = NULL;                    // Resourse menu name 
  wc.hInstance = hInstance;                  // Application descriptor 
  wc.lpfnWndProc = MyWindowFunc;             
  wc.lpszClassName = WND_CLASS_NAME;         // Class name 
                                             
  /* Register class in system */
  if (!RegisterClass(&wc))
  {
    MessageBox(NULL, "Error register window class", "ERROR", MB_OK);
    return 0;
  }

  /* Create window */
  hWnd =
    CreateWindow(WND_CLASS_NAME ,  // Class name
    "CGSG Summer Camp",            // Window title 
    WS_OVERLAPPEDWINDOW,           // Window style 
    CW_USEDEFAULT, CW_USEDEFAULT,  // Window position 
    CW_USEDEFAULT, CW_USEDEFAULT,  // Window size 
    NULL,                          // Parent window descriptor 
    NULL,                          // Loaded menu descriptor 
    hInstance,                     // Application descriptor 
    NULL);                         // Pointer to extra parametrs

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
  HDC hDC;            // Handle to the DC 
  PAINTSTRUCT ps;     // Paint handle 
  static INT W, H;    // Paint descriptor 
  char ch;            // Char to get from keyboard
  static HDC hMemDC;  // DC handles 
  static INT T;       // Time variable
  static rbtree Tree; // Tree variable
  HBRUSH hBr;         // Brush handle 
  HPEN hPen;          // Pen handle 
  static HBITMAP hBm; // DC handles 
  DBL rx = 0, ry = 0;
  static HFONT hFnt;   // Font
  static INT faket = 0, dx = 0, dy = 0, OldDx = 0, OldDy = 0, StartX = 0, StartY = 0, cnt = 1;
  static BOOL is_pressed = FALSE;
  POINT pt;
  static std::string str = "";
  switch (Msg)
  {
  case WM_CREATE:
    hDC = GetDC(hWnd);
    hMemDC = CreateCompatibleDC(hDC);
    SetTimer(hWnd, 30, 1, NULL);
    ReleaseDC(hWnd, hDC);
    T = (INT)time(NULL);
    hFnt = CreateFont(15, 5, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, RUSSIAN_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, PROOF_QUALITY, VARIABLE_PITCH || FF_ROMAN, "Times");
    Tree.Insert1(1, "1");
    Tree.Insert1(2, "2");
    Tree.Insert1(3, "3");
    Tree.Insert1(4, "4");
    Tree.Insert1(5, "5");
    Tree.Insert1(6, "6");
    Tree.Insert1(7, "7");
    Tree.Insert1(8, "8");

    return 0;
  case WM_SIZE:
    H = HIWORD(lParam);
    W = LOWORD(lParam);
    if (hBm != NULL)
      DeleteObject(hBm);
    hDC = GetDC(hWnd);
    hBm = CreateCompatibleBitmap(hDC, W, H);
    ReleaseDC(hWnd, hDC);
    SelectObject(hMemDC, hBm);
    SendMessage(hWnd, WM_TIMER, 30, 0);
    return 0;
  case WM_TIMER:
    faket++;
    hPen = CreatePen(PS_SOLID, 5, RGB(0, 0, 0));
    SelectObject(hMemDC, GetStockObject(DC_PEN));
    SetDCPenColor(hMemDC, RGB(0, 0, 0));

    hBr = CreateSolidBrush(RGB(0, 0, 0));
    SelectObject(hMemDC, GetStockObject(DC_BRUSH));
    SetDCBrushColor(hMemDC, RGB(150, 150, 150));

    Rectangle(hMemDC, 0, 0, W, H);

    Tree.Recalc(Tree.Root, &rx);
    Tree.Draw(hMemDC, hFnt, Tree.Root, W / 2 + OldDx, 0 + OldDy);
    InvalidateRect(hWnd, NULL, FALSE);
    return 0;
  case WM_PAINT:
    hDC = BeginPaint(hWnd, &ps);
    BitBlt(hDC, 0 ,0, W, H, hMemDC, 0, 0, SRCCOPY);
    EndPaint(hWnd, &ps);
    return 0;
  case WM_LBUTTONDOWN:
    is_pressed = TRUE;
    GetCursorPos(&pt);
    StartX = pt.x;
    StartY = pt.y;
    return 0;
  case WM_LBUTTONUP:
    is_pressed = FALSE;
    return 0;
  case WM_MOUSEMOVE:
    if (is_pressed)
    {
      GetCursorPos(&pt);
      dx = pt.x - StartX;
      dy = pt.y - StartY;
      OldDx += dx;
      OldDy += dy;
    }
    return 0;
  case WM_CHAR:
    ch = wParam;
    if (ch == ' ')
    {
      str.push_back('0' + cnt);
      Tree.Insert1(cnt, str);
      str.pop_back();
      cnt++;
    }
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

/* END OF 'main.cpp' FILE */