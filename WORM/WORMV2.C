/* Arsentev Artemy, 09-4, 21.10.2024 */
/*#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>


static int WRM_Field[WRM_FIELD_H][WRM_FIELD_W], WRM_Worm[WRM_MAX_LENGTH][2], WRM_WormLen, WRM_WormDir;

static void WRM_DrawSpot( int SpotX, int SpotY )
{
  int i, j;
  DWORD Color;

  Color = WRM_COLOR_BACK;

  switch (WRM_Field[SpotY][SpotX])
  {
  case WRM_SPOT_FREE:
    Color = WRM_COLOR_BACK;
    break;
  case WRM_SPOT_GOOD:
    Color = WRM_COLOR_GOOD;
    break;
  case WRM_SPOT_BAD:
    Color = WRM_COLOR_BAD;
    break;
  case WRM_SPOT_WORM:
    Color = WRM_COLOR_WORM;
    break;
  }

  for (i = 0; i < WRM_SPOT_SIZE ; i++)
    for (j = 0; j < WRM_SPOT_SIZE ; j++)
      GFX_PutPixel(WRM_FIELD_X + SpotX * WRM_SPOT_SIZE + j, WRM_FIELD_Y + SpotY * WRM_SPOT_SIZE + i, Color);
}

static void WRM_DrawField( void )
{
  int x, y;

  for (y = 0; y < WRM_FIELD_H; y++)
    for (x = 0; x < WRM_FIELD_W; x++)
      WRM_DrawSpot(x, y);
}

static void WRM_PlaceMushroom( int MushType )
{
  int x, y, n = 1000;

  while (n-- > 0)
  {
    x = rand() % WRM_FIELD_W;
    y = rand() % WRM_FIELD_H;

    if (WRM_Field[y][x] == WRM_SPOT_FREE)
    {
      WRM_Field[y][x] = MushType;
      return;
    }
  }
}

static void WRM_InitField( void )
{
  int i, j, n;

  for (i = 0; i < WRM_FIELD_H; i++)
    for (j = 0; j < WRM_FIELD_W; j++)
      WRM_Field[i][j] = WRM_SPOT_FREE;

  WRM_WormLen = 3;

  /* worm pos */
/*
  WRM_Worm[0][0] = 5;
  WRM_Worm[0][1] = 5;
  WRM_Worm[1][0] = 5;
  WRM_Worm[1][1] = 6;
  WRM_Worm[2][0] = 6;
  WRM_Worm[2][1] = 7;


  /* mushroom generating */
/*  n = 5;

  while (n-- > 0)
    WRM_PlaceMushroom(WRM_SPOT_GOOD);

  n = 2;

  while (n-- > 0)
    WRM_PlaceMushroom(WRM_SPOT_BAD);
}


void WRM_Init( void )
{
  GFX_Clear(WRM_COLOR_BAD);
  WRM_InitField();
  WRM_DrawField();
} 

void WRM_Kbd( unsigned char Key )
{
  switch (Key)
  {
  case 'a':
    if (WRM_WormDir != 1)
      WRM_WormDir = 3;
    break;
  case 'w':
    if (WRM_WormDir != 2)
      WRM_WormDir = 0;
    break;
  case 's':
    if (WRM_WormDir != 0)
      WRM_WormDir = 2;
    break;
  case 'd':
    if (WRM_WormDir != 3)
      WRM_WormDir = 1;
    break;
  }
}

void WRM_Step( void )
{
  static int Dx[4] = {0, 1, 0, -1}, Dy[4] = {-1, 0, 1, 0};
  int i;
  clock_t t;
  static clock_t start_time = -1, ball_start = 0;

  t = clock();

  if (t - ball_start > 0.1 * CLOCKS_PER_SEC)
  {
    ball_start = t;

    WRM_Field[WRM_Worm[WRM_WormLen - 1][1]][WRM_Worm[WRM_WormLen - 1][0]] = WRM_SPOT_FREE;


    for (i = WRM_WormLen - 1; i > 0; i--)
    {
      WRM_Worm[i][0] = WRM_Worm[i - 1][0];
      WRM_Worm[i][1] = WRM_Worm[i - 1][1];

      WRM_Field[WRM_Worm[i][1]][WRM_Worm[i][0]] = WRM_SPOT_WORM;
    }

    WRM_Worm[0][0] += Dx[WRM_WormDir];
    WRM_Worm[0][1] += Dy[WRM_WormDir];

    WRM_Worm[0][0] = (WRM_Worm[0][0] + WRM_FIELD_W) % WRM_FIELD_W;
    WRM_Worm[0][1] = (WRM_Worm[0][1] + WRM_FIELD_H) % WRM_FIELD_H;


    if (WRM_Field[WRM_Worm[0][1]][WRM_Worm[0][0]] == WRM_SPOT_GOOD)
    {
      WRM_WormLen++;
      WRM_PlaceMushroom(WRM_SPOT_GOOD);
    }
    
    else if (WRM_Field[WRM_Worm[0][1]][WRM_Worm[0][0]] == WRM_SPOT_BAD)
    {
      WRM_Field[WRM_Worm[WRM_WormLen - 1][1]][WRM_Worm[WRM_WormLen - 1][0]] = WRM_SPOT_FREE;
      WRM_WormLen--;
      WRM_PlaceMushroom(WRM_SPOT_BAD);
    }

    if (WRM_WormLen < 2)
    {
      exit(0);
    }

    WRM_Field[WRM_Worm[0][1]][WRM_Worm[0][0]] = WRM_SPOT_FREE;

    WRM_DrawField();
  }
}
*/