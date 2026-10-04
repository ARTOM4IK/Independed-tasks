/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : timer.h
 * PURPOSE     : Animation project.
 *               Timer definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'arvk'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __timer_h_
#define __timer_h_

#include "def.h"

/* Animation namespace */
namespace arvk
{
  /* Timer class */
  class timer
  {
  private:
    UINT64
      StartTime,    /* Start program time */
      OldTime,      /* Previous frame time */
      OldTimeFPS,   /* Old time FPS measurement */
      PauseTime,    /* Time during pause period */
      TimePerSec,   /* Timer resolution */
      FrameCounter; /* Frames counter */
  public:
    DBL
      GlobalTime, GlobalDeltaTime, /* Global time and interframe interval */
      Time, DeltaTime,             /* Time with pause and interframe interval */
      FPS;                         /* Frames per second value */
    BOOL
      IsPause;                     /* Pause flag */

    /* timer constructor.
     * ARGUMENTS:
     *   None.
     * RETURNS:
     *   None.
     */
    timer( VOID )
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
      GlobalTime = GlobalDeltaTime = Time = DeltaTime = 0;
    } /* End of 'timer' function */

    /* Reset timer function.
     * ARGUMENTS:
     *   None.
     * RETURNS:
     *   None.
     */
    VOID Reset( VOID )
    {
      TimePerSec = 0;
      StartTime = OldTime = OldTimeFPS = 0;
      FrameCounter = 0;
      IsPause = FALSE;
      FPS = 0.0;
      PauseTime = 0;
    } /* End of 'Reset' function */

    /* Response timer function.
     * ARGUMENTS:
     *   None.
     * RETURNS:
     *   None.
     */
    VOID Response( VOID )
    {
      LARGE_INTEGER t;
 
      QueryPerformanceCounter(&t);
      /* Global time */
      GlobalTime = (DBL)(t.QuadPart - StartTime) / TimePerSec;
      GlobalDeltaTime = (DBL)(t.QuadPart - OldTime) / TimePerSec;
      /* Time with pause */
      if (IsPause)
      {
        DeltaTime = 0;
        PauseTime += t.QuadPart - OldTime;
      }
      else
      {
        DeltaTime = GlobalDeltaTime;
        Time = (DBL)(t.QuadPart - PauseTime - StartTime) / TimePerSec;
      }
      /* FPS */
      FrameCounter++;
      if (t.QuadPart - OldTimeFPS > TimePerSec)
      {
        FPS = FrameCounter * TimePerSec / (DBL)(t.QuadPart - OldTimeFPS);
        OldTimeFPS = t.QuadPart;
        FrameCounter = 0;
      }
      OldTime = t.QuadPart;
    } /* End of 'Response' fucntion */
  }; /* End of 'timer' class */
} /* End of 'arvk' namespace */

#endif /* __timer_h_ */

/* END OF 'timer.h' FILE */
