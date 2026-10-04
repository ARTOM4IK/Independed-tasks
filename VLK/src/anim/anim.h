/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : anim.h
 * PURPOSE     : Animation project.
 *               Animation module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'arvk'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __anim_h_
#define __anim_h_

#include "win/win.h"
#include "rnd/render.h"
#include "input/input.h"
#include "input/timer.h"

/* Animation namespace */
namespace arvk
{
  class anim;

  /* Unit class */
  class unit
  {
  public:
    virtual ~unit( VOID )
    {
    }
    virtual VOID Render( anim *Ani )
    {
    } /* End of 'Render' function */
    virtual VOID Response( anim *Ani )
    {
    } /* End of 'Response' function */
  };

  /* Scene class */
  class scene
  {
  public:
    stock<unit *> Units;
    scene & operator<<( unit *Uni )
    {
      Units << Uni;
      return *this;
    }
  };

  /* Core class */
  class core
  {
  public:
    inline static std::string Path;
    core( VOID )
    {
      //std::filesystem::path P;// = std::filesystem::current_path();
      //if (P.string().back() != '\\' && P.string().back() != '/')
      //  P += "\\";
      //Path = P.string();
      CHAR Buf[_MAX_PATH];
      GetCurrentDirectory(sizeof(Buf), Buf);
      SIZE_T len = strlen(Buf);
      if (len > 0 && Buf[len - 1] != '\\' && Buf[len - 1] != '/')
        strcat(Buf, "\\");
      Path = Buf;
    }
  }; /* End of 'core' class */

  /* Animation class */
  class anim: public win, public input, public timer, public render, public core
  {

  private:
    std::atomic_bool IsRenderActive {};

    //scene *Scene;
    stock<unit *> Units;
    //std::map<std::string, unit * (*)( VOID )> UnitNames;
    /*static */std::map<std::string, unit * (*)( anim *Ani )> UnitNames;
  public:
    anim( HINSTANCE hInst = GetModuleHandle(nullptr) ) : win(hInst), input(win::hWnd, win::MouseWheel), render(win::hWnd)
    {
    }
    ~anim( VOID )
    {
      Units.walk([]( unit * Uni )
      {
        delete Uni;
      });
    }

  private:

    template<typename unit_type>
    class unit_register
    {
    private:
      static unit * Create( anim *Ani )
      {
        return new unit_type(Ani);
      } /* End of 'Create' function */
    public:
      unit_register( const std::string &UnitName )
      {
        UnitNames[UnitName] = Create;
      }

    }; /* End of 'unit_register' class */

    public:
      anim & operator<<( unit *Uni )
      {
        Units << Uni;
        return *this;
      } /* End of 'anim & operator<<' function */

      anim & operator<<( const std::string &Name )
      {
        if (auto uni_ref = UnitNames.find(Name); uni_ref != UnitNames.end())
          return *this << (*uni_ref->second)(this);
        return *this;
      } /* End of 'operator<<' function */

      //anim & operator<<( const std::string &UnitName )
      //{
      //  if (UnitNames.find(UnitName) != UnitNames.end())
      //    *this << UnitNames[UnitName]();
      //  return *this;
      //} /* End of 'anim & operator<<' function */

    VOID Render( VOID );
    VOID ReRender( VOID );
  public:
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
    virtual LRESULT OnMessage( UINT Msg, WPARAM wParam, LPARAM lParam ) override;
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
     *   - mouse keys   bits (see MK_*** bits constants):
     *       UINT Keys;
     * RETURNS: None.
     */
    virtual VOID OnButtonUp( INT X, INT Y, UINT Keys ) override;
    /* WM_*BUTTONUP window message handle function.
     * ARGUMENTS:
     * RETURNS: None.
     */
    virtual VOID Run( VOID ) override;

    ///* Get animation reference function.
    // * ARGUMENTS: None.
    // * RETURNS: 
    // *   (anim &) Animation reference
    // */
    //static anim & GetRef( VOID )
    //{
    //  static anim Instance;

    //  return Instance;
    //} /* End of 'GetRef' function */

    ///* Get animation pointer function.
    // * ARGUMENTS: None.
    // * RETURNS: 
    // *   (anim *) Animation pointer
    // */
    //static anim * Get( VOID )
    //{
    //  return &GetRef();                         
    //} /* End of 'Get' function */
  }; /* End of 'unit' class */
} /* End of 'arvk' namespace */

#endif /* __anim_h_ */

/* END OF 'anim.h' FILE */
