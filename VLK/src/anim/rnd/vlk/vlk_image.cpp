/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_dummy.cpp
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

#include "arvk.h"

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
BOOL arvk::VlkImage::ImageCreate( VkImage &Image, VkImageView &ImageView, VmaAllocation &Allocation,
                             INT W, INT H, BOOL IsColor, BOOL IsCube,
                             VkFormat Format, VkImageUsageFlags UsageFlags, VkImageLayout Layout,
                             VOID *PixelsData, UINT PixelsDataSize, UINT MipCount )
{
  if (MipCount < 1)
    MipCount = 1;
  W = COM_MAX(W, 1);
  H = COM_MAX(H, 1);
 
  // Create vulkan image
  VkImageCreateInfo ImageCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
    .imageType = VK_IMAGE_TYPE_2D,
    .format = Format,
    .extent {.width = (UINT)W, .height = (UINT)H, .depth = 1 },
    .mipLevels = MipCount,
    .arrayLayers = IsCube ? 6U : 1U,
    .samples = VK_SAMPLE_COUNT_1_BIT,
    .tiling = VK_IMAGE_TILING_OPTIMAL,
    .usage = UsageFlags,
    .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    .initialLayout = Layout,
  };
  // Create image through VMA
  VmaAllocationCreateInfo AllocationCreateInfo {};
  AllocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
  AllocationCreateInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  AllocationCreateInfo.flags = 0;
  AllocationCreateInfo.priority = 1.0f;
  if (vmaCreateImage(Allocator, &ImageCreateInfo, &AllocationCreateInfo, &Image, &Allocation, nullptr) != VK_SUCCESS ) 
    (VOID)0; // << "vmaImage: Cannot create image" << std::endl;
 
  // Create image view
  VkImageViewCreateInfo ImageViewCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
    .image = Image,
    .viewType = VK_IMAGE_VIEW_TYPE_2D,
    .format = Format,
    .components = {.r = VK_COMPONENT_SWIZZLE_IDENTITY, .g = VK_COMPONENT_SWIZZLE_IDENTITY, .b = VK_COMPONENT_SWIZZLE_IDENTITY, .a = VK_COMPONENT_SWIZZLE_IDENTITY},
    .subresourceRange
    {
      .aspectMask = VkImageAspectFlags(IsColor ? VK_IMAGE_ASPECT_COLOR_BIT : VK_IMAGE_ASPECT_DEPTH_BIT), // ??? shadow map
      .baseMipLevel = 0,
      .levelCount = MipCount,
      .baseArrayLayer = 0,
      .layerCount = IsCube ? 6U : 1U,
    }
  };
  vkCreateImageView(Device, &ImageViewCreateInfo, nullptr, &ImageView);
 
  if (PixelsData != nullptr)
  { 
    StageBufferUpdate(0, PixelsDataSize, PixelsData, CurrentFrame);
 
    // Copy through command buffer
    VkCommandBufferBeginInfo CommandBufferBeginInfo
    {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
      .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    };
    //vkResetCommandBuffer(TransferCommandBuffer, VK_COMMAND_BUFFER_RESET_RELEASE_RESOURCES_BIT);
    vkBeginCommandBuffer(TransferCommandBuffer, &CommandBufferBeginInfo);
  
    // Create transfer barrier
    VkImageMemoryBarrier ImageMemoryBarrier1
    {
      .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
      .srcAccessMask = 0, // VK_ACCESS_HOST_WRITE_BIT,
      .dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT, // 0,
      .oldLayout = Layout,
      .newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
      .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .image = Image,
      .subresourceRange
      {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .baseMipLevel = 0,
        .levelCount = MipCount,
        .baseArrayLayer = 0,
        .layerCount = IsCube ? 6U : 1U,
      },
    };
    vkCmdPipelineBarrier(TransferCommandBuffer,
      //VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_HOST_BIT,
      VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
      0, 0, nullptr, 0, nullptr, 1, &ImageMemoryBarrier1);
 
    // Copy buffer to image
    VkBufferImageCopy Region
    {
      .bufferOffset = 0,
      .bufferRowLength = (UINT)W,
      .bufferImageHeight = (UINT)H,
      .imageSubresource
      {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .mipLevel = 0,
        .baseArrayLayer = 0,
        .layerCount = IsCube ? 6U : 1U,
      },
      .imageOffset {.x = 0, .y = 0, .z = 0},
      .imageExtent {.width = (UINT)W, .height = (UINT)H, .depth = 1},
    };
    vkCmdCopyBufferToImage(TransferCommandBuffer, StageBuffer[CurrentFrame], Image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &Region);
  
    // Create transfer barrier
    VkImageMemoryBarrier ImageMemoryBarrier2
    {
      .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
      .srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT, // VK_ACCESS_TRANSFER_WRITE_BIT, // VK_ACCESS_HOST_WRITE_BIT,
      .dstAccessMask = VK_ACCESS_SHADER_READ_BIT, // 0,
      .oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL,
      .newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
      .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
      .image = Image,
      .subresourceRange
      {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .baseMipLevel = 0,
        .levelCount = MipCount,
        .baseArrayLayer = 0,
        .layerCount = 1,
      },
    };
    vkCmdPipelineBarrier(TransferCommandBuffer,
      // VK_PIPELINE_STAGE_HOST_BIT, VK_PIPELINE_STAGE_HOST_BIT, 0, //VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
      VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
      0, 0, nullptr, 0, nullptr, 1, &ImageMemoryBarrier2);
 
    vkEndCommandBuffer(TransferCommandBuffer);
    VkPipelineStageFlags PipelineStageFlags[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
    VkSubmitInfo SubmitInfo
    {
      .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
      .waitSemaphoreCount = 0,
      .pWaitDstStageMask = PipelineStageFlags,
      .commandBufferCount = 1,
      .pCommandBuffers = &TransferCommandBuffer,
    };
    ///vkWaitForFences(Device, 1, &TransferFence, VK_TRUE, UINT64_MAX);
    vkResetFences(Device, 1, &TransferFence);
    vkQueueSubmit(TransferQueue, 1, &SubmitInfo, TransferFence);
    //vkQueueWaitIdle(TransferQueue);
    vkWaitForFences(Device, 1, &TransferFence, VK_TRUE, UINT64_MAX);
 
    ImageGenerateMipmaps(Image, W, H, MipCount, Format, IsCube);
 
    // vkDestroyBuffer(Device, Buffer, nullptr);
    // vkFreeMemory(Device, BufferMemory, nullptr);
  }
  return TRUE;
} /* End of 'ImageCreate' function */
 
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
VOID arvk::VlkImage::ImageFree( VkImage &Image, VkImageView &ImageView, VmaAllocation &Allocation )
{
  if (ImageView != VK_NULL_HANDLE)
    vkDestroyImageView(Device, ImageView, nullptr);
  vmaDestroyImage(Allocator, Image, Allocation);
 
  ImageView = VK_NULL_HANDLE;
  Image = VK_NULL_HANDLE;
  /// Memory =  = VK_NULL_HANDLE;
  Allocation = VK_NULL_HANDLE;
} /* End of 'ImageFree' function */
 
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
VOID arvk::VlkImage::ImageSetLayout( VkImage Image,
                                VkImageLayout OldImageLayout, VkImageLayout NewImageLayout,
                                VkImageSubresourceRange SubresourceRange,
                                VkPipelineStageFlags SrcStageMask, VkPipelineStageFlags DstStageMask )
{
  // Create an Image ImageMemoryBarrier object
  VkImageMemoryBarrier ImageMemoryBarrier
  {
    .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
    .oldLayout = OldImageLayout,
    .newLayout = NewImageLayout,
    .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED, // SelectedGraphicsQueueFamilyIndex,
    .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED, // SelectedTransferQueueFamilyIndex,
    .image = Image,
    .subresourceRange = SubresourceRange,
  };
 
  VkPipelineStageFlags PipelineStageFlags = 0;
 
  if (NewImageLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL)
  {
    ImageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    ImageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    PipelineStageFlags = VK_PIPELINE_STAGE_TRANSFER_BIT;
  }
 
  else if(NewImageLayout == VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL)
  {
    ImageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
    ImageMemoryBarrier.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
    PipelineStageFlags = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  }
 
  else if(NewImageLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL)
  {
    ImageMemoryBarrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT; // | (Format == VK_FORMAT_D32_SFLOAT_S8_UINT || Format == VK_FORMAT_D24_UNORM_S8_UINT ? VK_IMAGE_ASPECT_STENCIL_BIT : 0);
    ImageMemoryBarrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
    PipelineStageFlags = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT;
  }
 
  // Put ImageMemoryBarrier inside setup command buffer
  vkCmdPipelineBarrier(TransferCommandBuffer, SrcStageMask, DstStageMask, 0, 0, nullptr, 0, nullptr, 1, &ImageMemoryBarrier);
} /* End of 'ImageSetLayout' function */
 
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
VOID arvk::VlkImage::ImageSetLayout( VkImage Image,
                                VkImageAspectFlags AspectMask,
                                VkImageLayout OldImageLayout, VkImageLayout NewImageLayout,
                                VkPipelineStageFlags SrcStageMask, VkPipelineStageFlags DstStageMask )
{
  VkImageSubresourceRange SubresourceRange = {};
  SubresourceRange.aspectMask = AspectMask;
  SubresourceRange.baseMipLevel = 0;
  SubresourceRange.levelCount = 1;
  SubresourceRange.layerCount = 1;
  ImageSetLayout(Image, OldImageLayout, NewImageLayout, SubresourceRange, SrcStageMask, DstStageMask);
} /* End of 'ImageSetLayout' function */
 

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
VOID arvk::VlkImage::ImageGenerateMipmaps( VkImage Image, INT W, INT H, UINT Levels, VkFormat Format, BOOL IsCube )
{
  if (Levels == 1)
    return;
  VkFormatProperties formatProperties;
  vkGetPhysicalDeviceFormatProperties(PhysDevice, Format, &formatProperties);
 
  // Copy through command buffer
  VkCommandBufferBeginInfo CommandBufferBeginInfo
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
  };
  vkBeginCommandBuffer(TransferCommandBuffer, &CommandBufferBeginInfo);
 
  VkImageMemoryBarrier ImageMemoryBarrier
  {
    .sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER,
    .srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
    .dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED,
    .image = Image,
    .subresourceRange
    {
      .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
      .baseMipLevel = 0,
      .levelCount = 1,
      .baseArrayLayer = 0,
      .layerCount = IsCube ? 6U : 1U,
    },
  };
 
  ImageMemoryBarrier.subresourceRange.baseMipLevel = 0;
  ImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, // VK_IMAGE_LAYOUT_UNDEFINED;
  ImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
  ImageMemoryBarrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT; // VK_ACCESS_TRANSFER_READ_BIT;
  ImageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
  vkCmdPipelineBarrier(TransferCommandBuffer,
    // VK_PIPELINE_STAGE_TRANSFER_BIT/*VK_PIPELINE_STAGE_HOST_BIT*/, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, //VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
    //VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
    /// VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
    VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
    0, 0, nullptr, 0, nullptr, 1, &ImageMemoryBarrier);
 
  for (UINT MipLevel = 1; MipLevel < Levels; MipLevel++)
  {
    ImageMemoryBarrier.subresourceRange.baseMipLevel = MipLevel;
    ImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    ImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    ImageMemoryBarrier.srcAccessMask = VK_ACCESS_SHADER_READ_BIT;
    ImageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    vkCmdPipelineBarrier(TransferCommandBuffer,
      // VK_PIPELINE_STAGE_TRANSFER_BIT/*VK_PIPELINE_STAGE_HOST_BIT*/, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, //VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
      VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
      0, 0, nullptr, 0, nullptr, 1, &ImageMemoryBarrier);
  }
 
  INT MipWidth = W, MipHeight = H;

  for (UINT MipLevel = 1; MipLevel < Levels; MipLevel++)
  {
    ImageMemoryBarrier.subresourceRange.baseMipLevel = MipLevel - 1;
    ImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    ImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    ImageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    ImageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    vkCmdPipelineBarrier(TransferCommandBuffer,
      // VK_PIPELINE_STAGE_TRANSFER_BIT/*VK_PIPELINE_STAGE_HOST_BIT*/, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, //VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
      VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
      0, 0, nullptr, 0, nullptr, 1, &ImageMemoryBarrier);
 
    VkImageBlit blit
    {
      .srcSubresource
      {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .mipLevel = MipLevel - 1,
        .baseArrayLayer = 0,
        .layerCount = IsCube ? 6U : 1U,
      },
      .srcOffsets
      {
        {.x = 0, .y = 0, .z = 0},
        {.x = MipWidth, .y = MipHeight, .z = 1},
      },
      .dstSubresource
      {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .mipLevel = MipLevel,
        .baseArrayLayer = 0,
        .layerCount = IsCube ? 6U : 1U,
      },
      .dstOffsets
      {
        {.x = 0, .y = 0, .z = 0},
        {.x = MipWidth > 1 ? MipWidth / 2 : 1, .y = MipHeight > 1 ? MipHeight / 2 : 1, .z = 1},
      },
    };
    vkCmdBlitImage(TransferCommandBuffer, Image, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL,
     Image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &blit, VK_FILTER_LINEAR);
 
    ImageMemoryBarrier.subresourceRange.baseMipLevel = MipLevel - 1;
    ImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL;
    ImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    ImageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
    ImageMemoryBarrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    vkCmdPipelineBarrier(TransferCommandBuffer,
      //VK_PIPELINE_STAGE_TRANSFER_BIT/*VK_PIPELINE_STAGE_HOST_BIT*/, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, //VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
      VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, // VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
      0, 0, nullptr, 0, nullptr, 1, &ImageMemoryBarrier);
  
    if (MipWidth > 1)
      MipWidth /= 2;
    if (MipHeight > 1)
      MipHeight /= 2;
  }
 
  for (UINT MipLevel = 0; MipLevel < Levels; MipLevel++)
  {
    ImageMemoryBarrier.subresourceRange.baseMipLevel = MipLevel;
    ImageMemoryBarrier.oldLayout = VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL;
    ImageMemoryBarrier.newLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL;
    ImageMemoryBarrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
    ImageMemoryBarrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
    vkCmdPipelineBarrier(TransferCommandBuffer,
      // VK_PIPELINE_STAGE_TRANSFER_BIT/*VK_PIPELINE_STAGE_HOST_BIT*/, VK_PIPELINE_STAGE_TRANSFER_BIT, 0, //VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT,
      VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,
      0, 0, nullptr, 0, nullptr, 1, &ImageMemoryBarrier);
  }
 
  vkEndCommandBuffer(TransferCommandBuffer);
  VkPipelineStageFlags PipelineStageFlags[] = {VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT};
  VkSubmitInfo SubmitInfo
  {
    .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
    .waitSemaphoreCount = 0,
    .pWaitDstStageMask = PipelineStageFlags,
    .commandBufferCount = 1,
    .pCommandBuffers = &TransferCommandBuffer,
  };
  vkWaitForFences(Device, 1, &TransferFence, VK_TRUE, UINT64_MAX);
  vkResetFences(Device, 1, &TransferFence);
  vkQueueSubmit(TransferQueue, 1, &SubmitInfo, TransferFence);
  vkQueueWaitIdle(TransferQueue);
  vkWaitForFences(Device, 1, &TransferFence, VK_TRUE, UINT64_MAX);
} /* End of 'ImageGenerateMipmaps' function */

/* END OF 'vlk_dummy.cpp' FILE */
