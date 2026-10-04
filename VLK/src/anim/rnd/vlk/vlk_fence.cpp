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

/* Create fence function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 * RETURNS: None.
 */
VOID arvk::VlkFence::CreateFence( VkDevice &Device )
{
  VkFenceCreateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO, // Structure type.
    .flags = VK_FENCE_CREATE_SIGNALED_BIT         // Base status (or VK_FENCE_CREATE_SIGNALED_BIT).
  };

  for (auto &fence : Fence)
    VK_CHECK(vkCreateFence(Device, &Info, nullptr, &fence));
  VK_CHECK(vkCreateFence(Device, &Info, nullptr, &TransferFence));
} /* End of 'CreateFence' function */

/* Create semaphores function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 * RETURNS: None.
 */
VOID arvk::VlkFence::CreateSemaphores( VkDevice &Device )
{
  VkSemaphoreCreateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, // Structure type.
    //.flags = VK_SEMAPHORE_WAIT_ANY_BIT         // Base status (or VK_FENCE_CREATE_SIGNALED_BIT).
  };

  for (auto &sems : RenderFinishSemaphores)
    VK_CHECK(vkCreateSemaphore(Device, &Info, nullptr, &sems));
  for (auto &sems : ImageAvailableSemaphores)
    VK_CHECK(vkCreateSemaphore(Device, &Info, nullptr, &sems));
} /* End of 'CreateSemaphores' function */

/* Destroy fence function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 * RETURNS: None.
 */
VOID arvk::VlkFence::DestroyFence( VkDevice &Device )
{
  for (auto &fence : Fence)
    vkDestroyFence(Device, fence, nullptr);
  vkDestroyFence(Device, TransferFence, nullptr);
  } /* End of 'DestroyFence' function */

/* Destroy semaphores function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 * RETURNS: None.
 */
VOID arvk::VlkFence::DestroySemaphores( VkDevice &Device )
{
  for (auto &sems : RenderFinishSemaphores)
    vkDestroySemaphore(Device, sems, nullptr);
  for (auto &sems : ImageAvailableSemaphores)
    vkDestroySemaphore(Device, sems, nullptr);
} /* End of 'DestroySemaphores' function */

/* END OF 'vlk_dummy.cpp' FILE */
