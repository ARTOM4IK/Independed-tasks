/* FILE NAME: rndtex.c
 * PROGRAMMER: AA4
 * LAST UPDATE: 31.01.2025
 * PURPOSE: 3D animation project.
 *          Texture module.
 */

#include <stdio.h>
#include "rndres.h"

/***
 * Texture stock handle
 ***/
 
/* Textures stock */
aa4TEXTURE AA4_RndTextures[AA4_MAX_TEXTURES]; /* Array of textures */
INT AA4_RndTexturesSize;                      /* Textures array store size */
 
/* Add texture to stock function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size in pixels:
 *       INT W, H;
 *   - number of color components:
 *       INT C;
 *   - texture pixels data:
 *       VOID *Bits;
 * RETURNS:
 *   (INT) texture stock number (-1 if error is occured).
 */
INT AA4_RndTexAddImg( CHAR *Name, INT W, INT H, INT C, VOID *Bits )
{
  INT mips;
 
  if (AA4_RndTexturesSize >= AA4_MAX_TEXTURES)
    return -1;
  /* Setup OpenGL texture */
  glGenTextures(1, &AA4_RndTextures[AA4_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, AA4_RndTextures[AA4_RndTexturesSize].TexId);
  mips = log(W > H ? W : H) / log(2);
  mips = mips < 1 ? 1 : mips;
  glTexStorage2D(GL_TEXTURE_2D, mips,
    C == 4 ? GL_RGBA8 : C == 3 ? GL_RGB8 : GL_R8, W, H);

  if (Bits != NULL)
  {
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, W, H,
                    C == 4 ? GL_BGRA : C == 3 ? GL_BGR : GL_LUMINANCE, GL_UNSIGNED_BYTE, Bits);
  }
  glGenerateMipmap(GL_TEXTURE_2D);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glBindTexture(GL_TEXTURE_2D, 0);

  /* Add to stock */
  AA4_RndTextures[AA4_RndTexturesSize].W = W;
  AA4_RndTextures[AA4_RndTexturesSize].H = H;
  strncpy(AA4_RndTextures[AA4_RndTexturesSize].Name, Name, AA4_STR_MAX - 1);

  return AA4_RndTexturesSize++;
} /* End of 'AA4_RndTexAddImg' function */
 
/* Add texture from file to stock function.
 * ARGUMENTS:
 *   - texture file name:
 *       CHAR *FileName;
 * RETURNS:
 *   (INT) texture stock number (-1 if error is occured).
 */
INT AA4_RndTexAddFromFile( CHAR *FileName )
{
  FILE *F;
  INT ret = -1;
  HBITMAP hBm;
 
  if ((hBm = LoadImage(NULL, FileName, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_CREATEDIBSECTION)) != NULL)
  {
    BITMAP Bm;
    GetObject(hBm, sizeof(BITMAP), &Bm);
    if (Bm.bmBitsPixel == 24 || Bm.bmBitsPixel == 32 || Bm.bmBitsPixel == 8)
      ret = AA4_RndTexAddImg(FileName, Bm.bmWidth, Bm.bmHeight, Bm.bmBitsPixel >> 3, Bm.bmBits); 
    DeleteObject(hBm);
    return ret;
  }
  if ((F = fopen(FileName, "rb")) != NULL)
  {
    INT w = 0, h = 0, flen, components = -1;
    BYTE *mem;
 
    fread(&w, 2, 1, F);
    fread(&h, 2, 1, F);
 
    fseek(F, 0, SEEK_END);
    flen = ftell(F);
    fseek(F, 4, SEEK_SET);
 
    if (4 + w * h * 4 == flen)
      /* Case of .G32 format */
      components = 4;
    else if (4 + w * h * 3 == flen)
      /* Case of .G24 format */
      components = 3;
    else if (4 + w * h == flen)
      /* Case of .GSM format */
      components = 1;
 
    if (components != -1 && (mem = malloc(w * h * components)) != NULL)
    {
      fread(mem, components, w * h, F);
      ret = AA4_RndTexAddImg(FileName, w, h, components, mem); 
      free(mem);
    }
    fclose(F);
  }
  return ret;
} /* End of 'AA4_RndTexAddFromFile' function */

  /* Texture handle initialization function.
   * ARGUMENTS: None.
   * RETURNS: None.
   */
VOID AA4_RndTexInit( VOID )
{
  AA4_RndTexturesSize = 0;
} /* End of 'AA4_RndTexInit' function */
 
/* Texture handle deinitialization function.
 * ARGUMENTS: None.
 * RETURNS: None.
 */
VOID AA4_RndTexClose( VOID )
{
  INT i;
 
  for (i = 0; i < AA4_RndTexturesSize; i++)
    glDeleteTextures(1, &AA4_RndTextures[i].TexId);
  AA4_RndShadersSize = 0;
} /* End of 'AA4_RndTexClose' function */

/* Add texture by OpenGL Low-Level format to stock function.
 * ARGUMENTS:
 *   - texture name:
 *       CHAR *Name;
 *   - texture size in pixels:
 *       INT W, H;
 *   - OpenGL texture element data type:
 *       INT GLType;
 * RETURNS:
 *   (INT) texture stock number (-1 if error is occured).
 */
INT AA4_RndTexAddFmt( CHAR *Name, INT W, INT H, INT GLType )
{
  if (AA4_RndTexturesSize >= AA4_MAX_TEXTURES)
    return -1;

  /* Setup OpenGL texture */
  glGenTextures(1, &AA4_RndTextures[AA4_RndTexturesSize].TexId);
  glBindTexture(GL_TEXTURE_2D, AA4_RndTextures[AA4_RndTexturesSize].TexId);
  glTexStorage2D(GL_TEXTURE_2D, 1, GLType, W, H);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glBindTexture(GL_TEXTURE_2D, 0);

  /* Add to stock */
  AA4_RndTextures[AA4_RndTexturesSize].W = W;
  AA4_RndTextures[AA4_RndTexturesSize].H = H;
  strncpy(AA4_RndTextures[AA4_RndTexturesSize].Name, Name, AA4_STR_MAX - 1);

  return AA4_RndTexturesSize++;
} /* End of 'AA4_RndTexAddFmt' function */

/* END OF 'rndtex.c' FILE */
