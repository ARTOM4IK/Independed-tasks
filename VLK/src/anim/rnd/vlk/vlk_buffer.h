/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_buffer.h
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

#ifndef __vlk_buffer_h_
#define __vlk_buffer_h_

#include "anim/rnd/vlk/vlk_def.h"

/* Animation namespace */
namespace arvk
{
  /* Vulkan dummy class */
  class VlkBuffer: public VlkCommandQueue
  {
  public:
    VkBuffer Buffer;
    VkDeviceMemory Memory;
    BYTE SizeOfBufferData;
    VmaAllocation Allocation{}; // VMA buffer allocation info

    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkBuffer( VOID )
    {
    } /* End of 'VlkBuffer' function */

    /* Class destructor */
    ~VlkBuffer( VOID )
    {
    } /* End of '~VlkBuffer' function */

    /* Create buffer function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     *   - Physical device:
     *       VkPhysicalDevice &PhysDevice;
     *   - Size:
     *       BYTE Size;
     *   - Flag:
     *       VkBufferUsageFlags Flag;
     *   - Sharing mode:
     *       VkSharingMode SharingMode;
     * RETURNS: None.
     */
    VOID CreateBuffer( VkDevice &Device, VkPhysicalDevice &PhysDevice, BYTE Size, VkBufferUsageFlags Flag, VkSharingMode SharingMode );

    /* Destroy buffer function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     * RETURNS: None.
     */
    VOID DestroyBuffer( VkDevice &Device );

    /* Allocate memory for buffer function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     *   - Physical device:
     *       VkPhysicalDevice &PhysDevice;
     * RETURNS: None.
     */
    VOID AllocBufferMemory( VkDevice &Device, VkPhysicalDevice &PhysDevice );

    /* Write data in buffer function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     *   - Physical device:
     *       VkPhysicalDevice &PhysDevice;
     *   - Size:
     *       BYTE Size;
     *   - Data:
     *       VOID *Data;
     * RETURNS: None.
     */
    VOID BufferWrite( VkDevice &Device, VkPhysicalDevice &PhysDevice, BYTE Size, VOID *Data );

    /* Read data in buffer function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     *   - Physical device:
     *       VkPhysicalDevice &PhysDevice;
     *   - Size:
     *       BYTE Size;
     * RETURNS: None.
     */
    VOID BufferRead( VkDevice &Device, VkPhysicalDevice &PhysDevice, BYTE &Size );

    /* Create buffer function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     *   - Physical device:
     *       VkPhysicalDevice &PhysDevice;
     *   - Size:
     *       BYTE Size;
     *   - Flag:
     *       VkBufferUsageFlags Flag;
     *   - Sharing mode:
     *       VkSharingMode SharingMode;
     * RETURNS: None.
     */
    VOID BufferCreate( VkBuffer &Buffer, VmaAllocation &Allocation, VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties );

    /* Vulkan buffer update through transfer queue function.
     * ARGUMENTS:
     *   - vulkan buffer handle:
     *       VkBuffer Buffer; 
     *   - buffer update offset and size in bytes:
     *       UINT Offset, Size;
     *   - buffer data pointer:
     *       const VOID *Data;
     * RETURNS: None.
     */
    VOID BufferUpdate( VkBuffer Buffer, UINT Offset, UINT Size, VOID *Data );

    /* Vulkan buffer free function.
     * ARGUMENTS:
     *   - vulkan buffer handle output reference:
     *       VkBuffer &Buffer;
     *   // - vulkan buffer memory handle output reference:
     *   //     VkDeviceMemory &BufferMemory;
     *   - VMA buffer allocation handle output reference:
     *       VmaAllocation &Allocation;
     * RETURNS: None.
     */
    VOID BufferFree( VkBuffer &Buffer, VmaAllocation &Allocation );

    /* Vulkan stage buffer update function.
     * ARGUMENTS:
     *   - stage buffer update offset and size in bytes:
     *       UINT Offset, Size;
     *   - stage buffer data pointer:
     *       const VOID *Data;
     * RETURNS: None.
     */
    VOID StageBufferUpdate( UINT Offset, UINT Size, VOID *Data, INT Index );

    /* Vulkan buffer update through graphics queue function.
     * ARGUMENTS:
     *   - vulkan buffer handle:
     *       VkBuffer Buffer; 
     *   - buffer update offset and size in bytes:
     *       UINT Offset, Size;
     *   - buffer data pointer:
     *       const VOID *Data;
     * RETURNS: None.
     */
    VOID BufferUpdateGraphics( VkBuffer Buffer, UINT Offset, UINT Size, VOID *Data, INT Index );
  }; /* End of 'VlkBuffer' class*/
} /* End of 'arvk' namespace */

#endif /* __vlk_buffer_h_ */

/* END OF 'vlk_buffer.h' FILE */
