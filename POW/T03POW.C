/* Arsentev Artemy, 09-4, 23.09.2024 */

#include <stdio.h>
#include <conio.h>

double power(double x, int n )
{
  int i, c = 1;

  for (i = 0; i < n; i++)
    c *= x;

  return c;
}


double power1(double x, int n )
{
  if (n == 0)
    return 1;
  if (n % 2 == 0)
  {
    double k = power(x, n / 2);
    return k * k;
  }
  else
  {
    double k = power(x, n / 2);
    return k * k * x;
  }
}

void main( void )
{
  double a;
  int b;

  printf("X:");
  scanf("%lf", &a);
  printf("N:");
  scanf("%i", &b);

  printf("%f^%i = %f", a, b, power1(a, b));
  
  _getch();
}