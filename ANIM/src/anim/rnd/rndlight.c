/* FILE NAME: rndlight.c
 * PROGRAMMER: AA4
 * LAST UPDATE: 17.03.2025
 * PURPOSE: 3D animation project.
 *          Light module.
*/

#include "rnd.h"

static INT
  AA4_RndLightShdAmbient,  /* Ambient shader */
  AA4_RndLightShdPoint,    /* Point light source shader */
  AA4_RndLightShdDir,      /* Directional light source shader */
  AA4_RndLightShdDraw,     /* Draw light source shader */
  AA4_RndLightShdSpot;     /* Spot light source shader */

static aa4PRIM 
  AA4_RndLightPrimFullScreen,  /* For ambient, directional, spot lights */
  AA4_RndLightPrimSphere;      /* For point lights */
static INT AA4_RndLightMtlNo;  /* Light source material  */

/* Add light source function.
 * ARGUMENTS:
 *   - light source type:
 *       aa4LIGHT_TYPE Type;
 * RETURNS:
 *   (aa4LIGHT *) pointer to add light source or NULL if no spoace for a new ligth source.
 */
static aa4LIGHT * AA4_RndLightAdd( aa4LIGHT_TYPE Type )
{
  aa4LIGHT *L;
  static CHAR Buf[102];
  static CHAR *Names[] =
  {
    "Ambient",
    "Point",
    "Directional",
    "Spot",
  };
 
  if (Type < AA4_LIGHT_AMBIENT || Type > AA4_LIGHT_SPOT || AA4_RndLightsSize >= AA4_RND_MAX_LIGHTS)
    return NULL;
  L = &AA4_RndLights[AA4_RndLightsSize++];
  memset(L, 0, sizeof(aa4LIGHT));
  L->Type = Type;
  L->Pos = VecSet(0, 1, 0);
  L->Dir = VecSet(0, 1, 0);
  L->Color = VecSet1(1);
  L->Att = VecSet(1, 0, 0);
  L->CutOffDist = Vec2Set(8, 18);
  L->CutOffAngle = Vec2Set(cos(D2R(30)), cos(D2R(47)));
  wsprintf(Buf, "Light source: %s", Names[Type]);
  L->UBONo = AA4_RndUBOCreate(Buf, AA4_RND_UBO_BIND_MATERIAL, sizeof(aa4RND_UBO_LIGHT), NULL);
  AA4_RndUBOLightUpdate(L);
  return L;
} /* End of 'AA4_RndLightAdd' function */

/* Light sources initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndLightsInit( VOID )
{
  INT i;
  aa4MATERIAL mtl = AA4_RndMtlGetDef();

  AA4_RndLightsSize = 0;

  AA4_RndPrimCreate(&AA4_RndLightPrimFullScreen, AA4_RND_PRIM_POINTS, NULL, 1, NULL, 0);
  /* create prim sphere for point lights */

  AA4_RndLightShdAmbient = AA4_RndShdAdd("lights/ambient");
  AA4_RndLightShdPoint = AA4_RndShdAdd("lights/point");
  /*AA4_RndLightShdDir = AA4_RndShdAdd("lights/dir");
  AA4_RndLightShdSpot = AA4_RndShdAdd("lights/spot");*/
/*  AA4_RndLightShdDraw = AA4_RndShdAdd("lights/draw");*/

  for (i = 0; i < AA4_RND_NUM_OF_TARGETS; i++)
    mtl.Tex[i] = AA4_RndTargetTexNo[i];

  strcpy(mtl.Name, "Lights");
  AA4_RndLightMtlNo = AA4_RndMtlAdd(&mtl);

  /* Default ambient light */
  AA4_RndLightAdd(AA4_LIGHT_AMBIENT);
}

/* Light sources deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndLightsClose( VOID )
{
  AA4_RndPrimFree(&AA4_RndLightPrimFullScreen);
}
 
/* Add point light source function.
 * ARGUMENTS:
 *   - point light source position:
 *       VEC Pos;
 * RETURNS:
 *   (aa4LIGHT *) pointer to add light source or NULL if no space for a new ligth source.
 */
aa4LIGHT * AA4_RndLightAddPoint( VEC Pos )
{
  aa4LIGHT *L;
  
  if ((L = AA4_RndLightAdd(AA4_LIGHT_POINT)) == NULL)
    return NULL;
  L->Pos = Pos;
  return L;
}
 
/* Add directional light source function.
 * ARGUMENTS:
 *   - directional light source direction:
 *       VEC Dir;
 * RETURNS:
 *   (aa4LIGHT *) pointer to add light source or NULL if no space for a new ligth source.
 */
aa4LIGHT * AA4_RndLightAddDir( VEC Dir )
{
  aa4LIGHT *L;

  if ((L = AA4_RndLightAdd(AA4_LIGHT_DIR)) == NULL)
    return NULL;
  L->Dir = Dir;
  return L;
}

/* Add spot light source function.
 * ARGUMENTS:
 *   - spot light source position:
 *       VEC Pos;
 *   - spot light source look-at point:
 *       VEC At;
 * RETURNS:
 *   (aa4LIGHT *) pointer to add light source or NULL if no space for a new ligth source.
 */
aa4LIGHT * AA4_RndLightAddSpot( VEC Pos, VEC At )
{
  aa4LIGHT *L;
  
  if ((L = AA4_RndLightAdd(AA4_LIGHT_SPOT)) == NULL)
    return NULL;
  L->Pos = Pos;
  L->Dir = VecNormalize(VecSubVec(At, Pos));
  AA4_RndUBOLightUpdate(L);
  return L;
}
/* Redraw all light sources function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndLightRedraw( VOID )
{
  INT lig;
  INT Shaders[] =
  {
    AA4_RndLightShdAmbient,
    AA4_RndLightShdPoint,
    AA4_RndLightShdDir,
    AA4_RndLightShdSpot,
  };

  /* Output light sources */
  glBlendFunc(GL_ONE, GL_ONE);
  glDepthMask(FALSE);
  glDisable(GL_DEPTH_TEST);
  for (lig = 0; lig < AA4_RndLightsSize; lig++)
  {
    aa4LIGHT *L = AA4_RndLights + lig;
 
    AA4_RndUBOApply(L->UBONo);
    AA4_RndLightPrimFullScreen.MtlNo = AA4_RndLightMtlNo;
    AA4_RndMaterials[AA4_RndLightMtlNo].ShdNo = Shaders[L->Type];
    AA4_RndPrimDraw(&AA4_RndLightPrimFullScreen, MatrIdentity());
  }
  glEnable(GL_DEPTH_TEST);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glDepthMask(TRUE);
}

/* END OF 'rndlight.c' FILE */
