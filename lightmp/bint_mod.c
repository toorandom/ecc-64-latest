#include "lightmp.h"
/* Calculates r such that  x = r mod y */
bint *
bint_mod (bint * x, bint * y, bint * r)
{
  bint *qtemp, *t1, *t2;
  bint_clean (r);
  if (x->sign == NEGATIVE)
    {
      x->sign = POSITIVE;
      if (bint_cmp (x, y) != FIRST_GREATER)
        {
          x->sign = NEGATIVE;
          t1 = bint_alloc (x->len + y->len, POSITIVE);
          bint_clean (t1);
          t1 = bint_add (x, y, t1);
          t2 = bint_alloc (x->len + y->len, POSITIVE);
          bint_clean (t2);
          t2 = bint_div (t1, y, t2, r);
          bint_free (t2);
          bint_free (t1);
          bint_normalize (r);
          return r;
        }
      else
        {
          t1 = bint_alloc (x->len + y->len, POSITIVE);
          t2 = bint_alloc (x->len + y->len, POSITIVE);
          bint_clean (t1);
          x->sign = POSITIVE;
          t1 = bint_div (x, y, t1, t2);
          bint_inc (t1);
          bint_clean (t2);
          t2 = bint_mul (t1, y, t2);
          bint_clean (t1);
          x->sign = NEGATIVE;
          t1 = bint_add (t2, x, t1);
          bint_clean (t2);
          qtemp = bint_alloc (x->len + y->len, POSITIVE);
          bint_clean (qtemp);
          t2 = bint_div (t1, y, qtemp, r);
          bint_free (qtemp);
         /* bint_free (t2); */
          bint_free (t1);
          bint_normalize (r);
          return r;
        }
    }
  qtemp = bint_alloc (x->len + y->len + 1, POSITIVE);
  bint_clean (r);
  bint_div (x, y, qtemp, r);
  bint_normalize (r);
  bint_free (qtemp);
  return r;
}

