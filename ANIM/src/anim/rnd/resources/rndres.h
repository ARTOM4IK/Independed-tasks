/* FILE NAME: rndres.h
 * PROGRAMMER: AA4
 * LAST UPDATE: 29.01.2025
 * PURPOSE: 3D animation project.
 *          Rendering resources declaration module.
 */

#ifndef __rndres_h_
#define __rndres_h_

#include "def.h"
#include "anim/rnd/rnd.h"

#define AA4_STR_MAX 300
 
/* Shader program store type */
typedef struct tagaa4SHADER
{
  CHAR Name[AA4_STR_MAX]; /* Shader filename prefix */
  INT ProgId;             /* Shader program Id */
} aa4SHADER;
 
/* Shaders stock */
#define AA4_MAX_SHADERS 30
extern aa4SHADER AA4_RndShaders[AA4_MAX_SHADERS]; /* Array of shaders */
extern INT AA4_RndShadersSize;                    /* Shadres array store size */

/* Texture representation type */
typedef struct tagaa4TEXTURE
{
  CHAR Name[AA4_STR_MAX]; /* Texture name */
  INT W, H;               /* Texture size in pixels */
  UINT TexId;             /* OpenGL texture Id */ 
} aa4TEXTURE;

/* Textures stock */
#define AA4_MAX_TEXTURES 300
extern aa4TEXTURE AA4_RndTextures[AA4_MAX_TEXTURES]; /* Array of textures */
extern INT AA4_RndTexturesSize;                      /* Textures array store size */
extern INT AA4_RndShdProgId;

/* Material store type */
typedef struct tagaa4MATERIAL
{
  CHAR Name[AA4_STR_MAX];   /* Material name */
  /* Illumination coefficients */
  VEC Ka, Kd, Ks;           /* Ambient, diffuse, specular coefficients */
  FLT Ph;                   /* Phong power coefficient */
  FLT Trans;                /* Transparency factor */
  INT Tex[8];               /* Texture references from texture table (or -1) */
  INT ShdNo;                /* Shader number in shader table */
  INT UBONo;                /* UBO number in UBO table */
  INT BufId;                /* Buffer Identification */
} aa4MATERIAL;

/* Material stock */
#define AA4_MAX_MATERIALS 300
extern aa4MATERIAL AA4_RndMaterials[AA4_MAX_MATERIALS]; /* Array of materials */
extern INT AA4_RndMaterialsSize;                        /* Materials array size */

/* Shader buffer stock */
#define AA4_MAX_SHADER_FILES 300

/* UBO representation type */
typedef struct tagaa4UBO
{
  CHAR Name[AA4_STR_MAX]; /* UBO name */
  INT Size;               /* UBO size in bytes */
  UINT UBOId;             /* OpenGL UBO Id */ 
  UINT BindPoint;         /* OpenGL UBO bind point */
} aa4UBO;

/* UBOs stock */
#define AA4_MAX_UBOS 3000
extern aa4UBO AA4_RndUBOs[AA4_MAX_UBOS]; /* Array of UBO */
extern INT AA4_RndUBOsSize;              /* UBO array store size */

/***
 * Common resource handle functions
 ***/
 
/* Resource initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndResInit( VOID );
 
/* Resource deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndResClose( VOID );

/***
 * Shader handle functions
 ***/

/* Load shader program from .GLSL files function.
 * ARGUMENTS:
 *   - shader file path to load (path\***.glsl):
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) load shader program Id.
 */
INT AA4_RndShdLoad( CHAR *ShaderFileNamePrefix );
/* Unload shader program fropm memory files function.
 * ARGUMENTS:
 *   - shader program Id:
 *       INT ProgId;
 * RETURNS:
 *   None.
 */
VOID AA4_RndShdDelete( INT ProgId );
/* Shader storage initialize function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_RndShdInit( VOID );
/* Shader storage deinitialize function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_RndShdClose( VOID );
/* Add shader to stock from file function.
 * ARGUMENTS:
 *   - shader file path to load:
 *       CHAR *ShaderFileNamePrefix;
 * RETURNS:
 *   (INT) new shader stock number.
 */
INT AA4_RndShdAdd( CHAR *ShaderFileNamePrefix );
/* Update from file all load shaders function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_RndShdUpdate( VOID );

/***
 * Materials handle functions
 ***/

/* Apply material on object function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       aa4PRIM *Pr;
 *   - world matrix:
 *       MATR World;
 * RETURNS:
 *   (VOID) Nothing.
 */
INT AA4_RndMtlApply( INT MtlNo );
/* Material initializate function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   (VOID) Nothing.
 */
VOID AA4_RndMtlInit( VOID );
/* Material deinitializate function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       aa4PRIM *Pr;
 *   - world matrix:
 *       MATR World;
 * RETURNS:
 *   (VOID) Nothing.
 */
VOID AA4_RndMtlClose( VOID );
/* Add material function.
 * ARGUMENTS:
 *   - pointer to material:
 *       aa4MATERIAL *Mtl;
 * RETURNS:
 *   (INT) Number of materials.
 */
INT AA4_RndMtlAdd( aa4MATERIAL *Mtl );
/* Set default material function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   (aa4MATERIAL) Default material.
 */
aa4MATERIAL AA4_RndMtlGetDef( VOID );
/* Get material by number function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   (aa4MATERIAL) material.
 */
aa4MATERIAL * AA4_RndMtlGet( INT MtlNo );
/* Get material by name function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   (aa4MATERIAL) material.
 */
aa4MATERIAL * AA4_RndMtlGetByName( CHAR *MtlName );
/* Get number of material by name function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   (aa4MATERIAL) material.
 */
INT AA4_RndMtlGetNoByName( CHAR *MtlName );

/***
 * Textures handle functions
 ***/

/* Texture handle initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndTexInit( VOID );
/* Texture handle deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndTexClose( VOID );
/* Add texture to stock function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size in pixels:
 *       INT W, H;
 *   - number of color components:
 *       INT C;
 *   - texture pixels data:
 *       VOID *Bits;
 * RETURNS:
 *   (INT) texture stock number (-1 if error is occured).
 */
INT AA4_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits );
/* Add texture from file to stock function.
 * ARGUMENTS:
 *   - texture file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (INT) texture stock number (-1 if error is occured).
 */
INT AA4_RndTexAddFromFile( CHAR *FileName );
/* Add texture by OpenGL Low-Level format to stock function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size in pixels:
 *       INT W, H;
 *   - OpenGL texture element data type:
 *       INT GLType;
 * RETURNS:
 *   (INT) texture stock number (-1 if error is occured).
 */
INT AA4_RndTexAddFmt( CHAR *Name, INT W, INT H, INT GLType );

/***
 * Uniform buffer object handle functions
 ***/

/* UBO handle initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndUBOInit( VOID );
/* UBO handle deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndUBOClose( VOID );
/* Add UBO to stock function.
 * ARGUMENTS:
 *   - UBO name:
 *       CHAR *Name;
 *   - OpenGL UBO bind point:
 *       UINT BindPoint;
 *   - UBO size in bytes:
 *       INT Size;
 *   - UBO data:
 *       VOID *Bits;
 * RETURNS:
 *   (INT) UBO stock number (-1 if error is occured).
 */
INT AA4_RndUBOCreate( CHAR *Name, UINT BindPoint, INT Size, VOID *Bits );
/* UBO data update function.
 * ARGUMENTS:
 *   - UBO number in stock:
 *       INT UBONo;
 *   - UBO offset in bytes:
 *       INT Offset;
 *   - UBO update data size in bytes:
 *       INT Size;
 *   - UBO data ('Size' bytes):
 *       VOID *Bits;
 * RETURNS: None.
 */
VOID AA4_RndUBOUpdate( INT UBONo, INT Offset, INT Size, VOID *Bits );
/* UBO apply function.
 * ARGUMENTS:
 *   - UBO number in stock:
 *       INT UBONo;
 * RETURNS: None.
 */
VOID AA4_RndUBOApply( INT UBONo );
/* UBO Cam data update function.
 * ARGUMENTS:
 *   - None.
 * RETURNS: None.
 */
VOID AA4_RndUBOCamUpdate( VOID );
/* UBO Sync data update function.
 * ARGUMENTS:
 *   - None.
 * RETURNS: None.
 */
VOID AA4_RndUBOSyncUpdate( VOID );
/* UBO Prim data update function.
 * ARGUMENTS:
 *   - Prim Matrixes.
 *       MATR W, MATR WINV, MATR WVP;
 * RETURNS: None.
 */
VOID AA4_RndUBOPrimUpdate( MATR W, MATR WINV, MATR WVP );

#endif /* __rndres_h_ */

/* END OF 'rndres.h' FILE */
