/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_pipeline.h
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

#ifndef __vlk_pipeline_h_
#define __vlk_pipeline_h_

#include "anim/rnd/vlk/vlk_def.h"
#include "anim/rnd/res/shd.h"

/* Animation namespace */
namespace arvk
{
  /* Vulkan pipeline class */
  class VlkPipeline: public VlkSwapchain
  {
  public:
    UINT CurrentFrame;

    VkShaderModule ShaderModule;
    std::vector<BYTE>Buf;

    VkDescriptorSetLayout DescriptorSetLayout;
    VkDescriptorSetLayout MaterialDescriptorSetLayout;
    VkPipelineLayout PipelineLayout;
    VkPipeline Pipeline;
    std::vector<VkPipelineShaderStageCreateInfo>ShaderStages;

    /* Class constructor.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VlkPipeline( VOID )
    {
      CurrentFrame = 0;
    } /* End of 'VlkPipeline' fucntion */

    /* Class destructor */
    ~VlkPipeline( VOID )
    {
    } /* End of '~VlkPipeline' fucntion */

    VOID CreatePipeline( VkDevice &Device, VkRenderPass &RenderPass, shader *Shader, INT &W, INT &H );
    VOID DestroyPipeline( VkDevice &Device );
    VOID CreateDescriptorLayout( VkDevice &Device );
    VOID CreateMaterialDescriptorLayout( VkDevice &Device );
    VOID DestroyDescriptorLayout( VkDevice &Device );
    VOID DestroyMaterialDescriptorLayout( VkDevice &Device );
    VOID CreatePipelineLayout( VkDevice &Device );
    VOID DestroyPipelineLayout( VkDevice &Device );
    VOID CreateShader( VkDevice &Device );
    VOID DestroyShader( VkDevice &Device );

  }; /* End of 'VlkPipeline' class*/
} /* End of 'arvk' namespace */

#endif /* __vlk_pipeline_h_ */

/* END OF 'vlk_pipeline.h' FILE */
