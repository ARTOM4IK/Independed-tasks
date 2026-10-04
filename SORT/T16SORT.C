/* Arsentev Artemy, 09-4, 11.10.2024 */

#include <stdio.h>
#include <time.h>
#include "SORT.H"

#define MAX 30000

void main( void )
{
  static UINT64 a[MAX];
  int si, fi;
  long t;

  void (*Sort[])( UINT64 *a, int n) = 
  {
    DigitalSort, MergeSort, QuickSort, HeapSort
  };

  void (*Fill[])( UINT64 *a, int n) = 
  {
    FillIncr, FillDecr, FillEq, FillMostly, FillLevels, FillRand
  };

  char * SortName[] = {"DigitalSort", "MergeSort", "QuickSort", "HeapSort"};
  char * FillName[] = {"FillIncr", "FillDecr", "FillEq", "FillMostly", "FillLevels", "FillRand"};

  for (si = 0; si < sizeof(Sort) / sizeof(Sort[0]); si++)
  {
    printf("Sort %s\n", SortName[si]);

    for (fi = 0; fi < sizeof(Fill) / sizeof(Fill[0]); fi++)
    {
      Fill[fi](a, MAX);
      t = clock();
      Sort[si](a, MAX);
      t = clock() - t;
      if (CheckSort(a, MAX))
        printf("%s %10.5f \n", FillName[fi], t / (double)CLOCKS_PER_SEC);
      else
        printf("FAIL\n");
    }
  }

  getchar();
}