#include "lightmp.h"
/* Calculates q,r such that
 * qy+r = x
 * with r < y
 */
bint *
bint_div (bint * x, bint * y, bint * q, bint * r)
{
  int i;
  char xflag = 0, yflag = 0;
  bint *tmp_exp10, *tmp;
  bint *t1, *t2;
  bint_clean (q);
  /* if y is zero then division cannot be performed */
  if ((y->len == 1) && (y->digits[0] == 0))
    {
      fprintf (stderr, "Division by zero!\n");
      exit (EXIT_FAILURE);
    }
  /* if len of both is 1 , we do the calculus without entering the loop */
  if ((x->len == 1) && (y->len == 1))
    {
      if (y->digits[0] != 0)
        {
          q->len = 1;
          q->digits[0] = x->digits[0] / y->digits[0];
          r->len = 1;
          r->digits[0] = x->digits[0] % y->digits[0];
          return q;
        }
      else
        {
          fprintf (stderr, "Division by zero\n");
          exit (EXIT_FAILURE);
        }
    }
  /* We don't want conflicts with the substraction when the input is a negative
big integer
   * so we convert it to positive to handle it and flag it to return the origina
l sign of the pointers
   */
  if (x->sign == NEGATIVE)
    {
      xflag = 1;
      x->sign = POSITIVE;
    }
  if (y->sign == NEGATIVE)
    {
      yflag = 1;
      y->sign = POSITIVE;
    }
  /* Clean , alloc and all stuff we will need */
  tmp_exp10 = bint_alloc (y->len + 1, POSITIVE);
  tmp = bint_alloc (y->len + x->len + 1, POSITIVE);
  bint_clean (q);
  bint_clean (r);
  bint_clean (tmp_exp10);
  bint_clean (tmp);
  bint_normalize (q);
  bint_normalize (tmp_exp10);
  q->len = x->len - 1;
  t1 = tmp_exp10;
  t2 = tmp;
/* We proceed doing substractions of x with the residues generated multiplied by
 10^i  */
  for (i = x->len - 1; i >= 0; i--)
    {
      bint_shift_right_digit (tmp_exp10, 1);
      tmp_exp10->digits[0] = x->digits[i];
      q->digits[i] = 0;
      while (bint_cmp (tmp_exp10, y) != SECOND_GREATER)
        {
          q->digits[i]++;
          bint_sub (tmp_exp10, y, tmp);
          bint_clean (tmp_exp10);
          bint_copy (tmp_exp10, tmp);
        }
    }
  /* fit the zeroes and set the len of the quotient */
  bint_normalize (q);
  q->len = x->len - 1 - (y->len - 1) + 1;

  /* Clean the values of tmp and r we are going to use now */
  bint_clean (tmp);
  bint_clean (r);

/* compute r in linear time
 *  yq+r=x
 *  r=x-yq
 *    q
 *   _____
 *  y|x
 *    r
 *
 *    x-qy=r
 */
  tmp = bint_mul (y, q, tmp);
  r = bint_sub (x, tmp, r);

  /* fix the zeroes */
  bint_normalize (q);
  bint_normalize (r);

/* Return back the signs if they were negative */
  if (yflag)
    y->sign = NEGATIVE;
  if (xflag)
    x->sign = NEGATIVE;
/* Set the sign of the quotient */
  q->sign = (y->sign != x->sign) ? NEGATIVE : POSITIVE;

/* Free the temporary memory */
  bint_free (t1);
  bint_free (t2);

  return q;
}
