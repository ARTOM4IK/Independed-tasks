/* Arsentev Artemy, 09-4, 29.10.2024 */

#include <stdio.h>
#include <stdlib.h>
#include "PCX.H"

void DrawPCX( char *FileName, int X0, int Y0 )
{
  FILE *F;
  int p = 0, i = 0, x = 0, y = 0,
    H, W, rep;
  BYTE Pal[256][3], R, G, B, v = 0, bt, **Planes;

  if ((F = fopen(FileName, "rb")) != NULL)
  {
    pcxFILEHEAD Head;
  
    if (fread(&Head, sizeof(pcxFILEHEAD), 1, F) == 1 &&
        Head.Manuf == 0x0A && Head.Encode == 1)
    {
      int BPL = Head.BytesPerLine;
  
      if ((Planes = malloc(sizeof(BYTE *) * Head.PlanesAmount)) != NULL)
      {
        W = Head.X2 - Head.X1 + 1;                      
        H = Head.Y2 - Head.Y1 + 1;

        for (p = 0; p < Head.PlanesAmount; p++)
        {
          Planes[p] = malloc(sizeof(BYTE *) * Head.BytesPerLine);
        }

        for (p = 0; p < Head.PlanesAmount; p++)
        {
          fseek(F, -769, SEEK_END);
          fread(&bt, 1, 1, F);
          fread(&Pal, 3, 256, F);
          fseek(F, sizeof(pcxFILEHEAD), SEEK_SET);

          while (y < H)
          {
            bt = fgetc(F);
            if ((bt >> 6) == 3)
            {
              rep = bt & 63;
              bt = fgetc(F);
            }
            else
              rep = 1;             
            while (rep-- > 0)
            {
              Planes[p][x] = bt;
              x++;
              if (x >= Head.BytesPerLine)
              {
                x = 0;
                p++;
                if (p >= Head.PlanesAmount)
                {
                  for (i = 0; i < W; i++)
                  {
                    if (Head.PlanesAmount == 1 && Head.BitsPerPixel == 24)
                      R = Planes[0][i * 3], G = Planes[0][i * 3 + 1], B = Planes[0][i * 3 + 2];
                    else if (Head.PlanesAmount == 3 && Head.BitsPerPixel == 8)
                      R = Planes[0][i], G = Planes[1][i], B = Planes[2][i];
                    else if (Head.PlanesAmount == 1 && Head.BitsPerPixel == 8)
                    {
                        v = Planes[0][i];
                        R = Pal[v][0], G = Pal[v][1], B = Pal[v][2];
                    }
                    else if (Head.PlanesAmount == 1 && Head.BitsPerPixel == 4)
                    {
                      v = (Planes[0][i >> 1] >> ((1 - (i & 1)) << 2)) & 0x0F;
                      R = Head.Pal[3 * v + 0], G = Head.Pal[3 * v + 1], B = Head.Pal[3 * v + 2];
                    }
                    else if (Head.PlanesAmount == 1 && Head.BitsPerPixel == 1)
                    {
                      v = (Planes[0][i >> 3] >> (7 - (i & 7))) & 1;
                      R = Head.Pal[3 * v + 0], G = Head.Pal[3 * v + 1], B = Head.Pal[3 * v + 2];
                    }
                    else if (Head.PlanesAmount == 4 && Head.BitsPerPixel == 1)
                    {
                      v = 0;
                      for (p = 0; p < 4; p++)
                        v |= ((Planes[p][i >> 3] >> (7 - (i & 7))) & 1) << p;
                      R = Head.Pal[v * 3 + 0];
                      G = Head.Pal[v * 3 + 1];
                      B = Head.Pal[v * 3 + 2];
                    }
                    GFX_PutPixel(X0 + i, Y0 + y, GFX_RGB(R, G, B));
                  }
                  y++;
                  p = 0;
                }
              }
            }
          }
        }

        for (p = 0; p < Head.PlanesAmount; p++)
          free(Planes[p]);
        free(Planes);
      }
    }
  }
  fclose(F);
}