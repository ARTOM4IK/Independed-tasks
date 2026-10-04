/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_dummy.h
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

#ifndef __vlk_fence_h_
#define __vlk_fence_h_

#include "anim/rnd/vlk/vlk_def.h"

/* Animation namespace */
namespace arvk
{
  /* Vulkan dummy class */
  class VlkFence: public VlkDescriptor
  {
  public:
    VkFence TransferFence {};               // Vulkan transfer queue sync fence
    std::vector<VkFence> Fence {};
    std::vector<VkSemaphore> RenderFinishSemaphores {}; // Rendering wait semaphores (used before present)
    std::vector<VkSemaphore> ImageAvailableSemaphores {}; // Swapchain ready image waiting semaphores
    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkFence( VOID )
    {
      Fence.resize(3);
      ImageAvailableSemaphores.resize(3);
      RenderFinishSemaphores.resize(3);
     } /* End of 'VlkFence' function */

    /* Class destructor */
    ~VlkFence( VOID )
    {
    } /* End of '~VlkDence' function */

    /* Create fence function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     * RETURNS: None.
     */
    VOID CreateFence( VkDevice &Device );

    /* Destroy fence function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     * RETURNS: None.
     */
    VOID DestroyFence( VkDevice &Device );

    /* Create semaphore function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     * RETURNS: None.
     */
    VOID CreateSemaphores( VkDevice &Device );

    /* Destroy semaphore function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     * RETURNS: None.
     */
    VOID DestroySemaphores( VkDevice &Device );
      
  }; /* End of 'VlkFence' class*/
} /* End of 'arvk' namespace */

#endif /* __vlk_fence_h_ */

/* END OF 'vlk_dummy.h' FILE */
