/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_context.cpp
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

/* Create context function.
 *  ARGUMENTS:
 *   - Window handle:
 *      HWND &hWnd;
 *   - Instance:
 *      VkInstance &Instance;
 * RETURNS: None.
 */
VOID arvk::VlkContext::CreateContext( HWND &hWnd, VkInstance &Instance )
{
  VkWin32SurfaceCreateInfoKHR SurfaceCreateInfo 
  {
    .sType = VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR,
    .flags = 0,
    .hinstance = GetModuleHandle(nullptr),                      // Api descriptor.
    .hwnd = hWnd,                                               // Window descriptor.
  };

  // Create surface
  VK_CHECK(vkCreateWin32SurfaceKHR(Instance, &SurfaceCreateInfo, nullptr, &Surface));
} /* End of 'CreateContext' fucntion */

/* Destroy context function.
 *  ARGUMENTS:
 *   - Instance:
 *      VkInstance &Instance;
 * RETURNS: None.
 */
VOID arvk::VlkContext::DestroyContext( VkInstance &Instance )
{
  vkDestroySurfaceKHR(Instance, Surface, nullptr);
} /* End of 'DestroyContext' fucntion */

                    
/* END OF 'vlk_context.cpp' FILE */
