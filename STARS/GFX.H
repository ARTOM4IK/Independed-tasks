/* Arsentev Artemy, 09-4, 31.10.2024 */

#define FONT_H 8

extern int GFX_W, GFX_H;
extern double GFX_FrameZoom;

char nam[10];

typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;
typedef double DBL;

DWORD GFX_RGB( int r, int g, int b );
void GFX_PutPixel( int x, int y, DWORD color );
void GFX_DrawFrame( void );
void GFX_Clear( DWORD color );
void GFX_LoadFont( void );
void GFX_DrawFontText( int x, int y, char *str, DWORD color );
void GFX_DrawChar( int x, int y, char str, DWORD color );

void GFX_Init( void );
void GFX_Close( void );
void GFX_ResizeFrame( int W, int H );
void GFX_ResizeFrameZoom( int WinW, int WinH, double Z );
void GFX_PutPixelA( int x, int y, DWORD color );
