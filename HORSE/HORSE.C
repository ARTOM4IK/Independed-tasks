/* Arsentev Artemy, 09-4, 06.11.2024 */

#include <stdio.h>
#include <stdlib.h>

#include "HORSE.H"

static int
  Dx[8] = {1, 2, 2, 1, -1, -2, -2, -1},
  Dy[8] = {-2, -1, 1, 2, 2, 1, -1, -2};


int Go( int X, int Y, int Pos )
{
  int i, newx, newy;

  if (Pos == N * M + 1)
    return 1;

  for (i = 0; i < 8; i++)
  {
    newx = X + Dx[i];
    newy = Y + Dy[i];
   if (newx >= 0 && newx < M &&
       newy >= 0 && newy < N &&
       A[newy][newx] == 0)
    {
     A[newy][newx] = Pos;
     if (Go(newx, newy, Pos + 1))
       return 1; 
     A[newy][newx] = 0;
    }
  }
  return 0;
}