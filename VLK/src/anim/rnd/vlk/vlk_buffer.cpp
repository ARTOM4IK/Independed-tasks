/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_buffer.cpp
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

/* Allocate memory for buffer function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 *   - Physical device:
 *       VkPhysicalDevice &PhysDevice;
 * RETURNS: None.
 */
VOID arvk::VlkBuffer::AllocBufferMemory( VkDevice &Device, VkPhysicalDevice &PhysDevice )
{
  VkMemoryRequirements MemoryRequirments;
  vkGetBufferMemoryRequirements(Device, Buffer, &MemoryRequirments);
  
  VkPhysicalDeviceMemoryProperties PhysicalDeviceMemoryProperties;
  vkGetPhysicalDeviceMemoryProperties(PhysDevice, &PhysicalDeviceMemoryProperties);
  
  UINT32 MemoryTypeIndex = -1;

  for (UINT32 i = 0; i < PhysicalDeviceMemoryProperties.memoryTypeCount; i++)
    if ((MemoryRequirments.memoryTypeBits & (1 << i)) && (PhysicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
    {
        MemoryTypeIndex = i;
        break; 
    }

  if (MemoryTypeIndex == -1)
    throw std::runtime_error("Memory type index is not found");

  VkMemoryAllocateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO, // Structure type.
    .allocationSize = MemoryRequirments.size,        // Memory size.
    .memoryTypeIndex = MemoryTypeIndex               // Memory type index
  };

  vkAllocateMemory(Device, &Info, nullptr, &Memory);
} /* End of 'AllocBufferMemory' function */

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
VOID arvk::VlkBuffer::CreateBuffer( VkDevice &Device, VkPhysicalDevice &PhysDevice, BYTE Size, VkBufferUsageFlags Flag, VkSharingMode SharingMode )
{
  VkBufferCreateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, // Structure type.
    .size = Size,                                  // Size in bytes.
    .usage = Flag,                                 // Bit mask for buffer usage.
    .sharingMode = SharingMode,                    // Using type if family queues call 
  };
  SizeOfBufferData = Size;

  vkCreateBuffer(Device, &Info, nullptr, &Buffer);
  AllocBufferMemory(Device, PhysDevice);
  vkBindBufferMemory(Device, Buffer, Memory, 0);

  // Create buffer through VMA
  //VmaAllocationCreateInfo AllocationCreateInfo{};
  //AllocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
  //AllocationCreateInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
  //AllocationCreateInfo.flags =
  //    VMA_ALLOCATION_CREATE_HOST_ACCESS_ALLOW_TRANSFER_INSTEAD_BIT |
  //    VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;
  //AllocationCreateInfo.priority = 1.0f;

  //vmaCreateBuffer(Allocator, &Info, &AllocationCreateInfo,
  //    &Buffer, &Allocation, nullptr);
} /* End of 'CreateBuffer' function */

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
VOID arvk::VlkBuffer::BufferCreate( VkBuffer &Buffer, VmaAllocation &Allocation, VkDeviceSize Size, VkBufferUsageFlags Usage, VkMemoryPropertyFlags Properties )
{
    VkBufferCreateInfo Info
    {
      .sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO, // Structure type.
      .size = Size,                                  // Size in bytes.
      .usage = Usage,                                // Bit mask for buffer usage.
      .sharingMode = VK_SHARING_MODE_EXCLUSIVE,      // Using type if family queues call 
    };
    SizeOfBufferData = Size;

    // Create buffer through VMA
    VmaAllocationCreateInfo AllocationCreateInfo{};
    AllocationCreateInfo.usage = VMA_MEMORY_USAGE_AUTO;
    AllocationCreateInfo.requiredFlags = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
    AllocationCreateInfo.flags =
        VMA_ALLOCATION_CREATE_HOST_ACCESS_ALLOW_TRANSFER_INSTEAD_BIT |
        VMA_ALLOCATION_CREATE_HOST_ACCESS_SEQUENTIAL_WRITE_BIT;
    AllocationCreateInfo.priority = 1.0f;

    vmaCreateBuffer(Allocator, &Info, &AllocationCreateInfo, &Buffer, &Allocation, nullptr);
} /* End of 'CreateBuffer' function */

/* Destroy buffer function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 * RETURNS: None.
 */
VOID arvk::VlkBuffer::DestroyBuffer( VkDevice &Device )
{
  //vmaDestroyBuffer(Allocator, Buffer, Allocation);
  vkFreeMemory(Device, Memory, nullptr);
  vkDestroyBuffer(Device, Buffer, nullptr);
} /* End of 'DestroyBuffer' function */

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
VOID arvk::VlkBuffer::BufferWrite( VkDevice &Device, VkPhysicalDevice &PhysDevice, BYTE Size, VOID *Data )
{
  VOID *MapPointer;
  VkBool32 Res = vkMapMemory(Device, Memory, 0, Size, 0, &MapPointer);

  VkMemoryRequirements MemoryRequirments;
  vkGetBufferMemoryRequirements(Device, Buffer, &MemoryRequirments);
  VkPhysicalDeviceMemoryProperties PhysicalDeviceMemoryProperties;
  vkGetPhysicalDeviceMemoryProperties(PhysDevice, &PhysicalDeviceMemoryProperties);
  
  VkMappedMemoryRange MappedMemoryRange
  {
    .sType = VK_STRUCTURE_TYPE_MAPPED_MEMORY_RANGE,
    .pNext = nullptr,
    .memory = Memory,
    .offset = 0,
    .size = Size
  };

  BOOL HasFlag = FALSE;

  for (UINT32 i = 0; i < PhysicalDeviceMemoryProperties.memoryTypeCount; i++)
    if ((MemoryRequirments.memoryTypeBits & (1 << i)) && (PhysicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
    {
      HasFlag = TRUE;
      break;
    }
  CopyMemory(MapPointer, Data, Size);

  //if (!HasFlag)
  //  vkFlushMappedMemoryRanges(Device, );
  
  vkUnmapMemory(Device, Memory);
} /* End of 'BufferWrite' function */

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
VOID arvk::VlkBuffer::BufferRead( VkDevice &Device, VkPhysicalDevice &PhysDevice, BYTE &Size )
{
  VOID *MapPointer;
  VkBool32 Res = vkMapMemory(Device, Memory, 0, Size, 0, &MapPointer);

  VkMemoryRequirements MemoryRequirments;
  vkGetBufferMemoryRequirements(Device, Buffer, &MemoryRequirments);
  VkPhysicalDeviceMemoryProperties PhysicalDeviceMemoryProperties;
  vkGetPhysicalDeviceMemoryProperties(PhysDevice, &PhysicalDeviceMemoryProperties);

  BOOL HasFlag = FALSE;

  for (UINT32 i = 0; i < PhysicalDeviceMemoryProperties.memoryTypeCount; i++)
    if ((MemoryRequirments.memoryTypeBits & (1 << i)) && (PhysicalDeviceMemoryProperties.memoryTypes[i].propertyFlags & VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT) == VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
    {
      HasFlag = TRUE;
      break;
    }

  //if (!HasFlag)
  //  vkInvalidateMappedMemoryRanges(Device, );

  vkUnmapMemory(Device, Memory);
} /* End of 'BufferRead' function */

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
VOID arvk::VlkBuffer::BufferUpdateGraphics( VkBuffer Buffer, UINT Offset, UINT Size, VOID *Data, INT Index )
{
  // Send data to stage buffer
  StageBufferUpdate(Offset, Size, Data, Index);
 
  VkBufferCopy copyRegion
  {
    .srcOffset = 0,
    .dstOffset = Offset,
    .size = Size,
  };
  vkCmdCopyBuffer(CommandBuffer[CurrentFrame], StageBuffer[Index], Buffer, 1, &copyRegion);
} /* End of 'BufferUpdateGraphics' function */
 
/* Vulkan stage buffer update function.
 * ARGUMENTS:
 *   - stage buffer update offset and size in bytes:
 *       UINT Offset, Size;
 *   - stage buffer data pointer:
 *       const VOID *Data;
 * RETURNS: None.
 */
VOID arvk::VlkBuffer::StageBufferUpdate( UINT Offset, UINT Size, VOID *Data, INT Index )
{
  // Correct buffer size
  if (Offset + Size > StageBufferSize[Index])
  {
    StageBufferSize[Index] = Offset + Size;
    // Reallocate stage buffer
    BufferFree(StageBuffer[Index], StageBufferAllocation[Index]);
    BufferCreate(StageBuffer[Index], StageBufferAllocation[Index], StageBufferSize[Index], VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT);
  }
  // Copy data
  if (Data != nullptr)
    if (VOID *BufData; vmaMapMemory(Allocator, StageBufferAllocation[Index], &BufData) == VK_SUCCESS)
    {
      memcpy(BufData, (BYTE *)Data + Offset, Size);
      vmaUnmapMemory(Allocator, StageBufferAllocation[Index]);
    }
} /* End of 'StageBufferUpdate' function */

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
VOID arvk::VlkBuffer::BufferUpdate( VkBuffer Buffer, UINT Offset, UINT Size, VOID *Data )
{
  StageBufferUpdate(Offset, Size, Data, CurrentFrame);
 
  vkResetCommandBuffer(TransferCommandBuffer, 0);

  // Copy stage buffer to target one through command buffer
  VkCommandBufferBeginInfo CommandBufferBeginInfo
  {
    .sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,
    .flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
  };
  vkBeginCommandBuffer(TransferCommandBuffer, &CommandBufferBeginInfo);
  VkBufferCopy copyRegion
  {
    .srcOffset = 0,
    .dstOffset = Offset,
    .size = Size,
  };
  vkCmdCopyBuffer(TransferCommandBuffer, StageBuffer[CurrentFrame], Buffer, 1, &copyRegion);
  vkEndCommandBuffer(TransferCommandBuffer);
  VkSubmitInfo SubmitInfo
  {
    .sType = VK_STRUCTURE_TYPE_SUBMIT_INFO,
    .commandBufferCount = 1,
    .pCommandBuffers = &TransferCommandBuffer,
  };
  vkQueueSubmit(TransferQueue, 1, &SubmitInfo, VK_NULL_HANDLE);
  vkQueueWaitIdle(TransferQueue);
 } /* End of 'BufferUpdate' function */

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
VOID arvk::VlkBuffer::BufferFree( VkBuffer &Buffer, VmaAllocation &Allocation )
{
  vmaDestroyBuffer(Allocator, Buffer, Allocation);
  Buffer = VK_NULL_HANDLE;
  Allocation = VK_NULL_HANDLE;
} /* End of 'BufferFree' function */

/* END OF 'vlk_buffer.cpp' FILE */
