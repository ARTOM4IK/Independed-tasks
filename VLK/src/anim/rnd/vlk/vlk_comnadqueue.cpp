/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_commandqueue.cpp
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

/* Get queue family indices function.
 * ARGUMENTS:
 *   - Physical device:
 *       VkPhysicalDevice &PhysDevice;
 *   - Surface:
 *       VkSurfaceKHR &Surface;
 * RETURNS:
 *   (queue_family_indices) queue family indices
 */
arvk::VlkCommandQueue::queue_family_indices arvk::VlkCommandQueue::GetQueueFamilyIndices( VkPhysicalDevice &PhysicalDevice, VkSurfaceKHR &Surface )
{
  UINT32 QueueFamilyCount = 0;

  vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyCount, nullptr);
  std::vector<VkQueueFamilyProperties> QueueFamilyProperties {QueueFamilyCount};
  vkGetPhysicalDeviceQueueFamilyProperties(PhysicalDevice, &QueueFamilyCount, QueueFamilyProperties.data());

  queue_family_indices Indices;
  BOOL IsFilledG = FALSE, IsFilledPr = FALSE, IsFilledT = FALSE;
  for (UINT32 i = 0; i < QueueFamilyCount; i++)
  {
    // Check render family queue support
    if ((QueueFamilyProperties[i].queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0 && !IsFilledG)
      Indices.GraphicsFamily = i, IsFilledG = TRUE;
      
    // Check render win out queue support
    VkBool32 PresentSupport = VK_FALSE;
    vkGetPhysicalDeviceSurfaceSupportKHR(PhysicalDevice, i, Surface, &PresentSupport);
    if (PresentSupport == VK_TRUE && !IsFilledPr)
      Indices.PresentFamily = i, IsFilledPr = TRUE;
    if ((QueueFamilyProperties[i].queueFlags & VK_QUEUE_TRANSFER_BIT) != 0 && !IsFilledT)
      Indices.TransferFamily = i, IsFilledT = TRUE;
  }

  return Indices;
} /* End of 'GetQueueFamilyIndices' function */

/* Create command queue function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 *   - Physical device:
 *       VkPhysicalDevice &PhysDevice;
 *   - Surface:
 *       VkSurfaceKHR &Surface;
 * RETURNS: None.
 */
VOID arvk::VlkCommandQueue::CreateCommandQueue( VkDevice &Device, VkPhysicalDevice &PhysicalDevice, VkSurfaceKHR &Surface )
{
  queue_family_indices Indices = GetQueueFamilyIndices(PhysicalDevice, Surface);

  vkGetDeviceQueue(Device, Indices.PresentFamily.value(), 0, &PresentQueue);
  vkGetDeviceQueue(Device, Indices.GraphicsFamily.value(), 0, &GraphicsQueue); 
  vkGetDeviceQueue(Device, Indices.TransferFamily.value(), 0, &TransferQueue); 

  VkCommandPoolCreateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO,      // Structure type.
    .flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT, // Command pool flags.
    .queueFamilyIndex = Indices.GraphicsFamily.value()        // Using family queues index.
  };

  VK_CHECK(vkCreateCommandPool(Device, &Info, nullptr, &CommandPool));
} /* End of 'CreateCommandQueue' fucntion */

/* Destroy command queue function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 * RETURNS: None.
 */
VOID arvk::VlkCommandQueue::DestroyCommandQueue( VkDevice &Device )
{
  vkDestroyCommandPool(Device, CommandPool, nullptr);
} /* End of 'DestroyCommandQueue' fucntion */

/* Create command buffer function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 * RETURNS: None.
 */
VOID arvk::VlkCommandQueue::CreateCommandBuffer( VkDevice &Device )
{
  VkCommandBufferAllocateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO, // Structure type.
    .commandPool = CommandPool,                              // Using command pool.
    .level = VK_COMMAND_BUFFER_LEVEL_PRIMARY,                // Command buffer type.
    .commandBufferCount = 1                                  // Number of allocating buffers.
  };
  for (auto &cmdbuf : CommandBuffer)
  {
    VK_CHECK(vkAllocateCommandBuffers(Device, &Info, &cmdbuf));

    VkCommandBufferBeginInfo BeginInfo
    {
      .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO, // Structure type.
      .flags = 0,                                           // Flags of buffer usage.
      .pInheritanceInfo = nullptr,                          // Buffer specializatiob (reqiuired for secondary buffers).
    };
    vkBeginCommandBuffer(cmdbuf, &BeginInfo);

    VK_CHECK(vkAllocateCommandBuffers(Device, &Info, &TransferCommandBuffer));
  }
} /* End of 'CreateCommandBuffer' fucntion */

/* END OF 'vlk_commandqueue.cpp' FILE */
