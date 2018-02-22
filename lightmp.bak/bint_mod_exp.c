#include "lightmp.h"
/*
 * This calculates  e
 * such that
 * a**n = e mod m
 */
bint *
bint_mod_exp (bint * a, bint * n, bint * m, bint * e)
{
  bint *x, *two, *q, *r, *tmp, *exp, *nback;
  tmp = bint_alloc (a->len * n->len * m->len, POSITIVE);
  x = bint_alloc (m->len * a->len * n->len, POSITIVE);
  r = bint_alloc (m->len * a->len * n->len, POSITIVE);
  q = bint_alloc ((m->len * a->len * n->len), POSITIVE);
  nback = bint_alloc ((m->len * a->len * n->len), POSITIVE);
  exp = bint_alloc (n->len * a->len * m->len, POSITIVE);
  exp->len = 1;
  exp->digits[0] = 1;
  two = bint_alloc (32, POSITIVE);
  two->len = 1;
  two->digits[0] = 2;
  x = bint_mod (a, m, x);
  bint_normalize (x);
  bint_copy (nback, n);
  while (!bint_is_zero (n))
    {
      if (!bint_is_even (n))
        {
          tmp = bint_mul (exp, x, tmp);
          bint_clean (exp);
          bint_copy (exp, tmp);
          bint_clean (tmp);
          tmp = bint_mod (exp, m, tmp);
          bint_clean (exp);
          bint_normalize (tmp);
          bint_copy (exp, tmp);
          bint_normalize (exp);
          bint_clean (tmp);
        }
      tmp = bint_mul (x, x, tmp);
      bint_clean (x);
      bint_normalize (tmp);
      bint_copy (x, tmp);
      bint_clean (tmp);
      tmp = bint_mod (x, m, tmp);
      bint_clean (x);
      bint_normalize (tmp);
      bint_copy (x, tmp);
      bint_clean (tmp);
      q = bint_div (n, two, q, r);
      bint_normalize (q);
      bint_clean (n);
      bint_copy (n, q);
    }
  bint_free (tmp);
  bint_free (r);
  bint_free (q);
  bint_free (x);
  bint_free (two);
  bint_clean (e);
  bint_normalize (exp);
  bint_copy (e, exp);[B[B[B[B[B[B[B[B
  bint_free (exp);
  bint_copy (n, nback);
  bint_free (nback);
  return e;
}
