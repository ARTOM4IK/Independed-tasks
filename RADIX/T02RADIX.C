/* Arsentev Artemy, 09-4, group 49, 20.09.2024 */

#include <stdio.h>
#include <conio.h>

void print_dig( int x )
{
  printf("%c", x < 10 ? '0' + x : 'A' + (x - 10));
}

void print_rad( unsigned long long x, int base )
{
  int y = x, size = 0, power_base = 1, i;

  while (y != 0)
  {
    y /= base;
    size++;
    power_base *= base;
  }

  for (i = size - 1; i >= 0; i--)
    print_dig(x / (power_base /= base) % base);
}

void main( void )
{
  unsigned long long x;
  int n;

  printf("X:");
  scanf("%i", &x);

  printf("Base:");
  scanf("%i", &n);
  
  print_rad(x, n);

  _getch();
}