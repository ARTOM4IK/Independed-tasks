/* Arsentev Artemy, 09-4, 20.12.2024 */ 

#include <stdio.h>
#include <glut.h>

#include "GFX.H"
#include "GFXLL.H"

VOID GFX_HorizontalPutLine( INT x1, INT x2, INT y, DWORD color )
{
  INT i;

  for (i = x1; i < x2; i++)
    GFX_PutPixel(i, y, color);
}

VOID GFX_PutLine( INT x1, INT y1, INT x2, INT y2, DWORD color )
{
  INT dx, dy, x, y, tmp, sx, F, IncrE, IncrNE, count;

  if (y1 > y2)
    tmp = x1, x1 = x2, x2 = tmp, tmp = y1, y1 = y2, y2 = tmp;
  dx = x2 - x1;
  dy = y2 - y1;
  x = x1;
  y = y1;

  if (dx < 0)
    sx = -1, dx = -dx;
  else
    sx = 1;

  GFX_PutPixel(x, y, color);

  if (dx >= dy)
  {
    F = 2 * dy - dx, IncrE = 2 * dy, IncrNE = 2 * dy - 2 * dx, count = dx;

    while (count-- > 0)
    {
      if (F > 0)
        y++, F += IncrNE;
      else
        F+= IncrE;
      x += sx;

      GFX_PutPixel(x, y, color);
    }
  }
  else
  {
    F = 2 * dx - dy, IncrE = 2 * dx, IncrNE = 2 * dx - 2 * dy, count = dy;
    while (count-- > 0)
    {
      if (F > 0)
        x += sx, F += IncrNE;
      else
        F+= IncrE;
      y++;

      GFX_PutPixel(x, y, color);
    }
  }
}

VOID GFX_Put4Points( INT x, INT y, INT cx, INT cy, DWORD color )
{
  GFX_PutPixel(x + cx, y + cy, color);
  GFX_PutPixel(-x + cx, -y + cy, color);
  GFX_PutPixel(x + cx, -y + cy, color);
  GFX_PutPixel(-x + cx, y + cy, color);
}

VOID GFX_Put8Points( INT x, INT y, INT cx, INT cy, DWORD color )
{
  GFX_PutPixel(x + cx, y + cy, color);
  GFX_PutPixel(y + cy, x + cx, color);
  GFX_PutPixel(y + cy, -x + cx, color);
  GFX_PutPixel(x + cx, -y + cy, color);
  GFX_PutPixel(-x + cx, -y + cy, color);
  GFX_PutPixel(-y + cy, -x + cx, color);
  GFX_PutPixel(-y + cy, x + cx, color);
  GFX_PutPixel(-x + cx, y + cy, color);
}

VOID GFX_PutCircle( INT X, INT Y, INT R, DWORD color )
{
  INT F, IncrE, IncrSE, x, y;

  F = 1 - R;
  x = 0;
  y = R;
  IncrE = 3;
  IncrSE = 5 - 2 * R;

  GFX_Put4Points(x, y, X, Y, color);

  while (x <= y)
  {
    if (F >= 0)
      y--, F+= IncrSE, IncrSE += 4;
    else
      F += IncrE, IncrSE += 2;
    IncrE += 2;
    x++;

    if (x > y)
      break;
    if (x == y)
    {
      GFX_Put4Points(x, y, X, Y, color);
      break;
    }
    GFX_Put8Points(x, y, X, Y, color);
  }
}