/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_device.h
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

#ifndef __vlk_device_h_
#define __vlk_device_h_

#include "anim/rnd/vlk/vlk_def.h"

/* Animation namespace */
namespace arvk
{
  /* Physical and logical device class */
  class VlkDevice: public VlkInstance
  {
  public:
    VkDevice Device;
    VkPhysicalDevice PhysDevice = VK_NULL_HANDLE;

    UINT32 QueueFamilyCount;
    VkPhysicalDeviceFeatures DeviceFeatures;
    std::vector<VkQueueFamilyProperties>QueueFamilies;
    uint32_t ExtensionCount;
    std::vector<VkExtensionProperties>AvailableExtensions;

    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkDevice( VOID )
    {
    } /* End of 'VlkDevice' fucntion */

    /* Class destructor */
    ~VlkDevice( VOID )
    {
    } /* End of '~VlkDevice' fucntion */

    /* Create logical device and choose physical function.
     *  ARGUMENTS:
     *   - Instance:
     *      VkInstance &Instance;
     * RETURNS: None.
     */
    VOID CreateDevice( VkInstance &Instance );

    /* Destroy logical and physical device function.
     *  ARGUMENTS:
     *   - Instance:
     *      VkInstance &Instance;
     * RETURNS: None.
     */
    VOID DestroyDevice( VkInstance &Instance );
  }; /* End of 'VlkDevice' class */
} /* End of 'arvk' namespace */

#endif /* __vlk_device_h_ */

/* END OF 'vlk_device.h' FILE */
