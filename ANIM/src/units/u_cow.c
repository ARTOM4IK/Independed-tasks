/* FILE NAME: u_cow.c
 * PROGRAMMER: AA4
 * DATE: 18.01.2024
 * PURPOSE: 3D animation project.
 *          Unit cow module.
 */

#include <windows.h>
#include "units.h"

/* Init unit function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
static VOID Init( aa4UNIT_COW *Uni, aa4ANIM *Ani )
{
  aa4MATERIAL mtl;

  mtl = AA4_RndMtlGetDef();
  mtl.Tex[0] = AA4_RndTexAddFromFile("bin/textures/photo2.bmp");
  Uni->Cow.MtlNo = AA4_RndMtlAdd(&mtl);
  AA4_RndPrimLoad(&Uni->Cow, "bin/models/cow.obj");
} /* End of 'Init' function */

/* Close unit function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
static VOID Close( aa4UNIT_COW *Uni, aa4ANIM *Ani )
{
  AA4_RndPrimFree(&Uni->Cow);
} /* End of 'Close' function */

/* Render unit function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
static VOID Render( aa4UNIT_COW *Uni, aa4ANIM *Ani )
{
  AA4_RndPrimDraw(&Uni->Cow, MatrMulMatr(MatrTranslate(VecSet(2, 3, 5)), MatrScale(VecSet1(0.25))));
} /* End of 'Render' function */

/* Response unit function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
static VOID Response( aa4UNIT_COW *Uni, aa4ANIM *Ani )
{
} /* End of 'Response' function */

/* Create unit function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
aa4UNIT * AA4_UnitCowCreate( VOID )
{
  aa4UNIT *Uni;
 
  Uni = AA4_AnimUnitCreate(sizeof(aa4UNIT_COW));
  if (Uni == NULL)
    return NULL;
  Uni->Init = (VOID *)Init;
  Uni->Close = (VOID *)Close;
  Uni->Render = (VOID *)Render;
  Uni->Response = (VOID *)Response;

  return Uni;
} /* End of 'AA4_UnitCowCreate' function */

/* END OF 'u_cow.c' FILE */
