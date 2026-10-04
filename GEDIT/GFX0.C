/* Arsentev Artemy, 09-4, 20.12.2024 */

#include <stdio.h>

#include <stdlib.h>
#include <string.h>

#include <glut.h>

#include "GFX.H"
#include "GFXLL.H"

DBL GFX_FrameZoom = 1;  /* Zoom factor */

int
  GFX_W, GFX_H;            /* Global frame size */

static int
  GFX_WinW = 1920, GFX_WinH = 1080;      /* Window size */

DWORD GFX_RGB( int r, int g, int b )
{
  return (r << 16) | (g << 8) | b;
}

VOID GFX_PutPixel( int x, int y, DWORD color )
{
  if (x < 0 || x >= GFX_W || y < 0 || y >= GFX_H || GFX_Frame == NULL)
    return;
  GFX_Frame[y * GFX_W + x] = color;
}

DWORD GFX_GetPixel( INT x, INT y )
{
  if (x < 0 || x >= GFX_W || y < 0 || y >= GFX_H || GFX_Frame == NULL)
    return -1;
  return GFX_Frame[y * GFX_W + x];
}

VOID GFX_DrawFrame( VOID )
{
  glRasterPos2d(-1, 1);
  glPixelZoom(GFX_FrameZoom, -GFX_FrameZoom);
  glDrawPixels(GFX_W, GFX_H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, GFX_Frame);
}

VOID GFX_ResizeFrameZoom( int WinW, int WinH, double Z )
{
  GFX_ResizeFrame(WinW / Z, WinH / Z);
  GFX_WinW = WinW;
  GFX_WinH = WinH;
  GFX_FrameZoom = Z;
}

VOID GFX_ResizeFrame( int W, int H )
{
  if (GFX_Frame != NULL)
    free(GFX_Frame);
  GFX_W = W;
  GFX_H = H;
  GFX_Frame = malloc(sizeof(DWORD) * W * H);
  memset(GFX_Frame, 0, sizeof(DWORD) * W * H);
}

VOID GFX_Init( VOID )
{
  GFX_ResizeFrameZoom(GFX_WinW, GFX_WinH, 1.0);
}