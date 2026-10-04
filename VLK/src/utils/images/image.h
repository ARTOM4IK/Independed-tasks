/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : image.h
 * PURPOSE     : Ray Tracing project.
 *               Precompiled header definition module.
 * PROGRAMMER  : CGSG-SummerCamp'2025.
 *               Artmey V. Arsentev.
 * LAST UPDATE : 23.07.2025.
 * NOTE        : Module namespace 'virt'.
 *
 * No part of this file may be changed without agreement of
 * Computer Graphics Support Group of 30 Phys-Math Lyceum
 */

#ifndef __image_h_
#define __image_h_

#include "def.h"

namespace arvk
{
  /* Image representation class */
  class image
  {
  private:
    // Image size in pixels
    INT Width = 0, Height = 0;
    // Windows Imaging Component factory
    IWICImagingFactory2 *WicFactory;
    // Image pixel data
    std::vector<BYTE> Pixels;
  public:
    // Rows access pointer by DWORD
    std::vector<DWORD *> RowsD;
    // Rows access pointer by BYTE quads
    std::vector<BYTE (*)[4]> RowsB;
 
    // Image size references
    const INT &W = Width, &H = Height;
 
    /* Class default construtor */
    image( VOID )
    {
    } /* End of 'image' function */
     
    /* Load image from memory function.
     * ARGUMENTS:
     *   - image data in memory:
     *       const BYTE *Data;
     *   - data size in bytes:
     *       SIZE_T DataSize;
     * RETURNS:
     *   (BOOL) success flag.
     */
    BOOL LoadFromMemory( const BYTE *Data, SIZE_T DataSize )
    {
        BOOL isok = FALSE;
        
        if (WicFactory == nullptr)
        {
            CoInitialize(nullptr);
            CoCreateInstance(CLSID_WICImagingFactory2, nullptr, CLSCTX_ALL,
                IID_PPV_ARGS(&WicFactory));
        }
        
        if (WicFactory != nullptr && Data != nullptr && DataSize > 0)
        {
            // Create stream from memory
            IWICStream *Stream = nullptr;
            WicFactory->CreateStream(&Stream);
            
            if (Stream != nullptr)
            {
                // Initialize stream with memory data
                Stream->InitializeFromMemory(const_cast<BYTE*>(Data), DataSize);
                
                // Create decoder from stream
                IWICBitmapDecoder *Decoder = nullptr;
                WicFactory->CreateDecoderFromStream(Stream, nullptr,
                    WICDecodeMetadataCacheOnDemand, &Decoder);
                
                if (Decoder != nullptr)
                {
                    // Полностью аналогично существующему конструктору из файла
                    IWICBitmapFrameDecode *Frame = nullptr;
                    Decoder->GetFrame(0, &Frame);
                    UINT fw = 0, fh = 0;
                    
                    if (Frame != nullptr)
                    {
                        Frame->GetSize(&fw, &fh);
                        if (fw != 0 && fh != 0)
                        {
                            IWICFormatConverter *Convert = nullptr;
                            WicFactory->CreateFormatConverter(&Convert);
                            
                            if (Convert != nullptr)
                            {
                                Convert->Initialize(Frame, GUID_WICPixelFormat32bppBGRA,
                                    WICBitmapDitherTypeNone, nullptr, 0.0,
                                    WICBitmapPaletteTypeCustom);
                                
                                Convert->GetSize(&fw, &fh);
                                Pixels.resize(fw * fh * 4);
                                
                                if (fw != 0 && fh != 0)
                                {
                                    WICRect Rect {0, 0, static_cast<INT>(fw), static_cast<INT>(fh)};
                                    Convert->CopyPixels(&Rect, fw * 4, fw * fh * 4,
                                        Pixels.data());
                                    Width = fw;
                                    Height = fh;
                                    isok = TRUE;
                                }
                                Convert->Release();
                            }
                        }
                        Frame->Release();
                    }
                    Decoder->Release();
                }
                Stream->Release();
            }
        }
        
        if (!isok)
        {
            // Fallback: попробовать как BMP или другие форматы
            // (можно добавить аналогично существующему конструктору)
        }
        
        // Setup row pointers
        if (isok)
        {
            RowsD.resize(Height);
            RowsB.resize(Height);
            
            for (INT i = 0; i < Height; i++)
            {
                RowsD[i] = (DWORD *)&Pixels[i * Width * 4];
                RowsB[i] = (BYTE (*)[4])&Pixels[i * Width * 4];
            }
        }
        
        return isok;
    }
    
    /* Load image from memory (vector version) function.
     * ARGUMENTS:
     *   - image data vector:
     *       const std::vector<BYTE> &Data;
     * RETURNS:
     *   (BOOL) success flag.
     */
    BOOL LoadFromMemory( const std::vector<BYTE> &Data )
    {
        if (Data.empty())
            return FALSE;
        return LoadFromMemory(Data.data(), Data.size());
    }

    /* Class construtor.
     * ARGUMENTS:
     *   - image file name:
     *       const std::string &FileName;
     */
    image( const std::string &FileName )
    {
      BOOL isok {};
      if (WicFactory == nullptr)
      {
        CoInitialize(nullptr);
        CoCreateInstance(CLSID_WICImagingFactory2, nullptr, CLSCTX_ALL,
          IID_PPV_ARGS(&WicFactory));
      }
 
      // Load through Window Image Component
      if (WicFactory != nullptr)
      {
        std::wstring FileNameW {FileName.begin(), FileName.end()};
        IWICBitmapDecoder *Decoder {};
 
        // Create decoder (loader)
        WicFactory->CreateDecoderFromFilename(FileNameW.c_str(), nullptr,
          GENERIC_READ, WICDecodeMetadataCacheOnDemand, &Decoder);
        if (Decoder != nullptr)
        {
          IWICBitmapFrameDecode *Frame {};
          Decoder->GetFrame(0, &Frame);
          UINT fw = 0, fh = 0;
          if (Frame != nullptr)
          {
            Frame->GetSize(&fw, &fh);
            if (fw != 0 && fh != 0)
            {
              // Converting image format to standard - RGBA with 8-bits per pixel
              IWICFormatConverter *Convert {};
              WicFactory->CreateFormatConverter(&Convert);
              if (Convert != nullptr)
              {
                // Converter initialization
                Convert->Initialize(Frame, GUID_WICPixelFormat32bppBGRA,
                  WICBitmapDitherTypeNone, nullptr, 0.0,
                  WICBitmapPaletteTypeCustom);
 
                // Size checking
                Convert->GetSize(&fw, &fh);
                Pixels.resize(fw * fh * 4);
                if (fw != 0 && fh != 0)
                {
                  // Copying image pixels to container pixel array
                  WICRect Rect {0, 0, static_cast<INT>(fw), static_cast<INT>(fh)};
                  Convert->CopyPixels(&Rect, fw * 4, fw * fh * 4,
                    (BYTE *)Pixels.data());
                  Width = fw;
                  Height = fh;
                  isok = TRUE;
                }
                Convert->Release();
              }
            }
            Frame->Release();
          }
          Decoder->Release();
        }
      }
      if (!isok)
      {
        if (HBITMAP hBm; (hBm = (HBITMAP)LoadImage(nullptr, FileName.c_str(), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE)) != nullptr)
        {
          // Case of BMP file
 
          // Create contextes
          HDC hDC = GetDC(nullptr);
          HDC hMemDC = CreateCompatibleDC(hDC);
          HDC hMemDC1 = CreateCompatibleDC(hDC);
          ReleaseDC(nullptr, hDC);
 
          SelectObject(hMemDC, hBm);
          BITMAP bm;
          GetObject(hBm, sizeof(bm), &bm);
 
          BITMAPINFOHEADER bmih {}; // memset(&bmih, 0, sizeof(bmih));
          bmih.biSize = sizeof(BITMAPINFOHEADER);
          bmih.biBitCount = 32;                  // BGRx - DWORD
          bmih.biPlanes = 1;                     // always
          bmih.biCompression = BI_RGB;           // 0 - no compression */
          bmih.biWidth = bm.bmWidth;             // width
          bmih.biHeight = -bm.bmHeight;          // height + first coded row is 0
          bmih.biSizeImage = bm.bmWidth * bm.bmHeight * 4; // image size in bytes
 
          VOID *Bits;
          HBITMAP hImage = CreateDIBSection(nullptr, (BITMAPINFO *)&bmih,
                             DIB_RGB_COLORS, &Bits, nullptr, 0);
          SelectObject(hMemDC1, hImage);
 
          // Draw load image to DIB
          BitBlt(hMemDC1, 0, 0, Width, Height, hMemDC, 0, 0, SRCCOPY);
          DeleteDC(hMemDC);
          DeleteDC(hMemDC1);
 
          Pixels.resize(bmih.biSizeImage);
          CopyMemory(&Pixels[0], Bits, bmih.biSizeImage); // Pixels.data()
          DeleteObject(hImage);
          DeleteObject(hBm);
 
          // Make alpha channel
          for (INT i = 3; i < Width * Height * 4; i += 4)
            Pixels[i] = 255;
        }
        else
        {
          std::fstream f(FileName, std::fstream::in | std::fstream::binary);
 
          if (f.is_open())
          {
            // Case of G24/G32
            INT fw = 0, fh = 0;
            f.read((CHAR *)&fw, 2);
            f.read((CHAR *)&fh, 2);
            f.seekg(0, std::fstream::end);
            INT flen = f.tellg();
            if (flen == 4 + fw * fh * 3)
            {
              // G24
              f.seekg(4, std::fstream::beg);
              Pixels.resize(fw * fh * 4);
              for (INT r = 0, p = 0; r < fh; r++)
                for (INT c = 0; c < fw; c++)
                {
                  BYTE rgb[3];
                  f.read((CHAR *)rgb, 3);
                  Pixels[p++] = rgb[0];
                  Pixels[p++] = rgb[1];
                  Pixels[p++] = rgb[2];
                  Pixels[p++] = 255;
                }
            }
            else if (flen == 4 + fw * fh * 4)
            {
              // G32
              f.seekg(4, std::fstream::beg);
              Pixels.resize(fw * fh * 4);
              Width = fw;
              Height = fh;
              f.read((CHAR *)Pixels.data(), 4 * fw * fh);
            }
            f.close();
          }
        }
      }
      // Setup row pointers
      INT i;
      RowsD.resize(Height);
      i = 0;
      for (auto &r : RowsD)
        r = (DWORD *)&Pixels[i++ * Width * 4];
      RowsB.resize(Height);
      i = 0;
      for (auto &r : RowsB)
        r = (BYTE (*)[4])&Pixels[i++ * Width * 4];
    } /* End of 'image' function */
 
    /* Class copying construtor.
     * ARGUMENTS:
     *   - const reference to copy object:
     *       const image &Img;
     */
    image( const image &Img ) :
      Width(Img.Width), Height(Img.Height), 
      W(Width), H(Height), Pixels(Img.Pixels)
    {
      // Setup row pointers
      INT i;
      RowsD.resize(Height);
      i = 0;
      for (auto &r : RowsD)
        r = (DWORD *)&Pixels[i++ * Width * 4];
      RowsB.resize(Height);
      i = 0;
      for (auto &r : RowsB)
        r = (BYTE (*)[4])&Pixels[i++ * Width * 4];
    } /* End of 'image' function *
 
    /* Class move construtor.
     * ARGUMENTS:
     *   - move reference to copy object:
     *       image &&Img;
     */
    image( image &&Img ) :
      Width(Img.Width), Height(Img.Height), 
      W(Width), H(Height), Pixels(std::move(Img.Pixels))
    {
      // Setup row pointers
      INT i;
      RowsD.resize(Height);
      i = 0;
      for (auto &r : RowsD)
        r = (DWORD *)&Pixels[i++ * Width * 4];
      RowsB.resize(Height);
      i = 0;
      for (auto &r : RowsB)
        r = (BYTE (*)[4])&Pixels[i++ * Width * 4];
      Img.Width = Img.Height = 0;
    } /* End of 'image' function */
  }; /* End of image class */
}

#endif /* __image_h_ */

/* END OF 'image.h' FILE */
