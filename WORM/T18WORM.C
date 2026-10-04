/* Arsentev Artemy, 09-4, 21.10.2024 */

#include <stdio.h>
#include <stdlib.h>

#include <glut.h>
#include "GFX.H"
#include "WORM.H"

#define FRAME_H 1080 / 2
#define FRAME_W 1920 / 2

static int StartGameFlag = 0;

void Display( void )
{
  glClear(GL_COLOR_BUFFER_BIT);
  
  glClearColor(0.30, 0.47, 0.8, 1);

  GFX_DrawFrame();

  if (StartGameFlag == 0)
  {
    GFX_DrawFontText(125, 50, "PRESS SPACE TO START", WRM_COLOR_GOOD);
  }

  else if (StartGameFlag == 1)
  {
    WRM_Step();
  }



  /* finish */
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

void SpecialKeyboard( int Key, int x, int y )
{
  if (Key == GLUT_KEY_LEFT)
    WRM_Kbd(Key);
}

void Keyboard( unsigned char key, int x, int y )
{
  if (key == 27)
    exit(0);
  else if (key == 'f')
    glutFullScreen();
  else if (key == ' ')
  {
    StartGameFlag = 1;
    GFX_Clear(WRM_COLOR_BACK);
    WRM_Init();
  }
  WRM_Kbd(key);
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
  glutSpecialFunc(SpecialKeyboard);
  glutMainLoop();
}