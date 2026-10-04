/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_swapchain.cpp
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
VOID arvk::VlkSwapchain::CreateSwapchain( VkDevice &Device, VkPhysicalDevice &PhysDevice, VkSurfaceKHR &Surface, INT &FrameW, INT &FrameH )
{
  VkSurfaceCapabilitiesKHR SurfaceCapabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysDevice, Surface, &SurfaceCapabilities);
  ClampedW = min(SurfaceCapabilities.maxImageExtent.width, max(FrameW, SurfaceCapabilities.minImageExtent.width)), ClampedH = min(SurfaceCapabilities.maxImageExtent.height, max(FrameH, SurfaceCapabilities.minImageExtent.height));

  VkSwapchainCreateInfoKHR SwapchainCreateInfo 
  {
    .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
    .flags = 0,
    .surface = Surface,
    .minImageCount = 3,                                          // Minimum images required for swapchain.    
    .imageFormat = VK_FORMAT_B8G8R8A8_SRGB,                      // Image color parametrs.
    .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,        // Using color space, 
    
    .imageExtent = VkExtent2D(ClampedW, ClampedH),                                  

    .imageArrayLayers = 1,                               // Layers count.
    
    .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,   // How to use swapchain (now as a color)
    
    .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,       // This swapchain can be used by 1 family queue. 
                                                         // (To be used > 1 family queue use VK_SHARING_MODE_CONCURRENT, 
                                                         // Next fields should have information about family queues).
    .queueFamilyIndexCount = 0,
    .pQueueFamilyIndices = nullptr,
    
    .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,  // Image transformation.

    .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,    // Alpha channel (now it's ignoring).
    .presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR,           // Interaction format with commands (now - "First In, First Out").
    .clipped = VK_TRUE,                                     // If VK_TRUE then colores of another window are ignored
    .oldSwapchain = VK_NULL_HANDLE,                         // Last swapchain. 
  };

  std::vector<VkPresentModeKHR> PresentModes;
  UINT32 ModesCount;
  vkGetPhysicalDeviceSurfacePresentModesKHR(PhysDevice, Surface, &ModesCount, nullptr);
  PresentModes.resize(ModesCount);
  vkGetPhysicalDeviceSurfacePresentModesKHR(PhysDevice, Surface, &ModesCount, PresentModes.data());  

  std::vector<VkSurfaceFormatKHR> SurfaceFormats;
  UINT32 FormatsCount;
  vkGetPhysicalDeviceSurfaceFormatsKHR(PhysDevice, Surface, &FormatsCount, nullptr);  
  SurfaceFormats.resize(FormatsCount);
  vkGetPhysicalDeviceSurfaceFormatsKHR(PhysDevice, Surface, &FormatsCount, SurfaceFormats.data());  

  // Create swapchain
  VK_CHECK(vkCreateSwapchainKHR(Device, &SwapchainCreateInfo, nullptr, &Swapchain));

  // Get image from swapchain
  std::vector<VkImage> SwapchainImages;
  UINT32 SwapchainImagesCount;
  VK_CHECK(vkGetSwapchainImagesKHR(Device, Swapchain, &SwapchainImagesCount, nullptr));
  
  SwapchainImages.resize(SwapchainImagesCount);
  SwapchainImageViews.resize(SwapchainImagesCount);
  VK_CHECK(vkGetSwapchainImagesKHR(Device, Swapchain, &SwapchainImagesCount, &SwapchainImages[0]));

  for (INT i = 0; i < SwapchainImages.size(); i++) 
  {
    VkImageViewCreateInfo ImageViewCreateInfo 
    {
      .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
      .image = SwapchainImages[i],
      
      .viewType = VK_IMAGE_VIEW_TYPE_2D,
      .format = VK_FORMAT_B8G8R8A8_SRGB,
      .components =
      {
        .r = VK_COMPONENT_SWIZZLE_IDENTITY,
        .g = VK_COMPONENT_SWIZZLE_IDENTITY,
        .b = VK_COMPONENT_SWIZZLE_IDENTITY,
        .a = VK_COMPONENT_SWIZZLE_IDENTITY,
      },
  
      // Plan of image usage.
      .subresourceRange =
      {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .baseMipLevel = 0,
        .levelCount = 1,
        .baseArrayLayer = 0,
        .layerCount = 1,
      },
    };
  
    // Create image views
    VK_CHECK(vkCreateImageView(Device, &ImageViewCreateInfo, nullptr, &SwapchainImageViews[i]));
  }
} /* End of 'CreateSwapchain' fucntion */

/* Destroy swapchain function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 * RETURNS: None.
 */
VOID arvk::VlkSwapchain::DestroySwapchain( VkDevice &Device )
{
  for (INT i = 0; i < SwapchainImageViews.size(); i++) 
    vkDestroyImageView(Device, SwapchainImageViews[i], nullptr);

  vkDestroySwapchainKHR(Device, Swapchain, nullptr);
} /* End of 'DestroySwapchain' fucntion */

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
 *   - RenderPass:
 *       VkRenderPass &RenderPass;
 * RETURNS: None.
 */
VOID arvk::VlkSwapchain::ResizeSwapchain( VkPhysicalDevice &PhysDevice, VkDevice &Device, VkSurfaceKHR &Surface, INT &FrameW, INT &FrameH, VkRenderPass &RenderPass )
{
  VkSurfaceCapabilitiesKHR SurfaceCapabilities;
  vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysDevice, Surface, &SurfaceCapabilities);

  if (min(SurfaceCapabilities.maxImageExtent.width, max(FrameW, SurfaceCapabilities.minImageExtent.width)) == 0 || min(SurfaceCapabilities.maxImageExtent.height, max(FrameH, SurfaceCapabilities.minImageExtent.height)) == 0)
    return;

  VkSwapchainKHR OldSwapChain = Swapchain;
  vkDeviceWaitIdle(Device);

  for (VkFramebuffer FrameBuffer : FrameBuffers)
    vkDestroyFramebuffer(Device, FrameBuffer, nullptr);
  
  for (INT i = 0; i < SwapchainImageViews.size(); i++)
    vkDestroyImageView(Device, SwapchainImageViews[i], nullptr);

  //Create new swapchain
  //VkSurfaceCapabilitiesKHR SurfaceCapabilities;
  //vkGetPhysicalDeviceSurfaceCapabilitiesKHR(PhysDevice, Surface, &SurfaceCapabilities);

  if (min(SurfaceCapabilities.maxImageExtent.width, max(FrameW, SurfaceCapabilities.minImageExtent.width)) != 0 || min(SurfaceCapabilities.maxImageExtent.height, max(FrameH, SurfaceCapabilities.minImageExtent.height)) != 0)
    ClampedW = min(SurfaceCapabilities.maxImageExtent.width, max(FrameW, SurfaceCapabilities.minImageExtent.width)), ClampedH = min(SurfaceCapabilities.maxImageExtent.height, max(FrameH, SurfaceCapabilities.minImageExtent.height));

  VkSwapchainCreateInfoKHR SwapchainCreateInfo 
  {
    .sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR,
    .flags = 0,
    .surface = Surface,
    .minImageCount = 2,                                          // Minimum images required for swapchain.    
    .imageFormat = VK_FORMAT_B8G8R8A8_SRGB,                      // Image color parametrs.
    .imageColorSpace = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR,        // Using color space, 
    
    .imageExtent = VkExtent2D(ClampedW, ClampedH),                                  

    .imageArrayLayers = 1,                               // Layers count.
    
    .imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,   // How to use image in swapchain
    
    .imageSharingMode = VK_SHARING_MODE_EXCLUSIVE,       // This swapchain can be used by 1 family queue. 
                                                         // (To be used > 1 family queue use VK_SHARING_MODE_CONCURRENT, 
                                                         // Next fields should have information about family queues).
    .queueFamilyIndexCount = 0,
    .pQueueFamilyIndices = nullptr,
    
    .preTransform = VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR,  // Image transformation.

    .compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,    // Alpha channel (now it's ignoring).
    .presentMode = VK_PRESENT_MODE_IMMEDIATE_KHR,           // Interaction format with commands (now - "First In, First Out").
    .clipped = VK_TRUE,                                     // If VK_TRUE then colores of another window are ignored
    .oldSwapchain = OldSwapChain,                           // Last swapchain. 
  };

  std::vector<VkPresentModeKHR> PresentModes;
  UINT32 ModesCount;
  vkGetPhysicalDeviceSurfacePresentModesKHR(PhysDevice, Surface, &ModesCount, nullptr);
  PresentModes.resize(ModesCount);
  vkGetPhysicalDeviceSurfacePresentModesKHR(PhysDevice, Surface, &ModesCount, PresentModes.data());  

  std::vector<VkSurfaceFormatKHR> SurfaceFormats;
  UINT32 FormatsCount;
  vkGetPhysicalDeviceSurfaceFormatsKHR(PhysDevice, Surface, &FormatsCount, nullptr);  
  SurfaceFormats.resize(FormatsCount);
  vkGetPhysicalDeviceSurfaceFormatsKHR(PhysDevice, Surface, &FormatsCount, SurfaceFormats.data());  

  // Create swapchain
  VK_CHECK(vkCreateSwapchainKHR(Device, &SwapchainCreateInfo, nullptr, &Swapchain));

  //Create new resources
  // Get image from swapchain
  std::vector<VkImage> SwapchainImages;
  UINT32 SwapchainImagesCount;
  VK_CHECK(vkGetSwapchainImagesKHR(Device, Swapchain, &SwapchainImagesCount, nullptr));
  
  SwapchainImages.resize(SwapchainImagesCount);
  SwapchainImageViews.resize(SwapchainImagesCount);
  VK_CHECK(vkGetSwapchainImagesKHR(Device, Swapchain, &SwapchainImagesCount, &SwapchainImages[0]));

  for (INT i = 0; i < SwapchainImages.size(); i++) 
  {
    VkImageViewCreateInfo ImageViewCreateInfo 
    {
      .sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
      .image = SwapchainImages[i],
      
      .viewType = VK_IMAGE_VIEW_TYPE_2D,
      .format = VK_FORMAT_B8G8R8A8_SRGB,
      .components =
      {
        .r = VK_COMPONENT_SWIZZLE_IDENTITY,
        .g = VK_COMPONENT_SWIZZLE_IDENTITY,
        .b = VK_COMPONENT_SWIZZLE_IDENTITY,
        .a = VK_COMPONENT_SWIZZLE_IDENTITY,
      },
  
      // Plan of image usage.
      .subresourceRange =
      {
        .aspectMask = VK_IMAGE_ASPECT_COLOR_BIT,
        .baseMipLevel = 0,
        .levelCount = 1,
        .baseArrayLayer = 0,
        .layerCount = 1,
      },
    };
  
    // Create image views
    VK_CHECK(vkCreateImageView(Device, &ImageViewCreateInfo, nullptr, &SwapchainImageViews[i]));
  }

  CreateFrameBuffer(Device, RenderPass, SwapchainImageViews, ClampedW, ClampedH);

  //Destroy old swapchain
  vkDestroySwapchainKHR(Device, OldSwapChain, nullptr);
} /* End of 'ResizeSwapchain' fucntion */

/* END OF 'vlk_swapchain.cpp' FILE */
