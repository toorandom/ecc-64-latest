#include "lightmp.h"

_ulong
max (_ulong a, _ulong b)
{
  return (_ulong)a > (_ulong)b ? a : b ;
}

_ulong
min (_ulong a, _ulong b)
{
  return (a + b - abs (a - b)) / 2;
}


_ulong
mod (_long a, _ulong m)
{
  _long x;
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


