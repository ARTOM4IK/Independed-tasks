/* Arsentev Artemy, 09-4, 10.10.2024 */

#include <stdio.h>
#include <time.h>
#include "DSORT.H"

#define MAX 30000

void main( void )
{
  static UINT64 m[MAX];
  clock_t t;

  Fill(m, MAX);

  t = clock();
  
  DigitalSort(m, MAX);

  t = clock() - t;

//  PrintArray(m, MAX);
  if (CheckSort(m, MAX))
    printf("Ok, %.5f", (double)t / CLOCKS_PER_SEC);
  else
    printf("Fail, %.5f", (double)t / CLOCKS_PER_SEC);

  getchar();
}