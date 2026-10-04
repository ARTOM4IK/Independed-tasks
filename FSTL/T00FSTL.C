/* Arsentev Arytemy, 09-4, group 49, 18.09.2024 */

#include <stdio.h>
#include <conio.h>

void main( void )
{
  double x;

  printf("X:");
  scanf("%lf", &x);

  printf("[%lf] = %i\n{%lf} = %lf", x, (int)x, x, x - (int)x);

  _getch();
}