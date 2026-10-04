/* Arsentev Artemy, 09-4, 29.10.2024 */

#include <stdio.h>
#include <stdlib.h>

#include <glut.h>
#include "GFX.H"
#include "PCX.H"

#define FRAME_H 1080 / 2
#define FRAME_W 1920 / 2


void Display( void )
{
  glClear(GL_COLOR_BUFFER_BIT);

  GFX_DrawFrame();

  DrawPCX("LOGO30.pcx", 0, 0);
  DrawPCX("o.pcx", 0, 0);
  DrawPCX("TR.pcx", 900, 0);
  DrawPCX("A2.pcx", 850, 300);
  DrawPCX("m.pcx", 600, 650);

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


  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutMainLoop();
  glClearColor(0.30, 0.47, 0.8, 1);
}