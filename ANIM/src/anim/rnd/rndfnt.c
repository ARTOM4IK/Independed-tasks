/* FILE NAME  : rndfnt.c
 * PROGRAMMER : AA4
 * LAST UPDATE: 05.02.2025
 * PURPOSE    : 3D animation project.
 *              Rendering system implemetation module.
 *              Resource implemetation module.
 *              Fonts handle module.
 */

#include <stdio.h>
#include <string.h>

#include "anim/rnd/rnd.h"

/* Font description structure */
typedef struct tagaa4FONT
{
  DWORD LineH, BaseH; /* Font line height and base line height in pixels */
  FLT AdvanceX[256];  /* Every letter shift right value (0 if no letter present) */
} aa4FONT;

/* Current font description */
/* Font data */
static aa4FONT AA4_RndFntFont;

/* Font characters primitives */
static aa4PRIM AA4_RndFntChars[256];

/* Font material */
static INT AA4_RndFntMtlNo;

/* Deinit font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndFntClose( VOID )
{
  INT i;

  for (i = 0; i < 256; i++)
    AA4_RndPrimFree(&AA4_RndFntChars[i]);
  memset(AA4_RndFntChars, 0, sizeof(AA4_RndFntChars));
  memset(&AA4_RndFntFont, 0, sizeof(AA4_RndFntFont));
} /* End of 'AA4_RndFntInit' function */

/* Load font from .G3DF file function.
 * ARGUMENTS:
 *   - font file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL AA4_RndFntLoad( CHAR *FileName )
{
  FILE *F;
  INT i;
  DWORD Sign, W, H, *Tex;
  aa4VERTEX Chars[256][4];
  aa4MATERIAL mtl;

  AA4_RndFntClose();

  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;

  if (fread(&Sign, 4, 1, F) != 1 || Sign != *(DWORD *)"G3DF")
  {
    fclose(F);
    return FALSE;
  }
  fread(&AA4_RndFntFont, sizeof(aa4FONT), 1, F);
  fread(&Chars, sizeof(aa4VERTEX), 256 * 4, F);
  fread(&W, 4, 1, F);
  fread(&H, 4, 1, F);
  if ((Tex = malloc(W * H * 4)) == NULL)
  {
    memset(AA4_RndFntChars, 0, sizeof(AA4_RndFntChars)); /* ? */
    memset(&AA4_RndFntFont, 0, sizeof(AA4_RndFntFont));
    fclose(F);
    return FALSE;
  }
  fread(Tex, 4, W * H, F);
  fclose(F);

  mtl = AA4_RndMtlGetDef();
  strncpy(mtl.Name, FileName, AA4_STR_MAX - 1);
  mtl.Tex[0] = AA4_RndTexAddImg(FileName, W, H, 4, Tex);
  mtl.ShdNo = AA4_RndShdAdd("font");
  AA4_RndFntMtlNo = AA4_RndMtlAdd(&mtl);

  for (i = 0; i < 256; i++)
  {
    AA4_RndPrimCreate(&AA4_RndFntChars[i], AA4_RND_PRIM_TRISTRIP, Chars[i], 4, NULL, 0);
    AA4_RndFntChars[i].MtlNo = AA4_RndFntMtlNo;
  }

  free(Tex);
  return TRUE;
} /* End of 'AA4_RndFntLoad' function */

/* Init font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndFntInit( VOID )
{
  AA4_RndFntLoad("bin/fonts/book.g3df");
} /* End of 'AA4_RndFntInit' function */

/* Draw string function.
 * ARGUMENTS:
 *   - string to draw:
 *       CHAR *Str;
 *   - draw position:
 *       VEC Pos;
 *   - font size:
 *      FLT Size;
 * RETURNS: None.
 */
VOID AA4_RndFntDraw( CHAR *Str, VEC Pos, FLT Size )
{
  FLT startx = Pos.X;

  while (*Str != 0)
  {
    if (*Str == '\n')
    {
      Pos.X = startx;
      Pos.Y -= Size;
    }
    else
    {
      AA4_RndPrimDraw(&AA4_RndFntChars[(UCHAR)*Str],
        MatrMulMatr(MatrScale(VecSet(Size, Size, 1)),
                    MatrTranslate(Pos)));
      Pos.X += AA4_RndFntFont.AdvanceX[(UCHAR)*Str] * Size;
    }
    Str++;
  }
} /* End of 'AA4_RndFntDraw' function */

/* END OF 'rndfnt.c' FILE */
