/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : lights.h
 * PURPOSE     : Ray Tracing project.
 *               Lights system header.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'arvk'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __lights_h_
#define __lights_h_

#include "res/resources.h"

/* Animation namespace */
namespace arvk
{
  /* Light type namespace */
  namespace ltype
  {  
    /* Light type enum */
    enum LightType
    {
      AMBIENT = 0,
      POINT = 1,
      DIR = 2,
      SPOT = 3,
    };
  }
  /* Light class */
  class light : public resource
  {
  public:
     
    ltype::LightType Type;
    vec3 Pos, Dir, Color, Att;
    vec2 CutOffAngle, CutOffDist;
    FLT CutOffAngleCos[2];
    
    prim *LightPrim;
    buffer *BufferLight;
    INT ShadowSize;
    matr ShadowMatr;
    BOOL IsShadowCast;
    //target ShadowTarget;
    material *ShadowMtl;
    UINT ShadowFBO;
    texture *ShadowTex;

    /* Class constructor.
     * ARGUMENTS: None.
     */
    light( VOID );
    /* Class destructor */
    ~light( VOID );

    /* Enable shadow function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID EnableShadow( VOID );
    /* Update lights function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Update( VOID );
  }; /* End of 'light' class */

  class light_manager
  {
  private:
    render &Rnd;
    prim *LightPrimFullScreen;
    material *LightMtl;
    shader *LightShaders[4]; // Ambient, Point, Dir, Spot

  public:
    stock<light*> Lights;

    /* Class constructor.
     * ARGUMENTS:
     *   - reference to render:
     *       render &Rnd;
     */
    light_manager( render &Rnd );

    /* Class destructor */
    ~light_manager( VOID );

    /* Create light function.
     * ARGUMENTS:
     *   - light:
     *       light *Lig;
     * RETURNS:
     *   (light *) created primitive interface.
     */
    light * LightCreate( ltype::LightType Type );
    /* Free light function.
     * ARGUMENTS:
     *   - light:
     *       light *Lig;
     * RETURNS: None.
     */
    VOID LightFree( light *Lig );
    /* Redraw lights function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Redraw( VOID );
    /* Redraw shadows function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID RedrawShadows( VOID );
    /* Update all lights function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */

    /* Light destroy function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID )
    {
    } /* End of 'Free' function */

    VOID UpdateAll( VOID );
  }; /* End of 'light_manager' class */
} /* End of 'arvk' namespace */

#endif /* __lights_h_ */

/* END OF 'lights.h' FILE */