/* FILE NAME: units.h
 * PROGRAMMER: AA4
 * DATE: 18.01.2024
 * PURPOSE: 3D animation project.
 *          Unit common declaration module.
 */

#ifndef __units_h_
#define __units_h_

#include "anim/anim.h"
#include "anim/rnd/rnd.h"

/****
 * Unit handle
 ***/

typedef struct aa4tagUNIT_CONTROL aa4UNIT_CONTROL;
struct aa4tagUNIT_CONTROL
{
  UNIT_BASE_FIELDS;
  VEC
    CamLoc, CamDir, CamPos;    /* Camera parametrs */
  DBL
    Speed, AngleSpeed;       /* Speed */
};

typedef struct aa4tagUNIT_COW aa4UNIT_COW;
struct aa4tagUNIT_COW
{
  UNIT_BASE_FIELDS;
  aa4PRIM Cow;                    /* Primitive */
  VEC Pos;                        /* Posotion */
};

typedef struct aa4tagUNIT_PRIMS aa4UNIT_PRIMS;
struct aa4tagUNIT_PRIMS
{
  UNIT_BASE_FIELDS;
  aa4PRIMS Prims[AA4_MAX_PRIMS];  /* Primitives */
  MATR Mat;                       /* Movement matrix */
  MATR MatrTotal;                 /* Total Movement matrix */
  VEC Pos;                        /* Position */
};

typedef struct aa4tagUNIT_SKY aa4UNIT_SKY;
struct aa4tagUNIT_SKY
{
  UNIT_BASE_FIELDS;
  aa4PRIM Pr;        /* Primitive */
  VEC Pos;           /* Postition */
};

typedef struct aa4tagUNIT_GRID aa4UNIT_GRID;
struct aa4tagUNIT_GRID
{
  UNIT_BASE_FIELDS;
  aa4PRIM Land;        /* Primitive */
};

typedef struct aa4tagUNIT_TESS aa4UNIT_TESS;
struct aa4tagUNIT_TESS
{
  UNIT_BASE_FIELDS;
  aa4PRIM Pr;
};

#define TAB_BITS 8
#define TAB_SIZE 8
#define TAB_MASK 8
#define AA4_GRID_SIZE 100

typedef struct aa4tagUNIT_NOISE aa4UNIT_NOISE;
struct aa4tagUNIT_NOISE
{
  UNIT_BASE_FIELDS;
  aa4PRIM Pr;
  aa4GRID G;
  INT Oct;
  aa4LIGHT *Sun;
};

/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (aa4UNIT *) pointer to created unit.
 */
aa4UNIT * AA4_AnimUnitCreate( INT Size );
/* Primitive creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (aa4UNIT *) pointer to created unit.
 */
aa4UNIT * AA4_UnitCowCreate( VOID );
/* Camera creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (aa4UNIT *) pointer to created unit.
 */
aa4UNIT * AA4_UnitCamCreate( VOID );
/* Primitives creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (aa4UNIT *) pointer to created unit.
 */
aa4UNIT * AA4_UnitPrimsCreate( VOID );
/* Sky creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (aa4UNIT *) pointer to created unit.
 */
aa4UNIT * AA4_AnimSkyCreate( VOID );
/* Grid creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (aa4UNIT *) pointer to created unit.
 */
aa4UNIT * AA4_AnimGridCreate( VOID );
/* Unit creation function.
 * ARGUMENTS:
 *   - unit structure size in bytes:
 *       INT Size;
 * RETURNS:
 *   (aa4UNIT *) pointer to created unit.
 */
aa4UNIT * AA4_AnimTessCreate( VOID );

#endif /* __units_h_ */
 
/* END OF 'units.h' FILE */
