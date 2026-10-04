/* Arsentev Artemy, 09-4, 07.10.2024 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void FillRand( short *a, int size )
{
  int i;

  srand(time(NULL));

  for (i = 0; i < size; i++)
    a[i] = rand() % 193 - 102;
}

void SortCounting( short *a, int size )
{
  short counter[193];
  int i, k, j;

  for (i = 0; i < 193; i++)
    counter[i] = 0;

  for (i = 0; i < size; i++)
    if (a[i] >= -102 && a[i] <= 90)
      counter[a[i] + 102]++;

  for (k = 0, i = 0; i < 193; i++)
    for (j = 0; j < counter[i]; j++)
      a[k++] = i - 102;

}

int CheckSort( short *a, int size )
{
  int i;

  for (i = 0; i < size - 1; i++)
    if (a[i] > a[i + 1])
      return 0;
  return 1;
}

#define MAX 30000

void main( void )
{
  short a[MAX];

  FillRand(a, MAX);
  SortCounting(a, MAX);
  if (CheckSort(a, MAX))
    printf("Ok");
  else
    printf("Fail");

  getchar();
}