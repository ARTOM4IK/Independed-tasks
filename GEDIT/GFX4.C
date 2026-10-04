/* Arsentev Artemy, 09-4, 20.12.2024 */

#include <stdio.h>

#include <glut.h>
#include <stdlib.h>

#include "GFX.H"
#include "GFXLL.H"

static INT BUFsize = 0;

static VOID GFX_Store( INT Lx, INT Rx, INT y )
{
  gfxLIST *NewEl;

  if (BUFsize == DEFINED_SIZE || GFX_StoreData == NULL)
  {
    if ((NewEl = malloc(sizeof(gfxLIST))) == NULL)
      return;

    NewEl->Next = GFX_StoreData;
    GFX_StoreData= NewEl;
  }
  GFX_StoreData->Lx[BUFsize] = Lx;
  GFX_StoreData->Rx[BUFsize] = Rx;
  GFX_StoreData->y[BUFsize] = y;
  BUFsize++;
}

static BOOL GFX_Restore( INT *Lx, INT *Rx, INT *y )
{
  gfxLIST *OldEl;

  if (GFX_StoreData == NULL)
    return FALSE;

  BUFsize--;

  if (GFX_StoreData == NULL)
    return FALSE;

  *Lx = GFX_StoreData->Lx[BUFsize];
  *Rx = GFX_StoreData->Rx[BUFsize];
  *y = GFX_StoreData->y[BUFsize];

  if (BUFsize == 0)
  {
    OldEl = GFX_StoreData;
    GFX_StoreData = GFX_StoreData->Next;
    free(OldEl);
    BUFsize = DEFINED_SIZE;
  }

  return TRUE;
}

VOID GFX_FloodFill( INT X, INT Y, DWORD Color )
{
  INT L, R, y, xi, left;
  DWORD BackColor = GFX_GetPixel(X, Y);

  GFX_StoreData = 0;

  GFX_Store(X, X, Y);
  while (GFX_Restore(&L, &R, &y))
  {
    L--;
    while (L >= 0 && GFX_GetPixel(L, y) == BackColor)
      L--;
    L++;

    R++;
    while (R < GFX_W && GFX_GetPixel(R, y) == BackColor)
      R++;
    R--;

    GFX_HorizontalPutLine(L, R, y, Color);

    y--;
    xi = L;

    while (xi <= R)
    {
      while (xi <= R && GFX_GetPixel(xi, y) != BackColor)
        xi++;
      if (xi <= R)
      {
        left = xi;
        while (xi <= R && GFX_GetPixel(xi, y) == BackColor)
          xi++;
        GFX_Store(left, xi - 1, y);
      }
    }
  y++;
  }
}