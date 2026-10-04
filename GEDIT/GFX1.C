/* Arsentev Artemy, 09-4, 20.12.2024 */

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include <glut.h>

#include "GFX.H"
#include "GFXLL.H"


VOID GFX_Clear( DWORD color )
{
  INT i, j;

  for (i = 0; i < GFX_W; i++)
    for (j = 0; j < GFX_W; j++)
      GFX_PutPixel(i, j, color);
}