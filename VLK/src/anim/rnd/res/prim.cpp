/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : prim.cpp
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

arvk::prim::prim( render &rnd ) /*: Mtl(Rnd->material_manager::Find("default"))*/
{
  Rnd = &rnd;
}

/* Primitive creation function.
 * ARGUMENTS:
 *   - primitive type:
 *       prim_type NewType;
 *   - vertex array:
 *       const std::vector<vertex_type> &V;
 *   - index array:
 *       const std::vector<INT> &Ind;
 * RETURNS:
 *   (prim &) self reference.
 */
template<class vertex_type>
  arvk::prim & arvk::prim::Create( prim_type NewType,
                  const std::span<vertex_type> &V,
                  const std::span<INT> &Ind, BOOL IsSkinned )
  {
    //Free();
    Type = NewType;
    Transform = matr::Identity();
    NumOfElements = 0;
    //if (IsSkinned)
    //{
      VertexStride = sizeof(vertex::skinned);
 
      if constexpr (requires{vertex::skinned::P;})
        VertexMap["InPosition"] = reinterpret_cast<INT_PTR>(&((vertex::skinned *)0)->P);
      if constexpr (requires{vertex::skinned::T;})
        VertexMap["InTexCoord"] = reinterpret_cast<INT_PTR>(&((vertex::skinned *)0)->T);
      if constexpr (requires{vertex::skinned::N;})
        VertexMap["InNormal"] = reinterpret_cast<INT_PTR>(&((vertex::skinned *)0)->N);
      if constexpr (requires{vertex::skinned::C;})
        VertexMap["InColor"] = reinterpret_cast<INT_PTR>(&((vertex::skinned *)0)->C);
      if constexpr (requires{vertex::skinned::Joints;})
        VertexMap["InJoints"] = reinterpret_cast<INT_PTR>(&((vertex::skinned *)0)->Joints);
      if constexpr (requires{vertex::skinned::Weights;})
        VertexMap["InWeights"] = reinterpret_cast<INT_PTR>(&((vertex::skinned *)0)->Weights);
      Rnd->BufferCreate(VertexBuf.Buffer, VertexBuf.Allocation, UINT(V.size() * sizeof(vertex::skinned)), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_SHARING_MODE_EXCLUSIVE);
      Rnd->BufferCreate(IndexBuffer.Buffer, IndexBuffer.Allocation, UINT(Ind.size() * sizeof(INT)), VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_SHARING_MODE_EXCLUSIVE);
      Rnd->BufferUpdate(VertexBuf.Buffer, 0, UINT(V.size() * sizeof(vertex::skinned)), V.data());
      Rnd->BufferUpdate(IndexBuffer.Buffer, 0, UINT(Ind.size() * sizeof(INT)), Ind.data());
      if (V.size() != 0)
      {
        // Collect min-max info
        if constexpr (requires{vertex::skinned::P;})
        {
          MinBB = MaxBB = V[0].P;
          for (auto vrt : V)
            MinBB = vrt.P.Min(MinBB), MaxBB = vrt.P.Max(MaxBB);
        }
        NoofV = V.size();
      }
    //}
    //else
    //{
    //  VertexStride = sizeof(vertex::std);
 
    //  if constexpr (requires{vertex::std::P;})
    //    VertexMap["InPosition"] = reinterpret_cast<INT_PTR>(&((vertex::std *)0)->P);
    //  if constexpr (requires{vertex::std::T;})
    //    VertexMap["InTexCoord"] = reinterpret_cast<INT_PTR>(&((vertex::std *)0)->T);
    //  if constexpr (requires{vertex::std::N;})
    //    VertexMap["InNormal"] = reinterpret_cast<INT_PTR>(&((vertex::std *)0)->N);
    //  if constexpr (requires{vertex::std::C;})
    //    VertexMap["InColor"] = reinterpret_cast<INT_PTR>(&((vertex::std *)0)->C);
    //  Rnd->BufferCreate(VertexBuf.Buffer, VertexBuf.Allocation, UINT(V.size() * sizeof(vertex::std)), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_SHARING_MODE_EXCLUSIVE);
    //  Rnd->BufferCreate(IndexBuffer.Buffer, IndexBuffer.Allocation, UINT(Ind.size() * sizeof(INT)), VK_BUFFER_USAGE_INDEX_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_SHARING_MODE_EXCLUSIVE);
    //  Rnd->BufferUpdate(VertexBuf.Buffer, 0, UINT(V.size() * sizeof(vertex::std)), V.data());
    //  Rnd->BufferUpdate(IndexBuffer.Buffer, 0, UINT(Ind.size() * sizeof(INT)), Ind.data());
    //  if (V.size() != 0)
    //  {
    //    // Collect min-max info
    //    if constexpr (requires{vertex::std::P;})
    //    {
    //      MinBB = MaxBB = V[0].P;
    //      for (auto vrt : V)
    //        MinBB = vrt.P.Min(MinBB), MaxBB = vrt.P.Max(MaxBB);
    //    }
    //    NoofV = V.size();
    //  }
    //}


    //if constexpr (requires{vertex::std::Tangent;})
    //  VertexMap["InTangent"] =
    //    reinterpret_cast<INT_PTR>(&((vertex::std *)0)->Tangent);
    //if constexpr (requires{vertex::std::Bitangent;})
    //  VertexMap["InBitangent"] =
    //    reinterpret_cast<INT_PTR>(&((vertex::std *)0)->Bitangent);
 
    ////VertexBuf.CreateBuffer(Rnd->Device, Rnd->PhysDevice, BYTE(V.size() * sizeof(vertex::std)), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE);
    //IndexBuffer.CreateBuffer(Rnd->Device, Rnd->PhysDevice, BYTE(Ind.size() * sizeof(INT)), VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE);
    //VertexBuf.BufferWrite(Rnd->Device, Rnd->PhysDevice, BYTE(V.size() * sizeof(vertex::std)), V.data());
    //IndexBuffer.BufferWrite(Rnd->Device, Rnd->PhysDevice, BYTE(Ind.size() * sizeof(INT)), Ind.data());
    //BufferCreate
 
    // Indices
    if (Ind.size() > 0)
    {
      if (V.size() != 0)
      {
      }
      NumOfElements = (INT)Ind.size();
    }
    else
        NumOfElements = (INT)V.size();
    return *this;
  } /* End of 'Create' function */

/* Primitive destroy function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::prim::Free( VOID )
{
  //VertexBuf.DestroyBuffer(Rnd->Device); //buffer destroy
  //IndexBuffer.DestroyBuffer(Rnd->Device); //buffer destroy
  Rnd->BufferFree(VertexBuf.Buffer, VertexBuf.Allocation);
  Rnd->BufferFree(IndexBuffer.Buffer, IndexBuffer.Allocation);

  NumOfElements = 0;
  MinBB = MaxBB = {};
} /* End of 'Free' function */

/* Primitive with empty vertex strem creation function.
 * ARGUMENTS:
 *   - primitive type:
 *       prim_type Type;
 *   - number of emmitted vertexes:
 *       INT NumOfV;
 * RETURNS:
 *   (prim &) self reference.
 */
arvk::prim & arvk::prim::Create( prim_type NewType, INT NumOfV )
{
  //Free();
  Type = NewType;
  Transform = matr::Identity();
  NumOfElements = NumOfV;
  VertexStride = 0;
  MinBB = MaxBB = vec3(0);

  VertexBuf.CreateBuffer(Rnd->Device, Rnd->PhysDevice, BYTE(NumOfV), VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_SHARING_MODE_EXCLUSIVE);
 
  return *this;
} /* End of 'Create' function */


/* Load model from .G3DM function.
 * ARGUMENTS:
 *   - file name (*.G3DM model) to be load:
 *       const std::string &FileName;
 *   - transform matrix:
 *       const matr &Transform;
 * RETURNS:
 *   (model &) self reference.
 */
arvk::model & arvk::model::Load( const std::string &FileName, const arvk::matr &Transform, const vec3 &FitSize )
{
  ////GLTF
  if (FileName[FileName.size() - 1] == 'f')
  {
    loader ldr;
    ldr.LoadG(FileName);
    ldrPtr = new loader(ldr);

    std::vector<material *> mtls; 


  std::vector<arvk::texture*> loadedTextures(ldr.Textures.size(), nullptr);

  //for (size_t i = 0; i < ldr.Textures.size(); i++)
  //{
  //    const auto& texInfo = ldr.Textures[i];
  //  
  //    std::cout << "Creating texture " << i << ": " << texInfo.Name << "\n";
  //  
  //    if (texInfo.ImageNo >= 0 && texInfo.ImageNo < ldr.Images.size())
  //    {
  //        const auto& imgData = ldr.Images[texInfo.ImageNo];
  //      
  //        std::string tempFile = "temp_tex_" + std::to_string(i) + ".png";
  //        std::ofstream out(tempFile, std::ios::binary);
  //      
  //        if (out.is_open())
  //        {
  //            out.write((const char*)imgData.ImageData.data(), imgData.ImageData.size());
  //            out.close();
  //          
  //            arvk::image img(tempFile);
  //          
  //            if (img.W > 0 && img.H > 0 && !img.RowsB.empty())
  //            {
  //                loadedTextures[i] = Rnd->texture_manager::TexCreate(
  //                    texInfo.Name,
  //                    img.W,
  //                    img.H,
  //                    4, // RGBA
  //                    reinterpret_cast<BYTE*>(img.RowsB[0][0]),
  //                    FALSE //
  //                );
  //              
  //                if (loadedTextures[i] != nullptr)
  //                {
  //                    std::cout << "  Created: " << img.W << "x" << img.H << " pixels\n";
  //                }
  //            }
  //          
  //            std::remove(tempFile.c_str());
  //        }
  //    }
  //}

  for (size_t i = 0; i < ldr.Textures.size(); i++)
  {
      const auto& texInfo = ldr.Textures[i];
        
      std::cout << "Creating texture " << i << ": " << texInfo.Name << "\n";
        
      if (texInfo.ImageNo >= 0 && texInfo.ImageNo < ldr.Images.size())
      {
          const auto& imgData = ldr.Images[texInfo.ImageNo];
            
          std::string cacheFileName = FileName;
          std::string tmp = imgData.Name;
          cacheFileName.erase(cacheFileName.find_last_of('/') + 1);
          cacheFileName += "textures/" + tmp;/*tmp.erase(0, tmp.find_last_of('/'));*/

          if (cacheFileName.find_last_of('.') == std::string::npos)
          {
              cacheFileName += ".png";
          }
        
          loadedTextures[i] = Rnd->texture_manager::TexCreateWithFileCache(
              cacheFileName,
              imgData.ImageData
          );          
          //loadedTextures[i] = Rnd->texture_manager::TexCreateFromMemory(
          //    texInfo.Name,
          //    imgData.ImageData
          //);
          //loadedTextures[i] = Rnd->texture_manager::TexCreate(imgData.Name);
          if (loadedTextures[i] != nullptr)
          {
              std::cout << "  Created successfully\n";
          }
          else
          {
              std::cout << "  Failed to create texture\n";
          }
      }
      else
      {
          std::cout << "  No image data found (ImageNo: " << texInfo.ImageNo << ")\n";
      }
  }

  std::vector<arvk::material*> createdMaterials(ldr.Materials.size(), nullptr);

  for (size_t i = 0; i < ldr.Materials.size(); i++)
  {
      const auto& gltfMat = ldr.Materials[i];
    
      std::cout << "\nCreating material " << i << ": " << gltfMat.Name << "\n";
    
      arvk::material* mat = Rnd->MtlCreate(gltfMat.Name);
      createdMaterials[i] = mat;
    
      if (mat == nullptr) continue;
    
      mat->Ka = gltfMat.GetKa();
      mat->Kd = gltfMat.GetKd();
      mat->Ks = gltfMat.GetKs();
      mat->Ph = gltfMat.GetPh();
      mat->Trans = gltfMat.GetTrans();
    
      // Tex[0] = BaseColor (binding 0)
      // Tex[3] = Normal (binding 1)  
      // Tex[1] = MetallicRoughness (binding 2)
      // Tex[2] = Emissive (binding 3)
      // Tex[4] = Occlusion (binding 4)
    
      if (gltfMat.BaseColorTexture != -1 && 
          gltfMat.BaseColorTexture < loadedTextures.size() &&
          loadedTextures[gltfMat.BaseColorTexture] != nullptr)
      {
          mat->Tex[0] = loadedTextures[gltfMat.BaseColorTexture];
          std::cout << "  BaseColor -> Tex[0]\n";
      }
    
      if (gltfMat.NormalTexture != -1 && 
          gltfMat.NormalTexture < loadedTextures.size() &&
          loadedTextures[gltfMat.NormalTexture] != nullptr)
      {
          mat->Tex[3] = loadedTextures[gltfMat.NormalTexture]; // Tex[3] Normal!
          std::cout << "  Normal -> Tex[3]\n";
      }
    
      if (gltfMat.MetallicRoughnessTexture != -1 && 
          gltfMat.MetallicRoughnessTexture < loadedTextures.size() &&
          loadedTextures[gltfMat.MetallicRoughnessTexture] != nullptr)
      {
          mat->Tex[1] = loadedTextures[gltfMat.MetallicRoughnessTexture]; // Tex[1] MetallicRoughness!
          std::cout << "  MetallicRoughness -> Tex[1]\n";
      }
    
      if (gltfMat.EmissiveTexture != -1 && 
          gltfMat.EmissiveTexture < loadedTextures.size() &&
          loadedTextures[gltfMat.EmissiveTexture] != nullptr)
      {
          mat->Tex[2] = loadedTextures[gltfMat.EmissiveTexture]; // Tex[2] Emissive!
          std::cout << "  Emissive -> Tex[2]\n";
      }
    
      if (gltfMat.OcclusionTexture != -1 && 
          gltfMat.OcclusionTexture < loadedTextures.size() &&
          loadedTextures[gltfMat.OcclusionTexture] != nullptr)
      {
          mat->Tex[4] = loadedTextures[gltfMat.OcclusionTexture];
          std::cout << "  Occlusion -> Tex[4]\n";
      }
    
      //mat->Create(gltfMat.Name,
      //            mat->Ka, mat->Kd, mat->Ks,
      //            mat->Ph, mat->Trans,
      //            nullptr, // шейдер
      //            {});     // текстуры уже установлены
    
      mat->UpdateDescriptorSet();
      mtls.push_back(mat);
  }

  //  // Load primitives
  //  std::function<VOID( INT )> CreatePrimitives =
  //    [this, mtls, &Transform, &ldr, &CreatePrimitives]( INT NodeIndex )
  //    {
  //      INT i = 0;
  //      material *mtl;
  //      const node &nd = ldr.Nodes[NodeIndex];
  //      //matr Tr = matr((FLT)nd.WorldMatrix.M[0][0], (FLT)nd.WorldMatrix.M[0][1], (FLT)nd.WorldMatrix.M[0][2], (FLT)nd.WorldMatrix.M[0][3],
  //      //               (FLT)nd.WorldMatrix.M[1][0], (FLT)nd.WorldMatrix.M[1][1], (FLT)nd.WorldMatrix.M[1][2], (FLT)nd.WorldMatrix.M[1][3],
  //      //               (FLT)nd.WorldMatrix.M[2][0], (FLT)nd.WorldMatrix.M[2][1], (FLT)nd.WorldMatrix.M[2][2], (FLT)nd.WorldMatrix.M[2][3],
  //      //               (FLT)nd.WorldMatrix.M[3][0], (FLT)nd.WorldMatrix.M[3][1], (FLT)nd.WorldMatrix.M[3][2], (FLT)nd.WorldMatrix.M[3][3]) * Transform;
  //      matr Tr = matr(
  //          (FLT)nd.WorldMatrix.M[0][0], (FLT)nd.WorldMatrix.M[1][0], (FLT)nd.WorldMatrix.M[2][0], (FLT)nd.WorldMatrix.M[3][0],
  //          (FLT)nd.WorldMatrix.M[0][1], (FLT)nd.WorldMatrix.M[1][1], (FLT)nd.WorldMatrix.M[2][1], (FLT)nd.WorldMatrix.M[3][1],
  //          (FLT)nd.WorldMatrix.M[0][2], (FLT)nd.WorldMatrix.M[1][2], (FLT)nd.WorldMatrix.M[2][2], (FLT)nd.WorldMatrix.M[3][2],
  //          (FLT)nd.WorldMatrix.M[0][3], (FLT)nd.WorldMatrix.M[1][3], (FLT)nd.WorldMatrix.M[2][3], (FLT)nd.WorldMatrix.M[3][3]
  //      ) * Transform;
  //      if (nd.Mesh != -1)
  //        for (auto &pr : ldr.Meshes[nd.Mesh].Prims)
  //        {
  //          if (pr.MaterialNo == -1)
  //            continue;
  //          std::vector<INT> Ind;
 
  //          //// Indices
  //          //if (auto ind16 = ldr.GetAccessorData<UINT16>(pr.IndexAccessor); ind16.size() != 0)
  //          //  Ind.reserve(ind16.size()), std::transform(ind16.begin(), ind16.end(), std::back_inserter(Ind), []( UINT16 X ){ return static_cast<INT>(X); });
  //          //else if (auto ind32 = ldr.GetAccessorData<INT>(pr.IndexAccessor); ind32.size() != 0)
  //          //  Ind = std::move(ind32);
  //          if (pr.IndexAccessor != -1)
  //          {
  //              auto indices = ldr.GetIndexData(pr.IndexAccessor);
  //              if (!indices.empty())
  //              {
  //                  Ind.reserve(indices.size());
  //                  for (auto index : indices)
  //                      Ind.push_back(static_cast<INT>(index));
  //              }
  //          } 
  //          // Vertexes
  //          auto pos = ldr.GetAccessorData<vec3>(pr.PositionAccessor);
  //          auto norm = ldr.GetAccessorData<vec3>(pr.NormalAccessor);
  //          auto tex = ldr.GetAccessorData<vec2>(pr.TexCoord0Accessor);
  //          auto color = ldr.GetAccessorData<vec4>(pr.Color0Accessor); 
  //          auto joints = ldr.GetAccessorData<vec4>(pr.Joints0Accessor);
  //          auto weights = ldr.GetAccessorData<vec4>(pr.Weights0Accessor);

  //          BOOL IsSkinned = joints.size() > 0 || weights.size() > 0; 

  //          if (IsSkinned)
  //          {
  //            std::vector<vertex::skinned> V;
  //            V.resize(pos.size(), {{0, 0, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}});
  //            INT vno = 0;
  //            for (auto &vrt : V)
  //            {
  //              vrt.P = Tr.TransformPoint(pos[vno]);
  //              if (vno < tex.size())
  //                vrt.T = tex[vno];
  //              if (vno < norm.size())
  //                vrt.N = norm[vno];
  //              if (vno < color.size())
  //                vrt.C = color[vno];
  //              if (vno < joints.size())
  //                vrt.Joints = joints[vno];
  //              if (vno < weights.size())
  //                vrt.Weights = weights[vno];
  //              vno++;
  //            }
  //            Prims << Rnd->PrimCreate(prim_type::TRIMESH, std::span(V), std::span(Ind), IsSkinned);
  //          }
  //          else
  //          {
  //            std::vector<vertex::std> V;
  //            V.resize(pos.size(), {{0, 0, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}});
  //            INT vno = 0;
  //            for (auto &vrt : V)
  //            {
  //              vrt.P = Tr.TransformPoint(pos[vno]);
  //              if (vno < tex.size())
  //                vrt.T = tex[vno];
  //              if (vno < norm.size())
  //                vrt.N = Tr.TransformNormal(norm[vno]).Normalizing();
  //              if (vno < color.size())
  //                vrt.C = color[vno];
  //              vno++;
  //            }
  //            Prims << Rnd->PrimCreate(prim_type::TRIMESH, std::span(V), std::span(Ind), IsSkinned);
  //          }
  //          // C++2023: #include <ranges>
  //          // std::ranges::transform(std::views::zip(pos, norm, tex), std::back_inserter(V),
  //          //   []( auto &&VTuple )
  //          //   {
  //          //     return {std::get<0>(VTuple), std::get<1>(VTuple), std::get<2>(VTuple), {1, 1, 1, 1}};
  //          //   });

  //          mtl = Rnd->MtlCreate("GLTF" + i);
  //          mtl->Ka = vec3(0.4);
  //          mtl->Kd = vec3(0.4);
  //          mtl->Ks = vec3(0.4);
  //          mtl->Ph = 0.4;
  //          mtl->Trans = 1;
  //          mtl->Update();
  //          Prims.back()->Mtl = mtls[pr.MaterialNo];

  //          INT t1 = 0;
  //        }
  //      //Model.Nodes[NodeIndex];
  //      for (INT subnode : nd.Subnodes)
  //        CreatePrimitives(subnode);
  //    };
  //  for (auto &rootnd : ldr.Scenes[ldr.SceneNo].RootNodes)
  //    CreatePrimitives(rootnd);
  //  //Prims[i] = Rnd->PrimCreate(prim_type::TRIMESH, std::span(V, nv), std::span(Ind, ni));
  //  return *this;
  //}
// Load primitives
std::function<VOID( INT )> CreatePrimitives =
  [this, mtls, &Transform, &ldr, &CreatePrimitives]( INT NodeIndex )
  {
    INT i = 0;
    material *mtl;
    const node &nd = ldr.Nodes[NodeIndex];
    matr Tr = matr((FLT)nd.WorldMatrix.M[0][0], (FLT)nd.WorldMatrix.M[0][1], (FLT)nd.WorldMatrix.M[0][2], (FLT)nd.WorldMatrix.M[0][3],
                    (FLT)nd.WorldMatrix.M[1][0], (FLT)nd.WorldMatrix.M[1][1], (FLT)nd.WorldMatrix.M[1][2], (FLT)nd.WorldMatrix.M[1][3],
                    (FLT)nd.WorldMatrix.M[2][0], (FLT)nd.WorldMatrix.M[2][1], (FLT)nd.WorldMatrix.M[2][2], (FLT)nd.WorldMatrix.M[2][3],
                    (FLT)nd.WorldMatrix.M[3][0], (FLT)nd.WorldMatrix.M[3][1], (FLT)nd.WorldMatrix.M[3][2], (FLT)nd.WorldMatrix.M[3][3]) * Transform;
    
    if (nd.Mesh != -1)
    {
      for (auto &pr : ldr.Meshes[nd.Mesh].Prims)
      {
        if (pr.MaterialNo == -1)
          continue;
        
        std::vector<INT> Ind;
        
        if (pr.IndexAccessor != -1)
        {
          auto indices = ldr.GetIndexData(pr.IndexAccessor);
          if (!indices.empty())
          {
            Ind.reserve(indices.size());
            for (auto index : indices)
              Ind.push_back(static_cast<INT>(index));
          }
        }
        
        std::vector<vec3> pos;
        if (pr.PositionAccessor != -1)
        {
          auto pos_data = ldr.GetAccessorData<byte12>(pr.PositionAccessor);
          pos.reserve(pos_data.size());
          for (const auto& p : pos_data)
          {
            const FLT* floats = reinterpret_cast<const FLT*>(&p);
            pos.push_back(vec3(floats[0], floats[1], floats[2]));
          }
        }
        
        std::vector<vec3> norm;
        if (pr.NormalAccessor != -1)
        {
          auto norm_data = ldr.GetAccessorData<byte12>(pr.NormalAccessor);
          norm.reserve(norm_data.size());
          for (const auto& n : norm_data)
          {
            const FLT* floats = reinterpret_cast<const FLT*>(&n);
            norm.push_back(vec3(floats[0], floats[1], floats[2]));
          }
        }        
        std::vector<vec2> tex;
        if (pr.TexCoord0Accessor != -1)
        {
          auto tex_data = ldr.GetAccessorData<byte8>(pr.TexCoord0Accessor);
          tex.reserve(tex_data.size());
          for (const auto& t : tex_data)
          {
            const FLT* floats = reinterpret_cast<const FLT*>(&t);
            tex.push_back(vec2(floats[0], floats[1]));
          }
        }
        
        std::vector<vec4> color;
        if (pr.Color0Accessor != -1)
        {
          auto color_data = ldr.GetAccessorData<byte16>(pr.Color0Accessor);
          color.reserve(color_data.size());
          for (const auto& c : color_data)
          {
            const FLT* floats = reinterpret_cast<const FLT*>(&c);
            color.push_back(vec4(floats[0], floats[1], floats[2], floats[3]));
          }
        }
        
        std::vector<mth::vec4<INT>> joints_flt;
        if (pr.Joints0Accessor != -1)
        {
          std::vector<mth::vec4<UINT16>> joints_temp; 
    
          if (auto joints_0 = ldr.GetAccessorData<mth::vec4<UINT8>>(pr.Joints0Accessor); joints_0.size() != 0)
          {
            joints_temp.reserve(joints_0.size());
            std::transform(joints_0.begin(), joints_0.end(), std::back_inserter(joints_temp), 
              [](mth::vec4<UINT8> X) 
              { 
                return mth::vec4<UINT16>(X.X, X.Y, X.Z, X.W); 
              });
          }
          else if (auto joints_1 = ldr.GetAccessorData<mth::vec4<UINT16>>(pr.Joints0Accessor); joints_1.size() != 0)
          {
            joints_temp = joints_1;
          }
    
          joints_flt.reserve(joints_temp.size());
          for (const auto& j : joints_temp)
          {
            joints_flt.push_back(mth::vec4<INT32>(ldr.Skins[nd.Skin].Joints[j.X], ldr.Skins[nd.Skin].Joints[j.Y], ldr.Skins[nd.Skin].Joints[j.Z], ldr.Skins[nd.Skin].Joints[j.W]));
          }
        }
        //std::vector<vec4> weights;
        //if (pr.Weights0Accessor != -1)
        //{
        //    auto weight_data = ldr.GetAccessorData<FLT>(pr.Weights0Accessor);
        //    if (weight_data.size() >= 4 && weight_data.size() % 4 == 0)
        //    {
        //        weights.reserve(weight_data.size() / 4);
        //        for (size_t i = 0; i < weight_data.size(); i += 4)
        //        {
        //            weights.push_back(vec4(
        //                weight_data[i],
        //                weight_data[i + 1],
        //                weight_data[i + 2],
        //                weight_data[i + 3]
        //            ));
        //        }
        //    }
        //}        

        std::vector<vec4> weights;
        if (pr.Weights0Accessor != -1)
        {
          auto weight_data = ldr.GetAccessorData<byte16>(pr.Weights0Accessor);
    
          if (!weight_data.empty())
          {
            weights.reserve(weight_data.size());
            for (const auto& w_bytes : weight_data)
            {
              const FLT* floats = reinterpret_cast<const FLT*>(&w_bytes);
              weights.push_back(vec4(floats[0], floats[1], floats[2], floats[3]));
            }
            std::cout << "Loaded " << weights.size() << " weights as byte16\n";
          }
          else
          {
            std::cout << "Could not load weights as byte16\n";
          }
        }

        BOOL IsSkinned = !joints_flt.empty() || !weights.empty();
        
        //if (IsSkinned)
        //{
            //std::vector<vertex::skinned> V;
            //V.resize(pos.size(), {{0, 0, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}, {0, 0, 0, 0}, {0, 0, 0, 0}});
            //INT vno = 0;
            //for (auto &vrt : V)
            //{
            //    vrt.P = pos[vno]; 
            //    if (vno < tex.size())
            //        vrt.T = tex[vno];
            //    if (vno < norm.size())
            //        vrt.N = norm[vno];  
            //    if (vno < color.size())
            //        vrt.C = color[vno];
            //    if (vno < joints_flt.size())
            //        vrt.Joints = joints_flt[vno];
            //    if (vno < weights.size())
            //        vrt.Weights = weights[vno];
            //    vno++;
            //}
            //Prims << Rnd->PrimCreate(prim_type::TRIMESH, std::span(V), std::span(Ind), IsSkinned);
            std::vector<vertex::skinned> V;
            V.resize(pos.size());

            INT vno = 0;
            for (auto &vrt : V)
            {
              vrt.P = pos[vno]; 
              vrt.T = (vno < tex.size()) ? tex[vno] : vec2(0, 0);
              vrt.N = (vno < norm.size()) ? norm[vno] : vec3(0, 0, 1); 
              //vrt.N = (vno < norm.size()) ? Tr.TransformNormal(norm[vno]).Normalizing() : vec3(0, 0, 1);
              vrt.C = (vno < color.size()) ? color[vno] : vec4(1, 1, 1, 1);
              vrt.Joints = (vno < joints_flt.size()) ? joints_flt[vno] : mth::vec4<INT>(0, 0, 0, 0);
              vrt.Weights = (vno < weights.size()) ? weights[vno] : vec4(0, 0, 0, 0);
              vno++;
            }

            std::span<vertex::skinned> vertexSpan(V);
            std::span<INT> indexSpan(Ind);

            Prims << Rnd->PrimCreate(prim_type::TRIMESH, vertexSpan, indexSpan, IsSkinned);
        //}
      //  else
      //  {
      //      std::vector<vertex::std> V;
      //      V.resize(pos.size(), {{0, 0, 0}, {0, 0}, {0, 0, 1}, {1, 1, 1, 1}});
      //      INT vno = 0;
      //      for (auto &vrt : V)
      //      {
      //          vrt.P = Tr.TransformPoint(pos[vno]);
      //          if (vno < tex.size())
      //              vrt.T = tex[vno];
      //          if (vno < norm.size())
      //              vrt.N = Tr.TransformNormal(norm[vno]).Normalizing();
      //          if (vno < color.size())
      //              vrt.C = color[vno];
      //          vno++;
      //      }
      //      Prims << Rnd->PrimCreate(prim_type::TRIMESH, std::span(V), std::span(Ind), IsSkinned);
      //  }
      //  
        Prims.back()->Mtl = mtls[pr.MaterialNo];
        i++;
      }
    }
    
    for (INT subnode : nd.Subnodes)
        CreatePrimitives(subnode);
  };
  for (auto &rootnd : ldr.Scenes[ldr.SceneNo].RootNodes)
      CreatePrimitives(rootnd);
    //Prims[i] = Rnd->PrimCreate(prim_type::TRIMESH, std::span(V, nv), std::span(Ind, ni));
    return *this;
  }

//G3DM
  INT a = 0;
  CHAR sym[5] {'|', '/', '-', '\\'};

  for (auto pr : Prims)
    Rnd->render::PrimFree(pr);
  Prims.clear();
  this->Transform = matr::Identity();
  MinBB = MaxBB = {0, 0, 0};

  std::fstream f(FileName, std::fstream::in | std::fstream::binary);

  if (!f.is_open())
    return *this;

  f.seekg(0, std::fstream::end);
  SIZE_T flen = f.tellg();
  f.seekg(0, std::fstream::beg);
  
  std::vector<BYTE> mem;
  mem.resize(flen);
  f.read((CHAR *)mem.data(), flen);
  BYTE *ptr = mem.data();

  rdr rd(ptr);

  DWORD sign;
  rd(&sign);
  if (sign != "G3DM"_dword)
    return *this;

  INT NoofP = 0, NoofM = 0, NoofT = 0;
  rd(&NoofP);
  rd(&NoofM);
  rd(&NoofT);

  BYTE *save_ptr = ptr;
  BOOL IsFirstVertex = TRUE;

  for (INT i = 0; i < NoofP; i++)
  {
    UINT nv = 0, ni = 0, mtl_no;
    vertex::std *V;
    INT *Ind;

    rd(&nv);
    rd(&ni);
    rd(&mtl_no);
    rd(&V, nv);
    rd(&Ind, ni);
    std::cout << std::format("Reading vertexes: {:1} / {:1} ({:1})\r", i + 1, NoofP, sym[a++ % 4]);

    if (nv > 0)
    {
      if (IsFirstVertex)
      {
        IsFirstVertex = FALSE;
        MinBB = MaxBB = V[0].P;
      }
      for (INT j = 0; j < nv; j++)
      {
        MinBB = MinBB.Min(V[j].P);
        MaxBB = MaxBB.Max(V[j].P);
      }
    }
  }
  std::cout << std::format("Reading vertexes: {:1} / {:1} (+)\r", NoofP, NoofP);
  std::cout << std::format("\n");

  vec3 B = MaxBB - MinBB, scv {1, 1, 1};
  matr M(matr::Identity());
  if (FitSize.X != 0)
  {
    scv = vec3{FitSize.X / B.X};
    M = matr::Translate(-MinBB) * matr::Scale(scv);
  }
  else if (FitSize.Y != 0)
  {
    scv = vec3{FitSize.Y / B.Y};
    M = matr::Translate(-MinBB) * matr::Scale(scv);
  }
  else if (FitSize.Z != 0)
  {
    scv = vec3{FitSize.Z / B.Z};
    M = matr::Translate(-MinBB) * matr::Scale(scv);
  }

  matr Trans = M * Transform;
  MinBB = Trans.TransformPoint(MinBB);
  MaxBB = Trans.TransformPoint(MaxBB);
  ptr = save_ptr;

  Prims.resize(NoofP);
  std::vector<INT> prims_mtl;
  prims_mtl.resize(NoofP);

  for (INT i = 0; i < NoofP; i++)
  {
    UINT nv = 0, ni = 0, mtl_no;
    vertex::std *V;
    INT *Ind;

    rd(&nv);
    rd(&ni);
    rd(&mtl_no);
    rd(&V, nv);
    rd(&Ind, ni);
    std::cout << std::format("Loading primitives: {:1} / {:1} ({:1})\r", i + 1, NoofP, sym[a++ % 4]);
    std::vector<vertex::skinned> SkV(nv);
    for (INT j = 0; j < nv; j++)
    {
      V[j].P = Trans.TransformPoint(V[j].P);
      V[j].N = Trans.TransformNormal(V[j].N).Normalizing();
      SkV[j] = vertex::skinned(V[j]);
    }
    std::span<vertex::skinned> vertexSpan(SkV);
    std::span<INT> indexSpan(Ind, ni);

    Prims[i] = Rnd->PrimCreate(prim_type::TRIMESH, vertexSpan, indexSpan);
  }
  std::cout << std::format("Loading primitives: {:1} / {:1} (+)\r", NoofP, NoofP);
  std::cout << std::format("\n");

  struct STORAGE_MATERIAL
  {
    CHAR Name[300];
    vec3 Ka, Kd, Ks;
    FLT Ph;
    FLT Trans;
    INT Tex[8];

    CHAR ShaderStr[300];
    INT Shader;
  };

  std::vector<material *> mtls;
  std::vector<STORAGE_MATERIAL> store_mtls;
  mtls.resize(NoofM);
  store_mtls.resize(NoofM);

  if (NoofM > 0)
  {
    rd(&store_mtls[0], NoofM);

    for (INT i = 0; i < NoofM; i++)
    {
      mtls[i] = Rnd->MtlCreate(FileName + "::" + store_mtls[i].Name);
      mtls[i]->Ka = store_mtls[i].Ka;
      mtls[i]->Kd = store_mtls[i].Kd;
      mtls[i]->Ks = store_mtls[i].Ks;
      mtls[i]->Ph = store_mtls[i].Ph;
      mtls[i]->Trans = store_mtls[i].Trans;
      mtls[i]->Update();
      std::cout << std::format("Loading materials: {:1} / {:1} ({:1})\r", i + 1, NoofM, sym[a++ % 4]);
    }
  }
  std::cout << std::format("Loading materials: {:1} / {:1} (+)\r", NoofM, NoofM);
  std::cout << std::format("\n");

  std::vector<texture *> texs;
  texs.resize(NoofT);
  for (INT i = 0; i < NoofT; i++)
  {
    CHAR Name[300];
    INT W, H, C;

    rd(Name, 300);
    rd(&W);
    rd(&H);
    rd(&C);
    std::cout << std::format("Loading textures: {:1} / {:1} ({:1})\r", i + 1, NoofT, sym[a++ % 4]);

    SIZE_T last_byte= (ptr - mem.data()) + W * H * C;
    if (last_byte <= mem.size())
      texs[i] = Rnd->TexCreate(FileName + "_" + Name, W, H, C, ptr);
    
    else
      break;
    ptr += W * H * C;
  }
  std::cout << std::format("Loading textures: {:1} / {:1} (+)\r", NoofT, NoofT);

  for (INT i = 0; i < NoofM; i++)
  {
    for (INT t = 0; t < 8; t++)
      if (store_mtls[i].Tex[t] != -1 && store_mtls[i].Tex[t] >= 0 && store_mtls[i].Tex[t] < texs.size() && texs[store_mtls[i].Tex[t]] != nullptr)
        mtls[i]->Tex[t] = texs[store_mtls[i].Tex[t]];
    mtls[i]->UpdateDescriptorSet();
  }

  for (INT i = 0; i < NoofP; i++)
    if (prims_mtl[i] != -1)
      if (prims_mtl[i] >= 0 && prims_mtl[i] < mtls.size())
        Prims[i]->Mtl = mtls[prims_mtl[i]]/*, Prims[i]->Mtl->Shd = Rnd->shader_manager::Find("default")*/;
      else
        Prims[i]->Mtl = Rnd->material_manager::Find("default");

  return *this;
}

/* Create primitive with empty vertex strem function.
  * ARGUMENTS:
  *   - primitive type:
  *       prim_type Type;
  *   - number of emmitted vertexes:
  *       INT NumOfV;
  * RETURNS:
  *   (prim *) created primitive interface.
  */
arvk::prim * arvk::primitive_manager::PrimCreate( prim_type Type, INT NumOfV )
{
  return resource_manager::Add(prim(RndRef).Create(Type, NumOfV));
} /* End of 'PrimCreate' function */

/* Create primitive function.
  * ARGUMENTS:
  *   - primitive pointer:
  *       prim *Pr;
  * RETURNS: None.
  *   (prim *) created primitive interface.
  */
VOID arvk::primitive_manager::PrimFree( prim *Pr )
{
  resource_manager::Delete(Pr);
} /* End of 'PrimFree' function */

template arvk::prim & arvk::prim::Create<arvk::vertex::std>(
    prim_type NewType,
    const std::span<arvk::vertex::std> &V,
    const std::span<INT> &Ind,
    BOOL IsSkinned
);

template arvk::prim & arvk::prim::Create<arvk::vertex::skinned>(
    prim_type NewType,
    const std::span<arvk::vertex::skinned> &V,
    const std::span<INT> &Ind,
    BOOL IsSkinned
);

template arvk::prim * arvk::primitive_manager::PrimCreate<arvk::vertex::std>(
    prim_type NewType,
    const std::span<arvk::vertex::std> &V,
    const std::span<INT> &Ind,
    BOOL IsSkinned
);

template arvk::prim * arvk::primitive_manager::PrimCreate<arvk::vertex::skinned>(
    prim_type NewType,
    const std::span<arvk::vertex::skinned> &V,
    const std::span<INT> &Ind,
    BOOL IsSkinned
);

/* END OF 'prim.cpp' FILE */
