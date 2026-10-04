/* Arsentev Artemy, 09-4, 11.11.2024 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include <windows.h>

#include <glut.h>
#include <commondf.h>

#include "GFX.H"
#include "LAB.H"

static INT IsPause = 0;
static DBL camX = 0, camY = 0;

void Timer( void )
{
  long t;
  static long StartTime = -1, OldTime, PauseTime = 0, FPSTime, FrameCount;

  t = clock();
  if (StartTime == -1)
    StartTime = OldTime = FPSTime = t;

  if (IsPause)
  {
    DeltaTime = 0;
    PauseTime += t - OldTime;
  }
  else
    DeltaTime = (t - OldTime) / (double)CLOCKS_PER_SEC;
  SyncTime = (t  - PauseTime - StartTime) / (double)CLOCKS_PER_SEC;

  FrameCount++;
  if (t - FPSTime > 3 * CLOCKS_PER_SEC)
  {
    FPS = FrameCount / ((t - FPSTime) / (double)CLOCKS_PER_SEC);
    FPSTime = t;
    FrameCount = 0;
    sprintf(nam, "%.3lf FPS", FPS);
  }
  OldTime = t;
}

static VOID Reshape( INT NewW, INT NewH )
{
  DBL size = 1, wp = size, hp = size;

  if (NewW > NewH)
    wp *= (DBL)NewW / NewH;
  else
    hp *= (DBL)NewH / NewW;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glFrustum(-wp / 2, wp / 2, -hp / 2, hp / 2, size, 300);
  glMatrixMode(GL_MODELVIEW);

  /*
  WinW = NewW;
  WinH = NewH;
  FrameSetSize(WinW / FrameZoom, WinH / FrameZoom);
  memset(Frame, 0, (FrameW * FrameH * 4));
  */

  glViewport(0, 0, NewW, NewH);
}

VOID Display( VOID )
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  Timer();

  glPushMatrix();
 
  /* Sample of 3D view */
  glLoadIdentity();

  if (camX < Ava.X)
    camX += 0.02;
  else if (camX > Ava.X)
    camX -= 0.02;

  if (camY < Ava.Y)
    camY += 0.02;
  else if (camY > Ava.Y)
    camY -= 0.02;

  gluLookAt(camX, 5, camX + 6.3, camX, 0, camY, 0, 1, 0);

  /* start 2d alg */
  LAB_Step();
  /* end 2d alg */

  glPopMatrix();

  /* Draw raster */
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  GFX_DrawFrame();

  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);

  /* Finalize */
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

VOID Keyboard( UCHAR Key, INT X, INT Y )
{
  if (Key == 27)
    exit(30);
  if (Key == 'p')
    IsPause = !IsPause;
  if (Key == 'f')
    glutFullScreen();
  if (Key == ' ')
    LAB_Keyboard(5);
} /* End of 'Keyboard' function */

VOID SpecialKeyboard( INT Key, INT X, INT Y )
{
  switch (Key)
  {
  case GLUT_KEY_LEFT:
    LAB_Keyboard(1);
    break;
  case GLUT_KEY_RIGHT:
    LAB_Keyboard(2);
    break;
  case GLUT_KEY_UP:
    LAB_Keyboard(3);
    break;
  case GLUT_KEY_DOWN:
    LAB_Keyboard(4);
    break;
    /*
    eyez;
    centerx;
    centery;
    centerz;
    */
  }
} /* End of 'SpecialKeyboard' function */

VOID main( INT ArgC, CHAR *ArgV[] )
{
  /* OpenGL + GLUT initialization */
  glutInit(&ArgC, ArgV);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
 
  /* Create window */
  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1300, 900);
  glutCreateWindow("CGSG solo");
 
  /* Setup callbacks */
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutSpecialFunc(SpecialKeyboard);
  glutReshapeFunc(Reshape);
 
  /* OpenGL default initial parameters */
  glClearColor(0.30, 0.47, 0.8, 1);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GFX_Init();
  LAB_Init("lab3d.txt");

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);

  /* Goto main loop */
  glutMainLoop();
}