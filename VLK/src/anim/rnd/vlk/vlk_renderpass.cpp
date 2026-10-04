/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_renderpass.cpp
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
VkFormat arvk::VlkRenderPass::FindDepthFormat( std::vector<VkFormat> &DepthFormats, VkImageTiling tiling, VkFormatFeatureFlags features, VkPhysicalDevice &PhysicalDevice )
{
  for (VkFormat format : DepthFormats)
  {
    VkFormatProperties props;
    vkGetPhysicalDeviceFormatProperties(PhysicalDevice, format, &props);

    if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) 
      return format;
    else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features)
      return format;
  }
  throw std::runtime_error("failed to find supported format!");
} /* End of 'FindDepthFormat' function */

/* Create render pass function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 *   - Image format:
 *       VkFormat &SwapchainImageFormat;
 * RETURNS: None.
 */
VOID arvk::VlkRenderPass::CreateRenderPass( VkDevice &Device, VkFormat &SwapchainImageFormat )
{
  VkAttachmentDescription AttachmentDescription[2];
  std::vector<VkFormat> DepthFormats = {VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT};
  VkFormat Format = FindDepthFormat(DepthFormats, VK_IMAGE_TILING_OPTIMAL, VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT, PhysDevice);

  /* G-Buffer. */
  AttachmentDescription[0] = 
  {
    .flags = 0,                                         // Flags.
    .format = SwapchainImageFormat,                     // Attachment image format.
    .samples = VK_SAMPLE_COUNT_1_BIT,                   // Multisampling.
    .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,              // Beggining of subpasses.
    .storeOp = VK_ATTACHMENT_STORE_OP_STORE,            // Try to write.
    .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,   // Same as Stencil Buffers.
    .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,  
    .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,         // Image layout in the beggining of rendering.
    .finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,     // Image layout in the end of rendering.
  };

  /* Z-Buffer. */
  AttachmentDescription[1] = 
  {
    .flags = 0,                                         // Flags.
    .format = Format,                                   // Attachment image format.
    .samples = VK_SAMPLE_COUNT_1_BIT,                   // Multisampling.
    .loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR,              // Beggining of subpasses.
    .storeOp = VK_ATTACHMENT_STORE_OP_STORE,            // Try to write.
    .stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE,   // Same as Stencil Buffers.
    .stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE,  
    .initialLayout = VK_IMAGE_LAYOUT_UNDEFINED,         // Image layout in the beggining of rendering.
    .finalLayout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,     // Image layout in the end of rendering.
  };

  VkAttachmentReference DepthReference
  {
    .attachment = 1,
    .layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
  };

  VkAttachmentReference ColorAttachmentReference[6];

  /* G-Buffer information and its status while subpass */
  ColorAttachmentReference[0] = 
  {
    .attachment = 0,                                    // Attachment index in general list.
    .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, // Layout images of attachment while rendering.
  };
  ColorAttachmentReference[1] = 
  {
    .attachment = 0,                                    // Attachment index in general list.
    .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, // Layout images of attachment while rendering.
  };
  ColorAttachmentReference[2] = 
  {
    .attachment = 0,                                    // Attachment index in general list.
    .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, // Layout images of attachment while rendering.
  };
  ColorAttachmentReference[3] = 
  {
    .attachment = 0,                                    // Attachment index in general list.
    .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, // Layout images of attachment while rendering.
  };
  ColorAttachmentReference[4] = 
  {
    .attachment = 0,                                    // Attachment index in general list.
    .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, // Layout images of attachment while rendering.
  };
  ColorAttachmentReference[5] = 
  {
    .attachment = 0,                                    // Attachment index in general list.
    .layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, // Layout images of attachment while rendering.
  };
  
  /* One pass information */
  VkSubpassDescription SubpassDescription
  {
    .flags = 0,                                           // Flags.
    .pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS, // Pipeline type that subpass uses.
    .inputAttachmentCount = 0,                            // Number of in attachments.
    .pInputAttachments = nullptr,                         // Their VkAttachmentReference[].
    .colorAttachmentCount = 6,                            // Number of out attachments.
    .pColorAttachments = ColorAttachmentReference,       // Their VkAttachmentReference[].
    .pResolveAttachments = nullptr,                       // Attachments for multisampling.
    .pDepthStencilAttachment = &DepthReference,                   // Depthbuffer Reference that is now in render.

    .preserveAttachmentCount = 0,                         // Attachments that don't use rn, but are needed to be saved
    .pPreserveAttachments = nullptr,
  };
  
  /* Transition betweem subpasses information */
  VkSubpassDependency SubpassDependency
  {
    .srcSubpass = VK_SUBPASS_EXTERNAL,                             // Index to transit.
                                                                   // VK_SUBPASS_EXTERNAL means that srcSubpass,

    .dstSubpass = 0,                                               // Subpass index to transit in.
    .srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, // All Pipeline status in srcSubpass (aftar that goes dstSubpass).
    .dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, // Status to get access from dstAccessMask.
    .srcAccessMask = 0,                                            // Access to G-Buffer in srcSubpass.
    .dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,         // Access to G-Buffer in dstSubpass.
    .dependencyFlags = 0,                                          // flags
  };

  /* Renderpass general information */
  VkRenderPassCreateInfo CreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO, // Structure type.
    .pNext = nullptr,                                   // Pointer to structure extention.
    .flags = 0,                                         // Flags.
    .attachmentCount = 2,                               // Number of color attachments in renderpass.
    .pAttachments = AttachmentDescription,              // Their descriptions.
    .subpassCount = 1,                                  // Number of subpasses.
    .pSubpasses = &SubpassDescription,                  // Desriptions of transitions.
    .dependencyCount = 1,                               // Number of transitions by subpass.
    .pDependencies = &SubpassDependency,                // Their descriptions.
  };

  VK_CHECK(vkCreateRenderPass(Device, &CreateInfo, nullptr, &RenderPass))
} /* End of 'CreateRenderPass' fucntion */

/* Destroy render pass function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 * RETURNS: None.
 */
VOID arvk::VlkRenderPass::DestroyRenderPas( VkDevice &Device )
{
  vkDestroyRenderPass(Device, RenderPass, nullptr); 
} /* End of 'DestroyRenderPas' fucntion */

/* END OF 'vlk_renderpass.cpp' FILE */
