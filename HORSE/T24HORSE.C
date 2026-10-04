/* Arsentev Artemy, 09-4, 06.11.2024 */

#include <stdio.h>
#include <stdlib.h>

#include "HORSE.H"

void main( void )
{
  int i, j;

  A[0][0] = 1;

  if(Go(0, 0, 2));
  
  for (i = 0; i < N; i++)
  {
    for (j = 0; j < M; j++)
      printf(" %3d", A[i][j]);
    printf("\n");
  }
  
  getchar();
}