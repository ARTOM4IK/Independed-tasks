/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_framebuffer.h
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

#ifndef __vlk_framebuffer_h_
#define __vlk_framebuffer_h_

#include "anim/rnd/vlk/vlk_def.h"

/* Animation namespace */
namespace arvk
{
  /* Frame buffer class */
  class VlkFrameBuffer: public VlkRenderPass
  {
  public:
    std::vector<VkFramebuffer> FrameBuffers;
    VkImage DepthImage;
    VkImageView DepthImageView;
    VmaAllocation Allocation {};

    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkFrameBuffer( VOID )
    {
    } /* End of 'VlkFrameBuffer' fucntion */

    /* Class destructor */
    ~VlkFrameBuffer( VOID )
    {
    } /* End of '~VlkFrameBuffer' fucntion */

    /* Create frame buffer function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     *   - Render pass:
     *       VkRenderPass &RenderPass;
     *   - Image views:
     *       std::vector<VkImageView> &SwapchainImageViews;
     *   - Frame size:
     *       INT &FrameW, INT &FrameH;
     * RETURNS: None.
     */
    VOID CreateFrameBuffer( VkDevice &Device, VkRenderPass &RenderPass, std::vector<VkImageView> &SwapchainImageViews, INT &W, INT &H );

    /* Destroy frame buffer function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     * RETURNS: None.
     */
    VOID DestroyFrameBuffer( VkDevice &Device );
  }; /* End of 'VlkFrameBuffer' class */
} /* End of 'arvk' namespace */

#endif /* __vlk_framebuffer_h_ */

/* END OF 'vlk_framebuffer.h' FILE */
