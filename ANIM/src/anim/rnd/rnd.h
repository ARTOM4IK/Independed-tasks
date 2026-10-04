/* FILE NAME: rnd.h
 * PROGRAMMER: AA4
 * LAST UPDATE: 22.01.2025
 * PURPOSE: anim
 *          Render declaration module.
*/

#ifndef __rnd_h_
#define __rnd_h_

#define GLEW_STATIC
#include <glew.h>
#include <wglew.h>
#include <gl/wglext.h>
#include "resources/rndres.h"
#include "def.h"

/***
 * Primitive support
 ***/

/* Vertex representation type */
typedef struct tagaa4VERTEX
{
  VEC P;  /* Vertex position */
  VEC2 T; /* Vertex texture coordinates */
  VEC N;  /* Vertex normal */
  VEC4 C; /* Vertex color */
} aa4VERTEX;

/* Primitive type */
typedef enum tagaa4PRIM_TYPE
{
  AA4_RND_PRIM_POINTS,   /* Array of points  – GL_POINTS */
  AA4_RND_PRIM_LINES,    /* Line segments (by 2 points) – GL_LINES */
  AA4_RND_PRIM_TRIMESH,  /* Triangle mesh - array of triangles – GL_TRIANGLES */
  AA4_RND_PRIM_TRISTRIP, /* Triangle strip - array of strip pairs – GL_TRIANGLE_STRIP */
  AA4_RND_PRIM_PATCH,    /* Patches- patches – GL_PATCH */
} aa4PRIM_TYPE;

/* Primitive representation type */
typedef struct tagaa4PRIM
{
  aa4PRIM_TYPE Type;    /* Primitive type */
  MATR Trans;           /* Additional transformation matrix */
  INT                
    VA,                 /* Vertex array Id */
    VBuf,               /* Vertex buffer Id */
    IBuf;               /* Index buffer Id (if 0 - use only vertex buffer) */
  VEC MinBB, MaxBB;     /* Bound box */
  INT NumOfElements;    /* Number of indices/vecrtices */
  INT MtlNo;            /* Material number in material array */
  INT NumOfPatchPoints; /* Number of patch points */
} aa4PRIM;

/* Primitive collection data type */
typedef struct tagaa4PRIMS
{
  INT NumOfPrims; /* Number of primitives in array */  
  aa4PRIM *Prims; /* Array of primitives */
  MATR Trans;     /* Common transformation matrix */
} aa4PRIMS;

/* Primitive collection data type */
typedef struct tagaa4GRID
{
  INT W, H;     /* Size */
  aa4VERTEX *V;  /* Vertexes */
} aa4GRID;

/*** UBO common data types and variables ***/

/* Camera UBO data UBO representation trype (update once per camera/frame change) */
typedef struct tagaa4RND_UBO_CAMERA
{
  MATR MatrVP;              /* Premultiplied 'view' and 'projection' matrixes */
  MATR MatrV;               /* Matrix 'view' */
  MATR MatrP;               /* Matrix 'projection' */
 
  VEC4 CamLoc;              /* Camera location */
  VEC4 CamRight;            /* Camera right direction */
  VEC4 CamUp;               /* Camera up direction */
  VEC4 CamDir;              /* Camera forward direction */
  VEC4 CamAt;               /* Camera at position */
  VEC4 FrameWHProjSizeDist; /* Camera frame size, projection size and distance */
} aa4RND_UBO_CAMERA;
 
/* Synchronization data UBO representation trype (update every frame) */
typedef struct tagaa4RND_UBO_SYNC
{
  VEC4 TimeDeltaTimeGlobalTimeDeltaTime; /* Time parameters */
  VEC4 IsWireFrameIsPauseFPS;            /* Wireframe and pause flags and FPS value */
} aa4RND_UBO_SYNC;
 
/* Material data UBO representation trype (update at material creation) */
typedef struct tagaa4RND_UBO_MTL
{
  VEC4 Ka;             /* Ambient Time parameters */
  VEC4 KdTrans;        /* Diffuse coefficient and transparency */
  VEC4 KsPh;           /* Specular coefficient and Phong power value */
  INT TextureFlags[8]; /* Material texture flags */
} aa4RND_UBO_MTL;
 
/* Primitive draw parameters data UBO representation trype (update before primitive drawing) */
typedef struct tagaa4RND_UBO_PRIM
{
  MATR MatrWVP;    /* Premultiplyed 'world' - 'view' - 'projection' matrixes */
  MATR MatrW;      /* World primitive matrix */
  MATR MatrWInv;   /* Inverse transposed world matrix (for normals) */
  INT AddonI[4];  /* Addon int data */
  FLT AddonF[4];   /* Addon float data */
  VEC4 AddonV[4];  /* Addon vec data */
} aa4RND_UBO_PRIM;

/* Light source draw parameters data UBO representation type (update at light source creation or modify) */
typedef struct tagaa4RND_UBO_LIGHT
{
  VEC4 PosCutOffAngle1;  /* Point and spot light source position and cut-off start angle cosine for spot light sources */
  VEC4 DirCutOffAngle2;  /* Directional and spot light source direction and cut-off end angle cosine for spot light sources */
  VEC4 ColorCutOffDist1; /* Light source color and start distance for point and spot light sources */
  VEC4 AttCutOffDist2;   /* Attenuation by distance coefficients: CC CL CQ  and end distance for point and spot light sources */
} aa4RND_UBO_LIGHT;

/* System UBO bind points */
#define AA4_RND_UBO_BIND_CAMERA     0
#define AA4_RND_UBO_BIND_SYNC       1
#define AA4_RND_UBO_BIND_MATERIAL   2
#define AA4_RND_UBO_BIND_PRIM       3
#define AA4_RND_UBO_BIND_LIGHT      4
#define AA4_RND_UBO_BIND_FIRST_FREE 5

/***
 * Target support
 ***/

/* Number of color attachments */
#define AA4_RND_NUM_OF_TARGETS 6

/* Array of color attachment textures */
extern INT AA4_RndTargetTexNo[AA4_RND_NUM_OF_TARGETS];

/***
 * Light support
 ***/
 
/* Light sources types */
typedef enum tagaa4LIGHT_TYPE
{
  AA4_LIGHT_AMBIENT = 0, /* Ambient light source */
  AA4_LIGHT_POINT = 1,   /* Point light source */
  AA4_LIGHT_DIR = 2,     /* Directional light source */
  AA4_LIGHT_SPOT = 3,    /* Spot light source */
} aa4LIGHT_TYPE;
 
/* Light source representation type */
typedef struct tagaa4LIGHT
{
  aa4LIGHT_TYPE Type; /* Light source type */
  VEC
    Pos,              /* Point and spot light source position */
    Dir,              /* Directional and spot light source direction */
    Color,            /* Light source color */
    Att;              /* Attenuation by distance coefficients: CC CL CQ */
  VEC2 CutOffAngle;   /* Start and end cut-off angles cosines for spot light sources */
  VEC2 CutOffDist;    /* Start/end distance for point and spot light sources */
  INT UBONo;          /* Light UBO data */
} aa4LIGHT;
 
/* Light sources array and fill size */
#define AA4_RND_MAX_LIGHTS 10000
extern aa4LIGHT AA4_RndLights[AA4_RND_MAX_LIGHTS];
extern INT AA4_RndLightsSize;

/* Windows Depended */
extern HGLRC AA4_hRndGLRC;
extern HWND AA4_hRndWnd;        /* Work window handle */
extern HDC AA4_hRndDC;     /* Work window memory device context */
extern INT AA4_RndFrameW, AA4_RndFrameH; /* Work window size */

extern FLT
  AA4_RndProjSize,     /* Project plane fit square */
  AA4_RndProjDist,     /* Distance to project plane from viewer (near) */
  AA4_RndProjFarClip;  /* Distance to project far clip plane (far) */

extern MATR
  AA4_RndMatrView, /* View coordinate system matrix */
  AA4_RndMatrProj, /* Projection coordinate system matrix */
  AA4_RndMatrVP;   /* Stored (View * Proj) matrix */

extern VEC
  AA4_RndCamLoc,   /* Camera location */
  AA4_RndCamUp,    /* Camera direction */
  AA4_RndCamAt,    /* Camera position */
  AA4_RndCamDir,   /* Camera direction */
  AA4_RndCamRight; /* Camera position */

extern UINT
  AA4_RndShdUBOCameraNo, /* UBO reference for camera UBO buffer */
  AA4_RndShdUBOPrimNo,   /* UBO reference for primitive UBO buffer */
  AA4_RndShdUBOMtlNo,    /* UBO reference for material UBO buffer */
  AA4_RndShdUBOSyncNo;   /* UBO reference for sync data UBO buffer */

extern aa4RND_UBO_CAMERA AA4_UboCam;
extern aa4RND_UBO_PRIM AA4_UboPrim;
extern aa4RND_UBO_SYNC AA4_UboSync;
extern aa4RND_UBO_MTL AA4_UboMtl;
extern aa4RND_UBO_LIGHT AA4_UboLig;

/* Shader addon parametrs */
extern INT AA4_RndShdAddonI[4];
extern FLT AA4_RndShdAddonF[4];
extern VEC4 AA4_RndShdAddonV[4];

/***
 * Render handle functions
 ***/

/* Start of render function.
 * ARGUMENTS:
 *       None.
 * RETURNS:
 *   None.
 */
VOID AA4_RndStart( VOID );
/* End of render function.
 * ARGUMENTS:
 *       None.
 * RETURNS:
 *   None.
 */
VOID AA4_RndEnd( VOID );
/* Resize function.
 * ARGUMENTS:
 *   - Window size:
 *       INT W, INT H;
 * RETURNS:
 *   None.
 */
VOID AA4_RndResize( INT W, INT H );
/* Resize function.
 * ARGUMENTS:
 *   - Window size:
 *       INT W, INT H;
 * RETURNS:
 *   None.
 */
VOID AA4_RndCopyFrame( VOID );
/* Init render function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
VOID AA4_RndInit( HWND hWnd );
/* Close render function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_RndClose( VOID );
/* Debug output function.
 * ARGUMENTS:
 *   - source APi or device:
 *       UINT Source;
 *   - error type:
 *       UINT Type;
 *   - error message id:
 *       UINT Id, 
 *   - message severity:
 *       UINT severity, 
 *   - message text length:
 *       INT Length, 
 *   - message text:
 *       CHAR *Message, 
 *   - user addon parameters pointer:
 *       VOID *UserParam;
 * RETURNS: None.
 */
VOID APIENTRY glDebugOutput( UINT Source, UINT Type, UINT Id, UINT Severity,
                             INT Length, const CHAR *Message,
                             const VOID *UserParam );

/***
 * Timer handle functions
 ***/

/* Init timer function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_TimerInit( VOID );
/* Response timer function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_TimerResponse( VOID );

/***
 * Prim handle functions
 ***/

/* Draw primitive function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       aa4PRIM *Pr;
 *   - world matrix:
 *       MATR World;
 * RETURNS:
 *   (VOID) Nothing.
 */
VOID AA4_RndPrimDraw( aa4PRIM *Pr, MATR World );
/* Free primitive struct function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       aa4PRIM *Pr;
 * RETURNS:
 *   (VOID) Nothing.
 */
VOID AA4_RndPrimFree( aa4PRIM *Pr );
/* Create primitive function.
 * ARGUMENTS:
 *   - pointer to primitive to create:
 *       aa4PRIM *Pr;
 *   - primitive type:
 *       aa4PRIM_TYPE Type;
 *   - vertex attributes array:
 *       aa4VERTEX *V;
 *   - vertex attributes array size:
 *       INT NoofV;
 *   - primitive vertex index array:
 *       INT *Ind;
 *   - primitive vertex index array size:
 *       INT NoofI;
 * RETURNS: None.
 */
BOOL AA4_RndPrimCreate( aa4PRIM *Pr, aa4PRIM_TYPE PrimType, aa4VERTEX *V, INT NoofV, INT* Ind, INT NoofI );
/* Load primitive from '*.OBJ' file function.
 * ARGUMENTS:
 *   - pointer to primitive to load:
 *       aa4PRIM *Pr;
 *   - '*.OBJ' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL AA4_RndPrimLoad( aa4PRIM *Pr, CHAR *FileName );
/* Primitive vertex normals evaluate function.
 * ARGUMENTS:
 *   - vertex attributes array:
 *       aa4VERTEX *V;
 *   - vertex attributes array size:
 *       INT NoofV;
 *   - primitive vertex index array:
 *       INT *Ind;
 *   - primitive vertex index array size:
 *       INT NoofI;
 * RETURNS: None.
 */
VOID AA4_RndPrimAutoNormals( aa4VERTEX *V, INT NoofV, INT *Ind, INT NoofI );

/***
 * Camera handle functions
 ***/

/* Set camera function.
 * ARGUMENTS:
 *   - View arguments:
 *       VEC Loc, VEC At, VEC Up;
 * RETURNS:
 *   None.
 */
VOID AA4_RndCamSet( VEC Loc, VEC At, VEC Up );

/***    
 * Prims handle functions
 ***/

/* Create array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       aa4PRIMS *Prs;
 *   - number of primitives to be add:
 *       INT NumOfPrims;
 * RETURNS:
 *   (BOOL) TRUE if successful, FALSE otherwise.
 */
BOOL AA4_RndPrimsCreate( aa4PRIMS *Prs, INT NumOfPrims );
/* Delete array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       aa4PRIMS *Prs;
 * RETURNS: None.
 */
VOID AA4_RndPrimsFree( aa4PRIMS *Prs );
/* Draw array of primitives function.
 * ARGUMENTS:
 *   - pointer to primitives structure:
 *       aa4PRIMS *Prs;
 *   - global transformation matrix:
 *       MATR World;
 * RETURNS: None.
 */
VOID AA4_RndPrimsDraw( aa4PRIMS *Prs, MATR World );
/* Load primitives from '*.G3DM' file function.
 * ARGUMENTS:
 *   - pointer to primitives to create:
 *       aa4PRIMS *Pr;
 *   - '*.G3DM' file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL AA4_RndPrimsLoad( aa4PRIMS *Pr, CHAR *FileName );

/***
 * Font handle functions
 ***/

/* Init font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndFntInit( VOID );
/* Deinit font subsystem function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndFntClose( VOID );
/* Load font from .G3DF file function.
 * ARGUMENTS:
 *   - font file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
BOOL AA4_RndFntLoad( CHAR *FileName );
/* Draw string function.
 * ARGUMENTS:
 *   - string to draw:
 *       CHAR *Str;
 *   - draw position:
 *       VEC Pos;
 *   - font size:
 *      FLT Size;
 * RETURNS: None.
 */
VOID AA4_RndFntDraw( CHAR *Str, VEC Pos, FLT Size );

/***
 * Grid handle functions
 ***/

/* Free grid function.
 * ARGUMENTS:
 *   - grid:
 *       aa4GRID *G;
 * RETURNS: None.
 */
VOID AA4_RndGridFree( aa4GRID *G );
/* Create grid function.
 * ARGUMENTS:
 *   - grid:
 *       aa4GRID *G;
 *   - grid size:
 *       INT W, INT H;
 * RETURNS: None.
 */
VOID AA4_RndGridCreate( aa4GRID *G, INT W, INT H );
/* Eval auto normals in grid function.
 * ARGUMENTS:
 *   - grid:
 *       aa4GRID *G;
 * RETURNS: None.
 */
VOID AA4_RndGridAutoNormals( aa4GRID *G );
/* Make primitive from grid function.
 * ARGUMENTS:
 *   - primitive:
 *       aa4PRIM *Pr;
 *   - grid:
 *       aa4GRID *G;
 * RETURNS: None.
 */
VOID AA4_RndPrimFromGrid( aa4PRIM *Pr, aa4GRID *G );
/* Marker system initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */

/***    
 * Marker handle functions
 ***/

VOID AA4_RndMarkerInit( VOID );
/* Marker system deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndMarkerClose( VOID );
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
VOID AA4_RndMrkDrawCylinder( VEC P0, FLT R0, VEC P1, FLT R1, VEC Color, MATR Transform );
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
VOID AA4_RndMrkDrawSphere( VEC C, VEC R, VEC Color, MATR Transform );
/* Render target initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */

/***
 * Target handle functions
 ***/

VOID AA4_RndTargetInit( VOID );
/* Render target deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndTargetClose( VOID );
/* Render target resize function.
 * ARGUMENTS:
 *   - new render target size (in pixels):
 *       INT W, H;
 * RETURNS: None.
 */
VOID AA4_RndTargetResize( INT W, INT H );
/* Start render target usage function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndTargetStart( VOID );
/* Finalize render target output function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndTargetEnd( VOID );

/***
 * Light handle functions
 ***/

/* Light sources initialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndLightsInit( VOID );
 
/* Light sources deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndLightsClose( VOID );
 
/* Add point light source function.
 * ARGUMENTS:
 *   - point light source position:
 *       VEC Pos;
 * RETURNS:
 *   (aa4LIGHT *) pointer to add light source or NULL if no space for a new ligth source.
 */
aa4LIGHT * AA4_RndLightAddPoint( VEC Pos );
 
/* Add directional light source function.
 * ARGUMENTS:
 *   - directional light source direction:
 *       VEC Dir;
 * RETURNS:
 *   (aa4LIGHT *) pointer to add light source or NULL if no space for a new ligth source.
 */
aa4LIGHT * AA4_RndLightAddDir( VEC Dir );
 
/* Add spot light source function.
 * ARGUMENTS:
 *   - spot light source position:
 *       VEC Pos;
 *   - spot light source look-at point:
 *       VEC At;
 * RETURNS:
 *   (aa4LIGHT *) pointer to add light source or NULL if no space for a new ligth source.
 */
aa4LIGHT * AA4_RndLightAddSpot( VEC Pos, VEC At );
 
/* Redraw all light sources function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndLightRedraw( VOID );
/* Update light source data on GPU function.
 * ARGUMENTS:
 *   - light source pointer:
 *       aa4LIGHT *Lig;
 * RETURNS: None.
 */
VOID AA4_RndUBOLightUpdate( aa4LIGHT *Lig );

#endif /* __rnd_h_ */

/* END OF 'rnd.h' FILE */
