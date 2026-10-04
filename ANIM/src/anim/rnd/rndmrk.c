/* FILE NAME  : rndmrk.c
 * PROGRAMMER : AA4
 * LAST UPDATE: 19.02.2025
 * PURPOSE    : 3D animation project.
 *              Rendering system markers handle module.
 */

#include "rnd.h"

/*** Marker semiglobal data ***/
static aa4PRIM
  AA4_RndMarkerPrimSphere,   /* Sphere marker primitive */
  AA4_RndMarkerPrimCylinder; /* Cylinder marker primitive */

/* Marker system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndMarkerInit( VOID )
{
  aa4MATERIAL mtl = AA4_RndMtlGetDef();

  AA4_RndPrimCreate(&AA4_RndMarkerPrimSphere, AA4_RND_PRIM_PATCH, NULL, 1, NULL, 0);
  AA4_RndMarkerPrimSphere.NumOfPatchPoints = 1;
  strncpy(mtl.Name, "Marker sphere material", AA4_STR_MAX);
  mtl.ShdNo = AA4_RndShdAdd("marker/sphere");
  AA4_RndMarkerPrimSphere.MtlNo = AA4_RndMtlAdd(&mtl);

  AA4_RndPrimCreate(&AA4_RndMarkerPrimCylinder, AA4_RND_PRIM_PATCH, NULL, 1, NULL, 0);
  AA4_RndMarkerPrimCylinder.NumOfPatchPoints = 1;
  strncpy(mtl.Name, "Marker cylinder material", AA4_STR_MAX);
  mtl.ShdNo = AA4_RndShdAdd("marker/cylinder");
  AA4_RndMarkerPrimCylinder.MtlNo = AA4_RndMtlAdd(&mtl);
} /* End of 'AA4_RndMarkerInit' function */

/* Marker system deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndMarkerClose( VOID )
{
  AA4_RndPrimFree(&AA4_RndMarkerPrimSphere);
  AA4_RndPrimFree(&AA4_RndMarkerPrimCylinder);
} /* End of 'AA4_RndMarkerClose' function */

/* Draw cylinder function.
 * ARGUMENTS:
 *   - cylinder start point:
 *       VEC P0;
 *   - cylinder start point radius:
 *       FLT R0;
 *   - cylinder end point:
 *       VEC P1;
 *   - cylinder end point radius:
 *       FLT R1;
 *   - cylinder color:
 *       VEC Color;
 *   - stransform matrix:
 *       MATR Transform;
 * RETURNS: None.
 */
VOID AA4_RndMrkDrawCylinder( VEC P0, FLT R0, VEC P1, FLT R1, VEC Color, MATR Transform )
{
  AA4_RndShdAddonF[0] = R0;
  AA4_RndShdAddonF[1] = R1;
  AA4_RndShdAddonV[0] = Vec4Set(P0.X, P0.Y, P0.Z, 1);
  AA4_RndShdAddonV[1] = Vec4Set(P1.X, P1.Y, P1.Z, 1);
  AA4_RndShdAddonV[2] = Vec4Set(Color.X, Color.Y, Color.Z, 1);
  AA4_RndPrimDraw(&AA4_RndMarkerPrimCylinder, Transform);
} /* End of 'AA4_RndMrkDrawCylinder' function */

/* Draw sphere function.
 * ARGUMENTS:
 *   - sphere center point:
 *       VEC C;
 *   - sphere (ellipsoid) radiuses:
 *       VEC R;
 *   - cylinder color:
 *       VEC Color;
 *   - stransform matrix:
 *       MATR Transform;
 * RETURNS: None.
 */
VOID AA4_RndMrkDrawSphere( VEC C, VEC R, VEC Color, MATR Transform )
{
  AA4_RndShdAddonV[0] = Vec4Set(C.X, C.Y, C.Z, 1);
  AA4_RndShdAddonV[1] = Vec4Set(R.X, R.Y, R.Z, 1);
  AA4_RndShdAddonV[2] = Vec4Set(Color.X, Color.Y, Color.Z, 1);
  AA4_RndPrimDraw(&AA4_RndMarkerPrimSphere, Transform);
} /* End of 'AA4_RndMrkDrawSphere' function */

/* END OF 'rndmrk.c' FILE */
