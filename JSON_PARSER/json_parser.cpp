/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : json_parser.cpp
 * PURPOSE     : Judjing Son.
 *               Main module.
 * PROGRAMMER  : AA4.
 *               
 * LAST UPDATE : 13.12.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "json_parser.h"

/* The main program function */
INT main( VOID )
{
  loader ldr;
  json jsn;
  
  ldr.LoadG("Strawberry.gltf");
  std::visit(json_visitor{}, jsn);

  return 0;
} /* End of 'main' function */

/* END OF 'json_parser.cpp' FILE */                                 
