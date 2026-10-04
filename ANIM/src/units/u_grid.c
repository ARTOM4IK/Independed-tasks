/* FILE NAME: u_grid.c
 * PROGRAMMER: AA4
 * DATE: 12.02.2024
 * PURPOSE: 3D animation project.
 *          Unit grid module.
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
static VOID Init( aa4UNIT_GRID *Uni, aa4ANIM *Ani )
{
  INT x, y;
  aa4GRID G;
  aa4MATERIAL mtl = AA4_RndMtlGetDef();
  HBITMAP hBm;
  BITMAP bm;

  if ((hBm = LoadImage(NULL, "bin/heights/hfcolor.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)) != NULL)
  {
    GetObject(hBm, sizeof(bm), &bm);
    G.W = bm.bmWidth;
    G.H = bm.bmHeight;
    if ((bm.bmBitsPixel == 8 || bm.bmBitsPixel == 24) &&
      (G.V = malloc(sizeof(aa4VERTEX) * G.W * G.H)) != NULL)
    {
      BYTE *Bits = bm.bmBits;

      for(y = 0; y < G.H; y++)
        for(x = 0; x < G.W; x++)
        {
          INT hgt = Bits[(G.H - 1- y) * bm.bmWidthBytes + x * (bm.bmBitsPixel / 8)];

          G.V[y * G.W + x].P = VecSet(x / (G.W - 1.0), hgt / 255.0, 1 - y / (G.H - 1.0));
        }
      mtl.Tex[0] = AA4_RndTexAddFromFile("bin/heights/hfcolor.bmp");
      mtl.ShdNo = AA4_RndShdAdd("grid");
      Uni->Land.MtlNo = AA4_RndMtlAdd(&mtl);
      AA4_RndGridAutoNormals(&G);
      AA4_RndPrimFromGrid(&Uni->Land, &G);
      Uni->Land.Trans = MatrMulMatr(Uni->Land.Trans, MatrScale(VecSet1(1000)));
    }
  }
} /* End of 'AA4_UnitInit' function */
 
/* Unit deinitialization function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID Close( aa4UNIT_GRID *Uni, aa4ANIM *Ani )
{
  AA4_RndPrimFree(&Uni->Land);
} /* End of 'AA4_UnitClose' function */
 
/* Unit inter frame events handle function.
 * ARGUMENTS:
 *   - self-pointer to unit object:
 *       aa4UNIT *Uni;
 *   - animation context:
 *       aa4ANIM *Ani;
 * RETURNS: None.
 */
static VOID Response( aa4UNIT_GRID *Uni, aa4ANIM *Ani )
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
static VOID Render( aa4UNIT_GRID *Uni, aa4ANIM *Ani )
{
  AA4_RndPrimDraw(&Uni->Land, MatrIdentity());
} /* End of 'AA4_UnitRender' function */

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (aa4UNIT *) pointer to created unit.
 */
aa4UNIT * AA4_AnimGridCreate( VOID )
{
  aa4UNIT *Uni;
 
  Uni = AA4_AnimUnitCreate(sizeof(aa4UNIT_GRID));
  if (Uni == NULL)
    return NULL;
  Uni->Init = (VOID *)Init;
  Uni->Close = (VOID *)Close;
  Uni->Render = (VOID *)Render;
  Uni->Response = (VOID *)Response;

  return Uni;
} /* End of 'AA4_AnimGridCreate' function */

/* END OF 'u_grid.c' FILE */
