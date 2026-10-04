/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : vlk_pipeline.cpp
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

VOID arvk::VlkPipeline::CreateShader( VkDevice &Device )
{
  VkShaderModuleCreateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO, // Structure type.
    .codeSize = Buf.size(),                               // Byte-code size (divides by 4).
    .pCode = reinterpret_cast<const UINT32 *>(Buf.data()), // Pointer to byte-code.
  };

  vkCreateShaderModule(Device, &Info, nullptr, &ShaderModule);
}

VOID arvk::VlkPipeline::DestroyShader( VkDevice &Device )
{
  vkDestroyShaderModule(Device, ShaderModule, nullptr);
}

VOID arvk::VlkPipeline::CreateMaterialDescriptorLayout( VkDevice &Device )
{
  VkDescriptorSetLayoutBinding DescriptorSetLayoutBindings[]
  {
    /* Diffuse/Albedo texture */
    {
      .binding = 0,
      .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
      .descriptorCount = 1,
      .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
      .pImmutableSamplers = nullptr,
    },

    /* Normal texture */
    {
      .binding = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
      .descriptorCount = 1,
      .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
      .pImmutableSamplers = nullptr,
    },
    
    /* Specular texture */
    {
      .binding = 2,
      .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
      .descriptorCount = 1,
      .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
      .pImmutableSamplers = nullptr,
    },
    
    /* Emissive texture */
    {
      .binding = 3,
      .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
      .descriptorCount = 1,
      .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
      .pImmutableSamplers = nullptr,
    },
    
    /* Ambient Occlusion texture */
    {
      .binding = 4,
      .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
      .descriptorCount = 1,
      .stageFlags = VK_SHADER_STAGE_FRAGMENT_BIT,
      .pImmutableSamplers = nullptr,
    },

    /* Bones */
    {
      .binding = 5,
      .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
      .descriptorCount = 1,
      .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
      .pImmutableSamplers = nullptr,
    },
  };
  
  VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,   // Structure type.
    .flags = 0,                                                     // Flags.
    .bindingCount = (UINT32)std::size(DescriptorSetLayoutBindings), // Number of bindings.
    .pBindings = DescriptorSetLayoutBindings,                       // Pointer to first binding.
  };
  
  vkCreateDescriptorSetLayout(Device, &DescriptorSetLayoutCreateInfo, nullptr, &MaterialDescriptorSetLayout);
}

VOID arvk::VlkPipeline::CreateDescriptorLayout( VkDevice &Device )
{
  VkDescriptorSetLayoutBinding DescriptorSetLayoutBindings[]
  {
    /* Time */
    {
      .binding = 0,                                        // Binding number on shader.
      .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER/*VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER*/, // Object type to bind.
      .descriptorCount = 1,                                // Number in array (for VK_DESCRIPTOR_TYPE_INLINE_UNIFORM_BLOCK size in bytes)
      .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS/*VK_SHADER_STAGE_VERTEX_BIT*/,            // Flag that means on what shader is this resource (can be unitable)
      .pImmutableSamplers = nullptr,                       // Pointer to unchangable samplers.
    },
  
    /* Camera */
    {
      .binding = 1,
      .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
      .descriptorCount = 1,
      .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
      .pImmutableSamplers = nullptr,
    },
  
    /* SSBO with World, WVP and WInv */
    {
      .binding = 2,
      .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
      .descriptorCount = 1,
      .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS,
      .pImmutableSamplers = nullptr,
    },

  };
  
  VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO,   // Structure type.
    .flags = 0,                                                     // Flags.
    .bindingCount = (UINT32)std::size(DescriptorSetLayoutBindings), // Number of bindings.
    .pBindings = DescriptorSetLayoutBindings,                       // Pointer to first binding.
  };
  
  vkCreateDescriptorSetLayout(Device, &DescriptorSetLayoutCreateInfo, nullptr, &DescriptorSetLayout);
}

VOID arvk::VlkPipeline::DestroyDescriptorLayout( VkDevice &Device )
{
  vkDestroyDescriptorSetLayout(Device, DescriptorSetLayout, nullptr);
}

VOID arvk::VlkPipeline::CreatePipelineLayout( VkDevice &Device )
{
  std::array<VkDescriptorSetLayout, 2> DescriptorSetLayouts {DescriptorSetLayout, MaterialDescriptorSetLayout};

  VkPushConstantRange matrix[2];
  matrix[0] = 
  {
    .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS/*VK_PIPELINE_STAGE_VERTEX_SHADER_BIT*//*VK_SHADER_STAGE_ALL_GRAPHICS*/,
    .offset = 0,
    .size = sizeof(/*render::BUF_PRIM**/render::PUSH_CONST),
  };
  matrix[1] = 
  {
    .stageFlags = VK_SHADER_STAGE_ALL_GRAPHICS/*VK_PIPELINE_STAGE_VERTEX_SHADER_BIT*//*VK_SHADER_STAGE_ALL_GRAPHICS*/,
    .offset = sizeof(/*render::BUF_PRIM**/render::PUSH_CONST),
    .size = sizeof(/*render::BUF_PRIM**/render::PUSH_MTL),
  };

  VkPipelineLayoutCreateInfo Info
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO, // Structure type.
    .setLayoutCount = UINT32(DescriptorSetLayouts.size()),  // Number of sets of descriptors.
    .pSetLayouts = DescriptorSetLayouts.data(),             // Set of descriptors.
    .pushConstantRangeCount = 1,                            // Number of constants.
    .pPushConstantRanges = &matrix[0],                         // Constants.
  };

  vkCreatePipelineLayout(Device, &Info, nullptr, &PipelineLayout);
}

VOID arvk::VlkPipeline::DestroyPipelineLayout( VkDevice &Device )
{
  vkDestroyPipelineLayout(Device, PipelineLayout, nullptr);
}

VOID arvk::VlkPipeline::DestroyMaterialDescriptorLayout( VkDevice &Device )
{
  if (MaterialDescriptorSetLayout != VK_NULL_HANDLE)
  {
    vkDestroyDescriptorSetLayout(Device, MaterialDescriptorSetLayout, nullptr);
    MaterialDescriptorSetLayout = VK_NULL_HANDLE;
  }
}

VOID arvk::VlkPipeline::CreatePipeline( VkDevice &Device, VkRenderPass &RenderPass, shader *Shader, INT &W, INT &H )
{
  VkVertexInputBindingDescription BindingDescr
  {
    .binding = 0,
    .stride = (UINT32)sizeof(vertex::skinned),
    .inputRate = VK_VERTEX_INPUT_RATE_VERTEX, // Standart flag of transting vertices (means smth if you need to index them on instances).
  };
  
  std::array<VkVertexInputAttributeDescription, 6> AttribDescrs {};
  
  // Information of pos attribute.
  AttribDescrs[0].binding = 0;
  AttribDescrs[0].location = 0;
  AttribDescrs[0].format = VK_FORMAT_R32G32B32_SFLOAT;    // vec3.
  AttribDescrs[0].offset = /*0*/offsetof(vertex::skinned, vertex::skinned::P);

  // Information of texture pos attribute.
  AttribDescrs[1].binding = 0;
  AttribDescrs[1].location = 1;
  AttribDescrs[1].format = VK_FORMAT_R32G32_SFLOAT;       // vec2.
  AttribDescrs[1].offset = /*12*/offsetof(vertex::skinned, vertex::skinned::T);

  // Information of normal attribute.
  AttribDescrs[2].binding = 0;
  AttribDescrs[2].location = 2;
  AttribDescrs[2].format = VK_FORMAT_R32G32B32_SFLOAT;    // vec3.
  AttribDescrs[2].offset = /*20*/offsetof(vertex::skinned, vertex::skinned::N);
  
  // Information of color attribute.
  AttribDescrs[3].binding = 0;
  AttribDescrs[3].location = 3;
  AttribDescrs[3].format = VK_FORMAT_R32G32B32A32_SFLOAT; // vec4.
  AttribDescrs[3].offset = /*32*/offsetof(vertex::skinned, vertex::skinned::C);

  // Information of color attribute.
  AttribDescrs[4].binding = 0;
  AttribDescrs[4].location = 4;
  AttribDescrs[4].format = VK_FORMAT_R32G32B32A32_SINT; // ivec4.
  AttribDescrs[4].offset = /*32*/offsetof(vertex::skinned, vertex::skinned::Joints);

  // Information of color attribute.
  AttribDescrs[5].binding = 0;
  AttribDescrs[5].location = 5;
  AttribDescrs[5].format = VK_FORMAT_R32G32B32A32_SFLOAT; // vec4.
  AttribDescrs[5].offset = /*32*/offsetof(vertex::skinned, vertex::skinned::Weights);

  VkPipelineVertexInputStateCreateInfo VertInputInfo 
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO,
    .vertexBindingDescriptionCount = 1,
    .pVertexBindingDescriptions = &BindingDescr,
    .vertexAttributeDescriptionCount = UINT32(AttribDescrs.size()),
    .pVertexAttributeDescriptions = AttribDescrs.data(),
  };

  VkPipelineShaderStageCreateInfo VertShdStageInfo
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
    .stage = VK_SHADER_STAGE_VERTEX_BIT,
    .module = Shader->ShaderModuleVert,
    .pName = "main",
  };
  
  VkPipelineShaderStageCreateInfo FragShdStageInfo 
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
    .stage = VK_SHADER_STAGE_FRAGMENT_BIT,
    .module = Shader->ShaderModuleFrag,
    .pName = "main",
  };

  ShaderStages.resize(2);
  ShaderStages[0] = VertShdStageInfo;
  ShaderStages[1] = FragShdStageInfo;

  std::vector<VkDynamicState> DynamicStates
  {
    VK_DYNAMIC_STATE_VIEWPORT,
    VK_DYNAMIC_STATE_SCISSOR,
  };
  
  VkPipelineDynamicStateCreateInfo DSCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
    .dynamicStateCount = (UINT32)DynamicStates.size(),
    .pDynamicStates = DynamicStates.data(),
  };
  
  VkViewport Vp
  {
    .x = 0.0f,
    .y = static_cast<FLT>(H),
    .width = static_cast<FLT>(W),
    .height = -static_cast<FLT>(H), 
    .minDepth = 0.0f,
    .maxDepth = 1.0f,
  };
  VkRect2D Sc
  {
    .offset {.x = 0, .y = 0},
    .extent {.width = UINT32(W), .height = UINT32(H)}
  };
  VkPipelineViewportStateCreateInfo VpCreateInfo 
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
    .pNext = nullptr,
    .viewportCount = 1,
    .pViewports = &Vp,
    .scissorCount = 1,
    .pScissors = &Sc,
  };

  VkPipelineDepthStencilStateCreateInfo DepthStencil
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
    .depthTestEnable = VK_TRUE,
    .depthWriteEnable = VK_TRUE,
    .depthCompareOp = VK_COMPARE_OP_LESS,            // Color to define object depth (in this case - closest).
    .depthBoundsTestEnable = VK_FALSE,               // flag to check depth borders.
    .stencilTestEnable = VK_FALSE,
  };

  VkPipelineRasterizationStateCreateInfo RastCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
    .rasterizerDiscardEnable = VK_FALSE,           // if VK_TRUE then np rasterization (it's needed when you don't need to draw e.g. for calculations).
    .polygonMode = VK_POLYGON_MODE_FILL,
    .cullMode = VK_CULL_MODE_NONE,
    .frontFace = VK_FRONT_FACE_CLOCKWISE,
    .depthBiasEnable = VK_TRUE,
    //.depthBiasClamp = 0.01,
    .lineWidth = 1.0f,
  };

  // Parametrs for disabling antialising.
  VkPipelineMultisampleStateCreateInfo MSCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
    .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,                    // Multysampling is disabled, but when it increases - image value increases,
                                                                      // but you take more resources.
    .sampleShadingEnable = VK_FALSE,                                  // VK_FALSE = sample in its center;
                                                                      // VK_TRUE = interpolation of samples around current pixel    
  };

  VkPipelineColorBlendAttachmentState BlendAttachState[6];
  BlendAttachState[0] = 
  {
    .blendEnable = VK_FALSE,
    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT |                     // Color components which will write into frmae buffer,
                      VK_COLOR_COMPONENT_G_BIT |                     
                      VK_COLOR_COMPONENT_B_BIT |                     
                      VK_COLOR_COMPONENT_A_BIT,
  };
  BlendAttachState[1] = 
  {
    .blendEnable = VK_FALSE,
    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT |                     // Color components which will write into frmae buffer,
                      VK_COLOR_COMPONENT_G_BIT |                     
                      VK_COLOR_COMPONENT_B_BIT |                     
                      VK_COLOR_COMPONENT_A_BIT,
  };
  BlendAttachState[2] = 
  {
    .blendEnable = VK_FALSE,
    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT |                     // Color components which will write into frmae buffer,
                      VK_COLOR_COMPONENT_G_BIT |                     
                      VK_COLOR_COMPONENT_B_BIT |                     
                      VK_COLOR_COMPONENT_A_BIT,
  };
  BlendAttachState[3] = 
  {
    .blendEnable = VK_FALSE,
    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT |                     // Color components which will write into frmae buffer,
                      VK_COLOR_COMPONENT_G_BIT |                     
                      VK_COLOR_COMPONENT_B_BIT |                     
                      VK_COLOR_COMPONENT_A_BIT,
  };
  BlendAttachState[4] = 
  {
    .blendEnable = VK_FALSE,
    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT |                     // Color components which will write into frmae buffer,
                      VK_COLOR_COMPONENT_G_BIT |                     
                      VK_COLOR_COMPONENT_B_BIT |                     
                      VK_COLOR_COMPONENT_A_BIT,
  };
  BlendAttachState[5] = 
  {
    .blendEnable = VK_FALSE,
    .colorWriteMask = VK_COLOR_COMPONENT_R_BIT |                     // Color components which will write into frmae buffer,
                      VK_COLOR_COMPONENT_G_BIT |                     
                      VK_COLOR_COMPONENT_B_BIT |                     
                      VK_COLOR_COMPONENT_A_BIT,
  };
  
  VkPipelineColorBlendStateCreateInfo BlendCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
    .logicOpEnable = VK_FALSE,                                        // If you need a logical operation while filling final color.
    .attachmentCount = 6, 
    .pAttachments = BlendAttachState,
  };

    VkPipelineInputAssemblyStateCreateInfo IACreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO,
    .topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST/*VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST*/,
    .primitiveRestartEnable = VK_FALSE,
  };

  VkGraphicsPipelineCreateInfo PipelineCreateInfo
  {
    .sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO,
    .stageCount = (UINT32)ShaderStages.size(),
    .pStages = ShaderStages.data(),
    .pVertexInputState = &VertInputInfo,
    .pInputAssemblyState = &IACreateInfo,
    .pViewportState = &VpCreateInfo,
    .pRasterizationState = &RastCreateInfo,
    .pMultisampleState = &MSCreateInfo,
    .pDepthStencilState = &DepthStencil,
    .pColorBlendState = &BlendCreateInfo,
    .pDynamicState = &DSCreateInfo,
    .layout = PipelineLayout,
    .renderPass = RenderPass,
    .basePipelineHandle = VK_NULL_HANDLE,                  // Create pipeline on another base.
    .basePipelineIndex = -1,
  };
  
  VK_CHECK(vkCreateGraphicsPipelines(Device, VK_NULL_HANDLE, 1, &PipelineCreateInfo, nullptr, &Pipeline));
  }

VOID arvk::VlkPipeline::DestroyPipeline( VkDevice &Device )
{
  vkDestroyPipeline(Device, Pipeline, nullptr);
  Pipeline = VK_NULL_HANDLE;
}

/* END OF 'vlk_pipeline.cpp' FILE */
