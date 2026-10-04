/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : animated_model.h
 * PURPOSE     : Simple animation system.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 
 */

#ifndef __animated_model_h_
#define __animated_model_h_

#include "arvk.h"

/* Vulkan namaspace */
namespace arvk
{
  /* Simple animation controller */
  class simple_animation_controller 
  {
  private:
      loader* Loader = nullptr;
      std::vector<matr::matr_data> BoneMatrices;
      std::vector<matr::matr_data> InverseBindMatrices;
      FLT CurrentTime = 0.0f;
      FLT Speed = 1.0f;
      BOOL IsPlaying = TRUE;
      
  public:
      simple_animation_controller(loader* ldr = nullptr) : Loader(ldr) 
      {
        if (Loader && !Loader->Skins.empty()) 
        {
          const auto& skin = Loader->Skins[0];
          size_t boneCount = Loader->Nodes.size();
            
          BoneMatrices.resize(boneCount, matr::Identity());
          InverseBindMatrices.resize(boneCount);
            
          // save bind matrix
          for (size_t i = 0; i < boneCount; i++) 
          {
            InverseBindMatrices[skin.Joints[i]] = skin.InverseBindMatrices[i];
          }
        }
      } /* End of 'simple_animation_controller' function */
      
      VOID SetLoader( loader* ldr )
      { 
        Loader = ldr; 
        if (Loader && !Loader->Skins.empty()) 
        {
          const auto& skin = Loader->Skins[0];
          size_t boneCount = Loader->Nodes.size();
        
          BoneMatrices.resize(boneCount, matr::Identity());
          InverseBindMatrices.resize(boneCount);
        
          for (size_t i = 0; i < skin.Joints.size(); i++) 
          {
            InverseBindMatrices[skin.Joints[i]] = skin.InverseBindMatrices[i];
          }
        }
      } /* End of 'SetLoader' function */
      
      VOID Update( FLT DeltaTime )
      {
        //if (!IsPlaying || !Loader || Loader->Animations.empty())
        //    return;
              
        CurrentTime += DeltaTime * Speed;
          
        FLT angle = CurrentTime * 30.0f;
          
        for (size_t i = 0; i < BoneMatrices.size(); i++)
        {
          //BoneMatrices[i] = InverseBindMatrices[i]/* * matr::Identity()*/;
          ////BoneMatrices[i] = matr::RotateY(CurrentTime * 2.0f);
          ////matr currentPose = matr::RotateY(angle * (i + 1) * 0.1f);
          ////BoneMatrices[i] = InverseBindMatrices[i] * currentPose;
          const auto& skin = Loader->Skins[0];
          if (i < BoneMatrices.size())
          {
            //INT jointIndex = skin.Joints[i];
            const auto& node = Loader->Nodes[i];
            
            matr worldMat;
            for (int row = 0; row < 4; row++)
              for (int col = 0; col < 4; col++)
                worldMat.M[row][col] = static_cast<FLT>(node.WorldMatrix.M[row][col]);
            
            //matr animRot = matr::RotateY(angle);
            
            BoneMatrices[i] = /*animRot */ (matr(InverseBindMatrices[i].M) * worldMat).M;
          }
          //BoneMatrices[i] = matr::Identity();
        }
      } /* End of 'Update' function */
      
      VOID Play( VOID ) 
      { 
        IsPlaying = TRUE;
      } /* End of 'Play' function */

      VOID Pause( VOID ) 
      { 
        IsPlaying = FALSE; 
      } /* End of 'Pause' function */

      VOID SetSpeed( FLT speed ) 
      { 
        Speed = speed; 
      } /* End of 'SetSpeed' function */

      FLT GetSpeed( VOID ) const 
      { 
        return Speed; 
      } /* End of 'GetSpeed' function */
      
      std::vector<matr::matr_data>& GetBoneMatrices( VOID ) 
      { 
        return BoneMatrices;
      } /* End of 'GetBoneMatrices' function */

      BOOL HasBones( VOID ) const 
      { 
        return !BoneMatrices.empty(); 
      } /* End of 'HasBones' function */
  }; /* End of 'simple_animation_controller' class */
  
  /* Animated model wrapper */
  class animated_model_wrapper 
  {
  private:
    model* BaseModel = nullptr;
    std::shared_ptr<loader> GltfLoader;
    simple_animation_controller AnimCtrl;
    buffer* BoneBuffer = nullptr;
    render* Rnd = nullptr;
      
  public:
    animated_model_wrapper( render* rnd ) : Rnd(rnd)
    {
    } /* End of 'animated_model_wrapper' function */
      
    ~animated_model_wrapper( VOID ) 
    {
      if (BoneBuffer) 
      {
        BoneBuffer->Free();
      }
    } /* End of '~animated_model_wrapper' function */
      
    BOOL Load( const std::string& FileName, const matr& Transform = matr::Identity(), const vec3& FitSize = vec3(0) ) 
    {
      BaseModel = Rnd->model_manager::ModelCreate(FileName, Transform, FitSize);
      if (!BaseModel) return FALSE;
          
      if (FileName.size() > 4 && FileName.substr(FileName.size() - 4) == "gltf") 
      {
        GltfLoader = std::shared_ptr<loader>(BaseModel->ldrPtr);
        //GltfLoader->LoadG(FileName);
        //GltfLoader = BaseModel->ldrPtr;

        if (!GltfLoader->Skins.empty()) 
        {
          AnimCtrl.SetLoader(GltfLoader.get());
          CreateBoneBuffer();
          std::cout << "Animation loaded with " 
                    << GltfLoader->Skins[0].Joints.size() 
                    << " bones\n";
          return TRUE;
        }
      }
          
      return FALSE;
    } /* End of 'Load' function */
      
    VOID UpdateAnimation( FLT DeltaTime ) 
    {
      if (!HasAnimation())
        return;
          
      AnimCtrl.Update(DeltaTime);
      UpdateBoneBuffer();
    } /* End of 'UpdateAnimation' function */
      
    model* GetModel( VOID ) const 
    {
      return BaseModel; 
    } /* End of 'GetModel' function */
      
    VOID Play( VOID ) 
    { 
      AnimCtrl.Play(); 
    } /* End of 'Play' function */

    VOID Pause( VOID ) 
    { 
      AnimCtrl.Pause();
    } /* End of 'Pause' function */

    VOID SetSpeed(FLT speed) 
    { 
      AnimCtrl.SetSpeed(speed);
    } /* End of 'SetSpeed' function */

    FLT GetSpeed( VOID ) const 
    { 
      return AnimCtrl.GetSpeed(); 
    } /* End of 'GetSpeed' function */
      
    BOOL HasAnimation( VOID ) const 
    { 
      return AnimCtrl.HasBones();
    } /* End of 'HasAnimation' function */
      
  private:
    VOID CreateBoneBuffer( VOID ) 
    {
      if (!AnimCtrl.HasBones())
        return;
    
      auto& bones = AnimCtrl.GetBoneMatrices();
    
      BoneBuffer = Rnd->buffer_manager::BufCreate<matr::matr_data>(1, nullptr);
    
      if (BoneBuffer) 
      {
        std::vector<matr::matr_data> initMatrices(bones.size(), matr::Identity());
        
        BoneBuffer->CreateData(initMatrices.data(), sizeof(matr::matr_data) * bones.size(), 0);
        
        if (BaseModel) 
        {
          for (auto prim : BaseModel->Prims) 
          {
            if (prim->Mtl != nullptr) 
            {
              prim->Mtl->SetBoneBuffer(BoneBuffer);
              prim->Mtl->UpdateDescriptorSet();
            }
          }
        }
      }
    } /* End of 'CreateBoneBuffer' function */
      
    VOID UpdateBoneBuffer( VOID ) 
    {
      if (!BoneBuffer || !AnimCtrl.HasBones()) 
        return;
          
      auto& bones = AnimCtrl.GetBoneMatrices();
          
      BoneBuffer->Update(bones.data(), sizeof(matr::matr_data) * bones.size());
    } /* End of 'UpdateBoneBuffer' function */
  }; /* End of 'animated_model_wrapper' class */
} /* End of 'arvk' namespace */

#endif /* __animated_model_h_ */