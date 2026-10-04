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

/* Write data in buffer function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 * RETURNS: None.
 */
VOID arvk::VlkDescriptor::CreateDescriptorPool( VkDevice &Device )
{
  std::array<VkDescriptorPoolSize, 2> PoolSizes {};
  
  PoolSizes[0].type = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER/*VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER*/; // descriptor type.
  PoolSizes[0].descriptorCount = 100;                      // Number of descriptor sizes.

  PoolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
  PoolSizes[1].descriptorCount = 100;                      // Number of descriptor sizes.

  VkDescriptorPoolCreateInfo PoolCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
    .maxSets = 100,                            // Max number ofdescriptor sets, that you can create.
    .poolSizeCount = (UINT)PoolSizes.size(), // Number of descriptor sizes.
    .pPoolSizes = PoolSizes.data(),          // Descriptor sizes.
  };

  VK_CHECK(vkCreateDescriptorPool(Device, &PoolCreateInfo, nullptr, &DescriptorPool));
} /* End of 'CreateDescriptorPool' function */

/* Write data in buffer function.
  *  ARGUMENTS:
  *   - Logical device:
  *      VkDevice &Device;
  * RETURNS: None.
  */
VOID arvk::VlkDescriptor::DestroyDescriptorPool( VkDevice &Device )
{
  vkDestroyDescriptorPool(Device, DescriptorPool, nullptr);
}

/* Write data in buffer function.
 *  ARGUMENTS:
 *   - Logical device:
 *      VkDevice &Device;
 *   - Descriptor set layout:
 *       VkDescriptorSetLayout &DescriptorSetLayout;
 * RETURNS: None.
 */
VOID arvk::VlkDescriptor::CreateDescriptorSet( VkDevice &Device, VkDescriptorSetLayout &DescriptorSetLayout )
{
  VkDescriptorSetAllocateInfo AllocInfo
  {
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
    .descriptorPool = DescriptorPool,        // Descriptor pool whrere you alloc memory.
    .descriptorSetCount = 1,                 // Number of descriptor set layouts.
    .pSetLayouts = &DescriptorSetLayout,    
  };
 
  VK_CHECK(vkAllocateDescriptorSets(Device, &AllocInfo, &DescriptorSet))
} /* End of 'CreateDescriptorSet' function */

/* Write data in buffer function.
 *  ARGUMENTS:
 *   - Buffer:
 *       VkBuffer &Buffer;
 *   - Logical device:
 *      VkDevice &Device;
 *   - Buffer data size:
 *       BYTE &SizeOfBufferData;
 * RETURNS: None.
 */
VOID arvk::VlkDescriptor::DescriptorBufferFill( VkBuffer &Buffer, VkDevice &Device, BYTE SizeOfBufferData, UINT Binding, BYTE Offset )
{
  VkDescriptorBufferInfo BufferInfo
  {
    .buffer = Buffer,          // Buffer to be written in this descriptor.
    .offset = Offset,          // Offset in bytes.
    .range = SizeOfBufferData, // Buffer size.
  };

  // Only one descriptor.
  std::array<VkWriteDescriptorSet, 1> DescriptorWrites;

  DescriptorWrites[0].sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
  DescriptorWrites[0].dstSet = DescriptorSet;                             
  DescriptorWrites[0].dstBinding = Binding;                                     
  DescriptorWrites[0].dstArrayElement = 0;                                
  DescriptorWrites[0].descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER /*VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER*/; 
  DescriptorWrites[0].descriptorCount = 1;                                
  DescriptorWrites[0].pBufferInfo = &BufferInfo;                          
  DescriptorWrites[0].pNext = nullptr;                          

  vkUpdateDescriptorSets(Device, (UINT)DescriptorWrites.size(), DescriptorWrites.data(), 0, nullptr);
} /* End of 'DescriptorBufferFill' function */

VOID arvk::VlkDescriptor::DescriptorImageFill( VkImageView &ImageView, VkSampler &Sampler, VkDevice &Device, UINT Binding )
{
    VkDescriptorImageInfo ImageInfo
    {
        .sampler = Sampler,
        .imageView = ImageView,
        .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
    };

    VkWriteDescriptorSet DescriptorWrite = {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = DescriptorSet,
        .dstBinding = Binding,
        .dstArrayElement = 0,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
        .pImageInfo = &ImageInfo,
    };

    vkUpdateDescriptorSets(Device, 1, &DescriptorWrite, 0, nullptr);
} /* End of 'DescriptorImageFill' function */

/* END OF 'vlk_dummy.cpp' FILE */
