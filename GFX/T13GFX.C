/* Arsentev Artemy, 09-4, 02.10.2024 */

#include <stdio.h>
#include <stdlib.h>

#include <glut.h>

#define FRAME_H 1080 / 2
#define FRAME_W 1920 / 2
#define ZOOM 3
#define FONT_H 8

unsigned char Frame[FRAME_H][FRAME_W][ZOOM];
unsigned char Font[256][FONT_H];

int k = 1;


void LoadFont( void )
{
  int i, j;

  FILE *F;
  F = fopen("SoftFont.fnt", "rb");

  if (F != NULL)
    for (i = 0; i < 256; i++)
      for (j = 0; j < FONT_H; j++)
        Font[i][j] = fgetc(F);

  fclose(F);
}

void PutPixel( int x, int y, int R, int G, int B )
{
  if (x < 0 || x >= FRAME_W || y < 0 || y >= FRAME_H)
    return;

  Frame[y][x][0] = B;
  Frame[y][x][1] = G;
  Frame[y][x][2] = R;
}

void Mouse( int x, int y )
{
  PutPixel(x, y, 0, 100, 0);
}

void DrawLetter( int x0, int y0, int *a, int *b, int *c )
{
  int A[8] = {60, 70, 134, 134, 254, 134, 134, 0}, chetire[8] = {6, 14, 22, 38, 70, 255, 6, 6}, i, j, fg, fg1, fg2, C[8] = {54, 66, 64, 64, 64, 64, 66, 52}, G[8] = {54, 66, 64, 64, 64, 71, 66, 52}, S[8] = {54, 66, 32, 16, 8, 4, 66, 54};

  fg = rand() & 255;
  fg1 = rand() & 255;
  fg2 = rand() & 255;

  for (i = 0; i < FONT_H; i++)
    for (j = 0; j < FONT_H; j++)
    {/*
      if ((A[i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j, y0 + i, fg, fg1, fg2);

      if ((A[i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j + 8, y0 + i, fg, fg1, fg2);

      if ((chetire[i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j + 16, y0 + i, fg, fg1, fg2);
      */
      /*if ((C[i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j, y0 + i, fg, fg1, fg2);

      if ((G[i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j + 8, y0 + i, fg, fg1, fg2);

      if ((S[i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j + 16, y0 + i, fg, fg1, fg2);

      if ((G[i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j + 24, y0 + i, fg, fg1, fg2);*/

      if ((a[i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j, y0 + i, fg, fg1, fg2);
      if ((b[i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j + 8, y0 + i, fg, fg1, fg2);
      if ((c[i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j + 16, y0 + i, fg, fg1, fg2);
    }
}

void DrawLetter2( int x0, int y0 )
{
  int i, j, fg, fg1, fg2;

  fg = rand() & 255;
  fg1 = rand() & 255;
  fg2 = rand() & 255;

  for (i = 0; i < FONT_H; i++)
    for (j = 0; j < FONT_H; j++)
    {
      if((Font['A'][i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j, y0 + i, fg, fg1, fg2);
      if((Font['A'][i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j + 8, y0 + i, fg, fg1, fg2);
      if((Font['4'][i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j + 16, y0 + i, fg, fg1, fg2);
    }

}

void DrawLetter3( int x0, int y0, char *stri, int r, int g, int b )
{
  int i, j;


  for (i = 0; i < FONT_H; i++)
    for (j = 0; j < FONT_H; j++)
    {
      if((Font[*stri][i] & (0x80 >> j)) != 0)
        PutPixel(x0 + j, y0 + i, r, g, b);
    }

}

void DrawFontText( char *str )
{
  int i = 0, j =0, fr_w = rand() % FRAME_W, fr_h = rand() % FRAME_H,
    fg = rand() & 255, fg2 = rand() & 255, fg3 = rand() & 255;

  while (*str != 0)
  {
    if (*str == '\n')
      i = 0, j += 8;
    else
    {
      DrawLetter3(fr_w + i * 8, fr_h + j, str, fg, fg2, fg3);
      i++;
    }
    *str++;
  }

}

void Display( void )
{
  glClear(GL_COLOR_BUFFER_BIT);

  /* draw */
  glRasterPos2d(-1, 1);
  glPixelZoom(ZOOM, -ZOOM);

  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);
  if (k == 1)
    DrawFontText("AA4\nLOVES CGSG");
  //DrawLetter2(rand() % FRAME_W, rand() % FRAME_H);

  /* PutPixel(rand() % FRAME_W, rand() % FRAME_H, rand() % 256, rand() % 256, rand() % 256); <-- random pixels */

  /* finish */
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

void Keyboard( unsigned char key, int x, int y )
{
  int x1, y1;
  if (key == 27)
    exit(0);
  else if (key == 'f')
    glutFullScreen();
  else if (key == 'p' && k == 1)
    k = 0;
  else if (key == 'p' && k == 0)
    k = 1;
  else if (key == ' ')
    for (x1 = 0; x1 < FRAME_W; x1++)
      for (y1 = 0; y1 < FRAME_H; y1++)
        PutPixel(x1, y1, 0, 0, 0);
  /* mouse click 
  else if (key == 1)
    Mouse(x, y);  */
}

void main( int argc, char *argv[] )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(FRAME_W, FRAME_H);
  glutCreateWindow("CGSG solo");

  LoadFont();

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutMouseFunc(Mouse);
  glutMainLoop();
  glClearColor(0.30, 0.47, 0.8, 1);
}