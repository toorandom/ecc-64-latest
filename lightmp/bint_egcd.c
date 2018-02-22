#include "lightmp.h"
/*
 * Calculates x,y,gcd such that
 * ax+by = gcd(a,b)
 * gcd = gcd(a,b)
 * lx,ly,gcd must have enough memory to allocate the results
 */
bint *
bint_egcd (bint * a, bint * b, bint * lx, bint * ly, bint * gcd)
{
  bint *x, *y, *t, *q, *r, *m, *qx, *qy, *lx_qx, *ly_qy, *a_backup, *b_backup;
  a_backup = bint_alloc (a->len, a->sign);
  b_backup = bint_alloc (b->len, b->sign);
  bint_copy (a_backup, a);
  bint_copy (b_backup, b);
  x = bint_alloc (a->len + b->len, POSITIVE);
  y = bint_alloc (a->len + b->len, POSITIVE);
  t = bint_alloc (a->len + b->len, POSITIVE);
  q = bint_alloc (a->len + b->len, POSITIVE);
  r = bint_alloc (a->len + b->len, POSITIVE);
  m = bint_alloc (a->len + b->len, POSITIVE);
  qx = bint_alloc (a->len + b->len + 1, POSITIVE);
  qy = bint_alloc (a->len + b->len + 1, POSITIVE);
  ly_qy = bint_alloc (a->len + b->len + 1, POSITIVE);
  lx_qx = bint_alloc (a->len + b->len + 1, POSITIVE);
  lx->len = 1;
  ly->len = 1;
  lx->digits[0] = 1;
  ly->digits[0] = 0;
  x->len = 1;
  y->len = 1;
  x->digits[0] = 0;
  y->digits[0] = 1;
  while (!bint_is_zero (b))
    {
      bint_copy (t, b);
      q = bint_div (a, b, q, r);
      m = bint_mod (a, b, m);
      bint_copy (b, m);
      bint_copy (a, t);
      bint_copy (t, x);
      qx = bint_mul (q, x, qx);
      lx_qx = bint_sub (lx, qx, lx_qx);
      bint_copy (x, lx_qx);
      bint_copy (lx, t);
      bint_copy (t, y);
      qy = bint_mul (q, y, qy);
      ly_qy = bint_sub (ly, qy, ly_qy);
      bint_copy (y, ly_qy);
      bint_copy (ly, t);
    }
  bint_copy (b, b_backup);
  bint_copy (gcd, a);
  bint_copy (a, a_backup);
  bint_free (a_backup);
  bint_free (b_backup);
  bint_free (x);
  bint_free (y);
  bint_free (t);
  bint_free (q);
  bint_free (r);
  bint_free (m);
  bint_free (qx);
  bint_free (qy);
  bint_free (lx_qx);
  bint_free (ly_qy);
  return gcd;
}
