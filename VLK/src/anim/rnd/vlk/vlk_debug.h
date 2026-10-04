/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_debug.h
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

#ifndef __vlk_debug_h_
#define __vlk_debug_h_

#include "anim/rnd/vlk/vlk_def.h"

 /* Animation namespace */
namespace arvk
{
  /* Debug class */
  class VlkDebug
  {
  public:
    VkDebugUtilsMessengerCreateInfoEXT DebugUtilsMessengerCreateInfo
    {
       .sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT,
       .messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT |
                          VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | 
                          VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT |
                          VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT,
       .messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT |
                      VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT |
                      VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT,
      .pfnUserCallback =
         []( VkDebugUtilsMessageSeverityFlagBitsEXT MessageSeverity, 
             VkDebugUtilsMessageTypeFlagsEXT MessageTypes, 
             const VkDebugUtilsMessengerCallbackDataEXT* CallBackData,
             VOID *UserData ) -> VkBool32
        {
          std::string Res = "DEBUG REPORT: (";
          std::cout << Res;

          if ((MessageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) != 0)
          {
            Res += "INFO", std::cout << "\033[44;37m" << "INFO" << "\033[0m";
            Res += ")";
            Res += CallBackData->pMessage;
            Res += "\n";
            std::cout << ")" << "\033[34m" << CallBackData->pMessage << "\033[0m" << std::endl;
          }
          if ((MessageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) != 0)
          {
            Res += "WARNING", std::cout << "\033[43;37m" << "WARNING" << "\033[0m";
            Res += ")";
            Res += CallBackData->pMessage;
            Res += "\n";
            std::cout << ")" << "\033[33m" << CallBackData->pMessage << "\033[0m" << std::endl;
          }
          if ((MessageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) != 0)
          {
            Res += "ERROR", std::cout << "\033[41;37m" << "ERROR" << "\033[0m";
            Res += ")";
            Res += CallBackData->pMessage;
            Res += "\n";
            std::cout << ")" << "\033[31m" << CallBackData->pMessage << "\033[0m" << std::endl;
          }
          return VK_FALSE;
        },

       .pUserData = nullptr
    };
    VkDebugUtilsMessengerEXT DebugUtilsMessenger;

    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkDebug( VOID )
    {
    } /* End of 'VlkDebug' fucntion */

    /* Class destructor */
    ~VlkDebug( VOID )
    {
    } /* End of '~VlkDebug' fucntion */

    /* Create debug function.
     *  ARGUMENTS:
     *   - Instance:
     *      VkInstance &Instance;
     * RETURNS: None.
     */
    VOID CreateDebug( VkInstance &Instance );

    /* Destroy debug function.
     *  ARGUMENTS:
     *   - Instance:
     *      VkInstance &Instance;
     * RETURNS: None.
     */
    VOID DestroyDebug( VkInstance &Instance );
  }; /* End of 'VlkDebug' class */
} /* End of 'arvk' namespace */

#endif /* __vlk_debug_h_ */

/* END OF 'vlk_debug.h' FILE */
