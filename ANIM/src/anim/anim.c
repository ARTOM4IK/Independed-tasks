/* FILE NAME: anim.c
 * PROGRAMMER: AA4
 * LAST UPDATE: 22.01.2025
 * PURPOSE: 3D animation project.
 *          Animation module.
 */

#include "anim.h"
#include <stdio.h>

aa4UNIT *Units[AA4_MAX_UNITS];
INT NumOfUnits;
aa4ANIM AA4_Anim;
aa4UNIT *Uni;

/* Init animation function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimInit( HWND hWnd )
{
  memset(&AA4_Anim, 0, sizeof(aa4ANIM));
  AA4_Anim.hWnd = hWnd;
  AA4_RndInit(hWnd);
  AA4_Anim.hDC = AA4_hRndDC;
  AA4_AnimInputInit();
} /* End of 'AA4_AnimInit' function */

/* Close animation function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_AnimClose( VOID )
{
  INT i;

  for (i = 0; i < AA4_Anim.NumOfUnits; i++)
  {
    AA4_Anim.Units[i]->Close(AA4_Anim.Units[i], &AA4_Anim);
    free(AA4_Anim.Units[i]);
    AA4_Anim.Units[i] = NULL;
  }
  AA4_RndClose();
} /* End of 'AA4_AnimClose' function */

/* Add unit to animation function.
 * ARGUMENTS:
 *   - Unit:
 *       aa4UNIT *Uni;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimUnitAdd( aa4UNIT *Uni )
{
  if (AA4_Anim.NumOfUnits < AA4_MAX_UNITS)
    AA4_Anim.Units[AA4_Anim.NumOfUnits++] = Uni, Uni->Init(Uni, &AA4_Anim);
} /* End of 'AnimUnitAdd' function */

/* Copy animation frame function.
 * ARGUMENTS:
 *   - DC handle:
 *       HDC hDC;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimCopyFrame( VOID )
{
  AA4_RndCopyFrame();
} /* End of 'AA4_AnimCopyFrame' function */

/* Animation render function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimRender( VOID )
{
  INT i;

  AA4_TimerResponse();
  AA4_AnimInputResponse();
  AA4_AnimResponse();
  AA4_RndStart();
  for (i = 0; i < AA4_Anim.NumOfUnits; i++)
    AA4_Anim.Units[i]->Render(AA4_Anim.Units[i], &AA4_Anim);
  AA4_RndEnd();
} /* End of 'AA4_AnimRender' function */

/* Animation response function.
 * ARGUMENTS:
 *   None;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimResponse( VOID )
{
  INT i;

  for (i = 0; i < AA4_Anim.NumOfUnits; i++)
    AA4_Anim.Units[i]->Response(AA4_Anim.Units[i], &AA4_Anim);
} /* End of 'AA4_AnimResponse' function */

/* Reszie animation function.
 * ARGUMENTS:
 *   - Window size:
 *       INT W, INT H;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimResize( INT W, INT H )
{
  AA4_RndResize(W, H);
  AA4_AnimRender();
} /* End of 'AA4_AnimResize' function */

/* Flip full screen function.
 * ARGUMENTS:
 *   - Window handle:
 *       HWND hWnd;
 * RETURNS:
 *   None.
 */
VOID AA4_AnimFlipFullScreen( VOID )
{
  HWND hWnd = AA4_Anim.hWnd;
  static BOOL IsFullScreen = FALSE;  /* Current mode */
  static RECT SaveRC;                /* Saved size */

  if (!IsFullScreen)
  {
    RECT rc;
    HMONITOR hmon;
    MONITORINFOEX moninfo;

    GetWindowRect(hWnd, &SaveRC);

    hmon = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);

    moninfo.cbSize = sizeof(moninfo);
    GetMonitorInfo(hmon, (MONITORINFO *)&moninfo);

    rc = moninfo.rcMonitor;

    AdjustWindowRect(&rc, GetWindowLong(hWnd, GWL_STYLE), FALSE);

    SetWindowPos(hWnd, HWND_TOP,
      rc.left, rc.top,
      rc.right - rc.left, rc.bottom - rc.top + 201,
      SWP_NOOWNERZORDER);
    IsFullScreen = TRUE;
  }
  else
  {
    SetWindowPos(hWnd, HWND_TOP,
      SaveRC.left, SaveRC.top,
      SaveRC.right - SaveRC.left, SaveRC.bottom - SaveRC.top,
      SWP_NOOWNERZORDER);
    IsFullScreen = FALSE;
  }
} /* End of 'AA4_AnimFlipFullScreen' function */

/* Exit animation function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_AnimDoExit( VOID )
{
  AA4_AnimClose();
  exit(30);
} /* End of 'AA4_AnimDoExit' function */

/* END OF 'anim.c' FILE */
