/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : buf.h
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

#ifndef __buf_h_
#define __buf_h_

#include "resources.h"
#include "anim/rnd/vlk/vlk_def.h"

/* Animation namespace */
namespace arvk
{
  /* Buffer namespace */
  class buffer : public resource
  {
  public:
    UINT BufId = 0;        // Buffer Id
    UINT BindingPoint = 0; // Binding point
    UINT BufSize = 0;      // Number of buffer quads
    VkBuffer Buffer {};             // Vulkan buffer handle
    VmaAllocation Allocation {}; // VMA buffer allocation info
 
    buffer( render &rnd ) 
    {
      Rnd = &rnd;
    } /* End of 'buffer' function */

    buffer( VOID ) 
    {
    } /* End of 'buffer' function */

    ~buffer( VOID )
    {
    } /* End of '~buffer' function */

    /* Buffer create function.
     * ARGUMENTS:
     *   - buffer binding point:
     *       UINT BufBindingPoint;
     *   - buffer data:
     *       const data_type *Data;
     * RETURNS:
     *   (buffer &) self reference.
     */ 
    template<typename data_type>
      buffer & Create( UINT BufBindingPoint, const data_type *Data  = {} )
      {
        Free();
        BufSize = sizeof(data_type);
        if (BufSize == 0)
          return *this;
 
        BindingPoint = BufBindingPoint;
 
        Apply();
        return *this;
      } /* End of 'Create' function */

    /* Buffer create function.
     * ARGUMENTS:
     *   - buffer binding point:
     *       UINT BufBindingPoint;
     *   - number of data elements:
     *       INT NumOfElements;
     *   - buffer data:
     *       const data_type *Data;
     * RETURNS:
     *   (buffer &) self reference.
     */
    template<typename data_type>
      buffer & Create( UINT BufBindingPoint, INT NumOfElements, const data_type *Data  = {} )
      {
        Free();
        BufSize = sizeof(data_type) * NumOfElements;
        if (BufSize == 0)
          return *this;
 
        BindingPoint = BufBindingPoint;

        Apply();
        return *this;
      } /* End of 'Create' function */

    /* Buffer free function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Free( VOID );

    /* Buffer direct create function.
     * ARGUMENTS:
     *   - buffer data:
     *       const VOID *Data;
     *   - buffer data size in bytes:
     *       UINT Size;
     * RETURNS: None.
     */
    VOID CreateData( VOID* Data, UINT Size, UINT Offset );

    /* Buffer update function.
     * ARGUMENTS:
     *   - buffer data:
     *       const data_type *Data;
     *   - start of elements update:
     *       INT Start;
     *   - length of elements, which will be updated:
     *       INT Size;
     * RETURNS: None.
     */
    VOID Update( VOID *Data, UINT Size  );

    VOID Apply( VOID )
    {
    }
  }; /* End of 'buffer' class */
 
  class buffer_manager : public resource_manager<buffer, INT>
  {
  public:
    /* Buffer creating function.
     * ARGUMENTS:
     *   - buffer binding point:
     *       UINT BufBindingPoint;
     *   - buffer data:
     *       const data_type *Data;                              
     * RETURNS:
     *   (buffer &) buffer.
     */
    template<typename data_type>
      buffer * BufCreate( UINT BufBindingPoint, const data_type *Data = {} )
      {
        return resource_manager::Add(buffer(RndRef).Create(BufBindingPoint, Data));
      } /* End of 'BufCreate' function */

    /* Buffer creating function.
     * ARGUMENTS:
     *   - buffer binding point:
     *       UINT BufBindingPoint;
     *   - number of elements:
     *       INT NumOfElements;
     *   - buffer data:
     *       const data_type *Data;                              
     * RETURNS:
     *   (buffer &) buffer.
     */
    template<typename data_type>
      buffer * BufCreate( UINT BufBindingPoint, INT NumOfElements, const data_type *Data  = {} )
      {
        return resource_manager::Add(buffer(RndRef).Create(BufBindingPoint, NumOfElements, Data));
      } /* End of 'Bufcreate' function */

    buffer_manager( render &Rnd ) : resource_manager(Rnd)
    {
    } /* End of 'buffer_manager' function */

    ~buffer_manager( VOID )
    {
    } /* End of '~buffer_manager' function */
  }; /* End of 'buffer_manager' class */
} /* End of 'arvk' namespace */

#endif /* __buf_h_ */

/* END OF 'buf.h' FILE */
