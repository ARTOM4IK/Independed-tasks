/* FILE NAME: input.c
 * PROGRAMMER: AA4
 * DATE: 18.01.2024
 * PURPOSE: 3D animation project.
 *          Input response module.
 */

#include <windows.h>
#include <mmsystem.h>
#include <string.h>
#include "anim.h"

static BYTE KeysOld[256];  /* key state in previous frame */
INT Mx, My, Mz, Mdx, Mdy, Mdz ;
DBL AA4_MouseWheel;
POINT pt;

  BYTE
    JBut[32], JButOld[32], JButClick[32]; /* Joystick button states */
  INT JPov;                               /* Joystick point-of-view control [-1,0..7] */
  DBL
    JX, JY, JZ, JR;                       /* Joystick axes */
    
/***
 * Keyboard
 ***/

/* Init keyboard input function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
static VOID AA4_AnimKeyboardInit( VOID )
{
  memset(AA4_Anim.Keys, 0, sizeof(BYTE) * 256);
  memset(AA4_Anim.KeysClick, 0, sizeof(BYTE) * 256);
  memset(KeysOld, 0, sizeof(BYTE) * 256);
} /* End of 'AA4_AnimKeyboardInit' function */

/* Response keyboard input function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
static VOID AA4_AnimKeyboardResponse( VOID )
{
  INT i;

  GetKeyboardState(AA4_Anim.Keys);
  for (i = 0; i < 256; i++)
  {
    AA4_Anim.Keys[i] >>= 7;
    AA4_Anim.KeysClick[i] = AA4_Anim.Keys[i] && !KeysOld[i];
  }
  memcpy(KeysOld, AA4_Anim.Keys, 256);

} /* End of 'AA4_AnimKeyboardResponse' function */

/***
 * Mouse
 ***/

/* Init keyboard input function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
static VOID AA4_AnimMouseInit( VOID )
{
  Mx = My = Mz = Mdx = Mdy = Mdz = AA4_MouseWheel = 0;
} /* End of 'AA4_AnimMouseInit' function */

/* Response mouse input function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
static VOID AA4_AnimMouseResponse( VOID )
{
  POINT pt;
 
  GetCursorPos(&pt);
  ScreenToClient(AA4_hRndWnd, &pt);
 
  Mdx = pt.x - Mx;
  Mdy = pt.y - My;

  Mx = pt.x;
  My = pt.y;

  Mdz = AA4_MouseWheel;
   Mz += AA4_MouseWheel;
  AA4_MouseWheel = 0;

  AA4_Anim.Mdx = Mdx;
  AA4_Anim.Mdy = Mdy;
  AA4_Anim.Mdz = Mdz;
} /* End of 'AA4_AnimMouseResponse' function */

/***
 * Joystick
 ***/

static VOID AA4_AnimJoystickInit( VOID )
{
}

static VOID AA4_AnimJoystickResponse( VOID )
{
}

VOID AA4_AnimInputInit( VOID )
{
  AA4_AnimKeyboardInit();
  AA4_AnimMouseInit();
  /* AA4_AnimJoystickInit(); */
}

VOID AA4_AnimInputResponse( VOID )
{
  AA4_AnimKeyboardResponse();
  AA4_AnimMouseResponse();
  /* AA4_AnimJoystickResponse(); */
}

/* END OF 'input.c' FILE */
