/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_swapchain.h
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

#ifndef __vlk_swapchain_h_
#define __vlk_swapchain_h_

#include "anim/rnd/vlk/vlk_def.h"

/* Animation namespace */
namespace arvk
{
  /* Swapchain class */
  class VlkSwapchain: public VlkFrameBuffer
  {
  public:
    VkSwapchainKHR Swapchain;
    std::vector<VkImageView> SwapchainImageViews;
    VkFormat SwapchainImageFormat = VK_FORMAT_B8G8R8A8_SRGB;
    INT ClampedW,ClampedH;
    UINT32 ActiveSwapchainImage;

    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkSwapchain( VOID )
    {
    } /* End of 'VlkSwapchain' fucntion */

    /* Class destructor */
    ~VlkSwapchain( VOID )
    {
    } /* End of '~VlkSwapchain' fucntion */

    /* Create swapchain function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     *   - Physical device:
     *       VkPhysicalDevice &PhysDevice;
     *   - Surface:
     *       VkSurfaceKHR &Surface;
     *   - Frame size:
     *       INT &FrameW, INT &FrameH;
     * RETURNS: None.
     */
    VOID CreateSwapchain( VkDevice &Device, VkPhysicalDevice &PhysDevice, VkSurfaceKHR &Surface, INT &FrameW, INT &FrameH );

    /* Resize swapchain function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     *   - Physical device:
     *       VkPhysicalDevice &PhysDevice;
     *   - Surface:
     *       VkSurfaceKHR &Surface;
     *   - Frame size:
     *       INT &FrameW, INT &FrameH;
     *   - FrameBuffer:
     *       VlkFrameBuffer &VlkFrameBuffer;
     *   - RenderPass:
     *       VkRenderPass &RenderPass;
     * RETURNS: None.
     */
    VOID ResizeSwapchain( VkPhysicalDevice &PhysDevice, VkDevice &Device, VkSurfaceKHR &Surface, INT &FrameW, INT &FrameH, VkRenderPass &RenderPass );

    /* Destroy swapchain function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     * RETURNS: None.
     */
    VOID DestroySwapchain( VkDevice &Device );
  }; /* End of 'VlkSwapchain' class */
} /* End of 'arvk' namespace */

#endif /* __vlk_swapchain_h_ */

/* END OF 'vlk_swapchain.h' FILE */
