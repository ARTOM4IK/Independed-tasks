#include <stdio.h>
#include <conio.h>

unsigned long long FibReq( int x )
{
  if (x < 2)
    return x;
  else
    return FibReq(x - 1) + FibReq(x - 2);
}


unsigned long long Fib( int x )
{
  int i, an, a_prelast, a_last;

  for (a_prelast = 0, a_last = 1, i = 2; i <= x; i++)
    an = a_last + a_prelast, a_prelast = a_last, a_last = an;
  return an;
}