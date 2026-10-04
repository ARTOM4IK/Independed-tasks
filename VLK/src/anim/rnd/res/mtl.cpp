/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mtl.cpp
 * PURPOSE     : Ray Tracing project.
 *               Precompiled header definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "arvk.h"

// material.cpp
//VOID arvk::material::UpdateDescriptorSet( VOID )
//{
//  if (Rnd == nullptr)
//    return;
//    
//  // Создаем дескрипторный сет если еще не создан
//  if (DescriptorSet == VK_NULL_HANDLE)
//  {
//    // Нужен доступ к DescriptorPool и DescriptorSetLayout из рендера
//    // Добавьте в render класс методы для получения:
//    // Rnd->GetDescriptorPool()
//    // Rnd->GetDescriptorSetLayout()
//        
//    VkDescriptorSetAllocateInfo allocInfo = 
//    {
//      .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
//      .descriptorPool = Rnd->DescriptorPool,  // из VlkDescriptor
//      .descriptorSetCount = 1,
//      .pSetLayouts = &Rnd->MaterialDescriptorSetLayout,  // из VlkPipeline
//    };
//        
//    vkAllocateDescriptorSets(Rnd->Device, &allocInfo, &DescriptorSet);
//  }
//    
//  // Записываем текстуры в дескриптор (биндинги 3-7)
//  std::vector<VkWriteDescriptorSet> descriptorWrites;
//  std::vector<VkDescriptorImageInfo> imageInfos;
//        
//  for (INT i = 0; i < 5; i++)  // первые 5 текстур
//  {
//    if (Tex[i] != nullptr && Tex[i]->ImageView != VK_NULL_HANDLE)
//    {
//      VkDescriptorImageInfo imageInfo = 
//      {
//        .sampler = Tex[i]->Sampler,
//        .imageView = Tex[i]->ImageView,
//        .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
//      };
//      imageInfos.push_back(imageInfo);
//            
//      VkWriteDescriptorSet write = 
//      {
//        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
//        .dstSet = DescriptorSet,
//        .dstBinding = static_cast<UINT>(i),
//        .dstArrayElement = 0,
//        .descriptorCount = 1,
//        .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
//        .pImageInfo = &imageInfos.back(),
//      };
//      descriptorWrites.push_back(write);
//    }
//  }
//    
//  if (!descriptorWrites.empty())
//  {
//    vkUpdateDescriptorSets(Rnd->Device, 
//      static_cast<UINT>(descriptorWrites.size()),
//      descriptorWrites.data(), 0, nullptr);
//  }


VOID arvk::material::UpdateDescriptorSet( VOID )
{
    if (Rnd == nullptr) return;
    
    if (DescriptorSet == VK_NULL_HANDLE)
    {
        VkDescriptorSetAllocateInfo allocInfo = 
        {
            .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .descriptorPool = Rnd->DescriptorPool,
            .descriptorSetCount = 1,
            .pSetLayouts = &Rnd->MaterialDescriptorSetLayout,
        };
        
        VkResult result = vkAllocateDescriptorSets(Rnd->Device, &allocInfo, &DescriptorSet);
        if (result != VK_SUCCESS)
        {
            std::cerr << "Failed to allocate descriptor set for material " << Name << "\n";
            return;
        }
    }
    
    std::vector<VkWriteDescriptorSet> writes;
    std::vector<VkDescriptorImageInfo> imageInfos(5);
    
    for (UINT binding = 0; binding < 5; binding++)
    {
        texture* texToUse = nullptr;
        
        // binding 0 -> Tex[0] (BaseColor)
        // binding 1 -> Tex[3] (Normal)  
        // binding 2 -> Tex[1] (MetallicRoughness)
        // binding 3 -> Tex[2] (Emissive)
        // binding 4 -> Tex[4] (Occlusion)
        
        INT texIndex = -1;
        switch(binding)
        {
        case 0: texIndex = 0; break; // BaseColor
        case 1: texIndex = 3; break; // Normal  
        case 2: texIndex = 1; break; // MetallicRoughness
        case 3: texIndex = 2; break; // Emissive
        case 4: texIndex = 4; break; // Occlusion
        }
        
        if (texIndex >= 0 && texIndex < 8 && Tex[texIndex] != nullptr && 
            Tex[texIndex]->ImageView != VK_NULL_HANDLE)
        {
            texToUse = Tex[texIndex];
        }
        
        static texture* placeholder = nullptr;
        if (texToUse == nullptr)
        {
            if (placeholder == nullptr)
            {
                std::vector<BYTE> white = {255, 255, 255, 255};
                placeholder = Rnd->texture_manager::TexCreate("placeholder", 1, 1, 4, white.data(), FALSE);
            }
            texToUse = placeholder;
        }
        
        if (texToUse != nullptr && texToUse->ImageView != VK_NULL_HANDLE)
        {
            VkDescriptorImageInfo imageInfo = 
            {
                .sampler = texToUse->Sampler,
                .imageView = texToUse->ImageView,
                .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
            };
            imageInfos[binding] = imageInfo;
            
            VkWriteDescriptorSet write = 
            {
                .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
                .dstSet = DescriptorSet,
                .dstBinding = binding,
                .dstArrayElement = 0,
                .descriptorCount = 1,
                .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
                .pImageInfo = &imageInfos[binding],
            };
            writes.push_back(write);
        }
    }
    if (BoneBuffer != nullptr && BoneBuffer->Buffer != VK_NULL_HANDLE)
    {
        VkDescriptorBufferInfo boneBufferInfo = 
        {
            .buffer = BoneBuffer->Buffer,
            .offset = 0,
            .range = VK_WHOLE_SIZE,
        };
        
        VkWriteDescriptorSet boneWrite = 
        {
            .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
            .dstSet = DescriptorSet,
            .dstBinding = 5,
            .dstArrayElement = 0,
            .descriptorCount = 1,
            .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
            .pBufferInfo = &boneBufferInfo,
        };
        writes.push_back(boneWrite);
        
        std::cout << "Updated bone descriptor for material " << Name << "\n";
    }
    else
    {
        std::cout << "No bone buffer for material " << Name << "\n";
    }    
    if (!writes.empty())
    {
        vkUpdateDescriptorSets(Rnd->Device, writes.size(), writes.data(), 0, nullptr);
    }
}

    //if (Rnd == nullptr)
    //{
    //    std::cerr << "Material::UpdateDescriptorSet: Rnd is nullptr\n";
    //    return;
    //}
    //
    //static texture* whiteTexture = nullptr;
    //if (whiteTexture == nullptr)
    //{

    //    std::vector<BYTE> whitePixel = {255, 255, 255, 255}; // RGBA белый
    //
    //    whiteTexture = new texture(*Rnd);
    //    whiteTexture->Name = "white_1x1";
    //
    //    whiteTexture->Create("white_1x1", 1, 1, 4, whitePixel.data(), FALSE);
    //    
    //    if (whiteTexture == nullptr || whiteTexture->ImageView == VK_NULL_HANDLE)
    //    {
    //        std::cerr << "Material::UpdateDescriptorSet: Failed to create white texture\n";
    //        return;
    //    }
    //    std::cout << "Material::UpdateDescriptorSet: Created white placeholder texture\n";
    //}
    //
    //if (Rnd->MaterialDescriptorSetLayout == VK_NULL_HANDLE)
    //{
    //    std::cerr << "Material::UpdateDescriptorSet: MaterialDescriptorSetLayout is null\n";
    //    return;
    //}
    //
    //if (Rnd->DescriptorPool == VK_NULL_HANDLE)
    //{
    //    std::cerr << "Material::UpdateDescriptorSet: DescriptorPool is null\n";
    //    return;
    //}
    //
    //if (DescriptorSet == VK_NULL_HANDLE)
    //{
    //    VkDescriptorSetAllocateInfo allocInfo = 
    //    {
    //        .sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
    //        .descriptorPool = Rnd->DescriptorPool,
    //        .descriptorSetCount = 1,
    //        .pSetLayouts = &Rnd->MaterialDescriptorSetLayout,
    //    };
    //    
    //    VkResult result = vkAllocateDescriptorSets(Rnd->Device, &allocInfo, &DescriptorSet);
    //    if (result != VK_SUCCESS)
    //    {
    //        std::cerr << "Material::UpdateDescriptorSet: Failed to allocate descriptor sets: " << result << "\n";
    //        DescriptorSet = VK_NULL_HANDLE;
    //        return;
    //    }
    //    
    //    std::cout << "Material::UpdateDescriptorSet: Allocated descriptor set for material " << Name << "\n";
    //}
    //
    //std::vector<VkWriteDescriptorSet> descriptorWrites;
    //std::vector<VkDescriptorImageInfo> imageInfos;
    //
    //for (UINT binding = 0; binding < 5; binding++)
    //{
    //    texture* currentTex = whiteTexture; // По умолчанию placeholder
    //    
    //    // Проверяем, есть ли реальная текстура для этого биндинга
    //    if (binding < 8 && Tex[binding] != nullptr && 
    //        Tex[binding]->ImageView != VK_NULL_HANDLE && 
    //        Tex[binding]->Sampler != VK_NULL_HANDLE)
    //    {
    //        currentTex = Tex[binding];
    //        std::cout << "Material::UpdateDescriptorSet: Using real texture for binding " 
    //                  << binding << ": " << currentTex->Name << "\n";
    //    }
    //    else
    //    {
    //        std::cout << "Material::UpdateDescriptorSet: Using placeholder for binding " << binding << "\n";
    //    }
    //    
    //    VkDescriptorImageInfo imageInfo = 
    //    {
    //        .sampler = currentTex->Sampler,
    //        .imageView = currentTex->ImageView,
    //        .imageLayout = VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
    //    };
    //    
    //    imageInfos.push_back(imageInfo);
    //    
    //    VkWriteDescriptorSet write = 
    //    {
    //        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
    //        .dstSet = DescriptorSet,
    //        .dstBinding = binding, // 0, 1, 2, 3, 4
    //        .dstArrayElement = 0,
    //        .descriptorCount = 1,
    //        .descriptorType = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
    //        .pImageInfo = &imageInfos.back(),
    //    };
    //    descriptorWrites.push_back(write);
    //}
    //
    //if (BufferMtl != nullptr && BufferMtl->Buffer != VK_NULL_HANDLE)
    //{
    //    VkDescriptorBufferInfo bufferInfo = 
    //    {
    //        .buffer = BufferMtl->Buffer,
    //        .offset = 0,
    //        .range = sizeof(BUF_MTL),
    //    };
    //    
    //    VkWriteDescriptorSet bufferWrite = 
    //    {
    //        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
    //        .dstSet = DescriptorSet,
    //        .dstBinding = 5, // Следующий свободный биндинг
    //        .dstArrayElement = 0,
    //        .descriptorCount = 1,
    //        .descriptorType = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
    //        .pBufferInfo = &bufferInfo,
    //    };
    //    descriptorWrites.push_back(bufferWrite);
    //}
    //
    //if (!descriptorWrites.empty())
    //{
    //    vkUpdateDescriptorSets(Rnd->Device, 
    //        static_cast<UINT>(descriptorWrites.size()),
    //        descriptorWrites.data(), 0, nullptr);
    //    
    //    std::cout << "Material::UpdateDescriptorSet: Updated " << descriptorWrites.size() 
    //              << " descriptor writes for material " << Name << "\n";
    //}
//}
/* Material creation function.
 * ARGUMENTS:
 *   - material name:
 *       const std::string &NewName;
 *   - illumination coefficients (ambient. diffuse, specular):
 *       const color3 &NewKa, &NewKd, &NewKs;
 *   - Phong shininess coefficient:
 *       FLT NewPh;
 *   - transparency coefficient:
 *       FLT NewTrans;
 *   - shader pointer:
 *       shader *NewShd;
 *   - textures list:
 *       std::initializer_list<texture *> Textures;
 * RETURNS:
 *   (material &) self reference.
 */
arvk::material & arvk::material::Create( const std::string &NewName,
                    const vec3 &NewKa, const vec3 &NewKd, const vec3 &NewKs,
                    FLT NewPh, FLT NewTrans,
                    shader *NewShd,
                    std::initializer_list<texture *> Textures)
{
  Free();
  Name = NewName;
  Ka = NewKa;
  Kd = NewKd;
  Ks = NewKs;
  Ph = NewPh;
  Trans = NewTrans;
  Shd = NewShd;
 
  INT i = 0;
  for (auto t : Textures)
    Tex[i++] = t;
  for (; i < 8; i++)
    Tex[i++] = nullptr;
 
  BUF_MTL buf =
  {
    vec4(Ka, 0),
    vec4(Kd, Trans),
    vec4(Ks, Ph)
  };
  for (i = 0; i < 8; i++)
    buf.TextureFlags[i] = Tex[i] != nullptr;
  BufferMtl = Rnd->buffer_manager::BufCreate(3, &buf);
  return *this;
} /* End of 'Create' fucntion */

/* Material apply function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (shader *) shader pointer.
 */
arvk::shader * arvk::material::Apply( VOID )
{
  if (Shd == nullptr)
    Shd = Rnd->shader_manager::Find("default");
  if (Shd != nullptr)
  {
    Shd->Apply();
    BufferMtl->Apply();
    for (INT t = 0; t < 8; t++)
    {
      if (Tex[t] != nullptr)
      {
        //glActiveTexture(GL_TEXTURE0 + t);
        Tex[t]->Apply();
      }
    }
  }
  return Shd;
} /* End of 'Apply' function */

/* Material free function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (VOID) None.
 */
VOID arvk::material::Free( VOID )
{
  if (BufferMtl != nullptr)
    BufferMtl->Free();
  BufferMtl = nullptr;
} /* End of 'Free' function */

/* Material update function.
 * ARGUMENTS: None.
 * RETURNS:
 *   (VOID) None.
 */
VOID arvk::material::Update( VOID )
{
  BUF_MTL buf =
  {
    vec4(Ka, 0),
    vec4(Kd, Trans),
    vec4(Ks, Ph)
  };
  for (INT i = 0; i < 8; i++)
    buf.TextureFlags[i] = Tex[i] != nullptr;
  //BufferMtl->Update(&buf);
} /* End of 'Update' function */

VOID arvk::material::UpdateBoneDescriptor( VOID ) 
{
    if (!Rnd || !BoneBuffer || DescriptorSet == VK_NULL_HANDLE) return;
        
    VkDescriptorBufferInfo boneInfo 
    {
        .buffer = BoneBuffer->Buffer,
        .offset = 0,
        .range = VK_WHOLE_SIZE
    };
        
    VkWriteDescriptorSet write 
    {
        .sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .dstSet = DescriptorSet,
        .dstBinding = 5,
        .dstArrayElement = 0,
        .descriptorCount = 1,
        .descriptorType = VK_DESCRIPTOR_TYPE_STORAGE_BUFFER,
        .pBufferInfo = &boneInfo
    };
        
    vkUpdateDescriptorSets(Rnd->Device, 1, &write, 0, nullptr);
}

/* Material creation function.
 * ARGUMENTS:
 *   - material name:
 *       const std::string &FileNamePrefix;
 * RETURNS:
 *   (material *) material pointer.
 */
arvk::material * arvk::material_manager::MtlCreate( const std::string &FileNamePrefix )
{
  return resource_manager::Add(material(RndRef).Create(FileNamePrefix));
} /* End of 'MtlCreate' function */

/* END OF 'prim.cpp' FILE */
