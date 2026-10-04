/* Arsentev Artemy, 09-4, group 49, 30.09.2024 */

#include <stdio.h>
#include <conio.h>

#define MAX 239

void main( void )
{
  int a[MAX], x, i, n, j, k, carry;

  printf("n: ");
  scanf("%d", &n);

  for (k = 1, carry = 0; k <= n; k++)
  {
    for (a[0] = 1, i = 1; i < MAX; i++)
      {
        a[i] = 0;
      }

    for (j = 0; j < k; j++)
    {
      for (i = 0; i < MAX; i++)
      {
        x = a[i] * 2 + carry;
        carry = x / 10;
        a[i] = x % 10;
      }
    }

    for (i = MAX - 1; i > 0 && a[i] == 0; i--)
      ;

    printf("2 ^ %d = ", k);
    

    for (; i >= 0; i--)
    {
      printf("%d", a[i]);
    }
    printf("\n");
  }
  _getch();
}