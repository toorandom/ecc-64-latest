/*
 * Calculates the greatest common divisor
 * this is if
 * x = x1*x2*x3*..*xn
 * y = y1*y2*y3*..*ym
 * A = { x1*x2*x3*..*xn } INTERSECTION { y1*y2*y3*..*ym }
 * gcd = max (A)
 */


bint *
bint_gcd (bint * x, bint * y)
{
  bint *t;
  int xswap = 0, yswap = 0;
  t = bint_alloc (x->len + y->len, POSITIVE);
  bint_clean (t);
  bint_normalize (x);
  bint_normalize (y);
  if (x->sign == NEGATIVE)
    {
      xswap = 1;
      x->sign = POSITIVE;
    }
  if (y->sign == NEGATIVE)
    {
      yswap = 1;
      y->sign = POSITIVE;
    }

  /*
     bint_debug(x,"INIT x");
     bint_debug(y,"INIT y");
   */
  t = bint_mod (x, y, t);
  /*
     bint_debug(t,"x%y");
   */
  if (bint_is_zero (t))
    {
      /*
         bint_debug(t,"t is zero");
         bint_debug(y,"ret");
       */
      if (yswap)
        y->sign = POSITIVE;
      if (xswap)
        x->sign = POSITIVE;
      bint_free (t);
      return y;
    }
  bint_clean (x);
  /*
     bint_debug(t,"Coping t");
   */
  bint_copy (x, t);
  /*
     bint_debug(x,"To x");
     printf("Free t\n");
   */
  bint_free (t);
  /*
     printf("Ret gcd(y,t)\n");
     bint_debug(y,"\ty");
     bint_debug(t,"\tt");
   */
  return bint_gcd (y, x);

}
