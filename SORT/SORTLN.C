/* Arsentev Artemy, 09-4, 11.10.2024 */

#include <stdio.h>
#include "SORT.H"

static UINT64 *b;

static void MergeSortRec( UINT64 *a, int n )
{
  int m, i, j, k;

  if (n < 2)
    return;

  m = n / 2;

  MergeSortRec(a, m);
  MergeSortRec(a + m, n - m);

  for (k = 0, i = 0, j = m; k < n; k++)
    if (j >= m || i < m && a[i] < a[j])
      a[k] = i++;
    else
      a[k] = j++;

  for (i = 0; i < n; i++)
    a[i] = b[i];
}

void MergeSort( UINT64 *a, int n )
{
  b = malloc(sizeof(UINT64) * n);
  
  if (b == NULL)
    return;
  MergeSortRec(a, n);

  free(b);
}

void QuickSort( UINT64 *a, int n )
{
  int b = 0, e = n - 1;
  UINT64 x = a[n / 2];

  if (n < 2)
    return;

  while (b <= e)
  {
    while (a[b] < x)
      b++;
    while (a[e] > x)
      e--;
    if (b <= e)
    {
      if (b != e)
        Swap(&a[b], &a[e]);
      b++;
      e--;
    }
  }
  QuickSort(a, e + 1);
  QuickSort(a + b, n - b);
}

void HeapCorrection( UINT64 *a, int n, int i )
{
  int left, right, big;

  while(1)
  {
    left = i * 2 + 1;
    right = i * 2 + 2;
    big = i;

      if (left < n && a[i] < a[left])
      big = left;
    if (right < n && a[big] < a[right])
      big = right;
    if (big == i)
      return;

    Swap(&a[i], &a[big]);
    i = big;
  }
}

void HeapSort( UINT64 *a, int n )
{
  int i;

  for (i = n / 2 - 1; i >= 0; i--)
    HeapCorrection(a, n, i);

  for (i = n - 1; i >= 0; i--)
  {
    Swap(&a[0], &a[--n]);
    HeapCorrection(a, n, 0);
  }
}