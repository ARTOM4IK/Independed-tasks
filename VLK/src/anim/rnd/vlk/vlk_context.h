/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_context.h
 * PURPOSE     : Vulkan animation project.
 *               Vulkan module.
 * PROGRAMMER  : CGSG-FallCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 29.10.2025.
 * NOTE        : Module namespace 'arvk'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __vlk_context_h_
#define __vlk_context_h_

#include "anim/rnd/vlk/vlk_def.h"

/* Animation namespace */
namespace arvk
{
  /* Set window context class */
  class VlkContext: public VlkDevice
  {
  public:
    VkSurfaceKHR Surface;
    std::vector<VkBuffer> StageBuffer {};
    std::vector<UINT> StageBufferSize {};
    std::vector<VmaAllocation> StageBufferAllocation {};

    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkContext( VOID )
    {
      StageBuffer.resize(4);
      StageBufferSize.resize(4);
      StageBufferAllocation.resize(4);
    } /* End of 'VlkContext' fucntion */

    /* Class destructor */
    ~VlkContext( VOID )
    {
    } /* End of '~VlkContext' fucntion */

    /* Create context function.
     *  ARGUMENTS:
     *   - Window handle:
     *      HWND &hWnd;
     *   - Instance:
     *      VkInstance &Instance;
     * RETURNS: None.
     */
    VOID CreateContext( HWND &hWnd, VkInstance &Instance );

    /* Destroy context function.
     *  ARGUMENTS:
     *   - Instance:
     *      VkInstance &Instance;
     * RETURNS: None.
     */
    VOID DestroyContext( VkInstance &Instance );
  }; /* End of 'VlkContext' class */
} /* End of 'arvk' namespace */

#endif /* __vlk_context_h_ */

/* END OF 'context.h' FILE */
