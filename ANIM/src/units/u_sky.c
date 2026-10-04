/* FILE NAME: u_sky.c
 * PROGRAMMER: AA4
 * DATE: 18.01.2024
 * PURPOSE: 3D animation project.
 *          Unit common module.
 */

  #include "units.h"

/* Unit initialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID Init( aa4UNIT_SKY *Uni, aa4ANIM *Ani )
{
  aa4MATERIAL mtl;

  mtl = AA4_RndMtlGetDef();
  mtl.ShdNo = AA4_RndShdAdd("sky_sphere");
  mtl.Tex[0] = AA4_RndTexAddFromFile("bin/textures/photo1.bmp");
  strcpy(mtl.Name, "Sky Sphere");
  Uni->Pr.MtlNo = AA4_RndMtlAdd(&mtl);
  AA4_RndPrimCreate(&Uni->Pr, AA4_RND_PRIM_POINTS, NULL, 1, NULL, 0);
} /* End of 'AA4_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID Close( aa4UNIT_SKY *Uni, aa4ANIM *Ani )
{
  AA4_RndPrimFree(&Uni->Pr);
} /* End of 'AA4_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID Response( aa4UNIT_SKY *Uni, aa4ANIM *Ani )
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
static VOID Render( aa4UNIT_SKY *Uni, aa4ANIM *Ani )
{
  glDepthMask(FALSE);
  AA4_RndPrimDraw(&Uni->Pr, MatrIdentity());
  glDepthMask(TRUE);
} /* End of 'AA4_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (aa4UNIT *) pointer to created unit.
 */
aa4UNIT * AA4_AnimSkyCreate( VOID )
{
  aa4UNIT *Uni;
 
  Uni = AA4_AnimUnitCreate(sizeof(aa4UNIT_SKY));
  if (Uni == NULL)
    return NULL;
  Uni->Init = (VOID *)Init;
  Uni->Close = (VOID *)Close;
  Uni->Render = (VOID *)Render;
  Uni->Response = (VOID *)Response;

  return Uni;
} /* End of 'AA4_AnimSkyCreate' function */

/* END OF 'u_sky.c' FILE */
