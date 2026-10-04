/* Arsentev Artemy, 09-4, group 49, 27.09.2024 */

#include <stdio.h>
#include <conio.h>
#include "FIB.H"

void main( void )
{
  int n;

  printf("X:");
  scanf("%i", &n);

  printf("%llu\n%llu", FibReq(n), Fib(n));

  _getch();
}