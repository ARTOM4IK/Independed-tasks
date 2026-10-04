/* Arsentev Artemy, 09-4, 11.10.2024 */

#include <stdio.h>
#include <stdlib.h>
#include "SORT.H"

UINT64 Randu64Adv( void )
{
  UINT64 w;

  w = rand() & 0x7FFF;
  w <<= 15;
  w |= rand() & 0x7FFF;
  w <<= 15;
  w |= rand() & 0x7FFF;
  w <<= 15;
  w |= rand() & 0x7FFF;
  w <<= 4;
  w |= rand() & 0x7F;
  return w;
}

void FillRandAdv( UINT64 *a, int size )
{
  int i;

  for (i = 0; i < size; i++)
    a[i] = Randu64Adv();
}


void FillIncr( UINT64 *a, int size )
{
  int i;

  for (i = 1, a[0] = randu64(); i < size; i++)
    a[i] = a[i - 1] + randu64() % 18 + 1;
}

void FillDecr( UINT64 *a, int size )
{
  int i;

  for (i = 1, a[0] = randu64(); i < size; i++)
    a[i] = a[i - 1] - randu64() % 18 - 1;
}

void FillEq( UINT64 *a, int size )
{
  int i;

  for (i = 1, a[0] = randu64(); i < size; i++)
    a[i] = a[0];
}

int CheckSort( UINT64 *a, int size )
{
  int i;

  for (i = 0; i < size - 1; i++)
    if (a[i] > a[i + 1])
      return 0;
  return 1;
}

void Swap( UINT64 *a, UINT64 *b )
{
  UINT64 tmp = *a;
  *a = *b;
  *b = tmp;
}

void FillMostly( UINT64 *a, int size )
{
  int i;

  FillIncr(a, size);

  for (i = 0; i < size; i++)
    Swap(&a[randu64() % size], &a[randu64() % size]);
}

void FillLevels( UINT64 *a, int size )
{
  UINT64 ds[10] = {47, 30, 28, 15, 52, 14, 88, 64, 32, 1};
  int i;

  for (i = 0; i < size; i++)
    a[i] = ds[randu64() % 10];

  for (i = 0; i < size; i++)
    Swap(&a[randu64() % size], &a[randu64() % size]);
}

void OutMas( UINT64 *a, int size )
{
  int i;

  for (i = 0; i < size; i++)
    printf("%llu ", a[i]);
  printf("\n");
}