/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_renderpass.h
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

#ifndef __vlk_renderpass_h_
#define __vlk_renderpass_h_

#include "anim/rnd/vlk/vlk_def.h"

/* Animation namespace */
namespace arvk
{
  /* Render pass class */
  class VlkRenderPass: public VlkContext
  {
  public:
    VkRenderPass RenderPass = VK_NULL_HANDLE;

    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkRenderPass( VOID )
    {
    } /* End of 'VlkRenderPass' fucntion */

    /* Class destructor */
    ~VlkRenderPass( VOID )
    {
    } /* End of '~VlkRenderPass' fucntion */

    /* Create render pass function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     *   - Image format:
     *       VkFormat &SwapchainImageFormat;
     * RETURNS: None.
     */
    VOID CreateRenderPass( VkDevice &Device, VkFormat &SwapchainImageFormat );

    /* Destroy render pass function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     * RETURNS: None.
     */
    VOID DestroyRenderPas( VkDevice &Device );
    /* Create frame buffer function.
     *  ARGUMENTS:
     *   - Depth formats:
     *       std::vector<VkFormat> DepthFormats;
     *   - Format tiling:
     *      VkImageTiling tiling;
     *   - Format features:
     *       VkFormatFeatureFlags features;
     *   - Physical device:
     *       VkPhysicalDevice &PhysicalDevice;
     * RETURNS: (VkFormat) Supporting depth format.
     */
    VkFormat FindDepthFormat( std::vector<VkFormat> &DepthFormats, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice &PhysicalDevice );
  }; /* End of 'VlkRenderPass' class */

} /* End of 'arvk' namespace */

#endif /* __vlk_renderpass_h_ */

/* END OF 'vlk_renderpass.h' FILE */
