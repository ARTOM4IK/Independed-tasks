/* Arsentev Artemy, 09-4, 11.11.2024 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <glut.h>
#include "GFX.H"


static BYTE Font[256][FONT_H];
int
  GFX_W, GFX_H;            /* Global frame size */

static int
  GFX_WinW = 1920, GFX_WinH = 1080;      /* Window size */
double GFX_FrameZoom = 1;  /* Zoom factor */

/* Frame buffer (GFX) */
static DWORD *GFX_Frame;

DWORD GFX_RGB( int r, int g, int b )
{
  return (r << 16) | (g << 8) | b;
}

DWORD GFX_RGBA( int r, int g, int b, int A )
{
  return (A << 24) | (r << 16) | (g << 8) | b;
}


void GFX_LoadFont( void )
{
  int i, j;

  FILE *F;
  F = fopen("SoftFont.fnt", "rb");

  if (F != NULL)
    for (i = 0; i < 256; i++)
      for (j = 0; j < FONT_H; j++)
        Font[i][j] = fgetc(F);

  fclose(F);
}

void GFX_PutPixel( int x, int y, DWORD color )
{
  if (x < 0 || x >= GFX_W || y < 0 || y >= GFX_H || GFX_Frame == NULL)
    return;
  GFX_Frame[y * GFX_W + x] = color;
}

void GFX_PutPixelA( int x, int y, DWORD color )
{
  if (x < 0 || x >= GFX_W || y < 0 || y >= GFX_H || GFX_Frame == NULL || color < 0x80010101)
    return;
  GFX_Frame[y * GFX_W + x] = (color | 0xFF000000);
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
      GFX_PutPixel(i, j, color);
}

void GFX_DrawFrame( void )
{
  glRasterPos2d(-1, 1);
  glPixelZoom(GFX_FrameZoom, -GFX_FrameZoom);
  glDrawPixels(GFX_W, GFX_H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, GFX_Frame);
}

void GFX_ResizeFrameZoom( int WinW, int WinH, double Z )
{
  GFX_ResizeFrame(WinW / Z, WinH / Z);
  GFX_WinW = WinW;
  GFX_WinH = WinH;
  GFX_FrameZoom = Z;
}

void GFX_ResizeFrame( int W, int H )
{
  if (GFX_Frame != NULL)
    free(GFX_Frame);
  GFX_W = W;
  GFX_H = H;
  GFX_Frame = malloc(sizeof(DWORD) * W * H);
  memset(GFX_Frame, 0, sizeof(DWORD) * W * H);
}

void GFX_Init( void )
{
  GFX_ResizeFrameZoom(GFX_WinW, GFX_WinH, 25.0);
  GFX_LoadFont();
}