/* FILE NAME: globe.c
 * PROGRAMMER: AA4
 * DATE: 05.01.2025
 * PURPOSE: draw sphere
*/

#include <windows.h>
#include <commondf.h>
#include <math.h>
#include <time.h>
#include "globe.h"
#include "mth.h"

static VEC Geom[GEOM_H][GEOM_W];            /* Points array */
static INT GLB_Ws, GLB_Hs;                  
static POINT pnts[GEOM_H][GEOM_W], pnt[4];  /* Points to paint array */
static VEC S[GEOM_H][GEOM_W];               /* Array of rotated vectors */
static DBL ProjectDist = 1, ProjSize = 1,   /* Project size and distance */
GLB_Hp, GLB_Wp;                             
static VEC GeomN[GEOM_H][GEOM_W];           /* Normales array */
static VEC n[4];                            /* Check 4 points array */
static VEC NewGeomN[GEOM_H][GEOM_W];        /* New normales array */
static MATR m, minv;                        /* Matrix variables */

/* Set number in range from 0 to 255 function.
 * ARGUMENTS:
 *   - Number:
 *       DBL x;
 * RETURNS:
 *   Number in range from 0 to 255.
 */

DBL Obrb( DBL x )
{
  if (x < 0)
    return 0;
  if (x > 255)
    return 255;
  return x;
} /* End of 'Obrb' function */

/* Init sphere.
 * ARGUMENTS:
 *   - Number:
 *       DBL x;
 * RETURNS:
 *   Number in range from 0 to 255.
 */

VOID GLB_INIT( DBL R )
{
  INT i, j;        /* Counter variables */
  DBL theta, phi;  /* Agle variables */
  
  m = MatrIdentity();
  for (i = 0, theta = 0; i < GEOM_H; i++, theta += PI / (GEOM_H - 1))
    for (j = 0, phi = 0; j < GEOM_W; j++, phi += 2 * PI / (GEOM_W - 1))
    {
      Geom[i][j].X = R * sin(theta) * sin(phi);
      Geom[i][j].Y = R * cos(theta);
      Geom[i][j].Z = R * sin(theta) * cos(phi);
    }
} /* End of 'GLB_INIT' function */

/* Get screen size function.
 * ARGUMENTS:
 *   - Number:
 *       INT Ws, INT Hs;
 * RETURNS:
 *   Nothing.
 */

VOID GLB_RESIZE( INT Ws, INT Hs )
{
  GLB_Ws = Ws; /* Screen width */
  GLB_Hs = Hs; /* Screen height */

  if (GLB_Ws >= GLB_Hs)
    GLB_Wp = ProjSize * GLB_Ws / GLB_Hs, GLB_Hp = ProjSize;
  else
    GLB_Wp = ProjSize, GLB_Hp = ProjSize * GLB_Hs / GLB_Ws;
} /* End of 'GLB_RESIZE' function */

/* Draw sphere function.
 * ARGUMENTS:
 *   - DC Handle:
 *       HDC hDC;
 * RETURNS:
 *   Nothing.
 */

VOID GLB_DRAW( HDC hDC )
{
  INT i, j;              /* Counter variables */
  INT xs, ys;            /* screen projection coordinates */
  DBL yp, xp;            /* projection coordinates with perspective */
  DBL t;                 /* Time variable */
  VEC L = VecSet1(1);    /* Light vector */

  SelectObject(hDC, GetStockObject(DC_PEN));
  SetDCPenColor(hDC, RGB(0, 255, 0));

  t = clock() / (DBL)CLOCKS_PER_SEC;

  m = MatrMulMatr(MatrRotateX(0.03), MatrMulMatr(MatrMulMatr(m, MatrRotateY(sin(0.03))), MatrRotateZ(sin(0.03))));
  minv = MatrTranspose(MatrInverse(m));

  for (i = 0; i < GEOM_H; i++)
    for (j = 0; j < GEOM_W; j++)
    {
      S[i][j] = VecMulMatr(Geom[i][j], m);
      S[i][j].Z -= 10;
    }

  for (i = 0; i < GEOM_H; i++)
    for (j = 0; j < GEOM_W; j++)
    {
      xp = S[i][j].X * ProjectDist / -S[i][j].Z;
      yp = S[i][j].Y * ProjectDist / -S[i][j].Z;

      xs = (INT)(xp * (GLB_Ws / GLB_Wp) + (GLB_Ws / 2));
      ys = (INT)(-yp * (GLB_Hs / GLB_Hp) + (GLB_Hs / 2));

      pnts[i][j].x = xs;
      pnts[i][j].y = ys;
    }

  for (i = 0; i < GEOM_H - 1; i++)
    for (j = 0; j < GEOM_W - 1; j++)
    {
      n[0] = S[i][j];
      n[1] = S[i + 1][j];
      n[2] = S[i + 1][j + 1];
      n[3] = S[i][j + 1];

      GeomN[i][j] = VecNormalize(VecAddVec(VecCrossVec(VecSubVec(n[1], n[0]), VecSubVec(n[3], n[0])), VecCrossVec(VecSubVec(n[3], n[2]), VecSubVec(n[1], n[2]))));
    }

  for (i = 0; i < GEOM_W; i++)
  {
    MoveToEx(hDC, pnts[0][i].x, pnts[0][i].y, NULL);
    for (j = 1; j < GEOM_H; j++)
      LineTo(hDC, pnts[j][i].x, pnts[j][i].y);
  }

  for (i = 0; i < GEOM_H; i++)          
  {
    MoveToEx(hDC, pnts[i][0].x, pnts[i][0].y, NULL);
    for (j = 1; j < GEOM_W; j++)
      LineTo(hDC, pnts[i][j].x, pnts[i][j].y);
  }

  for (i = 0; i < GEOM_H - 1; i++)
  {
    for (j = 0; j < GEOM_W - 1; j++)
    {
      DBL res;
      NewGeomN[i][j] = VecNormalize(VecMulMatr(GeomN[i][j], minv));
      res = VecDotVec(VecNormalize(L), NewGeomN[i][j]);

      SelectObject(hDC, GetStockObject(DC_BRUSH));
      SetDCBrushColor(hDC, RGB(Obrb(255 * res), Obrb(255 * res), Obrb(255 * res)));

      pnt[0] = pnts[i][j];
      pnt[1] = pnts[i + 1][j];
      pnt[2] = pnts[i + 1][j + 1];
      pnt[3] = pnts[i][j + 1];

      if ((pnt[0].x - pnt[1].x) *
        (pnt[1].y - pnt[2].y) +
        (pnt[1].x - pnt[2].x) *
        (pnt[2].y - pnt[3].y) +
        (pnt[2].x - pnt[3].x) *
        (pnt[3].y - pnt[0].y) +
        (pnt[3].x - pnt[0].x) *
        (pnt[0].y - pnt[1].y) < 0)
          Polygon(hDC, pnt, 4);
    }
  }  
} /* End of 'GLB_DRAW' function */

/* END OF 'globe.c' FILE */
