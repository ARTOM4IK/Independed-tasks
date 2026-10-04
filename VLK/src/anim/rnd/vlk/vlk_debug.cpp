/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_debug.cpp
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

/* Create debug function.
 *  ARGUMENTS:
 *   - Instance:
 *      VkInstance &Instance;
 * RETURNS: None.
 */
VOID arvk::VlkDebug::CreateDebug( VkInstance &Instance )
{
  #if defined(_DEBUG)
    auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(Instance, "vkCreateDebugUtilsMessengerEXT");
    if (func != nullptr)
      func(Instance, &DebugUtilsMessengerCreateInfo, nullptr, &DebugUtilsMessenger);
    else
      throw "Can't create debug handle";
  #endif
} /* End of 'CreateDebug' fucntion */

/* Destroy debug function.
 *  ARGUMENTS:
 *   - Instance:
 *      VkInstance &Instance;
 * RETURNS: None.
 */
VOID arvk::VlkDebug::DestroyDebug( VkInstance &Instance )
{
  #if defined(_DEBUG)
    auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(Instance, "vkDestroyDebugUtilsMessengerEXT");
    if (func != nullptr)
      func(Instance, DebugUtilsMessenger, nullptr);
    else
      throw "Can't destroy debug handle";
  #endif
} /* End of 'DestroyDebug' fucntion */

/* END OF 'vlk_debug.cpp' FILE */
