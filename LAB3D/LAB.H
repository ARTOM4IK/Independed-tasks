/* Arsentev Artemy, 09-4, 11.11.2024 */

#include "GFX.H"

#define MAX 100
#define MAX_ENEMIES 30
#define INFINITY 10000

#define LAB_SPOT_SPACE 0
#define LAB_SPOT_WALL 1
#define LAB_SPOT_AVA 2
#define LAB_SPOT_ENEMY 3

#define LAB_COLOR_BACK GFX_RGBA(0, 0, 0, 0)
#define LAB_COLOR_WALL GFX_RGBA(255, 255, 255, 255)
#define LAB_COLOR_AVA GFX_RGBA(0, 255, 0, 255)
#define LAB_COLOR_ENEMY GFX_RGBA(255, 0, 0, 255)

#define LAB_SPOT_SIZE 1

#define LAB_X 0
#define LAB_Y 0

typedef struct tagVEC
{
  INT X, Y;
} VEC2;

typedef struct tagENEMY
{
  INT X, Y;
  DBL DeltaTime;
} ENEMY;

BYTE Lab[MAX][MAX];
VEC2 Ava;

INT Solution[MAX][MAX];

static DBL SyncTime, DeltaTime, FPS;

ENEMY Enemies[MAX_ENEMIES];
INT NumOfEnemies;


VOID LAB_Keyboard( int Key );
VOID LAB_Init( CHAR *FileName );
VOID LAB_Step( VOID );
VOID LookAt( VOID );