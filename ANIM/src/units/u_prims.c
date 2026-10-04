/* FILE NAME: u_prims.c
 * PROGRAMMER: AA4
 * DATE: 10.02.2024
 * PURPOSE: 3D animation project.
 *          Unit prims module.
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
static VOID Init( aa4UNIT_PRIMS *Uni, aa4ANIM *Ani )
{
  Uni->Pos = VecSet(2, 3, 5);
  Uni->Mat = MatrIdentity();
  Uni->MatrTotal = MatrTranslate(Uni->Pos);
  AA4_RndPrimsLoad(Uni->Prims, "bin/models/Su-35_SuperFlanker.g3dm");
} /* End of 'Init' function */

/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID Close( aa4UNIT_PRIMS *Uni, aa4ANIM *Ani )
{
  AA4_RndPrimsFree(Uni->Prims);
} /* End of 'Close' function */

/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID Render( aa4UNIT_PRIMS *Uni, aa4ANIM *Ani )
{
  Uni->MatrTotal = MatrMulMatr(MatrTranslate(Uni->Pos), Uni->Mat);
  AA4_RndPrimsDraw(Uni->Prims, MatrMulMatr(MatrMulMatr(MatrTranslate(Uni->Pos), Uni->Mat), MatrScale(VecSet1(0.25))));
} /* End of 'Render' function */

/* Unit render function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID Response( aa4UNIT_PRIMS *Uni, aa4ANIM *Ani )
{
  FLT elev, azim, Dist = VecLen(VecSubVec(AA4_RndCamAt, AA4_RndCamLoc));

  if (Ani->Keys['W'] && !Ani->Keys[VK_SHIFT])
  {
    azim = Ani->GlobalDeltaTime * 100 * (Ani->Keys[VK_LEFT] - Ani->Keys[VK_RIGHT]);
    elev = Ani->GlobalDeltaTime * 100 * -(Ani->Keys[VK_UP] - Ani->Keys[VK_DOWN]);
    Uni->Pos.Z += Ani->GlobalDeltaTime * 42 * (Ani->Keys['E'] - Ani->Keys['Q']);

    //Uni->Mat = Uni->MatrTotal;
    Uni->Mat = MatrMulMatr(Uni->Mat, MatrRotateX(elev));
    Uni->Mat = MatrMulMatr(Uni->Mat, MatrRotateY(azim));

    /* Setup result camera */
    //AA4_RndCamSet(PointTransform(VecSet(0, Uni->Pos.Y + 10, 0), MatrMulMatr(Uni->Mat, MatrTranslate(Uni->Pos/*VecSet(Uni->Pos.X, 0, 0)*/))), Uni->Pos/*VecSet(Uni->Pos.X, 0, 0)*/, VecSet(0, 1, 0));
    AA4_RndCamSet(VecSet(0, Uni->Pos.Y + 10, 0), VecSet(1, 1, Uni->Pos.Z), AA4_RndCamUp);
  }
} /* End of 'Response' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (aa4UNIT *) pointer to created unit.
 */
aa4UNIT * AA4_UnitPrimsCreate( VOID )
{
  aa4UNIT *Uni;
 
  Uni = AA4_AnimUnitCreate(sizeof(aa4UNIT_PRIMS));
  if (Uni == NULL)
    return NULL;
  Uni->Init = (VOID *)Init;
  Uni->Close = (VOID *)Close;
  Uni->Render = (VOID *)Render;
  Uni->Response = (VOID *)Response;

  return Uni;
} /* End of 'AA4_UnitPrimsCreate' function */

/* END OF 'u_prims.c' FILE */
