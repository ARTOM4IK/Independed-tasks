/* Arsentev Artemy, 09-4, 31.10.2024 */
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include <glut.h>

#include "GFX.H"
#include "STARS.H"

static double SyncTime, DeltaTime, FPS;
static int IsPause = 0;


int GFX_WinW, GFX_WinH;

/* Create new image function */

int ImgCreate( IMG *Pic, int W, int H )
{
  Pic->W = Pic->H = 0;
  if ((Pic->Pixels = malloc(sizeof(DWORD) * W * H)) == NULL)
    return 0;
  Pic->W = W;
  Pic->H = H;
  return 1;
} /* End of 'ImgCreate' function */


/* Create new image function */
void ImgFree( IMG *Pic )
{
  free(Pic->Pixels);
  Pic->W = Pic->H = 0;
  Pic->Pixels = NULL;
} /* End of 'ImgFree' function */

/* Create new image function */

void ImgDraw( IMG *Pic, int X0, int Y0 )
{
  int x, y;

  for (y = 0; y < Pic->H; y++)
    for (x = 0; x < Pic->W; x++)
      GFX_PutPixelA(X0 + x, Y0 + y, Pic->Pixels[Pic->W * y + x]);
} /* End of 'ImgDraw' function */


/* Create new image function */
void ImgStamp( IMG *Pic )
{
  glRasterPos2d(-1, 1);
  glPixelZoom(1, -1);
  glDrawPixels(Pic->W, Pic->H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Pic->Pixels);
} /* End of 'ImgDraw' function */

int ImgLoad( IMG *Pic, char *FileName )
{
  FILE *F;
  int W = 0, H = 0;

  if ((F = fopen(FileName, "rb")) == NULL)
    return 0;
  fread(&W, 2, 1, F);
  fread(&H, 2, 1, F);
  if (ImgCreate(Pic, W, H))
    fread(Pic->Pixels, 4, W * H, F);
  fclose(F);
  return 1;
}

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

IMG Pic;

void Display( void )
{
  glClear(GL_COLOR_BUFFER_BIT);




  Timer();
  

  if ((GetKeyState(VK_CAPITAL) & 0x0001) != 1)
    GFX_Clear(GFX_RGBA(0, 0, 0, 255));
  
  GFX_DrawFontText(0, 0, nam, GFX_RGB(0, 255, 0));
  GFX_DrawFontText(430, 270, "JEDAYSKIY CGSG", GFX_RGB(0, 0, 255));
  
  DeltaTime1 = DeltaTime;
  StarsMove(DeltaTime);
  StarsDraw();

  ImgDraw(&Pic, -50, -50);

  

  GFX_DrawFrame();



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
  else if (key == '-' && GFX_FrameZoom > 1)
    GFX_FrameZoom /= 1.25, GFX_ResizeFrameZoom(GFX_WinW, GFX_WinH, GFX_FrameZoom);
  else if (key == '+' && GFX_FrameZoom < 12)
    GFX_FrameZoom *= 1.25, GFX_ResizeFrameZoom(GFX_WinW, GFX_WinH, GFX_FrameZoom);
}                                  

void Reshape( int NewW, int NewH )
{
  GFX_WinW = NewW;
  GFX_WinH = NewH;
  GFX_ResizeFrameZoom(GFX_WinW, GFX_WinH, GFX_FrameZoom);

  glViewport(0, 0, GFX_WinW, GFX_WinH);
}


void main( int argc, char *argv[] )
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1920 / 2, 1080 / 2);
  glutCreateWindow("CGSG solo");


  ImgLoad(&Pic, "cockpit.g32");
  ImgStamp(&Pic);
  
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  GFX_Init();
  StarsInit();
  ProjSet(GFX_W, GFX_H);


  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutReshapeFunc(Reshape);

  glutMainLoop();
  glClearColor(0.30, 0.47, 0.8, 1);
}