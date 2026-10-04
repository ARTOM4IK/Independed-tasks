/* FILE NAME: unit.c
 * PROGRAMMER: AA4
 * DATE: 18.01.2024
 * PURPOSE: 3D animation project.
 *          Unit common module.
 */

#include "anim.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID AA4_UnitInit( aa4UNIT *Uni, aa4ANIM *Ani )
{

} /* End of 'AA4_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID AA4_UnitClose( aa4UNIT *Uni, aa4ANIM *Ani )
{

} /* End of 'AA4_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID AA4_UnitResponse( aa4UNIT *Uni, aa4ANIM *Ani )
{
} /* End of 'AA4_UnitResponse' function */
 
/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID AA4_UnitRender( aa4UNIT *Uni, aa4ANIM *Ani )
{

} /* End of 'AA4_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (aa4UNIT *) pointer to created unit.
 */
aa4UNIT * AA4_AnimUnitCreate( INT Size )
{
  aa4UNIT *Uni;
 
  /* Memory allocation */
  if (Size < sizeof(aa4UNIT) || (Uni = malloc(Size)) == NULL)
    return NULL;
 
  /* Setup unit methods */
  Uni->Init = AA4_UnitInit;
  Uni->Close = AA4_UnitClose;
  Uni->Response = AA4_UnitResponse;
  Uni->Render = AA4_UnitRender;

  return Uni;
} /* End of 'AA4_AnimUnitCreate' function */

/* END OF 'unit.c' FILE */
