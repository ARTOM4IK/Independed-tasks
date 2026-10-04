/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : rt_win.cpp
 * PURPOSE     : Ray Tracing project.
 *               Ray tracing window definition module.
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

/* Class constructor.
 * ARGUMENTS:
 *   - windows instance handle:
 *       HINSTANCE hInst;
 */
arrt::rt_win::rt_win( HINSTANCE hInst ): hBrBack(nullptr)
{
} /* End of 'rt_win' function */

arrt::rt_win::~rt_win( VOID )
{
} /* End of '~rt_win' function */

/* Window run function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (win) created window.
 */
BOOL arrt::rt_win::OnCreate( CREATESTRUCT *CS )
{
  HBITMAP hbm;

  if (hbm = (HBITMAP)LoadImage(NULL, "src/rt/CGSG1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE))
  {
    LOGBRUSH logbr;                                                                       
    logbr.lbStyle = BS_PATTERN;
    logbr.lbColor = DIB_RGB_COLORS;
    logbr.lbHatch = (ULONG_PTR)hbm;
    hBrBack = CreateBrushIndirect(&logbr);
    DeleteObject(hbm);
  }
  else
    hBrBack = nullptr;

  SetTimer(hWnd, 47, 470, nullptr);
  Frm.Resize(200, 200);
  ImgW = ImgZoomW = Frm.W;
  ImgH = ImgZoomH = Frm.H;
  ImgZoom = 1;

  //for (INT y = 0; y < Frm.H; y++)
  //  for (INT x = 0; x < Frm.W; x++)
  //    Frm.PutPixel(x, y, x * x + y * y);
  Cam.Resize(Frm.W, Frm.H);

  Scn.Render(Cam, Frm);
  
  arrt::rt_win::Update();
  return TRUE;
} /* End of 'OnCreate' function */

/* WM_TIMER window message handle function.
 * ARGUMENTS:
 *   - specified the timer identifier.
 *       INT Id;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnTimer( INT Id )
{
  InvalidateRect(hWnd, nullptr, FALSE);
} /* End of 'OnTimer' function */

/* WM_DESTROY window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arrt::rt_win::OnDestroy( VOID )
{
  DeleteObject(hBrBack);
  KillTimer(hWnd, 47);
  PostQuitMessage(30);
} /* End of 'OnDestroy' function */

/* WM_SIZE window message handle function.
 * ARGUMENTS:
 *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
 *       UINT State;
 *   - new width and height of client area:
 *       INT W, H;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnSize( UINT State, INT W, INT H )
{
  if (Frm.W != 0 && Frm.H != 0)
  {
    InvalidateRect(hWnd, nullptr, FALSE);
    arrt::rt_win::Update();
  }
} /* End of 'OnSize' function */

/* WM_ERASEBKGND window message handle function.
 * ARGUMENTS:
 *   - device context of client area:
 *       HDC hDC;
 * RETURNS:
 *   (BOOL) TRUE if background is erased, FALSE otherwise.
 */
BOOL arrt::rt_win::OnEraseBkgnd( HDC hDC )
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
VOID arrt::rt_win::OnPaint( HDC hDC, PAINTSTRUCT *PS )
{
  SelectObject(hDC, GetStockObject(NULL_PEN));
  if (hBrBack != nullptr)
    SelectObject(hDC, hBrBack);
  else
    SelectObject(hDC, GetStockObject(NULL_BRUSH));

  if (Frm.W != 0 && Frm.H != 0)
  {
    if (ImgX > 0)
      Rectangle(hDC, 0, ImgY, ImgX + 1, ImgY + 1 + ImgZoomH);
    if (ImgY > 0)
      Rectangle(hDC, 0, 0, W + 1, ImgY + 1);
    if (W - ImgX - ImgZoomW > 0)
      Rectangle(hDC, ImgX + ImgZoomW, ImgY, W + 1, ImgY + 1 + ImgZoomH);
    if (H - ImgY - ImgZoomH > 0)
      Rectangle(hDC, 0, ImgY + ImgZoomH, W + 1, H + 1);
    Frm.Draw(hDC, ImgX, ImgY, ImgZoomW, ImgZoomH);
  }
  else
    Rectangle(hDC, 0, 0, W + 1, H + 1);
} /* End of 'OnPaint' function */

/* Window message update handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arrt::rt_win::Update( VOID )
{                         
  if (ImgZoom <= W)
    ImgX = (W - ImgZoomW) / 2.0;
  else
  {
    if (ImgX + ImgZoomW < W)
      ImgX = W - ImgZoomW;
    if (ImgX > 0)
      ImgX = 0;
  }
  if (ImgZoomH <= H)
    ImgY = (H - ImgZoomH) / 2.0;
  else
  {
    if (ImgY + ImgZoomH < H)
      ImgY = H - ImgZoomH;
    if (ImgY > 0)
      ImgY = 0;
  }

  auto handle_scrll =
    [this](INT ScrollType, INT ImgPos, INT ImgSize, INT WinSize)
    {
      SCROLLINFO ScrollInfo {.cbSize = sizeof(SCROLLINFO), .fMask = SIF_PAGE | SIF_POS | SIF_RANGE};

      if (ImgSize <= WinSize)
      {
        ScrollInfo.nMin = ScrollInfo.nMax = 0;
        SetScrollInfo(hWnd, ScrollType, &ScrollInfo, TRUE);
      }
      else
      {
        ScrollInfo.nMin = 0;
        ScrollInfo.nMax = ImgSize;
        ScrollInfo.nPage = WinSize;
        ScrollInfo.nPos = -ImgPos;
        SetScrollInfo(hWnd, ScrollType, &ScrollInfo, TRUE);
      }
    };
  handle_scrll(SB_VERT, ImgY, ImgZoomH, H);
  handle_scrll(SB_HORZ, ImgX, ImgZoomW, W);
} /* End of 'Update' function */

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
VOID arrt::rt_win::OnMouseWheel( INT X, INT Y, INT Z, UINT Keys )
{
  if (Z > 0 && ImgZoom < 13 && (ImgZoom < 0 || (UINT64)ImgW * ImgH * (ImgZoom + 1) * (ImgZoom + 1) < 1000000000ULL))
    ImgZoom++, ImgZoom = (ImgZoom == 0 || ImgZoom == -1) ? 1 : ImgZoom;
  else if (Z < 0 && ImgZoom > -12)
    ImgZoom--, ImgZoom = (ImgZoom == 0 || ImgZoom == -1) ? -2 : ImgZoom;

  if (ImgZoom > 0)
    ImgZoomW = ImgW * ImgZoom, ImgZoomH = ImgH * ImgZoom;
  else
    ImgZoomW = ImgW / -ImgZoom, ImgZoomH = ImgH / -ImgZoom;

  arrt::rt_win::Update();
  InvalidateRect(hWnd, nullptr, FALSE);
} /* End of '' function */

/* WM_KEYDOWN/WM_KEYUP window message handle function.
 * ARGUMENTS:
 *   - virtual key number (see VK_***, 'A', ..., '0', ...):
 *       UINT Key;
 *   - press flag:
 *       BOOL IsPress;
 *   - autorepeat counter:
 *       INT RepeatCount;
 *   - shift/control etc key states bits (see MK_***):
 *       UINT ShiftKeysFlags;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnKey( UINT Key, BOOL IsPress, INT RepeatCount, UINT ShiftKeysFlags )
{
  if (Key == VK_ESCAPE)
    if (Scn.IsRenderActive)
      Scn.IsToBeStop = TRUE;
    else
      DestroyWindow(hWnd);
  else if (Key == 'C')
  {
    Frm.Fill(0x00303108);
  }
  else if (Key == 'R')
  {
    if (Scn.IsRenderActive)
      return;
 
    Scn.IsRenderActive = TRUE;
    Scn.IsToBeStop = FALSE;
    Scn.IsReadyToFinish = FALSE;
 
    std::cout << std::endl << "Start render scene at ";
    std::time_t t_c =
      std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::cout << std::put_time(std::localtime(&t_c), "%H:%M:%S %d.%m.%Y\n");
 
    std::thread Th;
    Th = std::thread(
      [this]( VOID )
      {
        auto start_time = std::chrono::high_resolution_clock::now();
 
        Scn.Render(Cam, Frm);
 
        auto end_time = std::chrono::high_resolution_clock::now();
        auto duration = end_time - start_time;
        auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
        duration -= hours;
        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
        duration -= minutes;
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        duration -= seconds;
        auto milliseconds =
          std::chrono::duration_cast<std::chrono::milliseconds>(duration);
        duration -= milliseconds;
        std::cout << std::format("Frame render time in [{}:{}:{}.{}]\n",
          hours.count(), minutes.count(), seconds.count(), milliseconds.count());
 
        std::cout << "End render scene at ";
        std::time_t t_c =
          std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::cout << std::put_time(std::localtime(&t_c), "%H:%M:%S %d.%m.%Y\n");
 
        InvalidateRect(hWnd, NULL, FALSE);
        UpdateWindow(hWnd);
 
        Frm.AutoSaveTGA("CGSG forever!!!",
          {hours.count(), minutes.count(), seconds.count()});
 
        Scn.IsToBeStop = FALSE;
        Scn.IsReadyToFinish = TRUE;
        Scn.IsRenderActive = FALSE;
      });
    Th.detach();
  }
} /* End of 'OnKey' function */

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
VOID arrt::rt_win::OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys )
{
  if (IsDoubleClick)
    FlipFullScreen();
  MouseX = X;
  MouseY = Y;
  if (Keys & MK_RBUTTON)
  {
    X -= ImgX;
    Y -= ImgY;
    if (ImgZoom > 0)
    {
      X /= ImgZoom;
      Y /= ImgZoom;
    }
    else
    {
      X *= ImgZoom;
      Y *= ImgZoom;
    }
  }
} /* End of 'OnButtonDown' function */

/* WM_*BUTTONUP window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnButtonUp( INT X, INT Y, UINT Keys )
{
} /* End of 'OnButtonUp' function */

/* WM_MOUSEMOVE message handle function.
 * ARGUMENTS:
 *   - mouse cursor X and Y coordinates:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnMouseMove( INT X, INT Y, UINT Keys )
{
} /* End of 'OnMouseMove' function */

/* WM_HSCROLL message handle function.
 * ARGUMENTS:
 *   - handle of scroll window or nullptr for window scroll bars:
 *       HWND hWndCtl;
 *   - scrool bar request code (see SB_***):
 *       UINT Code;
 *   - scroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
 *       INT Pos;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnHScroll( HWND hWndCtl, UINT Code, INT Pos )
{
  switch (Code)
  {
    case SB_LINEDOWN:
      ImgX--;
      break;
    case SB_LINEUP:
      ImgX++;
      break;
    case SB_PAGEDOWN:
      ImgX -= W;
      break;
    case SB_PAGEUP:
      ImgX += W;
      break;
    case SB_THUMBTRACK:
      ImgX -= Pos;
      break;
  }
  arrt::rt_win::Update();
  InvalidateRect(hWnd, nullptr, FALSE);
} /* End of 'OnHScroll' function */

/* WM_VSCROLL message handle function.
 * ARGUMENTS:
 *   - handle of scroll window or nullptr for window scroll bars:
 *       HWND hWndCtl;
 *   - scrool bar request code (see SB_***):
 *       UINT Code;
 *   - scroll position for 'Code' is SB_THUMBPOSITION or SB_THUMBTRACK:
 *       INT Pos;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnVScroll( HWND hWndCtl, UINT Code, INT Pos )
{
  switch (Code)
  {
    case SB_LINEDOWN:
      ImgY--;
      break;
    case SB_LINEUP:
      ImgY++;
      break;
    case SB_PAGEDOWN:
      ImgY -= H;
      break;
    case SB_PAGEUP:
      ImgY += H;
      break;
    case SB_THUMBTRACK:
      ImgY += Pos;
      break;
  }
  arrt::rt_win::Update();
  InvalidateRect(hWnd, nullptr, FALSE);
} /* End of 'OnVScroll' function */

/* Window run function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arrt::rt_win::Run( VOID )
{
  MSG msg;

  while (GetMessage(&msg, nullptr, 0, 0))
  {
      TranslateMessage(&msg);
      DispatchMessage(&msg);
  }
} /* End of 'Run' function */

/* WM_INITDIALOG window message handle function.
 * ARGUMENTS:
 *   - control handle to be set focus:
 *       HWND hWndFocus;
 *   - additional dialog creation parameter:
 *       LPARAM lParam;
 * RETURNS:
 *   (BOOL) TRUE for use hWndFocus, FALSE for user focus window set.
 */
BOOL arrt::rt_win::OnInitDialog( HWND hWndFocus, LPARAM lParam )
{
  return TRUE;
} /* End of 'OnInitDialog' function */

/* WM_DRAWITEM window message handle function.
 * ARGUMENTS:
 *   - control identifier (for menu - 0):
 *       INT Id;
 *   - draw item information structure pointer:
 *       DRAWITEMSTRUCT *DrawItem;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnDrawItem( INT Id, DRAWITEMSTRUCT *DrawItem ) 
{
} /* End of 'OnDrawItem' function */

/* WM_ENTERSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arrt::rt_win::OnEnterSizeMove( VOID ) 
{
} /* End of 'OnEnterSizeMove' function */

/* WM_NOTIFY window message handle function.
 * ARGUMENTS:
 *   - control identifier:
 *       INT Id;
 *   - notification header depended to control type:
 *       NMHDR *NoteHead;
 * RETURNS:
 *   (LRESULT) return value depended to notification.
 */
LRESULT arrt::rt_win::OnNotify( INT Id, NMHDR *NoteHead )
{
  return 0;
} /* End of 'OnNotify' function */

/* WM_ACTIVATE window message handle function.
 * ARGUMENTS:
 *   - reason (WA_CLICKACTIVE, WA_ACTIVE or WA_INACTIVE):
 *       UINT Reason;
 *   - handle of active window:
 *       HWND hWndActDeact;
 *   - minimized flag:
 *       BOOL IsMinimized;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized )
{
} /* End of 'OnActivate' function */

/* WM_COMMAND window message handle function.
 * ARGUMENTS:
 *   - item (menu or accelerator) or control window identifier:
 *       INT Id;
 *   - control window handle:
 *       HWND hWndCtl;
 *   - notification: 0 - menu, 1 - accelerator, otherwise -
 *     depended to control (like BM_CLICKED):
 *       UINT CodeNotify;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnCommand( INT Id, HWND hWndCtl, UINT CodeNotify ) 
{
} /* End of 'OnCommand' function */

/* WM_DROPFILES window message handle function.
 * ARGUMENTS:
 *   - handle to an internal structure describing the dropped files:
 *       HDROP hDrop;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnDropFiles( HDROP hDrop )
{
} /* End of 'OnDropFiles' function */

/* WM_INITMENUPOPUP window message handle function.
 * ARGUMENTS:
 *   - handle of popup menu:
 *       HMENU hMenu;
 *   - submenu item position:
 *       UINT Item;
 *   - window system menu flag:
 *       BOOL IsSystemMenu;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnInitMenuPopup( HMENU hMenu, UINT Item, BOOL IsSystemMenu )
{
} /* End of 'OnInitMenuPopup' function */

/* WM_EXITSIZEMOVE window message handle function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arrt::rt_win::OnExitSizeMove( VOID )
{
} /* End of 'OnExitSizeMove' function */

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
VOID arrt::rt_win::OnLButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys )
{
} /* End of 'OnLButtonDown' function */

/* WM_*BUTTONUP window message handle function.
 * ARGUMENTS:
 *   - mouse window position:
 *       INT X, Y;
 *   - mouse keys bits (see MK_*** bits constants):
 *       UINT Keys;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnLButtonUp( INT X, INT Y, UINT Keys )
{
} /* End of 'OnLButtonUp' function */

/* WM_MENUSELECT window message handle function.
 * ARGUMENTS:
 *   - handle of menu:
 *       HMENU hMenu;
 *   - submenu item ID or submenu index
 *       INT Item;
 *   - handle of popup menu if selected popup submenu:
 *       HMENU hMenuPopup;
 *   - menu item flags (see MF_***):
 *       UINT Flags;
 * RETURNS: None.
 */
VOID arrt::rt_win::OnMenuSelect( HMENU hMenu, INT Item, HMENU hMenuPopup, UINT Flags ) 
{
} /* End of 'OnMenuSelect' function */

 /* END OF 'rt_win.cpp' FILE */
