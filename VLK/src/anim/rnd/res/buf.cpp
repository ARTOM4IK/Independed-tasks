/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : buf.cpp
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

/* Buffer direct create function.
 * ARGUMENTS:
 *   - buffer data:
 *       const VOID *Data;
 *   - buffer data size in bytes:
 *       UINT Size;
 * RETURNS: None.
 */
VOID arvk::buffer::CreateData( VOID* Data, UINT Size, UINT Offset )
{
  Rnd->BufferCreate(Buffer, Allocation, Size, /*VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT*/VK_BUFFER_USAGE_STORAGE_BUFFER_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT);

  if (Data != nullptr)
    Rnd->BufferUpdate(Buffer, 0, Size, Data);
} /* End of 'CreateData' function */

/* Buffer free function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID arvk::buffer::Free( VOID )
{
  Rnd->BufferFree(Buffer, Allocation);
} /* End of 'Free' function */

/* Buffer update function.
 * ARGUMENTS:
 *   - buffer data:
 *       VOID *Data;
 *   - length of elements, which will be updated:
 *       UINT Size;
 * RETURNS: None.
 */
VOID arvk::buffer::Update( VOID *Data, UINT Size )
{  
  if (Data != nullptr)
    Rnd->BufferUpdate(Buffer, 0, Size, Data);
} /* End of 'Update' finction */


/* END OF 'buf.cpp' FILE */
