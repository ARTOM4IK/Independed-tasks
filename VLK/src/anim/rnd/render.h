/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : render.h
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

#ifndef __render_h_
#define __render_h_

#include "def.h"
#include "anim/rnd/vlk/vlk_core.h"
#include "anim/input/timer.h"
#include "res/buf.h"
#include "res/tex.h"
#include "res/shd.h"
#include "res/mtl.h"
#include "res/prim.h"
#include "res/fnt.h"
#include "anim/rnd/trg.h"
#include "anim/rnd/lights.h"

/* Animaton namespace */
namespace arvk
{
  /* Render class */
  class render: public primitive_manager, public shader_manager, public material_manager, public texture_manager, public buffer_manager, public model_manager, public VlkCore
  {
  private:
    HWND &hWndRef;
    HDC hDC;
    HGLRC hGLRC;
 
    BOOL IsRenderInit {};
  public:
    timer Timer;
    camera Cam;
    target Trg;
    light_manager *Lights; 
    DBL FrameW, FrameH;
    VlkBuffer VertexBuf, IndexBuffer;

    //VlkInstance Ins;
    //VlkDebug Deb;
    //VlkDevice Dev;
    //VlkContext Con;
    //VlkSwapchain Swpch;
    //VlkFrameBuffer FrmBuf;
    //VlkRenderPass RndPass;
    //VlkCommandQueue CmdQueue;

    /* Camera buffer transfer structure */
    struct BUF_CAM
    {
      matr::matr_data MatrView; // Camera view matrix
      matr::matr_data MatrProj; // Camera projection matrix
      matr::matr_data MatrVP;   // Camera view by projection matrices production
      vec4 CamLocFrameW;        // Location + frame width
      vec4 CamDirProjDist;      // Direction + project distance
      vec4 CamRightWp;          // Right + project plane width
      vec4 CamUpHp;             // Up + project plane height
      vec4 CamAtFrameH;         // Look at point + frame height
      vec4 FrameWHProjSizeDist; // W + H + ProjSize + ProjDist
    }; /* End of 'BUF_CAM' structure */
 
    /* Time buffer transfer structure */
    struct BUF_SYNC
    {
      // Global time + global delta time + time + delta time
      vec4 SyncGlobalTimeGlobalDeltaTimeTimeDeltaTime;
    }; /* End of 'BUF_SYNC' structure */
 
    struct PUSH_CONST
    {
      matr::matr_data MatrWVP;
      matr::matr_data MatrW;
      vec4 Ka;             // Ambient
      vec4 KdTrans;        // Diffuse + Transparency
      vec4 KsPh;           // Specular + Phong
    };

    struct PUSH_MTL
    {
      vec4 Ka;             // Ambient
      vec4 KdTrans;        // Diffuse + Transparency
      vec4 KsPh;           // Specular + Phong
    };

    /* Primitive buffer transfer structure */
    struct BUF_PRIM
    {
      matr::matr_data MatrWVP;  // World by view by projection matrices production
      matr::matr_data MatrW;         // World matrix
      matr::matr_data MatrWInvTrans; // inverse transpose world matrix
      vec4 RndIsWireIsAny;           // Wireframe flag + not used x 3
      INT TextureFlags[8];           // Texture usage flags
    }; /* End of 'BUF_PRIM' structure */
 
    // OpenGL data buffers
    buffer
      *BufCam,  // Camera buffer
      *BufSync, // Timer buffer
      *BufPrim; // Primitive buffer

    render( HWND &hNewWndRef ) : primitive_manager(*this), model_manager(*this),shader_manager(*this), material_manager(*this), texture_manager(*this), buffer_manager(*this), hWndRef(hNewWndRef), hGLRC(nullptr), hDC(nullptr), FrameH(30), FrameW(30), Lights(nullptr), BufCam(nullptr), BufSync(nullptr), BufPrim(nullptr)
    {
    } /* End of 'render' function */
 
    ~render( VOID )
    {
    } /* End of '~render' function */
 
    /* Init render function.
     * ARGUMENTS: None.
     * RETURNS:
     *   None.
     */
    VOID Init( VOID ); 
    /* Close render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Close( VOID );  
    /* Resize function.
     * ARGUMENTS:
     *   - Window size:
     *       INT W, INT H;
     * RETURNS: None.
     */
    VOID Resize( INT NewW, INT NewH ); 
    /* Start of render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameStart( VOID ); 
    /* End of render function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID FrameEnd( VOID );
    /* Copy frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID ChangeWireMode( BOOL &IsWire );
    /* Debug output function.
     * ARGUMENTS:
     *   - source APi or device:
     *      UINT Source;
     *   - error type:
     *      UINT Type;
     *   - error message id:
     *      UINT Id, 
     *   - message severity:
     *      UINT severity, 
     *   - message text length:
     *      INT Length, 
     *   - message text:
     *      CHAR *Message, 
     *   - user addon parameters pointer:
     *      VOID *UserParam;
     * RETURNS: None.
     */
    static VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity, INT Length, const CHAR *Message, const VOID *UserParam );
    /* Primitive draw function.
     * ARGUMENTS:
     *   - primitive pointer:
     *       prim *Pr;
     *   - transformation matrix:
     *       const matr &World;
     * RETURNS: None.
     */
    VOID Draw( const prim *Pr, const matr &World = matr::Identity() );
    /* Draw model render function.
     *  ARGUMENTS:
     *   - pointer to model:
     *      model *Mdl;
     *   - world matrix:
     *       &World;
     * RETURNS: None.
     */
    VOID Draw( const model &Mdl, const matr &World = matr::Identity() );
  }; /* End of 'render' class */
} /* End of 'arvk' namespace */

#endif /* __render_h_ */

/* END OF 'render.h' FILE */
