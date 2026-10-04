/* Arsentev Artemy, 09-4, 16.10.2024 */

#include <stdio.h>
#include <stdlib.h>

#include <glut.h>
#include "GFX.H"
#include "ARC.H"

#define FRAME_H 1080 / 2
#define FRAME_W 1920 / 2


void Display( void )
{
  glClear(GL_COLOR_BUFFER_BIT);

  GFX_DrawFrame();

  if (StartGameFlag == 0)
  {
    GFX_DrawFontText(125, 50, "PRESS S TO START", INTERFACE_COLOR);
  }

  else if (StartGameFlag == 1)
  {
    Game_Step();
  }


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
  else if (key == 's')
  {
    StartGameFlag = 1;
    GFX_Clear(BACK_COLOR);
    Game_Init();
  }
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