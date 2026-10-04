/* Arsentev Artemy, 09-4, 20.12.2024 */

#ifndef __GFXLL_H_
#define __GFXLL_H_

#define DEFINED_SIZE 3000

/* Frame buffer (GFX) */
static DWORD *GFX_Frame;

typedef struct taggfxLIST gfxLIST;
struct taggfxLIST
{
  INT Lx[DEFINED_SIZE], Rx[DEFINED_SIZE], y[DEFINED_SIZE];
  gfxLIST *Next;
} *GFX_StoreData;

#endif /* __GFXLL_H_ */

/* END OF 'GFXLL.H' FILE */