/* Arsentev Artemy, 09-4, 21.10.2024 */

#include <stdio.h>
#include <stdlib.h>

#include <glut.h>
#include "GFX.H"

static DWORD Frame[GFX_H][GFX_W];
static BYTE Font[256][FONT_H];


DWORD GFX_RGB( int r, int g, int b )
{
  return (r << 16) | (g << 8) | b;
}

void GFX_LoadFont( void )
{
  int i, j;

  FILE *F;
  F = fopen("SoftFont.fnt", "rb");

  if (F != NULL)
  {
    for (i = 0; i < 256; i++)
      for (j = 0; j < FONT_H; j++)
        Font[i][j] = fgetc(F);
    
    fclose(F);
  }
}

void GFX_PutPixel( int x, int y, DWORD color )
{
  if (x < 0 || x >= GFX_W || y < 0 || y >= GFX_H)
    return;
  Frame[y][x] = color;
}

void GFX_DrawLetter( int x0, int y0, BYTE *a, DWORD color )
{
  int i, j;

  for (i = 0; i < FONT_H; i++)
    for (j = 0; j < FONT_H; j++)
    {
      if((a[i] & (0x80 >> j)) != 0)
        GFX_PutPixel(x0 + j, y0 + i, color);
    }
}

void GFX_DrawChLetter( int x0, int y0, char *stri, DWORD color )
{
  int i, j;


  for (i = 0; i < FONT_H; i++)
    for (j = 0; j < FONT_H; j++)
    {
      if((Font[*stri][i] & (0x80 >> j)) != 0)
        GFX_PutPixel(x0 + j, y0 + i, color);
    }
}

void GFX_DrawChar( int x, int y, char str, DWORD color )
{
  int i;

  for (i = 0; i < FONT_H; i++)
    GFX_DrawLetter(x, y, Font[str], color);
}

void GFX_DrawFontText( int x, int y, char *str, DWORD color )
{
  int i = 0, j = 0;

  while (*str != 0)
  {
    if (*str == '\n')
      i = 0, j += 8;
    else
    {
      GFX_DrawChLetter(x + i * 8, y + j, str, color);
      i++;
    }
    *str++;
  }
  }

void GFX_Clear( DWORD color )
{
  int i, j;

  for (i = 0; i < GFX_W; i++)
    for (j = 0; j < GFX_W; j++)
      GFX_PutPixel(i, j, GFX_RGB(0, 0, 0));
}

void GFX_DrawFrame( void )
{
  /* draw */
  glRasterPos2d(-1, 1);
  glPixelZoom(ZOOM, -ZOOM);
  glDrawPixels(GFX_W, GFX_H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Frame);
}