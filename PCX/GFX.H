/* Arsentev Artemy, 09-4, 29.10.2024 */

#define GFX_W 1920 / ZOOM
#define GFX_H 1080 / ZOOM

#define ZOOM 1
#define FONT_H 8

typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;

DWORD GFX_RGB( int r, int g, int b );
void GFX_PutPixel( int x, int y, DWORD color );
void GFX_DrawFrame( void );
void GFX_Clear( DWORD color );
void GFX_LoadFont( void );
void GFX_DrawFontText( int x, int y, char *str, DWORD color );
void GFX_DrawChar( int x, int y, char str, DWORD color );