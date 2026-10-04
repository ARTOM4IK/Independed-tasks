/* Arsentev Artemy, 09-4, 20.12.2024 */

#include <stdio.h>
#include <glut.h>

#include "GFX.H"
#include "GFXLL.H"

VOID TetaRose( INT x, INT y, INT b, INT a, DWORD color )
{
  INT i;

  GFX_PutLine(x, y, x + a, y + b, color);
  x += a;
  y += b;
  GFX_PutLine(x, y, x + b, y + a, color);
  x += b;
  y += a;
  GFX_PutLine(x, y, x - b, y + a, color);
  x -= b;
  y += a;
  GFX_PutLine(x, y, x - a, y + b, color);
  x -= a;
  y += b;
  GFX_PutLine(x, y, x - a, y - b, color);
  x -= a;
  y -= b;
  GFX_PutLine(x, y, x - b, y - a, color);
  x -= b;
  y -= a;
  GFX_PutLine(x, y, x + b, y - a, color);
  x += b;
  y -= a;
  GFX_PutLine(x, y, x + a, y - b, color);
  x += a;
  y -= b;
  GFX_PutLine(x, y, x, y + a + a + b + b, color);
  GFX_PutLine(x - a - b, y + a + b, x + a + b, y + a + b, color);
  GFX_PutLine(x + a, y + b, x - a, y + b + a + a, color);
  GFX_PutLine(x - a, y + b, x + a, y + b + a + a, color);

  for (i = y; i <= y + b + a; i++)
    GFX_PutLine(x - a, y + b, x, i, color);

  for (i = x; i <= x + b + a; i++)
    GFX_PutLine(x + a, y + b, i, y + b + a, color);

  for (i = y + b + a; i <= y + 2 * b + 2 * a; i++)
    GFX_PutLine(x + a, y + b + 2 * a, x, i, color);

  for (i = x - a - b; i <= x; i++)
    GFX_PutLine(x - a, y + b + 2 * a, i, y + b + a, color);

}

VOID Vroongel( INT x, INT y, INT b, INT a, INT c, INT d, INT e, DWORD color )
{
  INT i, j;

  GFX_PutLine(x, y, x + a, y + b, color);
  x += a;
  y += b;
  GFX_PutLine(x, y, x + b, y + a, color);
  x += b;
  y += a;
  GFX_PutLine(x, y, x - b, y + a, color);
  x -= b;
  y += a;
  GFX_PutLine(x, y, x - a, y + b, color);
  x -= a;
  y += b;
  GFX_PutLine(x, y, x - a, y - b, color);
  x -= a;
  y -= b;
  GFX_PutLine(x, y, x - b, y - a, color);
  x -= b;
  y -= a;
  GFX_PutLine(x, y, x + b, y - a, color);
  x += b;
  y -= a;
  GFX_PutLine(x, y, x + a, y - b, color);
  x += a;
  y -= b;

  /* diagonals */
  GFX_PutLine(x, y, x, y + a + a + b + b, color);
  GFX_PutLine(x - a - b, y + a + b, x + a + b, y + a + b, color);
  GFX_PutLine(x + e, y + a + b - e, x - e, y + b + a + e, color);
  GFX_PutLine(x - e, y + a + b - e, x + e, y + b + a + e, color);

  /* vroongel additional parts */
  GFX_PutLine(x + c, y + a + b - d, x + e, y + a + b - e, color);
  GFX_PutLine(x + e, y + a + b - e, x + d, y + a + b - c, color);

  GFX_PutLine(x + d, y + a + b + c, x + e, y + a + b + e, color);
  GFX_PutLine(x + e, y + a + b + e, x + c, y + b + a + d, color);

  GFX_PutLine(x - c, y + a + b + d, x - e, y + a + b + e, color);
  GFX_PutLine(x - e, y + a + b + e, x - d, y + a + b + c, color);

  GFX_PutLine(x - d, y + b + a - c, x - e, y + b + a - e, color);
  GFX_PutLine(x - e, y + b + a - e, x - c, y + b + a - d, color);

  /* fill */
  for (i = y; i <= y + b + a; i++)
    GFX_PutLine(x - a, y + b, x, i, color);

  for (i = x; i <= x + b + a; i++)
    GFX_PutLine(x + a, y + b, i, y + b + a, color);

  for (i = y + b + a; i <= y + 2 * b + 2 * a; i++)
    GFX_PutLine(x + a, y + b + 2 * a, x, i, color);

  for (i = x - a - b; i <= x; i++)
    GFX_PutLine(x - a, y + b + 2 * a, i, y + b + a, color);

  /* additional fill */
  
  for (i = x + a, j = y + b; i <= x + e && j >= y + a + b - e; i++, j--)
    GFX_PutLine(x + c, y + a + b - d, i, j, color);

  for (i = x + a, j = y + 2 * a + b; i <= x + e && j <= y + a + b + e; i++, j++)
    GFX_PutLine(x + d, y + a + b + c, i, j, color);

  for (i = x - a, j = y + 2 * a + b; i >= x - e && j <= y + a + b + e; i--, j++)
    GFX_PutLine(x - c, y + a + b + d, i, j, color);

  for (i = x - a, j = y + b; i >= x - e && j >= y + a + b - e; i--, j--)
    GFX_PutLine(x - d, y + a + b - c, i, j, color);

}

VOID vrngl( INT x, INT y, INT a, INT b, DWORD color )
{
  TetaRose(x, y, -b, a, color);
  TetaRose(x, y - a, a, b, color);
}