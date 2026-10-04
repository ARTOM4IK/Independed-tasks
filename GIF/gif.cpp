/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : gif.cpp
 * PURPOSE     : Googling Information Forever project.
 *               Main module.
 * PROGRAMMER  : AA4.
 *               
 * LAST UPDATE : 21.10.2025.
 * NOTE        : None.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#include "t50gif.h"
#include "glut.h"

DWORD Frame[GFX_H][GFX_W];

/* Translate color to DWORD function.
 * ARGUMENTS:
 *   - Color parametrs:
 *       int r, int g, int b;
 * RETURNS: None.
 */
DWORD GFX_RGB( INT r, INT g, INT b )
{
  return (r << 16) | (g << 8) | b;
} /* End of 'GFX_RGB' function */

/* Put pixel on screen function.
 * ARGUMENTS:
 *   - pixel position and color:
 *       int x, int y, DWORD color;
 * RETURNS: None.
 */
void GFX_PutPixel( INT x, INT y, DWORD color )
{
  if (x < 0 || x >= GFX_W || y < 0 || y >= GFX_H)
    return;
  Frame[y][x] = color;
} /* End of 'GFX_PutPixel' function */

/* Draw frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void GFX_DrawFrame( VOID )
{
  /* draw */
  glRasterPos2d(-1, 1);
  glPixelZoom(ZOOM, -ZOOM);
  glDrawPixels(GFX_W, GFX_H, GL_BGRA_EXT, GL_UNSIGNED_BYTE, Frame);
} /* End of 'GFX_DrawFrame' function */


/* Render frame function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
void Render( std::vector<DWORD> Pixels, INT W, INT H, INT X0, INT Y0 )
{
  glClear(GL_COLOR_BUFFER_BIT);

  GFX_DrawFrame();

  for (INT y = 0; y < H; y++)
    for (INT x = 0; x < W; x++)
      GFX_PutPixel(x + X0, y + Y0, Pixels[y * W + x]);

  /* finish */
  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
} /* End of 'Render' function */

/* Clear screen function.
 * ARGUMENTS:
 *   - Color:
 *       DWORD color;
 * RETURNS: None.
 */
void GFX_Clear( DWORD color )
{
  int i, j;

  for (i = 0; i < GFX_W; i++)
    for (j = 0; j < GFX_W; j++)
      GFX_PutPixel(i, j, GFX_RGB(0, 0, 0));
} /* End of 'GFX_Clear' function */

/* Open gif file function.
 * ARGUMENTS:
 *   - Filename:
 *       const std::string &FileName;
 * RETURNS: None.
 */
VOID gif::Open( const std::string &FileName )
{
  std::fstream f(FileName, std::fstream::in | std::fstream::binary);

  if (!f.is_open())
    return;

  HEADER Head;
 
  f.read((CHAR *)&Head, sizeof(Head));
  if ((std::string(Head.Sign, Head.Sign + 6)) != "GIF87a" && (std::string(Head.Sign, Head.Sign + 6)) != "GIF89a")
    return;
  UINT BitsPerPixel = (Head.Info & 7) + 1, ColorBits = ((Head.Info >> 4) & 7) + 1;
  std::array<BYTE [3], 256> GlobalPalette {};
  BOOL IsGlobalPalette = Head.Info >> 7;

  if (IsGlobalPalette)
    f.read(reinterpret_cast<CHAR *>(&GlobalPalette), 3 * (1 << BitsPerPixel));


  while (TRUE)
  {
    CHAR ch;

    if (!f.get(ch))
      break;
    if (ch == ',')
    {
      IMAGE_HEADER ih;

      std::array<BYTE [3], 256> LocalPalette;
      f.read(reinterpret_cast<CHAR *>(&ih), sizeof(ih));
      BOOL  IsLocalPalette = ih.Info >> 7, IsImgStay = ih.Info >> 6;
      if (IsLocalPalette)                
        f.read(reinterpret_cast<CHAR *>(&LocalPalette), 1);
      else
        LocalPalette = GlobalPalette;
      BYTE ImageCodeSize;
      W = ih.W;
      H = ih.H;
      Pixels.resize(W * H);
      X0 = ih.X0, Y0 = ih.Y0;
      f.read(reinterpret_cast<CHAR *>(&ImageCodeSize), 1);

      std::vector<BYTE> InData;
      BYTE Size;

      //Decompress LZW
      INT InPos = 0, CodeSize = ImageCodeSize + 1, bufpos = 0;
      const INT MAX_BITS = 12, CODE_CLEAR = 1 << ImageCodeSize, CODE_TERM = CODE_CLEAR + 1, MAX_CODES = 1 << MAX_BITS;
      BYTE Accum = 0, BitPos = 8;
      static INT Cnt = 0;

      do
      {
        f.read((CHAR *)&Size, 1);
        if (f.gcount() != 1 || Size == 0)
          break;
        INT buf_pos = static_cast<INT>(InData.size());
        InData.resize(buf_pos + Size);
        f.read((CHAR *)&InData[buf_pos], Size);
      } while (Size != 0);

      struct
      {
        INT Pref, Suf;
      } Dict[MAX_CODES] {};
      INT DictSize = CODE_CLEAR + 2;

      auto ReadBits = [&]( INT BitsCount ) -> INT
      {
        INT Bits = 0;

        for (INT i = 0; i < BitsCount; i++)
        {
          if (BitPos > 7)
          {
            CHAR byte = 0;

            byte = InData[bufpos++];

            Accum = byte;
            BitPos = 0;
          }
          INT bit = (Accum >> BitPos++) & 1;

          Bits |= (bit << i);
        }
        return Bits;
      };
      auto Out = [&]( INT Bit ) -> VOID
      {
          if (Cnt >= W * H)
              Cnt = 0;

          if (IsAnimated && Bit != TransColor || !IsAnimated)
              Pixels[Cnt] = ((LocalPalette[Bit][0] << 16) | (LocalPalette[Bit][1] << 8) | (LocalPalette[Bit][2]));
          else
          {
              INT x = Cnt % W;
              INT y = Cnt / W;
        
              INT globalX = X0 + x;
              INT globalY = Y0 + y;
        
              if (globalX >= 0 && globalX < GFX_W && globalY >= 0 && globalY < GFX_H)
              {
                  DWORD backgroundColor = Frame[globalY][globalX];
                  Pixels[Cnt] = backgroundColor;
              }
              else
                  Pixels[Cnt] = 0;
          }
          Cnt++;
      };

      INT Cur = ReadBits(CodeSize), Next = 0;

      while (Cur == CODE_TERM || Cur == CODE_CLEAR)
      {
        Cur = ReadBits(CodeSize);
      }

      INT buf_pos = InData.size();

      while (bufpos <= buf_pos)
      {
        Next = ReadBits(CodeSize);
        if (Next == CODE_TERM)
        {
          Out(Dict[Cur].Suf);
          Cnt = 0;
          if (frames > 0)
          {
          }
          Render(Pixels, W, H, X0, Y0);
          if (IsAnimated && DelayTime > 0)
            Sleep(DelayTime * 10); 
          frames++;
          break;
        }
        else if (Next == CODE_CLEAR)
        {
          DictSize = CODE_CLEAR + 2;
          CodeSize = ImageCodeSize + 1;
          Cur = ReadBits(CodeSize);
          Out(Cur);
        }
        else
        {
          static BYTE DecodeStack[MAX_CODES];
          INT i = 0, Code = Next;
        
          if (Code >= DictSize)
            i = 1, Code = Cur;
          while (Code >= CODE_CLEAR)
          {
            if (i < MAX_CODES && Code < MAX_CODES)
            {
              DecodeStack[i++] = Dict[Code].Suf;
              Code = Dict[Code].Pref;
            }
            if (Code < MAX_CODES && Dict[Code].Pref >= Code)
              break;
          }
          DecodeStack[i++] = Code;
          if (Next >= DictSize)
            DecodeStack[0] = DecodeStack[i - 1];
          while (i-- > 0)
            Out(DecodeStack[i]);
          if (DictSize < MAX_CODES)
            Dict[DictSize++] = {Cur, Code};
          if (DictSize < MAX_CODES)
          {
            if (DictSize >= (1 << CodeSize) && CodeSize < MAX_BITS)
              CodeSize++;
          }
          Cur = Next;
        }
      }
    }
    else if (ch == '!')
    {
      static BOOL first_open = TRUE;

      f.get(ch);

      if (UCHAR(ch) == 0xFF && first_open)
      {
        first_open = FALSE;

        EXT_APPLICATION ea {};

        f.read(reinterpret_cast<CHAR *>(&ea), sizeof(EXT_APPLICATION));

        std::string Name {};
        std::string Version {};
        
        Name = std::string(ea.Name, 8);
        Version = std::string(ea.Version, 4);

        while (ch != 0)
          f.get(ch);
      }
      else if (UCHAR(ch) == 0xF9)
      {
        EXT_GRAPHICS eg {};
        BYTE Size;

        f.read(reinterpret_cast<CHAR *>(&Size), 1);
        f.read(reinterpret_cast<CHAR *>(&eg), Size);
        IsAnimated = TRUE;
        DelayTime = eg.DelayTime;
        LastTransColor = TransColor;
        TransColor = eg.TransColor;
      }
    }
    else if (ch == ';')
      break;
  }
  f.close();
} /* End of 'Open' function */

/* END OF 'gif.cpp' FILE */                                 
