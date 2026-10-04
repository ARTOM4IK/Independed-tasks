/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : t49lzw.h
 * PURPOSE     : LZW project.
 *               Header module.
 * PROGRAMMER  : AA4.
 *               
 * LAST UPDATE : 23.09.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __t49lzw_h_
#define __t49lzw_h_

#include <cassert>
 
#ifndef WIN32
#define WIN32
#include <commondf.h>
#undef WIN32
#else
#include <commondf.h>
#endif /* WIN32 */
#define BOOL bool
#include <string>
#include <vector>
#include <fstream>
#include <exception>
#include <map> 
#include <wincodec.h>  
#include <functional>
#include <array> 
#include <format>

#include <iostream>
#include <format>

#define FRAME_H 1080 / 2
#define FRAME_W 1920 / 2
#define GFX_W 1920 / ZOOM
#define GFX_H 1080 / ZOOM

#define ZOOM 1

typedef unsigned long DWORD;
typedef unsigned short WORD;
typedef unsigned char BYTE;

extern DWORD Frame[GFX_H][GFX_W];

#pragma pack(push, 1)
  /* GIF file header structure */
  struct HEADER
  {
    CHAR Sign[6];         // GIF file signature 'GIF8?a'
    WORD W, H;            // Image size
    BYTE Info;            // Image information byte:
                          // 0..2 bits - bits per pixel (- 1)
                          // 4..6 bits - color resolution (- 1)
                          // 7 bit - global color table presence flag
    BYTE BackgroundColor; // Backgound color index
    BYTE Reserved;        // Not used (0)
  }; /* End of 'HEADER' structure */
 
  /* GIF image header structure */
  struct IMAGE_HEADER
  {
    WORD X0, Y0, W, H; // Image start coordinates and size
    BYTE Info;         // Image information byte:
                       // 0..2 bits - bits per pixel (- 1)
                       // 6 bit - interlacing flag
                       // 7 bit - local color table presence flag
   }; /* End of 'IMAGE_HEADER' structure */

  /* GIF application extension (0xFF) structure */
  struct EXT_APPLICATION
  {
    CHAR Name[8]; // Application name
    CHAR Version[3]; // Version info (for NETSCAPE: 0x01, 2bytes: 0..65535 repeat count)
  }; /* End of 'EXT_APPLICATION' structure */

  /* GIF graphics extension (0xF9) structure */
  struct EXT_GRAPHICS
  {
    BYTE Info;       // Graphics info bits:
                     // 0 bit: 1 if 'TransColor' used
                     // 1 bit: 1 if expected click between frames, 0 – auto
                     // 2-4 bits: disposal method:
                     // 0 – no deals
                     // 1 – image stay without changes
                     // 2 – image deleted by background
                     // 3 – restore image below frame
                     // 4-7 – not usage
    WORD DelayTime;  // Interframe delay time in 1/100 seconds
    BYTE TransColor; // Transparent color index
  }; /* End of 'EXT_GRAPHICS' structure */
#pragma pack(pop)

/* Gif class */
class gif
{
public:
  INT W, H, frames, curframe, X0, Y0;
  EXT_GRAPHICS eg {};
  std::vector<DWORD> Pixels;
  std::fstream f;
  BOOL IsAnimated;
  WORD DelayTime;
  BYTE TransColor, LastTransColor;

  /* Class constructor.
   * AGUMENTS: None.
   */
  gif( VOID )
  {
    curframe = 0;
    frames = 1;
    LastTransColor = -1;
  } /* End of 'gif' function */

  /* Class destructor*/
  ~gif( VOID )
  {
  } /* End of '~gif' fucntion */

  /* Open gif file function.
   * ARGUMENTS:
   *   - Filename:
   *       const std::string &FileName;
   * RETURNS: None.
   */
  VOID Open( const std::string &FileName );
}; /* End of 'gif' class */

#endif /* __t50gif_h_ */

/* END OF 't50gif.h' FILE */                                 
