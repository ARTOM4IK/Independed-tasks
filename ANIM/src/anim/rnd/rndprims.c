/* FILE NAME  : rndprims.c
 * PROGRAMMER : AA4
 * LAST UPDATE: 03.02.2025
 * PURPOSE    : 3D animation project.
 *              Rendering primitives handle module.
 */

#include <stdio.h>
#include <string.h>

#include "rnd.h"

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       aa4PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL AA4_RndPrimsCreate( aa4PRIMS *Prs, INT NumOfPrims )
{
  memset(Prs, 0, sizeof(aa4PRIMS));
  if ((Prs->Prims = malloc(sizeof(aa4PRIM) * NumOfPrims)) == NULL)
    return FALSE;
  Prs->NumOfPrims = NumOfPrims;
  Prs->Trans = MatrIdentity();
  return TRUE;
} /* End of 'AA4_RndPrimsCreate' function */

/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       aa4PRIMS *Prs;
 * RETURNS: None.
 */
VOID AA4_RndPrimsFree( aa4PRIMS *Prs )
{
  free(Prs->Prims);
  memset(Prs, 0, sizeof(aa4PRIMS));
} /* End of 'AA4_RndPrimsFree' function */

/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       aa4PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID AA4_RndPrimsDraw( aa4PRIMS *Prs, MATR World )
{
  INT i;
  MATR m = MatrMulMatr(Prs->Trans, World);

  AA4_RndShdAddonI[0] = Prs->NumOfPrims;
  /* Draw all nontransparent primitives */ 
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (AA4_RndMtlGet(Prs->Prims[i].MtlNo)->Trans == 1)
      AA4_RndShdAddonI[1] = i, AA4_RndPrimDraw(&Prs->Prims[i], m);

  /* Draw all transparent primitives */ 
  glEnable(GL_CULL_FACE);

  /* Draw all front-face-culling */ 
  glCullFace(GL_FRONT);
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (AA4_RndMtlGet(Prs->Prims[i].MtlNo)->Trans != 1)
      AA4_RndShdAddonI[1] = i, AA4_RndPrimDraw(&Prs->Prims[i], m);

  /* Draw all back-face-culling */ 
  glCullFace(GL_BACK);
  for (i = 0; i < Prs->NumOfPrims; i++)
    if (AA4_RndMtlGet(Prs->Prims[i].MtlNo)->Trans != 1)
      AA4_RndShdAddonI[1] = i, AA4_RndPrimDraw(&Prs->Prims[i], m);

  glDisable(GL_CULL_FACE);
} /* End of 'AA4_RndPrimsDraw' function */

/* Load primitives from '*.G3DM' file function.
 * ARGUMENTS:
 *   - pointer to primitives to create:
 *       aa4PRIMS *Prs;
 *   - '*.G3DM' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL AA4_RndPrimsLoad( aa4PRIMS *Prs, CHAR *FileName )
{
  FILE *F;
  INT flen, p, m, t;
  BYTE *mem, *ptr;
  DWORD Sign; /* == "G3DM" */
  DWORD NumOfPrims;
  DWORD NumOfMaterials;
  DWORD NumOfTextures;

  memset(Prs, 0, sizeof(aa4PRIMS));
  if ((F = fopen(FileName, "rb")) == NULL)
    return FALSE;

  /* Obtain file length */
  fseek(F, 0, SEEK_END);
  flen = ftell(F);

  /* Allocate memory for whole file */
  if ((mem = malloc(flen)) == NULL)
  {
    fclose(F);
    return FALSE;
  }
  rewind(F);
  /* Load who;e file to memory */
  fread(mem, 1, flen, F);
  fclose(F);

  ptr = mem;
  /* Signature */
  Sign = *(DWORD *)ptr;
  ptr += 4;
  if (Sign != *(DWORD *)"G3DM")
  {
    free(mem);
    return FALSE;
  }

  /* Quantities */
  NumOfPrims = *(DWORD *)ptr;
  ptr += 4;
  NumOfMaterials = *(DWORD *)ptr;
  ptr += 4;
  NumOfTextures = *(DWORD *)ptr;
  ptr += 4;

  if (!AA4_RndPrimsCreate(Prs, NumOfPrims))
  {
    free(mem);
    return FALSE;
  }

  /* Primitives */
  for (p = 0 ; p < NumOfPrims; p++)
  {
    DWORD NumOfVertexes;
    DWORD NumOfFacetIndexes;  /* num of facets * 3 */
    DWORD MtlNo;              /* Material number in table below (in material section) */
    aa4VERTEX *V;
    INT *Ind;

    NumOfVertexes = *(DWORD *)ptr;
    ptr += 4;
    NumOfFacetIndexes = *(DWORD *)ptr;
    ptr += 4;
    MtlNo = *(DWORD *)ptr;
    ptr += 4;
    V = (aa4VERTEX *)ptr;
    ptr += sizeof(aa4VERTEX) * NumOfVertexes;
    Ind = (INT *)ptr;
    ptr += sizeof(INT) * NumOfFacetIndexes;

    AA4_RndPrimCreate(&Prs->Prims[p], AA4_RND_PRIM_TRIMESH, V, NumOfVertexes, Ind, NumOfFacetIndexes);
    Prs->Prims[p].MtlNo = AA4_RndMaterialsSize + MtlNo;
  }
 
  /* Materials */
  for (m = 0 ; m < NumOfMaterials; m++)
  {
    struct
    {
       CHAR Name[300]; /* Material name */
       /* Illumination coefficients */
       VEC Ka, Kd, Ks;     /* Ambient, diffuse, specular coefficients */
       FLT Ph;             /* Phong power coefficient – shininess */
       FLT Trans;          /* Transparency factor */
       DWORD Tex[8];       /* Texture references 
                            * (8 time: texture number in G3DM file, -1 if no texture) */
       /* Shader information */
       CHAR ShaderString[300]; /* Additional shader information */
       DWORD Shader;       /* Shader number (uses after load into memory) */
    } *fmat;
    aa4MATERIAL mtl = AA4_RndMtlGetDef();

    fmat = (VOID *)ptr;
    ptr += sizeof(*fmat);
    strncpy(mtl.Name, fmat->Name, AA4_STR_MAX - 1);
    mtl.Ka = fmat->Ka;
    mtl.Kd = fmat->Kd;
    mtl.Ks = fmat->Ks;
    mtl.Ph = fmat->Ph;
    mtl.Trans = fmat->Trans;
    for (t = 0; t < 8; t++)
      mtl.Tex[t] = fmat->Tex[t] == -1 ? -1 : AA4_RndTexturesSize + fmat->Tex[t];
    AA4_RndMtlAdd(&mtl);
  }

  /* Textures */
  for (t = 0 ; t < NumOfTextures; t++)
  {
    CHAR *Name;
    DWORD W, H, C;

    Name = (CHAR *)ptr;
    ptr += 300;
    W = *(DWORD *)ptr;
    ptr += 4;
    H = *(DWORD *)ptr;
    ptr += 4;
    C = *(DWORD *)ptr;
    ptr += 4;
    AA4_RndTexAddImg(Name, W, H, C, ptr);
    ptr += C * W * H;
  }

  free(mem);
  return TRUE;
} /* End of 'AA4_RndPrimsLoad' function */

/* END OF 'rndprims.c' FILE */
