/*************************************************************
 * Copyright (C) 2025
 *    Computer Graphics Support Group of 30 Phys-Math Lyceum
 *************************************************************/
 
/* FILE NAME   : fnt.cpp
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

#include "arvk.h"

/* Load font from .G3DF file function.
 * ARGUMENTS:
 *   - font file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (BOOL) TRUE if success, FALSE otherwise.
 */
arvk::font& arvk::font::Load(const std::string& FileName)
{
  std::ifstream F(FileName, std::ios::binary);
  if (!F.is_open())
    return *this;

  DWORD Sign;
  F.read(reinterpret_cast<char*>(&Sign), 4);
  if (Sign != *(DWORD*)"G3DF")
  {
    F.close();
    return *this;
  }

  F.read(reinterpret_cast<char*>(&LineH), sizeof(DWORD));
  F.read(reinterpret_cast<char*>(&BaseH), sizeof(DWORD));
  F.read(reinterpret_cast<char*>(AdvanceX), sizeof(FLT) * 256);

  vertex::std CharVertices[256][4];
  F.read(reinterpret_cast<char*>(CharVertices), sizeof(vertex::std) * 256 * 4);

  DWORD W, H;
  F.read(reinterpret_cast<char*>(&W), 4);
  F.read(reinterpret_cast<char*>(&H), 4);

  std::vector<DWORD> Tex(W * H);
  F.read(reinterpret_cast<char*>(Tex.data()), W * H * 4);
  F.close();

  // Создание материала
  Mat = Rnd->MtlCreate("font");

  //Mat = anim::Get()->material_manager::Find("default");
  if (Mat != nullptr)
  {
    //Mat->Name = FileName;
    Mat->Tex[0] = Rnd->TexCreate(FileName, W, H, 4, reinterpret_cast<BYTE*>(Tex.data()));
    //Mat->Shd = anim::Get()->ShdCreate("font");
    Mat->Shd = Rnd->shader_manager::Find("font");
  }

  for (INT i = 0; i < 256; i++)
  {
      std::span<vertex::std> vertices(CharVertices[i], 4);

      std::span<INT> indices;
    
      prim* newPrim = Rnd->PrimCreate(prim_type::STRIP, vertices, indices);
      if (newPrim != nullptr)
      {
          Chars[i] = newPrim;
          Chars[i]->Mtl = Mat;
      }
  }

  return *this;
} /* End of 'Load' function */

VOID arvk::font::Draw( const CHAR *Str, vec3 Pos, FLT Size )
{
  if (Mat == nullptr)
    return;

  FLT startx = Pos.X;

  while (*Str != 0)
  {
    if (*Str == '\n')
    {
      Pos.X = startx;
      Pos.Y -= Size;
    }
    else if ((UCHAR)*Str < 256)
    {
      matr transform = matr::Scale(vec3(Size, Size, 1)) * matr::Translate(Pos);
      Rnd->Draw(Chars[(UCHAR)*Str], transform);
      Pos.X += AdvanceX[(UCHAR)*Str] * Size;
    }
    Str++;
  }
} /* End of 'Draw' function */

 /* END OF 'buf.cpp' FILE */
