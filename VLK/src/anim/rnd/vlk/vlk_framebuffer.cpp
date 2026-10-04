/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_framebuffer.cpp
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
VOID arvk::VlkFrameBuffer::CreateFrameBuffer( VkDevice &Device, VkRenderPass &RenderPass, std::vector<VkImageView> &SwapchainImageViews, INT &W, INT &H )
{
  std::vector<VkFormat> DepthFormats = {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT};
  VkFormat Format = FindDepthFormat(DepthFormats, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT, PhysDevice);

  // Create frame buffer
  FrameBuffers.resize(SwapchainImageViews.size());

  VkImageCreateInfo ImageCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0,
    .imageType = VK_IMAGE_TYPE_2D,
    .format = Format,
    .extent = {.width = UINT(W), .height = UINT(H), .depth = 1},
    .mipLevels = 1,
    .arrayLayers = 1,
    .samples = VK_SAMPLE_COUNT_1_BIT,
    .tiling = VK_IMAGE_TILING_OPTIMAL,
    .usage = VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
    .sharingMode = VK_SHARING_MODE_EXCLUSIVE,
    .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED/*VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL*/,
  };
 
  // Create image through VMA
  VmaAllocationCreateInfo AllocationCreateInfo {};
  AllocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
  AllocationCreateInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  AllocationCreateInfo.flags = 0;
  AllocationCreateInfo.priority = 1.0f;
  VK_CHECK(vmaCreateImage(Allocator, &ImageCreateInfo, &AllocationCreateInfo, &DepthImage, &Allocation, nullptr));

  // Create vulkan image
  VkImageViewCreateInfo ImageViewCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
    .pNext = nullptr,
    .flags = 0,
    .image = DepthImage,
    .viewType = VK_IMAGE_VIEW_TYPE_2D,
    .format = Format,
    .components = {VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY, VK_COMPONENT_SWIZZLE_IDENTITY},
    .subresourceRange = {VK_IMAGE_ASPECT_DEPTH_BIT, 0, 1, 0, 1},
  };

  vkCreateImageView(Device, &ImageViewCreateInfo, nullptr, &DepthImageView);

  for (INT i = 0; i < SwapchainImageViews.size(); i++)
  {

    std::array<VkImageView, 2> Attachments = {SwapchainImageViews[i], DepthImageView};
    VkFramebufferCreateInfo FrameBufferCreateInfo
    {
      .sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO,
      .renderPass = RenderPass,
      .attachmentCount = UINT32(2/*Attachments.size()*/),
      .pAttachments = Attachments.data(),
      .width = UINT32(W),
      .height = UINT32(H),
      .layers = 1,                                                   // Number of layers of drawing buffer.
    };
  
    VK_CHECK(vkCreateFramebuffer(Device, &FrameBufferCreateInfo, nullptr, &FrameBuffers[i]))
  }
} /* End of 'CreateFrameBuffer' fucntion */

/* Destroy frame buffer function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 * RETURNS: None.
 */
VOID arvk::VlkFrameBuffer::DestroyFrameBuffer( VkDevice &Device )
{
  for (VkFramebuffer FrameBuffer : FrameBuffers)
    vkDestroyFramebuffer(Device, FrameBuffer, nullptr);

  vkDestroyImageView(Device, DepthImageView, nullptr);
  vmaDestroyImage(Allocator, DepthImage, Allocation);
} /* End of 'DestroyFrameBuffer' fucntion */

/* END OF 'vlk_framebuffer.cpp' FILE */
