#include "lightmp.h"
/*
 * calculates
 * a=a-1
 * and fix the size if the carry flag modifies the size of the result
 */
bint *
bint_dec (bint * a)
{
  int i, cf = 0, t, j = 0;
  for (i = 0; i < a->len; i++)
    {
      t = (a->digits[i] - cf - (i > 0 ? 0 : 1));
      if (t < 0)
        {
          t = BASE - abs (t);
          cf = 1;
        }
      else
        cf = 0;
      a->digits[i] = t;
    }
  while (a->digits[a->len - 1 - j] == 0)
    j++;
  a->len = a->len - j;
  if (a->len < 1)
    {
      a->len = 1;
      a->digits[0] = 0;
    }
  bint_normalize (a);
  return a;
}
