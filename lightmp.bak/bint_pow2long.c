#include "lightmp.h"
/*
 * computes
 * x**y and saves the result in z
 * with y long type
 * z must have enought memory, generaly the memory needed is
 * z->len * y
 */

bint *
bint_pow2long (bint * x, _ulong y, bint * z)
{
  int i;
  bint *t = bint_alloc (4096, POSITIVE);
  t->len = 1;
  t->digits[0] = 1;
  t->sign = POSITIVE;
  if (y == 0)
    {
      z->digits[0] = 1;
      z->len = 1;
      return z;
    }
  for (i = 0; i < y; i++)
    {
      bint_mul (x, t, z);
      bint_copy (t, z);
      bint_clean (z);
    }
  bint_copy (z, t);
/*
  bint_free (t);
*/
  return z;
}
