/* Arsentev Artemy, 09-4, group 49, 25.09.2024 */

#include <stdio.h>
#include <conio.h>
unsigned long long print_rad( unsigned long long x, int base )
{
  int y = x, size = 0, power_base = 1, i, z = 0;

  while (y != 0)
  {
    y /= base;
    size++;
    power_base *= base;
  }

  for (i = size - 1; i >= 0; i--)
  {
    z += x / (power_base /= base) % base;
  }
  return z;
}

void main( void )
{
  unsigned long long x, y;
  int count = 0;

  do
  {
    printf("X:");
    scanf("%llu", &x);

    y = print_rad(x, 2);
    
    if (y % 2 == 0)
        count++;

  } while (x != 0);
  
  printf("%d", count - 1);
 
  _getch();
}