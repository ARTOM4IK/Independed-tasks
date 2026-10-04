/* Arsentev Artemy, 09-4, 25.09.2024 */

#include <stdio.h>
#include <conio.h>

void main( void )
{
  int x;

  printf("x:");
  scanf("%d", &x);

  if (x % 2 == 0)
    printf("%d is Even", x);
  else
    printf("%d is Odd", x);

  _getch();
}