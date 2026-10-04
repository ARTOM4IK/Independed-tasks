/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : frame.h
 * PURPOSE     : Fractal project.
 *               Frame module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artemy V. Arsentev
 * LAST UPDATE : 21.07.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __frame_h_
#define __frame_h_

#include "t50gif.h"
#include <cmath>

/* Frame representation type */
struct frame
{
  INT W, H;      //Frame size;
  DWORD *Frame;  //Array of pixels

  /* Type constructor.
    * ARGUMENTS:
    *   - new frame width:
    *       INT NewW;
    *   - new frame height:
    *       INT NewH;
    */
  frame ( INT NewW = 500, INT NewH = 500 ) : W(NewW), H(NewH)
  {
    Frame = new DWORD[H * W];
  } /* End of 'frame' function */

  /* Type destructor */
  ~frame ( VOID )
  {
    delete[] Frame;
  } /* End of '~frame' function */

  /* Resize frame function.
   * ARGUMENTS:
    *   - new frame width:
    *       INT NewW;
    *   - new frame height:
    *       INT NewH;
   * RETURNS: None.
   */
  VOID Resize( INT w, INT h )
  {
    delete[] Frame;

    if (w * h == 0)
      return;
    W = w;
    H = h;
    Frame = new DWORD[H * W];
  } /* End od 'Resize' funcion */

  /* Put color on pixel in frame function.
   * ARGUMENTS:
    *   - pos by X axis:
    *       INT x;
    *   - pos by Y axis:
    *       INT y;
    *   - color:
    *       DWORD color;
   * RETURNS: None.
   */
  VOID PutPixel( INT x, INT y, DWORD color )
  {
    if (x < 0 || x >= W || y < 0 || y >= H)
      return;

    Frame[y * W + x] = color;
  } /* End od 'PutPixel' funcion */

  /* Render frame function.
   * ARGUMENTS:
   *   - fractal:
   *       frac F;
   * RETURNS: None.
   */
  VOID Render( const gif &gi )
  {
    for (INT y = 0; y < gi.H; y++)
      for (INT x = 0; x < gi.W; x++)
        PutPixel(x, y, gi.Pixels[y * gi.W + x]);
  } /* End od 'Render' funcion */

  /* Draw frame function.
   * ARGUMENTS:
   *   - window hadle:
   *       HDC hDC;
   * RETURNS: None.
   */
  VOID Draw( HDC hDC )
  {
    BITMAPINFOHEADER bmith = {0};
    bmith.biSize = sizeof(BITMAPINFOHEADER);
    bmith.biWidth = W;
    bmith.biHeight = -H;
    bmith.biPlanes = 1;
    bmith.biBitCount = 32;
    StretchDIBits(hDC, 0, 0, W, H, 0, 0, W, H, Frame, (BITMAPINFO *)&bmith, DIB_RGB_COLORS, SRCCOPY);
  } /* End od 'Draw' funcion */
}; /* End of 'frame' structure */

#endif /* __frame_h_ */
 
/* END OF 'frame.h' FILE */
