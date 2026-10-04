/* Arsentev Artemy, 09-4, 25.09.2024 */

#include <stdio.h>
#include <conio.h>

void main( void )
{
    int x;

  printf("year: ");
  scanf("%d", &x);

  if (x % 4 == 0 && (x % 400 == 0 || x % 100 != 0))
    printf("%d is Bissextile", x);
  else
    printf("%d is not Bissextile", x);

  _getch();
}