/* Arsentev Artemy, 09-4, 30.10.2024 */
#define _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <time.h>
#include <math.h>
#include "CMPL.H"

DBL SyncTime, FPS;

CMPL SetCmpl( DBL a, DBL b )
{
  CMPL z;
  z.Im = b;
  z.Re = a;
  return z;
}

CMPL AddCmpl( CMPL z1, CMPL z2 )
{
  return SetCmpl(z1.Re + z2.Re, z1.Im + z2.Im); 
}

CMPL MultCmpl( CMPL z1, CMPL z2 )
{
  return SetCmpl(z1.Re * z2.Re - z1.Im * z2.Im, z1.Re * z2.Im + z1.Im * z2.Re); 
}

DBL Norm2( CMPL Z )
{
  return Z.Re * Z.Re + Z.Im * Z.Im;
}

CMPL SubCmpl( CMPL z1, CMPL z2 )
{
  return SetCmpl(z1.Re - z2.Re, z1.Im - z2.Im);
}

CMPL MulCmpl( CMPL z1, DBL x )
{
  return SetCmpl(z1.Re * x, z1.Im * x);
}

CMPL SoprCmpl( CMPL z )
{
  return SetCmpl(z.Re, -z.Im);
}

CMPL DivCmpl( CMPL z1, CMPL z2 )
{
  return MultCmpl(z1, MulCmpl(SoprCmpl(z2), 1 / Norm2(z2)));
}



void Timer( void )
{
  long t;
  static long StartTime = -1, FPSTime, FrameCount;
  

  t = clock();
  
  if (StartTime == -1)
    StartTime = FPSTime = t;
  
  SyncTime = (t - StartTime) / (double)CLOCKS_PER_SEC;
  
  FrameCount++;
  
  if (t - FPSTime > 3 * CLOCKS_PER_SEC)
  {
    FPS = FrameCount / ((t - FPSTime) / (double)CLOCKS_PER_SEC);
    FPSTime = t;
    FrameCount = 0;
    sprintf(nam, "%.3lf FPS", FPS);
  }
}

int Jul( CMPL z, CMPL c ) 
{
  int n = 0;
  CMPL b = z, bt = z;
  
  while (n++ < 255 && Norm2(b) < 4.0)
  {
    b = AddCmpl(MultCmpl(bt, bt), c);
    bt = b;
  }
  return n;
}

int Newton( CMPL z )
{                  
  int n = 0;
  CMPL z1 = z; /* z1 --> n+1, z --> n */ 
  
  while (n++ < 255 && Norm2(z1) < 4.0)
  {
    z1 = SubCmpl(z, DivCmpl(SubCmpl(MultCmpl(MultCmpl(z, z), z), SetCmpl(1, 0)), MulCmpl(MultCmpl(z, z), 3)));
    z = z1;
  }
  return n;
}

int WrongNewton( CMPL z, CMPL C )
{                  
  int n = 0;
  CMPL z1 = z; /* z1 --> n+1, z --> n */ 
  CMPL con;
  con.Re = 1;
  con.Im = 0;
  
  while (n++ < 255 && Norm2(z1) < 4.0)
  {
/*    z1 = SubCmpl(C, DivCmpl(SubCmpl(MultCmpl(MultCmpl(z, z), C), con), MulCmpl(MultCmpl(z, C), 3))); */
    z1 = SubCmpl(z, DivCmpl(SubCmpl(MultCmpl(MultCmpl(C, C), z), con), MulCmpl(MultCmpl(z, z), 3)));
  
    z = z1;
  }
  return n;
}

void frac( void )
{
  int x, y, n;
  CMPL z;
  CMPL C = SetCmpl(0.35 + 0.08 * sin(SyncTime + 3), 0.39 + 0.08 * sin(1.1 * SyncTime));
  

  for (y = 0; y < GFX_H; y++)
    for (x = 0; x < GFX_W; x++)
    {
      z = SetCmpl(x * (double)(X1 - X0) / GFX_W + X0, y * (double)(Y1 - Y0) / GFX_H + Y0);

      n = Jul(z, C); 
      /*n = Newton(z);*/

      GFX_PutPixel(x, y, GFX_RGB(n, n * 64, n * 32));
    }
}