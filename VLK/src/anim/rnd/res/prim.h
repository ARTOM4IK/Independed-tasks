/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : prim.h
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

#ifndef __prim_h_
#define __prim_h_

#include "resources.h"
#include "anim/rnd/res/gltf.h"

/* Project namespace */
namespace arvk
{
  //namespace vertex
  //{
  //  struct std
  //  {
  //    vec3 P;  // Vertex position
  //    vec2 T;  // Vertex texture coordinates
  //    vec3 N;  // Normal at vertex
  //    vec4 C;  // Vertex color
 
  //    std( VOID )
  //    {
  //    }
  //    std( const vec3 &NewP,
  //         const vec2 &NewT = vec2(0, 0),
  //         const vec3 &NewN = vec3(0, 1, 0),
  //         const vec4 &NewC = vec4(1) ) :
  //      P(NewP), T(NewT), N(NewN), C(NewC)
  //    {
  //    }
  //  }; /* End of 'std' structure */
  //} /* end of 'vertex' namespace */

  class render;
 
  /* Primitive shape representation type */
  enum struct prim_type
  {
    TRIMESH, /* Triangle mesh */
    POINTS,  /* Points collection */
    STRIP    /* Strip of triangles */
  }; /* End of 'prim_type' enum */

  /* Primitive handle class */
  class prim : public resource
  {
    friend render;
    friend class primitive_manager;
    template<typename entry_type, typename index_type> friend class resource_manager;
 
  private:
    prim_type Type {};    // Primitive type
    UINT VA {};           // Primitive vertex array
    UINT VBuf {};         // Vertex buffer
    UINT IBuf {};         // Index buffer
    INT NumOfElements {}, NoofV {}; // Number of elements
    matr Transform {};    // Primitive transformation matrix
    VlkBuffer VertexBuf, IndexBuffer {};
 
    mutable BOOL IsVAUpdated = FALSE; // Veretx array update flag
 
    // Vertex parameters map (vertex attribute field, offset)
    std::map<std::string, INT> VertexMap;
    INT VertexStride {}; // Vertex stride in bytes
 
  public:
    material *Mtl {};     // Material pointer
    vec3
      MinBB {0},          // Minimal primitive position
      MaxBB {0};          // Maximal primitive position
 

    prim( VOID ) 
    {
    } /* End of 'buffer' function */

    /* Class constructor */
    prim( render &rnd );
 
    /* Class destructor */
    ~prim( VOID )
    {
    } /* End of '~prim' function */
 
    /* Primitive destroy function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );
 
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
      prim & Create( prim_type NewType,
                     const std::span<vertex_type> &V,
                     const std::span<INT> &Ind, BOOL IsSkinned = FALSE );

    /* Update primitive vertex array function.
     * ARGUMENTS: None.
     * RETURNS: Non.
     */
    VOID UpdateVA( VOID ) const
    {
      //if (Mtl == nullptr || Mtl->Shd == nullptr)
      //  return;
      //if (IsVAUpdated)
      //  return;
      //IsVAUpdated = TRUE;
 
      //// Activate vertex array
      //glBindVertexArray(VA);
      //                                      
      //// Activate vertex buffer
      //glBindBuffer(GL_ARRAY_BUFFER, VBuf);
 
      ////Setup data order due to vertex map
      //for (auto &a : VertexMap)
      //  if (auto attr = Mtl->Shd->Attributes.find(a.first);
      //      attr != Mtl->Shd->Attributes.end())
      //  {
      //    glEnableVertexAttribArray(attr->second.Loc);
      //    glVertexAttribPointer(attr->second.Loc,     // layout
      //      attr->second.Components,                  // coumponents count
      //      attr->second.IsFloat ? GL_FLOAT : GL_INT, // comp. type
      //      FALSE,                                    // normalize flag
      //      VertexStride,                             // stride
      //      reinterpret_cast<VOID *>((UINT_PTR)a.second)); // offset
      //  }
      //// Disable vertex array
      //glBindVertexArray(0);
    } /* End of 'UpdateVA' function */

    /* Primitive with empty vertex strem creation function.
     * ARGUMENTS:
     *   - primitive type:
     *       prim_type Type;
     *   - number of emmitted vertexes:
     *       INT NumOfV;
     * RETURNS:
     *   (prim &) self reference.
     */
    prim & Create( prim_type NewType, INT NumOfV );
  }; /* End of 'prim' class */
 
  /* Primitive manager */
  class primitive_manager : public resource_manager<prim>
  {
  public:
    primitive_manager( render &Rnd ) : resource_manager<prim>(Rnd)
    {
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
     *   (prim *) created primitive interface.
     */
    template<class vertex_type>
     prim * PrimCreate( prim_type NewType,
                         const std::span<vertex_type> &V,
                         const std::span<INT> &Ind, BOOL IsSkinned = FALSE )
      {
        return resource_manager::Add(prim(RndRef).Create(NewType, V, Ind, IsSkinned));
      } /* End of 'PrimCreate' function */
 
    /* Create primitive with empty vertex strem function.
     * ARGUMENTS:
     *   - primitive type:
     *       prim_type Type;
     *   - number of emmitted vertexes:
     *       INT NumOfV;
     * RETURNS:
     *   (prim *) created primitive interface.
     */
    prim * PrimCreate( prim_type Type, INT NumOfV );
                                                                                          
    /* Create primitive function.
     * ARGUMENTS:
     *   - primitive pointer:
     *       prim *Pr;
     * RETURNS: None.
     *   (prim *) created primitive interface.
     */
    VOID PrimFree( prim *Pr );
  }; /* End of 'primitive_manager' class */

  /* Unstructured data file reader class */
  class rdr
  {
  private:
    // Memory pointer reference
    BYTE *&Ptr;
 
  public:
    /* Class constructor.
      * ARGUMENTS:
      *   - reference to memory pointer:
      *       BYTE *&PtrRef;
      */
    rdr( BYTE *&PtrRef ) : Ptr(PtrRef)
    {
    } /* End of 'rdr' function */
 
    /* Read data function.
      * ARGUMENT:
      *   - read data pointer:
      *       type *Data;
      *   - read data count:
      *       INT Count;
      * RETURNS: None.
      */
    template<typename type>
      VOID operator()( type *Data, const INT Count = 1 )
      {
        if (Count == 1)
          *Data = *(type *)Ptr, Ptr += sizeof(type);
        else
        {
          memcpy(Data, Ptr, sizeof(type) * Count);
          Ptr += sizeof(type) * Count;
        }
      } /* End of 'operator()' function */
 
    /* Read data function.
      * ARGUMENT:
      *   - read data (skip with store pointer) pointer:
      *       type **Data;
      *   - read data count:
      *       INT Count;
      * RETURNS: None.
      */
    template<typename type>
      VOID operator()( type **Data, const INT Count = 1 )
      {
        *Data = (type *)Ptr;
        Ptr += sizeof(type) * Count;
      } /* End of 'operator()' function */
  }; /* End of 'rdr' class */

  /* Set of primitives class */
  class model : public resource
  {
  public:
    matr Transform;      // Transformation matrix
    loader *ldrPtr;
    stock<prim *> Prims; // Stock of primitives
    vec3
      MinBB {},          // Minimal primitives set position
      MaxBB {};          // Maximal primitives set position
    buffer* BoneBuffer = nullptr;
    VOID SetBoneBuffer(buffer* bones) { BoneBuffer = bones; }

    /* Default constructor */
    model( VOID ) : Transform(matr::Identity())
    {
    } /* End of 'model' function */

    /* Default constructor */
    model( render &rnd ) : Transform(matr::Identity())
    {
      Rnd = &rnd;
    } /* End of 'model' function */
 
    /* Destructor */
    ~model( VOID )
    {
    }
 
    /* Add new primitive to set function.
     * ARGUMENTS:
     *   - primitive to be add:
     *       primt *Pr;
     * RETURNS:
     *   (model &) self reference.
     */
    model & operator<<( prim *Pr )
    {
      Prims << Pr;
      return *this;
    } /* End of 'operator<<' function */
 
    /* Load model from .G3DM function.
     * ARGUMENTS:
     *   - file name (*.G3DM model) to be load:
     *       const std::string &FileName;
     *   - transform matrix:
     *       const matr &Transform;
     * RETURNS:
     *   (model &) self reference.
     */
    model & Load( const std::string &FileName, const matr &Transform = matr::Identity(), const vec3 &FitSize = vec3(0) );

    /* Free model function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID )
    {
    } /* End of 'Free' function */
  }; /* End of model' class */

  /* Primitive manager */
  class model_manager : public resource_manager<model>
  {
  public:
    model_manager( render &Rnd ) : resource_manager<model>(Rnd)
    {
    }
    model * ModelCreate( const std::string &FileName, const matr &Transform = matr::Identity(), const vec3 &FitSize = vec3(0) )
    {
      return resource_manager::Add(model(RndRef).Load(FileName, Transform, FitSize));
    }
  };
 } /* end of 'arvk' namespace */

#endif /* __prim_h_ */

/* END OF 'prim.h' FILE */
