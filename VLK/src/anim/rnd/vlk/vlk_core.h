/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_core.h
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

#ifndef __vlk_core_h_
#define __vlk_core_h_

#include "anim/rnd/vlk/vlk_def.h"

#include "anim/rnd/vlk/vlk_debug.h"
#include "anim/rnd/vlk/vlk_instance.h"
#include "anim/rnd/vlk/vlk_device.h"
#include "anim/rnd/vlk/vlk_context.h"
#include "anim/rnd/vlk/vlk_renderpass.h"
#include "anim/rnd/vlk/vlk_framebuffer.h"
#include "anim/rnd/vlk/vlk_swapchain.h"
#include "anim/rnd/vlk/vlk_pipeline.h"
#include "anim/rnd/vlk/vlk_comnadqueue.h"
#include "anim/rnd/vlk/vlk_buffer.h"
#include "anim/rnd/vlk/vlk_descriptor.h"
#include "anim/rnd/vlk/vlk_fence.h"
#include "anim/rnd/vlk/vlk_image.h"

/* Animation namespace */
namespace arvk
{
  /* Vulkan core class */
  class VlkCore: public VlkImage
  {
  public:
    //VkQueue GraphicsQueue {};               // Vulkan base graphics queue
    //VkQueue PresentQueue {};                // Vulkan base present queue
    //VkQueue TransferQueue {};               // Vulkan base transfer queue
    //UINT SelectedGraphicsQueueFamilyIndex = 0;       // Vulkan graphics queue family index
    //UINT SelectedPresentQueueFamilyIndex = 0;        // Vulkan present queue family index
    //UINT SelectedTransferQueueFamilyIndex = 0;       // Vulkan transfer queue family index
 
    //UINT ActiveSwapchainImage {};           // Active swap chain image number : 0 .. UsedBufferCount-1
  
    //// Graphics pipeline
    //VkPipeline GraphicsPipeline;                   // Vulkan graphics pipeline handle
    //VkPipelineLayout GraphicsPipelineLayout {};    // Vulkan graphics pipeline layout handle
 
    //// Layouts
    //VkDescriptorSetLayout FrameDescriptorSetLayout {};     // Vulkan frame pipeline descriptor set layout
    //VkDescriptorSetLayout PrimitiveDescriptorSetLayout {}; // Vulkan primitive pipeline descriptor set layout
    //VkDescriptorSetLayout MaterialDescriptorSetLayout {};  // Vulkan material pipeline descriptor set layout
    //VkDescriptorSetLayout SyncDescriptorSetLayout {};      // Vulkan sync (time) pipeline descriptor set layout

    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkCore( VOID )
    {
    } /* End of 'VlkCore' function */

    /* Class destructor */
    ~VlkCore( VOID )
    {
    } /* End of '~VlkCore' function */
  }; /* End of 'VlkCore' class*/
} /* End of 'arvk' namespace */

#endif /* __vlk_core_h_ */

/* END OF 'vlk_core.h' FILE */
