/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_instance.h
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

#ifndef __vlk_instance_h_
#define __vlk_instance_h_

#include "anim/rnd/vlk/vlk_def.h"

/* Animation namespace */
namespace arvk
{
  /* Instance class */
  class VlkInstance: public VlkDebug
  {
  public:
    VkInstance Instance;
    // Memory allocator
    VmaAllocator Allocator {};                     // VMA allocator
    VmaAllocatorCreateInfo AllocatorCreateInfo {}; // Allocator creation information data

    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkInstance( VOID )
    {
    } /* End of 'VlkInstance' fucntion */

    /* Class destructor */
    ~VlkInstance( VOID )
    {
    } /* End of '~VlkInstance' fucntion */

    /* Create instance function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID CreateInstance( VOID );

    /* Destroy instance function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID DestroyInstance( VOID );
  }; /* End of 'VlkInstance' class */
} /* End of 'arvk' namespace */

#endif /* __vlk_instance_h_ */

/* END OF 'vlk_instance.h' FILE */
