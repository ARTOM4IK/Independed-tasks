/* Arsentev Artemy, 09-4, 11.10.2024 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "SORT.H"

static UINT64 seed64 = 1;

UINT64 randu64( void )
{
  UINT64 x = seed64;

  x ^= x << 13;
  x ^= x >> 7;
  x ^= x << 17;

  return seed64 = x;
}

void srandu64( UINT64 SeedValue )
{
  seed64 = SeedValue;
}

void FillRand( UINT64 *a, int size )
{
  int i;

  srandu64(time(NULL));

  for (i = 0; i < size; i++)
    a[i] = randu64();
}

void DigitalSort( UINT64 *a, int size )
{
  UINT64 *b;
  int counter[10], offset[10], i, digit_count;
  UINT64 pow10;

  if ((b = malloc(sizeof(UINT64) * size)) == NULL)
    return;

  for (digit_count = 0, pow10 = 1; digit_count < 20 ; digit_count++, pow10 *= 10)
  {
    /*fill 0 counter*/
    memset(counter, 0, sizeof(counter));

    /*counting meets*/
    for (i = 0; i < size; i++)
      counter[a[i] / pow10 % 10]++;

    /*offset counting*/
    for (offset[0] = 0, i = 1; i < 10; i++)
      offset[i] = offset[i - 1] + counter[i - 1];

    /*counting in b*/
    for (i = 0; i < size; i++)
      b[offset[a[i] / pow10 % 10]++] = a[i];

    /*counting from b to a*/
    memcpy(a, b, sizeof(UINT64) * size);
  }
  free(b);
}