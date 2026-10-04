/* Arsentev Artemy, 09-4, 10.10.2024 */

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "DSORT.H"

static UINT64 seed64 = 1;

unsigned randu64( void )
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
/*
UINT64 randu64( void )
{
  UINT64 w;

  w = rand() & 0x7FFF;
  w <<= 15;
  w |= rand() & 0x7FFF;
  w <<= 15;
  w |= rand() & 0x7FFF;
  w <<= 15;
  w |= rand() & 0x7FFF;
  w <<= 15;
  w |= rand() & 0x7F;
  w <<= 4;
  return w;
}
*/
void Fill( UINT64 *a, int size )
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

void DigitalSort256( UINT64 *a, int size )
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
/*    for (i = 0; i < size; i++)
        b[offset[((BYTE *)&a[i])[x]++] = a[i];
*/

    /*counting from b to a*/
    memcpy(a, b, sizeof(UINT64) * size);
  }
  free(b);
}

int CheckSort( UINT64 *a, int size )
{
  int i;

  for (i = 0; i < size - 1; i++)
    if (a[i] > a[i + 1])
      return 0;
  return 1;
}


void PrintArray( UINT64 *a, int size )
{
  int i;

  for (i = 0; i < size; i++)
    printf("%llu ", a[i]);
  printf("\n");
}