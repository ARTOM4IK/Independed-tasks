/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : frame.h
 * PURPOSE     : Ray Tracing project.
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

#include <mutex>
#include <iostream>
#include <fstream>
#include <cstring>
#include <filesystem>

#include "def.h"
 
#pragma pack(push, 1)
#include <tgahead.h>
#pragma pack(pop)

/* Ray tracing namespace */
namespace arrt
{
  /* Frame representation type */
  class frame
  {
  private:
    DWORD *Frame;  //Array of pixels
    // Frame access mutex
    std::recursive_mutex frame_mutex;
  public:
    INT W, H;      //Frame size;

    /* Type constructor.
      * ARGUMENTS:
      *   - new frame width:
      *       INT NewW;
      *   - new frame height:
      *       INT NewH;
      */
    frame ( INT NewW = 1920, INT NewH = 1080 ) : W(NewW), H(NewH)
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
      const std::lock_guard<std::recursive_mutex> lock(frame_mutex);
      delete[] Frame;

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
      const std::lock_guard<std::recursive_mutex> lock(frame_mutex);
      if (x < 0 || x >= W || y < 0 || y >= H)
      return;

      Frame[y * W + x] = color & 0xFFFFFF;
    } /* End od 'PutPixel' funcion */

    /* Convert RGB color to DWORD function.
     * ARGUMENTS:
      *   - color parametrs:
      *       DBL R, DBL G, DBL B;
     * RETURNS:
     *   (DWORD) color.
     */
    static DWORD ToRGB( DBL R, DBL G, DBL B )
    {
      auto clamp =
        [](FLT Value ) -> BYTE
        {
          if (Value < 0)
            return 0;
          if (Value > 1)
            return 255;
          return Value * 255;
        };
      return (clamp(R) << 16) | (clamp(G) << 8) | clamp(B);
    } /* End of 'ToRGB' function */                        

    /* Draw frame function.
     * ARGUMENTS:
     *   - pixel position:
     *       INT x, INT y;
     *   - pixel color:
     *       mth::vec3<DBL> color;
     * RETURNS: None.
     */
    VOID PutPixel( INT x, INT y, mth::vec3<DBL> color )
    {
      const std::lock_guard<std::recursive_mutex> lock(frame_mutex);
      if (x < 0 || x >= W || y < 0 || y >= H)
        return;

      Frame[y * W + x] = ToRGB(color[0], color[1], color[2]) & 0xFFFFFF;
    } /* End od 'PutPixel' funcion */

    /* Render frame function.
     * ARGUMENTS: None.
     * RETURNS: None.
     */
    VOID Render ( VOID )
    {
    } /* End of 'Render' function */

    /* Draw frame function.
     * ARGUMENTS:
     *   - window hadle:
     *       HDC hDC;
     * RETURNS: None.
     */
    VOID Draw( HDC hDC, INT X, INT Y, INT FrameW, INT FrameH )
    {
      const std::lock_guard<std::recursive_mutex> lock(frame_mutex);
      BITMAPINFOHEADER bmith
      {
        .biSize = sizeof(BITMAPINFOHEADER),
        .biWidth = W,
        .biHeight = -H,
        .biPlanes = 1,
        .biBitCount = 32,
        .biCompression = BI_RGB,
        .biSizeImage = static_cast<DWORD>(W * H * sizeof(DWORD)),
        .biXPelsPerMeter = 30,
        .biYPelsPerMeter = 30,
        .biClrUsed = 0,
        .biClrImportant = 0,
      };

      SetStretchBltMode(hDC, COLORONCOLOR);
      StretchDIBits(hDC, X, Y, FrameW, FrameH, 0, 0, W, H, Frame, (BITMAPINFO *)&bmith, DIB_RGB_COLORS, SRCCOPY);
    } /* End od 'Draw' funcion */

      /* Fill frame with specified color function.
       * ARGUMENTS:
       *   - pixels color:
       *       DWORD Color;
       * RETURNS: None.
       */
      VOID Fill( DWORD Color )
      {
        // Lock access
        const std::lock_guard<std::recursive_mutex> lock(frame_mutex);
 
        // Set pixel color
        INT n = W * H;
        DWORD *ptr = Frame;
        while (n-- > 0)
          *ptr++ = Color;
      } /* End of 'Fill' function */

      /* Store frame buffer image to TGA file function.
       * ARGUMENTS:
       *   - file name:
       *       const std::string &FileName;
       *   - addition comments:
       *       const std::string &Comments;
       *   - render/job time (hours, minutes, seconds):
       *       const std::tuple<INT, INT, INT> &JobTime;
       * RETURNS:
       *   (BOOL) TRUE if success, FALSE otherwise.
       */
      BOOL SaveTGA( const std::string &FileName,
                    const std::string &Comments = "",
                    const std::tuple<INT, INT, INT> &JobTime = {0, 0, 0} )
      {
        // Lock access
        const std::lock_guard<std::recursive_mutex> lock(frame_mutex);
 
        std::filesystem::path PathName(FileName);
        if (!PathName.has_extension())
          PathName += ".tga";
 
        std::fstream f(PathName, std::fstream::out | std::fstream::binary);
        if (!f.is_open())
          return FALSE;
 
        // Fill file header
        tgaFILEHEADER head {};  
        INT len = static_cast<INT>(Comments.length());
 
        if (len > 254)
          len = 255;
        else
          if (len != 0)
            len++;
        head.IDLength = len;
        head.ColorMapType = 0;
        head.ImageType = 2;
        head.BitsPerPixel = 32;
        head.Width = W;
        head.Height = H;
        head.ImageDescr = 1 << 5; // image start - left-top corner
 
        // Store header and comments
        f.write(reinterpret_cast<CHAR *>(&head), sizeof(head));
        if (len != 0)
          f.write(Comments.c_str(), len - 1), f.put(0);
 
        // Store image
        f.write(reinterpret_cast<CHAR *>(Frame), W * H * 4);
 
        tgaEXTHEADER ext = {0};
        strcpy(ext.AuthorName, "VG4");
        strcpy(ext.SoftwareID, "CGSG RayTracing'2025-summer");
        strcpy(ext.AuthorComment, "CGSG forever!!!");
        ext.VersionNumber = 100;
        ext.GammaDenominator = 1;
        ext.GammaNumerator = 1;
        ext.PixelDenominator = 1;
        ext.PixelNumerator = 1;
        strcpy(ext.JobName, "CGSG Raytracing");
 
        ext.JobHour = std::get<0>(JobTime);
        ext.JobMinute = std::get<1>(JobTime);
        ext.JobSecond = std::get<2>(JobTime);
 
        f.write((CHAR *)&ext, sizeof(ext));
 
        tgaFILEFOOTER foot = {0};
        foot.ExtensionOffset = sizeof(head) + head.IDLength + 4 * W * H;
        strncpy(foot.Signature, TGA_EXT_SIGNATURE, 18);
        f.write((CHAR *)&foot, sizeof(foot));
 
        f.close();
        return TRUE;
      } /* End of 'SaveTGA' function */
 
      /* Auto naming store frame buffer image to TGA file function.
       * ARGUMENTS:
       *   - addition comments:
       *       const std::string &Comments;
       *   - render/job time (hours, minutes, seconds):
       *       const std::tuple<INT, INT, INT> &JobTime;
       * RETURNS:
       *   (BOOL) TRUE if success, FALSE otherwise.
       */
      BOOL AutoSaveTGA( const std::string &Comments = "",
                        const std::tuple<INT, INT, INT> &JobTime = {0, 0, 0} )
      {
        SYSTEMTIME st;
 
        GetLocalTime(&st);
        CHAR Buf[300];
 
        std::string path("bin/images/AutoSave");
        std::filesystem::create_directories(path);  // <filesystem>
 
        wsprintf(Buf, "%04d%02d%02d_%02d%02d%02d_%03d_%02d",
          st.wYear, st.wMonth, st.wDay, st.wHour,
          st.wMinute, st.wSecond, st.wMilliseconds,
          rand() % 90);
        return SaveTGA(path + "/" + Buf + ".tga", Comments, JobTime);
      } /* End of 'AutoSaveTGA' function */
  }; /* End of 'frame' structure */
} /* End of 'arrt' namespace*/
#endif /* __frame_h_ */
 
/* END OF 'frame.h' FILE */
