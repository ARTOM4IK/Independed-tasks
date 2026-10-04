/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : win.h
 * PURPOSE     : Ray Tracing project.
 *               Space mathematics test module.
 *               Matrices test.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 24.07.2025.
 * NOTE        : Module namespace 'tst'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __win_h_
#define __win_h_

#include "def.h"

/* Animation namespace */
namespace arvk
{
  /* Window class */
  class win
  {
  protected:
    HWND hWnd;           // window handle
    INT W, H;            // window size
    HINSTANCE hInstance; // application handle
  private:
    inline static std::recursive_mutex window_mutex;
    static LRESULT CALLBACK WinFunc( HWND hWnd, UINT Msg,
                                     WPARAM wParam, LPARAM lParam );
 
    BOOL IsFullScreen;
    RECT FullScreenSaveRect;
  public:
    INT MouseWheel = 0;
    BOOL IsActive;
 
    /* Class constructor.
     * ARGUMENTS:
     *   - windows instance handle:
     *       HINSTANCE hInst;
     */
    win( HINSTANCE hInst = GetModuleHandle(nullptr) );

    /* Class destructor */ 
    virtual ~win( VOID );
 
    /* Create window function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (win &) window.
     */
    win & Create( VOID );

    /* Run window function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Run( VOID );

    /* Flip full screen function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FlipFullScreen( VOID );

    /* Get window handle function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (HWND) window handle.
     */
    HWND GetHWnd( VOID ) const
    {
      return hWnd;
    }
  private:
    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    virtual BOOL OnCreate( CREATESTRUCT *CS );
    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnDestroy( VOID );
    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    virtual BOOL OnEraseBkgnd( HDC hDC );                                                                               
    /* WM_PAINT window message handle function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     *   - paint message structure pointer:
     *       PAINTSTRUCT *PS;
     * RETURNS: None.
     */
    virtual VOID OnPaint( HDC hDC, PAINTSTRUCT *Ps );
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
    virtual VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized );
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
    virtual VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys );
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
    virtual VOID OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys );
    /* WM_*BUTTONUP window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    virtual VOID OnButtonUp( INT X, INT Y, UINT Keys );
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
    virtual VOID OnLButtonDown( BOOL Flag, INT X, INT Y, UINT Keys );
    /* WM_*BUTTONUP window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    virtual VOID OnLButtonUp( INT X, INT Y, UINT Keys );
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
    virtual VOID OnKey( UINT Key, BOOL IsPress, INT RepeatCount, UINT ShiftKeysFlags );
    /* WM_INITDIALOG window message handle function.
     * ARGUMENTS:
     *   - control handle to be set focus:
     *       HWND hWndFocus;
     *   - additional dialog creation parameter:
     *       LPARAM lParam;
     * RETURNS:
     *   (BOOL) TRUE for use hWndFocus, FALSE for user focus window set.
     */
    virtual BOOL OnInitDialog( HWND hWndFocus, LPARAM lParam );
    /* WM_MOUSEMOVE message handle function.
     * ARGUMENTS:
     *   - mouse cursor X and Y coordinates:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    virtual VOID OnMouseMove( INT X, INT Y, UINT Keys );
    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    virtual VOID OnSize( UINT State, INT W, INT H );
    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    virtual VOID OnTimer( INT Id );
    /* WM_DROPFILES window message handle function.
     * ARGUMENTS:
     *   - handle to an internal structure describing the dropped files:
     *       HDROP hDrop;
     * RETURNS: None.
     */
    virtual VOID OnDropFiles( HDROP hDrop );
    /* WM_DRAWITEM window message handle function.
     * ARGUMENTS:
     *   - control identifier (for menu - 0):
     *       INT Id;
     *   - draw item information structure pointer:
     *       DRAWITEMSTRUCT *DrawItem;
     * RETURNS: None.
     */
    virtual VOID OnDrawItem( INT Id, DRAWITEMSTRUCT *DrawItem );
    /* WM_NOTIFY window message handle function.
     * ARGUMENTS:
     *   - control identifier:
     *       INT Id;
     *   - notification header depended to control type:
     *       NMHDR *NoteHead;
     * RETURNS:
     *   (LRESULT) return value depended to notification.
     */
    virtual LRESULT OnNotify( INT Id, NMHDR *NoteHead );
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
    virtual VOID OnCommand( INT Id, HWND hWndCtl, UINT CodeNotify );
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
    virtual VOID OnMenuSelect( HMENU hMenu, INT Item, HMENU hMenuPopup, UINT Flags );
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
    virtual VOID OnInitMenuPopup( HMENU hMenu, UINT Item, BOOL IsSystemMenu );
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
    virtual VOID OnHScroll( HWND hWndCtl, UINT Code, INT Pos );
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
    virtual VOID OnVScroll( HWND hWndCtl, UINT Code, INT Pos );
    /* WM_EXITSIZEMOVE window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnExitSizeMove( VOID );
    /* WM_ENTERSIZEMOVE window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnEnterSizeMove( VOID );
    /* Window message update handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Update( VOID );
    /* Window message handle function.
     * ARGUMENTS:
     *   - window handle message:
     *       UINT Msg;
     *   - additional dialog creation parameters:
     *       WPARAM wParam, LPARAM lParam;
     * RETURNS:
     *   (LRESULT) hWnd message.
     */
    virtual LRESULT OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam );
  }; /* End of 'win' class*/
} /* End of 'arvk' namespace */

#endif /* __win_h_ */

/* END OF 'win.h' FILE */
