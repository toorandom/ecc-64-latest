#include "lightmp.h"

long
max (long a, long b)
{
  return (a + b + abs (a - b)) / 2;
}

long
min (long a, long b)
{
  return (a + b - abs (a - b)) / 2;
}


  bint_free (exp);
  bint_copy (n, nback);
  bint_free (nback);
  return e;
}

int
mod (int a, int m)
{
  int x;
  if (a < 0)
    {
      if (abs (a) < m)
	return (a + m) % m;
      else
	{
	  x = abs (a / m) + 1;
	  x = x * m;
	  x = x + a;
	  return x % m;
	}
    }
  return a % m;
}


