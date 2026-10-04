/* FILE NAME: rnddata.c
 * PROGRAMMER: AA4
 * LAST UPDATE: 22.01.2025
 * PURPOSE: 3D animation project.
 *          Data of render module.
 */

#include "anim/rnd/rnd.h"

HGLRC AA4_hRndGLRC;
HWND AA4_hRndWnd;                   /* Work window handle */
HDC AA4_hRndDC;                     /* Work window memory device context */
  INT AA4_RndFrameW, AA4_RndFrameH; /* Work window size */
/* Proj references */
FLT
  AA4_RndProjSize = 0.1,     /* Project plane fit square */
  AA4_RndProjDist = 0.1,     /* Distance to project plane from viewer (near) */
  AA4_RndProjFarClip = 300;  /* Distance to project far clip plane (far) */
/* Matr references */
MATR
  AA4_RndMatrView, /* View coordinate system matrix */
  AA4_RndMatrProj, /* Projection coordinate system matrix */
  AA4_RndMatrVP;   /* Stored (View * Proj) matrix */
/* Cam references */
VEC
  AA4_RndCamLoc,   /* camera location */
  AA4_RndCamUp,    /* camera up direction  */
  AA4_RndCamAt,    /* camera look at */
  AA4_RndCamDir,   /* camera direction */
  AA4_RndCamRight; /* camera right direction  */
/* UBO references */
UINT
  AA4_RndShdUBOCameraNo, /* UBO reference for camera UBO buffer */
  AA4_RndShdUBOPrimNo,   /* UBO reference for primitive UBO buffer */
  AA4_RndShdUBOMtlNo,   /* UBO reference for material UBO buffer */
  AA4_RndShdUBOSyncNo;   /* UBO reference for sync data UBO buffer */

aa4RND_UBO_CAMERA AA4_UboCam; /* UBO Cam buffer */
aa4RND_UBO_PRIM AA4_UboPrim;  /* UBO Prim buffer */
aa4RND_UBO_SYNC AA4_UboSync;  /* UBO Sync buffer */
aa4RND_UBO_MTL AA4_UboMtl;    /* UBO Mtl buffer */
aa4RND_UBO_LIGHT AA4_UboLig;   /* UBO Lig buffer */

INT AA4_RndShdAddonI[4];   /* Addon int data */
FLT AA4_RndShdAddonF[4];   /* Addon float data */
VEC4 AA4_RndShdAddonV[4];  /* Addon vec data */

INT AA4_RndTargetTexNo[AA4_RND_NUM_OF_TARGETS];  /* Array of color attachment textures */

aa4LIGHT AA4_RndLights[AA4_RND_MAX_LIGHTS];
INT AA4_RndLightsSize;

/* END OF 'rnddata.c' FILE */
