/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_commandqueue.h
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

#ifndef __vlk_commandqueue_h_
#define __vlk_commandqueue_h_

#include "anim/rnd/vlk/vlk_def.h"

/* Animation namespace */
namespace arvk
{
  /* Command pool and command queue class */
  class VlkCommandQueue: public VlkPipeline
  {
  public:
    VkQueue PresentQueue = VK_NULL_HANDLE, GraphicsQueue = VK_NULL_HANDLE, TransferQueue = VK_NULL_HANDLE;
    VkCommandPool CommandPool;
    VkCommandBuffer TransferCommandBuffer;
    std::vector<VkCommandBuffer> CommandBuffer;

    struct queue_family_indices
    {
      std::optional<UINT32> GraphicsFamily;      // Render-Family queue index
      std::optional<UINT32> PresentFamily;       // Window Out-Family queue index
      std::optional<UINT32> TransferFamily;
    };

    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkCommandQueue( VOID )
    {
      CommandBuffer.resize(3);
    } /* End of 'VlkCommandQueue' fucntion */

    /* Class destructor */
    ~VlkCommandQueue( VOID )
    {
    } /* End of '~VlkCommandQueue' fucntion */

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
    VOID CreateCommandQueue( VkDevice &Device, VkPhysicalDevice &PhysicalDevice, VkSurfaceKHR &Surface );

    /* Create command buffer function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     * RETURNS: None.
     */
    VOID CreateCommandBuffer( VkDevice &Device );

    /* Destroy command queue function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     * RETURNS: None.
     */
    VOID DestroyCommandQueue( VkDevice &Device );

    /* Get queue family indices function.
     * ARGUMENTS:
     *   - Physical device:
     *       VkPhysicalDevice &PhysDevice;
     *   - Surface:
     *       VkSurfaceKHR &Surface;
     * RETURNS:
     *   (queue_family_indices) queue family indices.
     */
    queue_family_indices GetQueueFamilyIndices( VkPhysicalDevice &PhysicalDevice, VkSurfaceKHR &Surface );
  }; /* End of 'VlkCommandQueue' class */
} /* End of 'arvk' namespace */

#endif /* __vlk_commandqueue_h_ */

/* END OF 'vlk_commandqueue.h' FILE */
