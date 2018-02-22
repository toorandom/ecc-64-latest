#include "lightmp.h"
/*
 * Computes
 * c = a*b
 * c must have at least a->len+b->len+1 memory allocated
 */
bint *
bint_mul (bint * a, bint * b, bint * c)
{
  int i, j, t, digit, cf = 0;
  bint_clean (c);
  if (bint_is_zero (a) || bint_is_zero (b))
    {
      c->len = 1;
      c->digits[0] = 0;
      return c;
    }
  for (i = 0; i < a->len; i++)
    for (j = 0; j < b->len; j++)
      {
        t = c->digits[i + j] + a->digits[i] * b->digits[j] + (j < 1 ? 0 : cf);
        cf = t / BASE;
        digit = t % BASE;
        c->digits[i + j] = digit;
        c->digits[i + b->len] = (j > b->len - 2) ? cf : 0;
      }
  c->len = a->len + b->len + 1;
  c->sign = (a->sign == b->sign) ? POSITIVE : NEGATIVE;
  bint_normalize (c);
  return c;
}

