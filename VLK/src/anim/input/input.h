/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : input.h
 * PURPOSE     : Animation project.
 *               Input definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'arvk'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __input_h_
#define __input_h_

#include <cstring>
//#include <mmsystem.h>

#include "def.h"

/* Animation namespace */
namespace arvk
{
  /* Keyboard class*/
  class keyboard
  {
  public:
    BYTE KeysOld[256];              // key state in previous frame 
    BYTE Keys[256], KeysClick[256]; // Keyboard clicks

    /* keyboard  constructor.
     * ARGUMENTS:
     *   None.
     * RETURNS:
     *   None.
     */
    keyboard( VOID )
    {
      Reset();
    } /* End of 'Keyboard' function */

    /* Reset input function.
     * ARGUMENTS:
     *   None.
     * RETURNS:
     *   None.
     */
    VOID Reset( VOID )
    {
      memset(Keys, 0, 256);
      memset(KeysClick, 0, 256);
      memset(KeysOld, 0, 256);
    } /* End of 'Keyboard' function */

    /* Response keyboard input function.
     * ARGUMENTS:
     *   None.
     * RETURNS:
     *   None.
     */
    VOID Response( VOID )
    {
      CHAR ch = GetKeyboardState(Keys);
      //for (INT i = 0; i < 256; i++)
      //{
      //  Keys[i] >>= 7;
      //  KeysClick[i] = Keys[i] && !KeysOld[i];
      //}

      for ( auto &key : Keys )
        key >>= 7;
      for (INT i = 0; i < 256; i++)
        KeysClick[i] = Keys[i] && !KeysOld[i];
      memcpy(KeysOld, Keys, 256);
    } /* End of 'Response' function */
  }; /* End of 'keyboard' class */

  /* Joystick class */
  class joystick      
  {
  public:
    BYTE JBut[32], JButOld[32], JButClick[32];  /* Joystick button states */
    INT JPov;                                   /* Joystick point-of-view control [-1,0..7] */
    DBL JX, JY, JZ, JR;                         /* Joystick axes */

    /* joystick constructor.
     * ARGUMENTS:
     *   None.
     * RETURNS:
     *   None.
     */
    joystick( VOID ): JPov(0), JX(0), JY(0), JZ(0), JR(0) 
    {
      memset(JBut, 0, 32);
      memset(JButOld, 0, 32);
      memset(JButClick, 0, 32);
    } /* End of 'joystick' function */

    /* Reset input function.
     * ARGUMENTS:
     *   None.
     * RETURNS:
     *   None.
     */
    VOID Reset( VOID )
    {
      JPov = 0;
      JX = JY = JZ = JR = 0;
      memset(JBut, 0, 32);
      memset(JButOld, 0, 32);
      memset(JButClick, 0, 32);
    } /* End of 'Reset' function */

//    VOID Response( VOID )
//    {
//      /* Joystick */
//      if (joyGetNumDevs() > 0)
//      {
//        JOYCAPS jc;
// 
//        /* Get joystick info */
//        if (joyGetDevCaps(JOYSTICKID1, &jc, sizeof(jc)) == JOYERR_NOERROR)
//        {
//          JOYINFOEX ji;
// 
//          ji.dwSize = sizeof(JOYINFOEX);
//          ji.dwFlags = JOY_RETURNALL;
//          if (joyGetPosEx(JOYSTICKID1, &ji) == JOYERR_NOERROR)
//          {
//            /* Buttons */
//            for (INT i = 0; i < 32; i++)
//            {
//              JBut[i] = (ji.dwButtons >> i) & 1;
//              JButClick[i] = JBut[i] && !JButOld[i];
////              JButOld[i] = JBut[i];
//            }
//            memcpy(JButOld, JBut, 32);
//            
//            /* Axes */
//            JX = 2.0 * (ji.dwXpos - jc.wXmin) / (jc.wXmax - jc.wXmin) - 1;
//            JY = 2.0 * (ji.dwYpos - jc.wYmin) / (jc.wYmax - jc.wYmin) - 1;
//            JZ = 2.0 * (ji.dwZpos - jc.wZmin) / (jc.wZmax - jc.wZmin) - 1;
//            JR = 2.0 * (ji.dwRpos - jc.wRmin) / (jc.wRmax - jc.wRmin) - 1;
// 
//            /* Point of view */ 
//            JPov = ji.dwPOV == 0xFFFF ? -1 : ji.dwPOV / 4500;
//          }       
//        }
//      }
//    }
  }; /* End of 'joystick' class */

  /* Mouse class */
  class mouse
  {
  private:
  public:
    HWND &hWndRef;
  protected:
  public:
    INT &Wheel;
    INT Mx, My, Mz, Mdz, Mdx, Mdy;
    BYTE MBut[3], OldMBut[3], MButClick[3];

    /* mouse constructor.
     * ARGUMENTS:
     *   None.
     * RETURNS:
     *   None.
     */
    mouse( HWND &hWndRef, INT &WheelRef ) : hWndRef(hWndRef), Wheel(WheelRef), Mx(0), My(0), Mz(0), Mdz(0), Mdx(0), Mdy(0)
    {
      memset(MBut, 0, 3);
      memset(OldMBut, 0, 3);
      memset(MButClick, 0, 3);
    } /* End of 'mouse' function */

    /* Reset input function.
     * ARGUMENTS:
     *   None.
     * RETURNS:
     *   None.
     */
    VOID Reset( VOID )
    {
      Mx = My = Mz = Mdx = Mdy = Mdz = 0;
      memset(MBut, 0, 3);
      memset(OldMBut, 0, 3);
      memset(MButClick, 0, 3);
    } /* End of 'Reset' function */

    /* Response mouse input function.
     * ARGUMENTS:
     *   - Window handle:
     *       HWND hWnd;
     * RETURNS:
     *   None.
     */
     VOID Response( VOID )
     {
       POINT pt;
 
       GetCursorPos(&pt);
       ScreenToClient(hWndRef, &pt);
 
       Mdx = pt.x - Mx;
       Mdy = pt.y - My;

       Mx = pt.x;
       My = pt.y;

       Mdz = Wheel;
       Mz += Wheel;
       Wheel = 0;

       MBut[0] = GetAsyncKeyState(VK_LBUTTON) >> 15;
       MBut[1] = GetAsyncKeyState(VK_RBUTTON) >> 15;
       MBut[2] = GetAsyncKeyState(VK_MBUTTON) >> 15;

       for (INT i = 0; i < 3; i++)
         MButClick[i] = !OldMBut[i] && MBut[i];
       memcpy(OldMBut, MBut, 3);
    } /* End of 'Response' function */
  }; /* End of 'mouse' class */

  /* Input class */
  class input: public keyboard, public mouse, public joystick
  {   
  public:
    /* input constructor.
     * ARGUMENTS:
     *   None.
     * RETURNS:
     *   None.
     */
    input( HWND hWnd, INT MouseWheel ): mouse(hWnd, MouseWheel)
    {
    } /* End of '' function */

    /* Reset input function.
     * ARGUMENTS:
     *   None.
     * RETURNS:
     *   None.
     */
    VOID Reset( VOID )
    {
      keyboard::Reset();
      mouse::Reset();
      joystick::Reset();
    } /* End of 'Reset' function */

    /* Response input function.
     * ARGUMENTS:
     *   - Window handle:
     *       HWND hWnd;
     * RETURNS:
     *   None.
     */
    VOID Response( VOID )
    {
      mouse::Response();
      keyboard::Response();
      //joystick::Response();
    } /* End of 'Response' function */
  }; /* End of 'input' class */
} /* End of 'arvk' namespace */

#endif /* __input_h_ */

/* END OF 'input.h' FILE */
