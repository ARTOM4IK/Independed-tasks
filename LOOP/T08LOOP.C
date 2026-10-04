/* Arsentev Artemy, 09-4, 25.09.2024 */

#include <stdio.h>
#include <conio.h>

void main( void )
{
  int n, i = 0, sum = 0;

  printf("n:");
  scanf("%d", &n);

  if (n >= 0)
    while (i <= n)
    {
      sum += i * i * i;
      i++;
    }
  else
  {
    while (i >= n)
    {
      sum += i * i * i;
      i--;
    }
  }

  printf("sum: %d", sum);

  _getch();
}