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

#ifndef __vlk_image_h_
#define __vlk_image_h_

#include "anim/rnd/vlk/vlk_def.h"

/* Animation namespace */
namespace arvk
{
  /* Vulkan dummy class */
  class VlkImage: public VlkFence
  {
  public:

    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkImage( VOID )
    {
    } /* End of 'VlkImage' function */

    /* Class destructor */
    ~VlkImage( VOID )
    {
    } /* End of '~VlkImage' function */

    /* Vulkan image creation function.
     * ARGUMENTS:
     *   - vulkan image handle output reference:
     *       VkImage &Image;
     *   - vulkan image view handle output reference:
     *       VkImageView &ImageView;
     *   - VMA image allocation handle output reference:
     *       VmaAllocation &Allocation;
     *   - image size:
     *       INT W, H;
     *   - image color flag (otherwise Image is depth buffer):
     *       BOOL IsColor,
     *   - cube map flag (create 6 layers and 'PixelData' contain 6 joined same size images):
     *       BOOL IsCube,
     *   - vulkan image Format (see VK_FORMAT_***):
     *       VkFormat Format;
     *   - vulkan image usage flags bitwise combination (VK_IMAGE_USAGE_***):
     *       VkImageUsageFlags UsageFlags;
     *   - vulkan image layout (see VK_IMAGE_LAYOUT_***):
     *       VkImageLayout Layout;
     *   - image pixel data:
     *       const VOID *PixelsData;
     *   - image pixel data size (in bytes):
     *       UINT PixelsDataSize;
     *   - number of mipmaps to be create:
     *       UINT MipCount;
     * RETURNS:
     *   (BOOL) success creation result.
     */
    BOOL ImageCreate( VkImage &Image, VkImageView &ImageView, VmaAllocation &Allocation,
                                 INT W, INT H, BOOL IsColor, BOOL IsCube,
                                 VkFormat Format, VkImageUsageFlags UsageFlags, VkImageLayout Layout,
                                 VOID *PixelsData, UINT PixelsDataSize, UINT MipCount );

    /* Vulkan image free function.
     * ARGUMENTS:
     *   - vulkan image handle output reference:
     *       VkImage &Image;
     *   - vulkan image view handle output reference:
     *       VkImageView &ImageView;
     *   - VMA image allocation info output reference:
     *       VmaAllocation &Allocation
     * RETURNS: None.
     */
    VOID ImageFree( VkImage &Image, VkImageView &ImageView, VmaAllocation &Allocation );

    /* Vulkan image set layout function.
     * Create an image memory 'ImageMemoryBarrier' for changing the layout of
     * an Image and put it into an active command buffer
     * ARGUMENTS:
     *   - vulkan image handle:
     *       VkImage Image;
     *   - vulkan image old and new layouts (see VK_IMAGE_LAYOUT_***):
     *       VkImageLayout OldImageLayout, NewImageLayout;
     *   - vulkan image subrsourcse description:
     *       VkImageSubresourceRange SubresourceRange;
     *   - vulkan pipeline source and destination stage flags (see VK_PIPELINE_STAGE_***):
     *       VkPipelineStageFlags SrcStageMask, DstStageMask;
     * RETURNS: None.
     */
    VOID ImageSetLayout( VkImage Image,
                                    VkImageLayout OldImageLayout, VkImageLayout NewImageLayout,
                                    VkImageSubresourceRange SubresourceRange,
                                    VkPipelineStageFlags SrcStageMask, VkPipelineStageFlags DstStageMask );

    /* Vulkan image set layout (on first mip level and layer) function.
     * ARGUMENTS:
     *   - vulkan image handle:
     *       VkImage Image;
     *   - vulkan image old and new layouts (see VK_IMAGE_LAYOUT_***):
     *       VkImageLayout OldImageLayout, NewImageLayout;
     *   - vulkan image subrsourcse description:
     *       VkImageSubresourceRange SubresourceRange;
     *   - vulkan pipeline source and destination stage flags (see VK_PIPELINE_STAGE_***):
     *       VkPipelineStageFlags SrcStageMask, DstStageMask;
     * RETURNS: None.
     */
    VOID ImageSetLayout( VkImage Image,
                                    VkImageAspectFlags AspectMask,
                                    VkImageLayout OldImageLayout, VkImageLayout NewImageLayout,
                                    VkPipelineStageFlags SrcStageMask, VkPipelineStageFlags DstStageMask );

    /* Vulkan Image set layout (on first mip level and layer) function.
     * ARGUMENTS:
     *   - vulkan image handle:
     *       VkImage Image;
     *   - image size:
     *       INT W, H;
     *   - vulkan Image Format (see VK_FORMAT_***):
     *       VkFormat Format;
     *   - cube map flag (create 6 layers and 'PixelData' contain 6 joined same size images):
     *       BOOL IsCube;
     * RETURNS: None.
     */
    VOID ImageGenerateMipmaps( VkImage Image, INT W, INT H, UINT Levels, VkFormat Format, BOOL IsCube );

  }; /* End of 'Image' class*/
} /* End of 'arvk' namespace */

#endif /* __vlk_image_h_ */

/* END OF 'vlk_image.h' FILE */
