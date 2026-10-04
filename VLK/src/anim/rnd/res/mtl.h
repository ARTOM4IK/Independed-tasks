/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : mtl.h
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

#ifndef __mtl_h_
#define __mtl_h_

#include "resources.h"
#include "shd.h"
#include "tex.h"
#include "buf.h"

/* Animation namespace */
namespace arvk
{
  /* Material class */
  class material : public resource
  {
  private:
    struct BUF_MTL
    {
      vec4 Ka;             // Ambient
      vec4 KdTrans;        // Diffuse + Transparency
      vec4 KsPh;           // Specular + Phong
      INT TextureFlags[8]; // Texture usage flags
    }; /* End of 'BUF_MTL' structure */
 
  public:
    std::string Name;     // Material name
    vec3 Ka, Kd, Ks;      // Illumination coefficients (anbient, diffuse, specular)
    FLT Ph, Trans;        // Phong coefficient and transparency value
    shader *Shd {};       // Shader pointer
    texture *Tex[8] {};   // Texture pointers
    buffer *BufferMtl {}; // Material data buffer
    VkDescriptorSet DescriptorSet = VK_NULL_HANDLE;
    buffer* BoneBuffer = nullptr;

    material( VOID ) : Ph(0), Trans(0), Ka(vec3(0)), Kd(vec3(0)), Ks(vec3(0)) 
    {
    } /* End of 'buffer' function */


    material( render &rnd ) : Ph(0), Trans(0), Ka(vec3(0)), Kd(vec3(0)), Ks(vec3(0)) 
    {
      Rnd = &rnd;
    } /* End of 'material' function */

    ~material( VOID )
    {
    } /* End of '~material' function */

    VOID SetBoneBuffer(buffer* bones) {
        BoneBuffer = bones;
        UpdateBoneDescriptor();
    }
    
    BOOL HasBoneBuffer( VOID ) const { return BoneBuffer != nullptr; }
    
    VOID UpdateBoneDescriptor( VOID ); 

    VOID UpdateDescriptorSet( VOID );

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
    material & Create( const std::string &NewName,
                       const vec3 &NewKa = vec3(0.1), const vec3 &NewKd = vec3(0.9), const vec3 &NewKs = vec3(0.0),
                       FLT NewPh = 30, FLT NewTrans = 1,
                       shader *NewShd = nullptr,
                       std::initializer_list<texture *> Textures = {} );
    /* Material creation function.
     * ARGUMENTS:
     *   - material name:
     *       const std::string &FileNamePrefix;
     * RETURNS:
     *   (material *) material pointer.
     */
    VOID Free( VOID );

    /* Material apply function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (shader *) shader pointer.
     */
    shader * Apply( VOID );

    /* Update material function.
     * ARGUMENTS: None.
     * RETURNS:
     *   (VOID) None.
     */
    VOID Update( VOID );
  }; /* End of 'material' class */
 
  /* Material manager class */
  class material_manager : public resource_manager<material, std::string>
  {
  public:
    material * MtlCreate( const std::string &FileNamePrefix );

    /* Material free function.
     * ARGUMENTS:
     *   - primitive pointer:
     *       prim *Pr;
     * RETURNS: None.
     *   (prim *) created primitive interface.
     */
    VOID MtlFree( material *Mtl )
    {
      resource_manager::Delete(Mtl);
    } /* End of 'MtlFree' function */

    material_manager( render &Rnd ) : resource_manager(Rnd)
    {
    }

    ~material_manager( VOID )
    {
    }
  }; /* End of 'material_manager' class */
} /* End of 'arvk' namespace */

#endif /* __mtl_h_ */

/* END OF 'mtl.h' FILE */
