/* Arsentev Artemy, 09-4, 31.10.2024 */

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

#include <glut.h>

#include "STARS.H"

VEC Stars[MAX];

DBL Speed = 30000;
DBL ProjDist = 1.0;
DBL ProjSize = 1.0;
DBL Wp, Hp, Ws, Hs;
DBL tt;

int DeltaTime1;



double R0( void )
{
  return rand() / (double) RAND_MAX;
}

double R1( void )
{
  return 2.0 * rand() / RAND_MAX - 1;
}

static VEC StarInit( void )
{
  VEC s;

  s.X = INFINITY * R1();
  s.Y = INFINITY * R1();
  s.Z = INFINITY * R0();

  return s;
}

void ProjSet( DBL WS, DBL HS )
{
  Ws = WS;
  Hs = HS;

  if (Ws >= Hs)
    Wp = ProjSize * Ws / Hs, Hp = ProjSize;
  else
    Wp = ProjSize, Hp = ProjSize * Hs / Ws;
}

static void StarDraw( VEC S )
{
  DBL xp, yp, xs, ys, xh, yh;

  yp = S.Y * (ProjDist / S.Z);
  xp = S.X * (ProjDist / S.Z);

  xs = xp * (Ws / Wp) + (Ws / 2);
  ys = -yp * (Hs / Hp) + (Hs / 2);
  
  if (GetAsyncKeyState(VK_LEFT) & 0x8000)
    tt -= 0.30 * DeltaTime1;
  if (GetAsyncKeyState(VK_RIGHT) & 0x8000)
    tt += 0.30 * DeltaTime1;

  xh = xs * cos(tt) - ys * sin(tt);
  yh = xs * sin(tt) + ys * cos(tt);

  GFX_PutPixel((int)xh, (int)yh, GFX_RGB(255, 255, 255));
}

void StarsInit( void )
{
  int i;

  for (i = 0; i < MAX; i++)
    Stars[i] = StarInit();
}

void StarsMove( DBL DeltaTime )
{
  int i;

  for (i = 0; i < MAX; i++)
  {
      Stars[i].Z -= Speed * DeltaTime;
    if (Stars[i].Z <= ProjDist)
      Stars[i].Z += INFINITY;
  }
}

void StarsDraw( void )
{
  int i;

  for (i = 0; i < MAX; i++)
    StarDraw(Stars[i]);
}