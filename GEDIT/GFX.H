/* Arsentev Artemy, 09-4, 20.12.2024 */

#ifndef __GFX_H_
#define __GFX_H_

#include <commondf.h>

typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef double DBL;

extern INT GFX_W, GFX_H;
extern DBL GFX_FrameZoom;

char nam[10];

DWORD GFX_RGB( INT r, INT g, INT b );
VOID GFX_PutPixel( INT x, INT y, DWORD color );
VOID GFX_DrawFrame( VOID );
VOID GFX_Clear( DWORD color );
DWORD GFX_GetPixel( INT X, INT Y);

VOID GFX_Init( VOID );
VOID GFX_Close( VOID );
VOID GFX_ResizeFrame( INT W, INT H );
VOID GFX_ResizeFrameZoom( INT WinW, INT WinH, DBL Z );

VOID GFX_HorizontalPutLine( INT x1, INT x2, INT y, DWORD color );
VOID GFX_PutLine( INT x1, INT y1, INT x2, INT y2, DWORD color );
VOID GFX_PutCircle( INT x, INT y, INT R, DWORD color );
VOID TetaRose( INT x, INT y, INT a, INT b, DWORD color );
VOID Vroongel( INT x, INT y, INT b, INT a, INT c, INT d, INT e, DWORD color );

VOID GFX_FloodFill( INT X, INT y, DWORD Color );
VOID vrngl( INT x, INT y, INT a, INT b, DWORD color );

#endif /* __GFX_H_ */

/* END OF 'GFX.H' FILE */