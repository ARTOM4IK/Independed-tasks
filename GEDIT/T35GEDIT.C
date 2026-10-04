/* Arsentev Artemy, 09-4, 20  .12.2024 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#include <glut.h>

#include "GFX.H"

INT GFX_WinW, GFX_WinH, OLDx, OLDy;
HWND hWndMain;
DWORD CurrentColor = 0x00FFFF;

VOID Display( VOID )
{
  glClear(GL_COLOR_BUFFER_BIT);

  GFX_DrawFrame();

  /*GFX_PutCircle(60, 60, 52, CurrentColor);*/

  /* finish */
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

VOID BuffCpyPst( VOID )
{

  if (OpenClipboard(hWndMain))
  {
    HANDLE h = GetClipboardData(CF_BITMAP);
 
    if (h != NULL)
    {
      INT x, y;
      HDC hDCScreen = GetDC(NULL);
      HDC hDC = CreateCompatibleDC(hDCScreen);
      BITMAP bm;
 
      GetObject(h, sizeof(bm), &bm);
      SelectObject(hDC, h);
 
      for (y = 0; y < bm.bmHeight; y++)
        for (x = 0; x < bm.bmWidth; x++)
        {
          COLORREF col = GetPixel(hDC, x, y);
          DWORD c = GFX_RGB(GetRValue(col),
                            GetGValue(col),
                            GetBValue(col));
 
          GFX_PutPixel(x, y, c);
        }
 
      DeleteDC(hDC);
      ReleaseDC(NULL, hDCScreen);
    }
    CloseClipboard();
  }
 
}

VOID Keyboard( unsigned char key, INT x, INT y )
{
  if (key == 27)
    exit(0);
  else if (key == 'f')
    glutFullScreen();
  else if (key == '-' && GFX_FrameZoom > 1)
    GFX_FrameZoom /= 1.25, GFX_ResizeFrameZoom(GFX_WinW, GFX_WinH, GFX_FrameZoom);
  else if (key == '+' && GFX_FrameZoom < 12)
    GFX_FrameZoom *= 1.25, GFX_ResizeFrameZoom(GFX_WinW, GFX_WinH, GFX_FrameZoom);
  else if (key == 'k')
  {
    CHOOSECOLOR cc = {0};
    static COLORREF Pal[16];

    cc.lStructSize = sizeof(CHOOSECOLOR);
    cc.hwndOwner = hWndMain;
    cc.rgbResult = RGB(CurrentColor >> 16, CurrentColor >> 8, CurrentColor);
    cc.lpCustColors = Pal;
    cc.Flags = CC_RGBINIT | CC_FULLOPEN | CC_ANYCOLOR;
    if (ChooseColor(&cc))
      CurrentColor = GFX_RGB(GetRValue(cc.rgbResult), GetGValue(cc.rgbResult), GetBValue(cc.rgbResult));
  }
  else if (key == 'c')
    GFX_Clear(RGB(0, 0, 0));
  else if (key == 'q')
    TetaRose(x / GFX_FrameZoom, y / GFX_FrameZoom, 40, 20, CurrentColor);
  else if (key == 'e')
    vrngl( x / GFX_FrameZoom, y / GFX_FrameZoom, 40, 20, CurrentColor );
    /*Vroongel(x / GFX_FrameZoom, y / GFX_FrameZoom, 40, 20, 15, 30, 35, CurrentColor);*/
  else if (key == 'g')
    GFX_FloodFill( x / GFX_FrameZoom, y / GFX_FrameZoom, CurrentColor );
  else if (key = 'v')
    BuffCpyPst();
}

VOID Reshape( INT NewW, INT NewH )
{
  GFX_WinW = NewW;
  GFX_WinH = NewH;
  GFX_ResizeFrameZoom(GFX_WinW, GFX_WinH, GFX_FrameZoom);

  glViewport(0, 0, GFX_WinW, GFX_WinH);
}

VOID Mouse( INT button, INT state, INT x, INT y )
{
  OLDx = x, OLDy = y;
  if (state == GLUT_DOWN)
    GFX_PutPixel(x, y, CurrentColor);
}

VOID Motion( INT x, INT y )
{
  GFX_PutLine(OLDx / GFX_FrameZoom, OLDy / GFX_FrameZoom, x / GFX_FrameZoom, y / GFX_FrameZoom, CurrentColor);
  OLDx = x, OLDy = y;
}

VOID GFX_LoadImage( VOID )
{
  OPENFILENAME ofn = {0};
  static CHAR FileName[300];

  ofn.lStructSize = sizeof(OPENFILENAME);
  ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST;
  ofn.hwndOwner = hWndMain;
  ofn.lpstrDefExt = "*.g24";
  ofn.lpstrFile = FileName;
  ofn.nMaxFile = sizeof(FileName);
  ofn.lpstrTitle = "Load Image";
  ofn.lpstrFilter = "G24 images (*.g24)\0*.g24\0All files (*.*)\0*.*\0";
  ofn.nFilterIndex = 1;
  if (GetOpenFileName(&ofn))
  {
    FILE *F;

    if ((F = fopen(FileName, "rb")) != NULL)
    {
      INT w = 0, h = 0;

      fread(&w, 2, 1, F);
      fread(&h, 2, 1, F);
      fseek(F, 0, SEEK_END);
      if (ftell(F) == 4 + 3 * w * h)
      {
        INT x, y;

        fseek(F, 4, SEEK_SET);
        for (y = 0; y < h; y++)
          for (x = 0; x < w; x++)
          {
            BYTE rgb[3];

            fread(rgb, 3, 1, F);
            GFX_PutPixel(OLDx + x, OLDy + y,
              0xFF000000 | (rgb[2] << 16) | (rgb[1] << 8) | rgb[0]);
          }
      }
      fclose(F);
    }
  }
}

VOID MenuHandle( INT key )
{
  switch (key)
  {
  case 0:
    exit(30);
    break;
  case 1:
    break;
  case 2:
    GFX_LoadImage();
    break;
  }
}

VOID SubMenuHandle( INT key )
{
  switch (key)
  {
  case 0:
    GFX_PutCircle(60, 60, 52, CurrentColor);
    break;
  case 1:
    break;
  case 2:
    break;
  }
}

VOID main( INT argc, char *argv[] )
{
  INT menu;

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(1920 / 2, 1080 / 2);
  glutCreateWindow("CGSG solo");

  GFX_Init();

  hWndMain = FindWindow(NULL, "CGSG solo");

  menu = glutCreateMenu(MenuHandle);

  glutAddMenuEntry("Exit", 0);
  glutAddSubMenu("Select", 1);
  glutAddMenuEntry("Load file", 2);
  glutAttachMenu(GLUT_RIGHT_BUTTON);

  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutReshapeFunc(Reshape); 
  glutMouseFunc(Mouse);
  glutMotionFunc(Motion);


  glutMainLoop();
  glClearColor(0.30, 0.47, 0.8, 1);
} /* End of 'main' function */

/* End of T35GEDIT.C file */