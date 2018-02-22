#include "lightmp.h"
int
bint_2_binary (bint * x, char *dst)
{
  bint *t1, *t2, *t3, *x2, *two ;
  char *dst2;
  int k = 0, i = 0;
  t1 = bint_alloc (x->len + 1, POSITIVE);
  t2 = bint_alloc (x->len + 1, POSITIVE);
  t3 = bint_alloc (x->len + 1, POSITIVE);
  x2 = bint_alloc (x->len + 1, POSITIVE);
  dst2 = calloc (4096, sizeof (char));
  two = bint_alloc (32, POSITIVE);
  two->digits[0] = 2;
  two->len = 1;
  bint_copy (x2, x);
  bint_clean (t2);
  bint_clean (t3);
  while (!bint_is_zero (x2))
    {
      bint_div (x2, two, t2, t3);
      dst2[k] = t3->digits[0];
      bint_clean (x2);
      bint_clean (t3);
      bint_copy (x2, t2);
      k++;
    }
  for (i = k-1; i >= 0; i--)
    dst[k - i-1] = dst2[i];
  bint_free (t1);
  bint_free (t2);
  bint_free (t3);
  bint_free (x2);
  bint_free (two);
  free (dst2);
  return k;
}
