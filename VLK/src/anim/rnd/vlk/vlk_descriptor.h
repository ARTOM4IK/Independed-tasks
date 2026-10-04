/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_dummy.h
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

#ifndef __vlk_descriptor_h_
#define __vlk_descriptor_h_

#include "anim/rnd/vlk/vlk_def.h"

/* Animation namespace */
namespace arvk
{
  /* Vulkan dummy class */
  class VlkDescriptor: public VlkBuffer
  {
  public:
    VkDescriptorPool DescriptorPool;
    VkDescriptorSet DescriptorSet;

    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkDescriptor( VOID )
    {
    } /* End of 'VlkDescriptor' function */

    /* Class destructor */
    ~VlkDescriptor( VOID )
    {
    } /* End of '~Descriptor' function */

    /* Create descriptor pool function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     * RETURNS: None.
     */
    VOID CreateDescriptorPool( VkDevice &Device );

    /* Write data in buffer function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     * RETURNS: None.
     */
    VOID DestroyDescriptorPool( VkDevice &Device );

    /* Create descriptor sets function.
     *  ARGUMENTS:
     *   - Logical device:
     *      VkDevice &Device;
     *   - Descriptor set layout:
     *       VkDescriptorSetLayout &DescriptorSetLayout;
     * RETURNS: None.
     */
    VOID CreateDescriptorSet( VkDevice &Device, VkDescriptorSetLayout &DescriptorSetLayout );

    /* Descriptor buffer fill function.
     *  ARGUMENTS:
     *   - Buffer:
     *       VkBuffer &Buffer;
     *   - Logical device:
     *      VkDevice &Device;
     *   - Buffer data size:
     *       BYTE SizeOfBufferData;
     * RETURNS: None.
     */
    VOID DescriptorBufferFill( VkBuffer &Buffer, VkDevice &Device, BYTE SizeOfBufferData, UINT Binding, BYTE Offset );
    VOID DescriptorImageFill( VkImageView &ImageView, VkSampler &Sampler, VkDevice &Device, UINT Binding );

  }; /* End of 'VlkDescriptor' class*/
} /* End of 'arvk' namespace */

#endif /* __vlk_descriptor_h_ */

/* END OF 'vlk_dummy.h' FILE */
