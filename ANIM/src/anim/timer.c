/* FILE NAME: timer.c
 * PROGRAMMER: AA4
 * DATE: 17.01.2024
 * PURPOSE: 3D animation project.
 *          Timer module.
 */

#include "anim/anim.h"

static UINT64
  StartTime,    /* Start program time */
  OldTime,      /* Previous frame time */
  OldTimeFPS,   /* Old time FPS measurement */
  PauseTime,    /* Time during pause period */
  TimePerSec,   /* Timer resolution */
  FrameCounter; /* Frames counter */

/* user data (set later in animation context) */
DBL
  GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
  Time, DeltaTime,             /* Time with pause and interframe interval */
  FPS;                         /* Frames per second value */
BOOL
  IsPause;                     /* Pause flag */

/* Init timer function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_TimerInit( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceFrequency(&t);
  TimePerSec = t.QuadPart;
  QueryPerformanceCounter(&t);
  StartTime = OldTime = OldTimeFPS = t.QuadPart;
  FrameCounter = 0;
  IsPause = FALSE;
  FPS = 30.0;
  PauseTime = 0;
}

/* Response timer function.
 * ARGUMENTS:
 *   None.
 * RETURNS:
 *   None.
 */
VOID AA4_TimerResponse( VOID )
{
  LARGE_INTEGER t;
 
  QueryPerformanceCounter(&t);
  /* Global time */
  AA4_Anim.GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
  AA4_Anim.GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
  /* Time with pause */
  if (IsPause)
  {
    AA4_Anim.DeltaTime = 0;
    PauseTime += t.QuadPart - OldTime;
  }
  else
  {
    AA4_Anim.DeltaTime = GlobalDeltaTime;
    AA4_Anim.Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
  }
  /* FPS */
  FrameCounter++;
  if (t.QuadPart - OldTimeFPS > TimePerSec)
  {
    AA4_Anim.FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
    OldTimeFPS = t.QuadPart;
    FrameCounter = 0;
  }
  OldTime = t.QuadPart;

  AA4_RndUBOSyncUpdate();
}

/* END OF 'timer.c' FILE */
