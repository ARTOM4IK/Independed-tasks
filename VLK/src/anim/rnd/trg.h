/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : trg.h
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

#ifndef __trg_h_
#define __trg_h_

#include "res/resources.h"
#include "anim/rnd/lights.h"

/* Animation namespace */
namespace arvk
{
  /* Target class */
  class target : public resource
  {
  private:
  public:
    UINT RndBufId;
    UINT FBOId;
    INT Attachments;            
    INT Width, Height;          
    prim *Screen;
    prim *SkyBox;                
    std::vector<texture*> TargetTex;

    /* Class constructor.
     * ARGUMENTS: None. 
     */
    target( VOID );

    /* Class desstructor */
    ~target( VOID );

    /* Init target function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Init( VOID );
    /* Create target function.
     * ARGUMENTS:
     *   - frame size:
     *       INT W, INT H;
     * RETURNS:
     *   (target&) New target.
     */
    target& Create( INT W, INT H );

    /* Free target function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

    /* Target resize function.
     * ARGUMENTS:
     *   - new target size:
     *       INT W, H;
     * RETURNS: 
     *   (BOOL) TRUE if successful, FALSE otherwise.
     */
    VOID Resize( INT W, INT H );
    /* Start target frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Start( VOID );
    /* End target frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID End( VOID );
  }; /* End of 'target' class */
} /* End of 'arvk' namespace */

#endif /* __trg_h_ */

/* END OF 'trg.h' FILE */
