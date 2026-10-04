/* FILE NAME: rndres.c
 * PROGRAMMER: AA4
 * LAST UPDATE: 29.01.2025
 * PURPOSE: 3D animation project.
 *          Rendering resources module.
 */

#include "anim/rnd/rnd.h"

/* Resource initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndResInit( VOID )
{
  AA4_RndShdInit();
  AA4_RndMtlInit(); 
  AA4_RndTexInit();
} /* End of 'AA4_RndResInit' function */
 
/* Resource deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndResClose( VOID )
{
  AA4_RndTexClose();
  AA4_RndShdClose();
  AA4_RndMtlClose();
} /* End of 'AA4_RndResClose' function */

/* END OF 'rndres.c' FILE */
