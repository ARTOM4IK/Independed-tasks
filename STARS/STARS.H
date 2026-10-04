/* Arsentev Artemy, 09-4, 31.10.2024 */

#include "GFX.H"

#define INFINITY 100000.0
#define MAX 10000

extern int DeltaTime1;

typedef struct tagVEC
{
  DBL X, Y, Z;
} VEC;

/* Image representation type */
typedef struct
{
  int W, H;      /* Image size */
  DWORD *Pixels; /* Image pixel colors */
} IMG;

extern DBL Speed; 

void StarsInit( void );
void StarsMove( DBL DeltaTime );
void StarsDraw( void );
void ProjSet( DBL WS, DBL HS );       