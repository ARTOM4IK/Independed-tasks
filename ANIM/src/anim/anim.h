/* PROGRAMMER: AA4
 * LAST UPDATE: 22.01.2025
 * PURPOSE: 3D animation project.
 *          Animation declaration module.
 */

#ifndef __anim_h_
#define __anim_h_

#include "rnd/rnd.h"

#define AA4_MAX_UNITS 3000
#define AA4_MAX_PRIMS 3000

#define UNIT_BASE_FIELDS \
  VOID (*Init)( aa4UNIT *Uni, aa4ANIM *Ani );      \
  VOID (*Close)( aa4UNIT *Uni, aa4ANIM *Ani );     \
  VOID (*Response)( aa4UNIT *Uni, aa4ANIM *Ani );  \
  VOID (*Render)( aa4UNIT *Uni, aa4ANIM *Ani )

typedef struct tagaa4UNIT aa4UNIT;
typedef struct tagaa4ANIM
{
  HWND hWnd;                      /* Window */
  HDC hDC;                        /* Context from memory (tirim from AA4_hRndDCFrame) */
  INT W, H;                       /* Window size */
  aa4UNIT *Units[AA4_MAX_UNITS];  /* Animation units array */
  INT NumOfUnits;                 /* Units amount */
  DBL
    GlobalTime, GlobalDeltaTime,  /* Global time and interframe interval */
    Time, DeltaTime,              /* Time with pause and interframe interval */
    AngleSpeed,                   /* Speed by angle */
    FPS,
    Mdz, Mdx, Mdy;                /* Frames per second value */
  BOOL
    IsPause;
  VEC
    CamLoc, CamDir, CamPos;       /* Camera parametrs */
  BYTE Keys[256], KeysClick[256]; /* Keyboard clicks */
} aa4ANIM;

struct tagaa4UNIT
{
  UNIT_BASE_FIELDS;
};

extern aa4ANIM AA4_Anim;
extern DBL AA4_MouseWheel;

/* Init animation function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimInit( HWND hWnd );
/* Close animation function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_AnimClose( VOID );
/* Add unit to animation function.
 * ARGUMENTS:
 *   - Unit:
 *       aa4UNIT *Uni;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimUnitAdd( aa4UNIT *Uni );
/* Copy animation frame function.
 * ARGUMENTS:
 *   - DC handle:
 *       HDC hDC;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimCopyFrame( VOID );
/* Animation render function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimRender( VOID );
/* Animation response function.
 * ARGUMENTS:
 *   None;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimResponse( VOID );
/* Reszie animation function.
 * ARGUMENTS:
 *   - Window size:
 *       INT W, INT H;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimResize( INT W, INT H );
/* Flip full screen function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimFlipFullScreen( VOID );
/* Init animation input function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_AnimInputInit( VOID );
/* Response animation input function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_AnimInputResponse( VOID );
/* Exit animation function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_AnimDoExit( VOID );

#endif /* __anim_h_ */
 
/* END OF 'anim.h' FILE */
