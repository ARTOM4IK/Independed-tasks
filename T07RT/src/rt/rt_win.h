/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : rt_win.h
 * PURPOSE     : Ray Tracing project.
 *               Ray tracing window declaration module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 24.07.2025.
 * NOTE        : Module namespace 'arrt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __rt_win_h_
#define __rt_win_h_

#include "arrt.h"
#include "rt_def.h"

/* Ray tracing namespace */
namespace arrt
{
  /* Concept for derived classes */
  template<class T, class U>
    concept Derived = std::is_base_of_v<U, T>;

  /* Concept for scene objects classes */
  template<typename T>
    concept SceneObject = Derived<T, shape> || Derived<T, light>;

  /* Ray tracing window class */
  class rt_win: public win
  {
  private:
    BOOL IsFullScreen;                              // is full screen flag
    RECT FullScreenSaveRect;                        // full screen save rectangle
    INT MouseWheel;                                 // mouse wheel parametr

    INT ImgX, ImgY, ImgH, ImgW, ImgZoomW, ImgZoomH; // image parametrs
    DBL ImgZoom = 1;                                // image zoom
    DBL MouseX = 0, MouseY = 0;                     // mouse position
    
    using scenes_pool = std::map<std::string, VOID (*)( rt_win &RT )>;

    /* Single instance scene map optain function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (static scenes_pool &) scene pool reference.
     */
    inline static scenes_pool & GetScenes( VOID )
    {
      static scenes_pool Scenes;

      return Scenes;
    } /* End of 'GetScenes' function */

  public:
    BOOL IsActive;                                  // is active flag
    HBRUSH hBrBack;                                 // brush handle
    frame Frm;                                      // frame
    camera Cam;                                     // camera
    scene Scn;                                      // scene
 
    /* Class constructor.
     * ARGUMENTS:
     *   - windows instance handle:
     *       HINSTANCE hInst;
     */
    rt_win( HINSTANCE hInst = GetModuleHandle(nullptr) );

    /* Class destructor */ 
    virtual ~rt_win( VOID );
 
    /* Window run function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Run( VOID ) override;
 
    template<typename scene_type>
      class scene_register
      {
      private:
        static VOID Create( rt_win &RT )
        {
          scene_type _(RT);
        }
      public:
        scene_register( const std::string &SceneName )
        {
          GetScenes()[SceneName] = Create;
        }
      }; /* End of 'scene_register' class */
    
      /* Add scene function.
       * ARGUMENTS:
       *   - scnene name:
       *       const std::string &SceneName;
       * RETURNS:
       *   (rt_win &) ray tracing window.
       */
      rt_win & operator<<( const std::string &SceneName )
      {
        auto &Scenes(GetScenes());
        if (auto sc = Scenes.find(SceneName); sc != Scenes.end())
          sc->second(*this);
        return *this;
      } /* End of 'operator<<' function */

      /* Add object to scene function.
       * ARGUMENTS:
       *   - pointer to object:
       *       object_type *Obj;
       * RETURNS:
       *   (rt_win &) ray tracing window.
       */
      template<SceneObject object_type>
      rt_win & operator<<( object_type *Obj )
      {
        Scn << Obj;
        return *this;
      } /* End of 'operator<<' function */
  private:
    /* WM_CREATE window message handle function.
     * ARGUMENTS:
     *   - structure with creation data:
     *       CREATESTRUCT *CS;
     * RETURNS:
     *   (BOOL) TRUE to continue creation window, FALSE to terminate.
     */
    virtual BOOL OnCreate( CREATESTRUCT *CS ) override;
    /* WM_DESTROY window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnDestroy( VOID ) override;
    /* WM_ERASEBKGND window message handle function.
     * ARGUMENTS:
     *   - device context of client area:
     *       HDC hDC;
     * RETURNS:
     *   (BOOL) TRUE if background is erased, FALSE otherwise.
     */
    virtual BOOL OnEraseBkgnd( HDC hDC ) override;                                                                               
    /* WM_PAINT window message handle function.
     * ARGUMENTS:
     *   - window device context:
     *       HDC hDC;
     *   - paint message structure pointer:
     *       PAINTSTRUCT *PS;
     * RETURNS: None.
     */
    virtual VOID OnPaint( HDC hDC, PAINTSTRUCT *Ps ) override;
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
    virtual VOID OnActivate( UINT Reason, HWND hWndActDeact, BOOL IsMinimized ) override;
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
    virtual VOID OnMouseWheel( INT X, INT Y, INT Z, UINT Keys ) override;
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
    virtual VOID OnButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys ) override;
    /* WM_*BUTTONUP window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    virtual VOID OnButtonUp( INT X, INT Y, UINT Keys ) override;
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
    virtual VOID OnLButtonDown( BOOL IsDoubleClick, INT X, INT Y, UINT Keys ) override;
    /* WM_*BUTTONUP window message handle function.
     * ARGUMENTS:
     *   - mouse window position:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    virtual VOID OnLButtonUp( INT X, INT Y, UINT Keys ) override;
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
    virtual VOID OnKey( UINT Key, BOOL IsPress, INT RepeatCount, UINT ShiftKeysFlags ) override;
    /* WM_INITDIALOG window message handle function.
     * ARGUMENTS:
     *   - control handle to be set focus:
     *       HWND hWndFocus;
     *   - additional dialog creation parameter:
     *       LPARAM lParam;
     * RETURNS:
     *   (BOOL) TRUE for use hWndFocus, FALSE for user focus window set.
     */
    virtual BOOL OnInitDialog( HWND hWndFocus, LPARAM lParam ) override;
    /* WM_MOUSEMOVE message handle function.
     * ARGUMENTS:
     *   - mouse cursor X and Y coordinates:
     *       INT X, Y;
     *   - mouse keys bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    virtual VOID OnMouseMove( INT X, INT Y, UINT Keys ) override;
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
    virtual VOID OnHScroll( HWND hWndCtl, UINT Code, INT Pos ) override;
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
    virtual VOID OnVScroll( HWND hWndCtl, UINT Code, INT Pos ) override;
    /* WM_SIZE window message handle function.
     * ARGUMENTS:
     *   - sizing flag (see SIZE_***, like SIZE_MAXIMIZED)
     *       UINT State;
     *   - new width and height of client area:
     *       INT W, H;
     * RETURNS: None.
     */
    virtual VOID OnSize( UINT State, INT W, INT H ) override;
    /* WM_TIMER window message handle function.
     * ARGUMENTS:
     *   - specified the timer identifier.
     *       INT Id;
     * RETURNS: None.
     */
    virtual VOID OnTimer( INT Id ) override;
    /* WM_DROPFILES window message handle function.
     * ARGUMENTS:
     *   - handle to an internal structure describing the dropped files:
     *       HDROP hDrop;
     * RETURNS: None.
     */
    virtual VOID OnDropFiles( HDROP hDrop ) override;
    /* WM_DRAWITEM window message handle function.
     * ARGUMENTS:
     *   - control identifier (for menu - 0):
     *       INT Id;
     *   - draw item information structure pointer:
     *       DRAWITEMSTRUCT *DrawItem;
     * RETURNS: None.
     */
    virtual VOID OnDrawItem( INT Id, DRAWITEMSTRUCT *DrawItem ) override;
    /* WM_NOTIFY window message handle function.
     * ARGUMENTS:
     *   - control identifier:
     *       INT Id;
     *   - notification header depended to control type:
     *       NMHDR *NoteHead;
     * RETURNS:
     *   (LRESULT) return value depended to notification.
     */
    virtual LRESULT OnNotify( INT Id, NMHDR *NoteHead ) override;
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
    virtual VOID OnCommand( INT Id, HWND hWndCtl, UINT CodeNotify ) override;
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
    virtual VOID OnMenuSelect( HMENU hMenu, INT Item, HMENU hMenuPopup, UINT Flags ) override;
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
    virtual VOID OnInitMenuPopup( HMENU hMenu, UINT Item, BOOL IsSystemMenu ) override;
    /* WM_EXITSIZEMOVE window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnExitSizeMove( VOID ) override;
    /* WM_ENTERSIZEMOVE window message handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID OnEnterSizeMove( VOID ) override;
    /* Window message update handle function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    virtual VOID Update( VOID ) override;
  }; /* End of 'rt_win' class */
} /* End of 'arrt' namespace */

#endif /* __rt_win_h_ */

/* END OF 'rt_win.h' FILE */
