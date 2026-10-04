/* Arsentev Artemy, 09-4, 16.10.2024 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include "ARC.H"

static int HeartCounter = 0, ARC_Bricks[BR_NY][BR_NX];

void ARC_DrawBrick( int Nx, int Ny )
{
  static int i, j;

  static DWORD Colors[] =
  {
    0x0, 0x0000FF, 0xFF00FF, /*0x0, 0x0000FF, 0xFF00FF, 0x00FFFF, 0xFFFF00, 0xFFFFFF */
  };

  for ( i = 0; i < BR_H; i++)
    for ( j = 0; j < BR_W; j++)
      GFX_PutPixel(BR_X + BR_W * Nx + j, BR_Y + BR_H * Ny + i, Colors[ARC_Bricks[Ny][Nx]/*(sizeof(Colors) / sizeof(Colors[0]))*/]);
}

void ARC_InitBricks( void )
{
  int i, j;

  for ( i = 0; i < BR_NY; i++)
    for ( j = 0; j < BR_NX; j++)
    {
      ARC_Bricks[i][j] = 1;
      ARC_DrawBrick(j, i);
    }
}

int ARC_Hit( int x, int y )
{
  if (x < BR_X || y < BR_Y)
    return 0;

  x = (x - BR_X) / BR_W;
  y = (y - BR_Y) / BR_H;

  if (x >= BR_NX || y >= BR_NY)
    return 0;

  if (ARC_Bricks[y][x] == 0)
    return 0;

  ARC_Bricks[y][x]--;
  ARC_DrawBrick(x, y);
}

void Game_Init( void )
{
  int i;

  GFX_Clear(BACK_COLOR);
  GFX_DrawFontText(4, 6, "CGSG FOREVER", INTERFACE_COLOR);
  for (i = 0; i < GFX_W; i++)
    GFX_PutPixel(i, 16, INTERFACE_COLOR); /* border */

  for (i = 2 - HeartCounter; i >= 0; i--)
    GFX_DrawChar(GFX_W - 24 - i * 8, 6, 3, DEBUG_COLOR);

  ARC_InitBricks();
}

void Game_Step( void )
{
  static int sx = 1, sy = 1, x = 0, y = 30, i, bx = 0, life = -1, speed = 4, bw = 16;

  if (life == 2)
  {
    StartGameFlag = 2;
    GFX_Clear(BACK_COLOR);
    GFX_DrawFontText(150, 50, "GAME OVER", INTERFACE_COLOR);
  }
  else
  {
    /* bar movement */

    for (i = 0; i < bw; i++)
    {
      GFX_PutPixel(bx + i, GFX_H - 1, ITEM_COLOR);
    }

    /* AI */

    /* left movement */

    if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0 && bx + bw / 2 > x ||
      ((GetAsyncKeyState(VK_LCONTROL) & 0x8000) != 0) && bx > 0)
    {
      for (i = 0; i < speed; i++)
      {
        GFX_PutPixel(bx + 16, GFX_H - 1, BACK_COLOR);
        bx--;
        GFX_PutPixel(bx, GFX_H - 1, ITEM_COLOR);
      }
    }

    /* right movement */

    if ((GetKeyState(VK_CAPITAL) & 0x0001) != 0 && (bx + bw / 2 < x) ||
      ((GetAsyncKeyState(VK_RCONTROL) & 0x8000) != 0) && bx + bw < GFX_W - 1)
    {
      for (i = 0; i < speed; i++)
      {
        GFX_PutPixel(bx, GFX_H - 1, BACK_COLOR);
        bx++;
        GFX_PutPixel(bx + 15, GFX_H - 1, ITEM_COLOR);
      }
    }

    /* ball movement */
    GFX_PutPixel(x, y, BACK_COLOR);

    x += sx;
    y += sy;

    /* cololion correction */

    if (x < 1 || x >= GFX_W - 1)
      sx = -sx;

    if (y <= 17)
      sy = -sy;

    if (ARC_Hit(x + sx, y))
      sx = -sx;

    if (ARC_Hit(x, y + sy))
      sy = -sy;

    if ((y >= GFX_H - 2) && (x >= bx && x <= bx + 16))
    {
      sy = -sy;
      GFX_DrawChar(GFX_W - 24 - life * 8, 6, 3, BACK_COLOR);
    }
    else if ((y >= GFX_H - 2) && (x < bx || x > bx + 8))
    {
      x = bx;
      y = GFX_H - 3;
      sy = 1;
      sx = 1;
      life++;
      GFX_DrawChar(GFX_W - 24 - life * 8, 6, 3, BACK_COLOR);
    }

    GFX_PutPixel(x, y, ITEM_COLOR);
  }
}