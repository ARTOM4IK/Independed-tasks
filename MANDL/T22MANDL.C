/* Arsentev Artemy, 09-4, 30.10.2024 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include <glut.h>
#include "GFX.H"
#include "CMPL.H"

#define FRAME_H 1080 / 2
#define FRAME_W 1920 / 2

void Display( void )
{
  glClear(GL_COLOR_BUFFER_BIT);

  GFX_DrawFrame();

  Timer();
  

  frac();
  
  GFX_DrawFontText(0, 0, nam, GFX_RGB(0, 255, 0));

  /* finish */
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

void Keyboard( unsigned char key, int x, int y )
{
  if (key == 27)
    exit(0);
  else if (key == 'f')
    glutFullScreen();
}

void main( int argc, char *argv[] )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(FRAME_W, FRAME_H);
  glutCreateWindow("CGSG solo");

  
  GFX_LoadFont();

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutMainLoop();
  glClearColor(0.30, 0.47, 0.8, 1);
}