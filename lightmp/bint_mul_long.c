#include "lightmp.h"
/*
 * Calculates
 * x*y and saves result in z
 * note that y is a long type
 * z must have memory
 */
bint *
bint_mul_long (bint * x, _ulong y, bint * z)
{
  unsigned char tmp[24];
  int i;
  bint *t;
  snprintf ((char *) &tmp, sizeof (tmp), "%ld", y);
  t = bint_alloc (strlen ((char *) &tmp) + 1, POSITIVE);
  t->len = strlen ((char *) &tmp);
  for (i = t->len - 1; i >= 0; i--)
    t->digits[t->len - 1 - i] = tmp[i] - '0';

  bint_normalize (t);
  z = bint_mul (x, t, z);
  if (y > 2)
    z->len++;
  bint_normalize (z);
  bint_free (t);
  return z;
}

